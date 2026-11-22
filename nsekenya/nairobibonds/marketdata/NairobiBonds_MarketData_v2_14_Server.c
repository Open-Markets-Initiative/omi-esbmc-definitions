// nsekenya/nairobibonds/marketdata/NairobiBonds_MarketData_v2_14_Server.c
/*
 * Nairobi Securities Exchange Nairobi Bonds Market Data
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
 *   - a run counted by a field
 *   - a Reassemble rule
 *   - a field filling what is left of what holds it
 *   - a run filling a byte budget a field states
 *   - the dispatch that chooses a message by its type
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

/* ---- Transport Header: 4 bytes ----------------------------------------------- */

/* Table 1: Transport Header */
typedef struct {
  uint8_t start_byte;         /* byte 0 */
  uint8_t message_length[2];  /* bytes 1 to 2 */
  uint8_t length_check;       /* byte 3 */
} TransportHeader;

/* any Transport Header at all: every byte one the checker chooses */
static void any_transport_header(TransportHeader *record) {
  record->start_byte = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->length_check = arbitrary();
}

/* Transport Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_transport_header(const TransportHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->start_byte;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->length_check;

  return at;
}

/* Transport Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_transport_header(TransportHeader *record, const uint8_t *wire, size_t at) {
  record->start_byte = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->length_check = wire[at++];

  return at;
}

/* what was read of Transport Header is what was written, byte for byte */
static void equal_transport_header(const TransportHeader *read, const TransportHeader *written) {
  assert(read->start_byte == written->start_byte);
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->length_check == written->length_check);
}

/* Transport Header: written and read back, then read and written back */
static void check_transport_header(void) {
  TransportHeader sent;
  TransportHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_transport_header(&sent);
  assert(encode_transport_header(&sent, wire, 0) == 4);
  assert(decode_transport_header(&got, wire, 0) == 4);
  equal_transport_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_transport_header(&got, wire, 0) == 4);
  assert(encode_transport_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- User Name: 16 bytes ----------------------------------------------------- */

/* User name as assigned by the exchange */
typedef struct {
  uint8_t user_name_length_byte;     /* byte 0 */
  uint8_t user_name_characters[15];  /* bytes 1 to 15 */
} UserName;

/* any User Name at all: every byte one the checker chooses */
static void any_user_name(UserName *record) {
  record->user_name_length_byte = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->user_name_characters[i] = arbitrary(); }
}

/* User Name to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_user_name(const UserName *record, uint8_t *wire, size_t at) {
  wire[at++] = record->user_name_length_byte;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->user_name_characters[i]; }

  return at;
}

/* User Name off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_user_name(UserName *record, const uint8_t *wire, size_t at) {
  record->user_name_length_byte = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->user_name_characters[i] = wire[at++]; }

  return at;
}

/* what was read of User Name is what was written, byte for byte */
static void equal_user_name(const UserName *read, const UserName *written) {
  assert(read->user_name_length_byte == written->user_name_length_byte);
  for (size_t i = 0; i < 15; i++) { assert(read->user_name_characters[i] == written->user_name_characters[i]); }
}

/* User Name: written and read back, then read and written back */
static void check_user_name(void) {
  UserName sent;
  UserName got;
  uint8_t wire[16];
  uint8_t again[16];

  any_user_name(&sent);
  assert(encode_user_name(&sent, wire, 0) == 16);
  assert(decode_user_name(&got, wire, 0) == 16);
  equal_user_name(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_user_name(&got, wire, 0) == 16);
  assert(encode_user_name(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Time: 4 bytes ----------------------------------------------------------- */

/* Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} Time;

/* any Time at all: every byte one the checker chooses */
static void any_time(Time *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_time(const Time *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_time(Time *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Time is what was written, byte for byte */
static void equal_time(const Time *read, const Time *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Time: written and read back, then read and written back */
static void check_time(void) {
  Time sent;
  Time got;
  uint8_t wire[4];
  uint8_t again[4];

  any_time(&sent);
  assert(encode_time(&sent, wire, 0) == 4);
  assert(decode_time(&got, wire, 0) == 4);
  equal_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_time(&got, wire, 0) == 4);
  assert(encode_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Server Message Header: 29 bytes ----------------------------------------- */

/* Table 2: Message Header */
typedef struct {
  uint8_t sequence_number[4];   /* bytes 0 to 3 */
  UserName user_name;           /* bytes 4 to 19 */
  uint8_t user_number[4];       /* bytes 20 to 23 */
  Time time;                    /* bytes 24 to 27 */
  uint8_t server_message_type;  /* byte 28 */
} ServerMessageHeader;

/* any Server Message Header at all: every byte one the checker chooses */
static void any_server_message_header(ServerMessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  any_user_name(&record->user_name);
  for (size_t i = 0; i < 4; i++) { record->user_number[i] = arbitrary(); }
  any_time(&record->time);
  record->server_message_type = arbitrary();
}

/* Server Message Header to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_server_message_header(const ServerMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  at = encode_user_name(&record->user_name, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_number[i]; }
  at = encode_time(&record->time, wire, at);
  wire[at++] = record->server_message_type;

  return at;
}

/* Server Message Header off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_server_message_header(ServerMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  at = decode_user_name(&record->user_name, wire, at);
  for (size_t i = 0; i < 4; i++) { record->user_number[i] = wire[at++]; }
  at = decode_time(&record->time, wire, at);
  record->server_message_type = wire[at++];

  return at;
}

/* what was read of Server Message Header is what was written, byte for byte */
static void equal_server_message_header(const ServerMessageHeader *read, const ServerMessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  equal_user_name(&read->user_name, &written->user_name);
  for (size_t i = 0; i < 4; i++) { assert(read->user_number[i] == written->user_number[i]); }
  equal_time(&read->time, &written->time);
  assert(read->server_message_type == written->server_message_type);
}

/* Server Message Header: written and read back, then read and written back */
static void check_server_message_header(void) {
  ServerMessageHeader sent;
  ServerMessageHeader got;
  uint8_t wire[29];
  uint8_t again[29];

  any_server_message_header(&sent);
  assert(encode_server_message_header(&sent, wire, 0) == 29);
  assert(decode_server_message_header(&got, wire, 0) == 29);
  equal_server_message_header(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_server_message_header(&got, wire, 0) == 29);
  assert(encode_server_message_header(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Today Date: 12 bytes ---------------------------------------------------- */

/* Today date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} TodayDate;

/* any Today Date at all: every byte one the checker chooses */
static void any_today_date(TodayDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Today Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_today_date(const TodayDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Today Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_today_date(TodayDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Today Date is what was written, byte for byte */
static void equal_today_date(const TodayDate *read, const TodayDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Today Date: written and read back, then read and written back */
static void check_today_date(void) {
  TodayDate sent;
  TodayDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_today_date(&sent);
  assert(encode_today_date(&sent, wire, 0) == 12);
  assert(decode_today_date(&got, wire, 0) == 12);
  equal_today_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_today_date(&got, wire, 0) == 12);
  assert(encode_today_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Country Code: 4 bytes --------------------------------------------------- */

/* Indicates the exchanges country code. */
typedef struct {
  uint8_t country_code_length_byte;    /* byte 0 */
  uint8_t country_code_characters[3];  /* bytes 1 to 3 */
} CountryCode;

/* any Country Code at all: every byte one the checker chooses */
static void any_country_code(CountryCode *record) {
  record->country_code_length_byte = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->country_code_characters[i] = arbitrary(); }
}

/* Country Code to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_country_code(const CountryCode *record, uint8_t *wire, size_t at) {
  wire[at++] = record->country_code_length_byte;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->country_code_characters[i]; }

  return at;
}

/* Country Code off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_country_code(CountryCode *record, const uint8_t *wire, size_t at) {
  record->country_code_length_byte = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->country_code_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Country Code is what was written, byte for byte */
static void equal_country_code(const CountryCode *read, const CountryCode *written) {
  assert(read->country_code_length_byte == written->country_code_length_byte);
  for (size_t i = 0; i < 3; i++) { assert(read->country_code_characters[i] == written->country_code_characters[i]); }
}

/* Country Code: written and read back, then read and written back */
static void check_country_code(void) {
  CountryCode sent;
  CountryCode got;
  uint8_t wire[4];
  uint8_t again[4];

  any_country_code(&sent);
  assert(encode_country_code(&sent, wire, 0) == 4);
  assert(decode_country_code(&got, wire, 0) == 4);
  equal_country_code(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_country_code(&got, wire, 0) == 4);
  assert(encode_country_code(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Previous Business Day: 12 bytes ----------------------------------------- */

/* Previous Business Day */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} PreviousBusinessDay;

/* any Previous Business Day at all: every byte one the checker chooses */
static void any_previous_business_day(PreviousBusinessDay *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Previous Business Day to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_previous_business_day(const PreviousBusinessDay *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Previous Business Day off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_previous_business_day(PreviousBusinessDay *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Previous Business Day is what was written, byte for byte */
static void equal_previous_business_day(const PreviousBusinessDay *read, const PreviousBusinessDay *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Previous Business Day: written and read back, then read and written back */
static void check_previous_business_day(void) {
  PreviousBusinessDay sent;
  PreviousBusinessDay got;
  uint8_t wire[12];
  uint8_t again[12];

  any_previous_business_day(&sent);
  assert(encode_previous_business_day(&sent, wire, 0) == 12);
  assert(decode_previous_business_day(&got, wire, 0) == 12);
  equal_previous_business_day(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_previous_business_day(&got, wire, 0) == 12);
  assert(encode_previous_business_day(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Text P 50: 50 bytes ----------------------------------------------------- */

/* Indicates further detail on logon failures and success. */
typedef struct {
  uint8_t text_p_50_length_byte;     /* byte 0 */
  uint8_t text_p_50_characters[49];  /* bytes 1 to 49 */
} TextP50;

/* any Text P 50 at all: every byte one the checker chooses */
static void any_text_p50(TextP50 *record) {
  record->text_p_50_length_byte = arbitrary();
  for (size_t i = 0; i < 49; i++) { record->text_p_50_characters[i] = arbitrary(); }
}

/* Text P 50 to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_text_p50(const TextP50 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->text_p_50_length_byte;
  for (size_t i = 0; i < 49; i++) { wire[at++] = record->text_p_50_characters[i]; }

  return at;
}

/* Text P 50 off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_text_p50(TextP50 *record, const uint8_t *wire, size_t at) {
  record->text_p_50_length_byte = wire[at++];
  for (size_t i = 0; i < 49; i++) { record->text_p_50_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Text P 50 is what was written, byte for byte */
static void equal_text_p50(const TextP50 *read, const TextP50 *written) {
  assert(read->text_p_50_length_byte == written->text_p_50_length_byte);
  for (size_t i = 0; i < 49; i++) { assert(read->text_p_50_characters[i] == written->text_p_50_characters[i]); }
}

/* Text P 50: written and read back, then read and written back */
static void check_text_p50(void) {
  TextP50 sent;
  TextP50 got;
  uint8_t wire[50];
  uint8_t again[50];

  any_text_p50(&sent);
  assert(encode_text_p50(&sent, wire, 0) == 50);
  assert(decode_text_p50(&got, wire, 0) == 50);
  equal_text_p50(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_text_p50(&got, wire, 0) == 50);
  assert(encode_text_p50(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Code P 6: 6 bytes ------------------------------------------------ */

/* Member code of affiliated member. */
typedef struct {
  uint8_t member_code_p_6_length_byte;    /* byte 0 */
  uint8_t member_code_p_6_characters[5];  /* bytes 1 to 5 */
} MemberCodeP6;

/* any Member Code P 6 at all: every byte one the checker chooses */
static void any_member_code_p6(MemberCodeP6 *record) {
  record->member_code_p_6_length_byte = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->member_code_p_6_characters[i] = arbitrary(); }
}

/* Member Code P 6 to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_member_code_p6(const MemberCodeP6 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->member_code_p_6_length_byte;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->member_code_p_6_characters[i]; }

  return at;
}

/* Member Code P 6 off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_member_code_p6(MemberCodeP6 *record, const uint8_t *wire, size_t at) {
  record->member_code_p_6_length_byte = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->member_code_p_6_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Member Code P 6 is what was written, byte for byte */
static void equal_member_code_p6(const MemberCodeP6 *read, const MemberCodeP6 *written) {
  assert(read->member_code_p_6_length_byte == written->member_code_p_6_length_byte);
  for (size_t i = 0; i < 5; i++) { assert(read->member_code_p_6_characters[i] == written->member_code_p_6_characters[i]); }
}

/* Member Code P 6: written and read back, then read and written back */
static void check_member_code_p6(void) {
  MemberCodeP6 sent;
  MemberCodeP6 got;
  uint8_t wire[6];
  uint8_t again[6];

  any_member_code_p6(&sent);
  assert(encode_member_code_p6(&sent, wire, 0) == 6);
  assert(decode_member_code_p6(&got, wire, 0) == 6);
  equal_member_code_p6(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_member_code_p6(&got, wire, 0) == 6);
  assert(encode_member_code_p6(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Session Key Challenge Message: 243 bytes -------------------------------- */

/* Returned to a user when a successful TCP socket connection is established to the system. */
typedef struct {
  uint8_t challenge[243];  /* bytes 0 to 242 */
} SessionKeyChallengeMessage;

/* any Session Key Challenge Message at all: every byte one the checker chooses */
static void any_session_key_challenge_message(SessionKeyChallengeMessage *record) {
  for (size_t i = 0; i < 243; i++) { record->challenge[i] = arbitrary(); }
}

/* Session Key Challenge Message to the wire: 243 bytes from at, returning where the next byte goes */
static size_t encode_session_key_challenge_message(const SessionKeyChallengeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 243; i++) { wire[at++] = record->challenge[i]; }

  return at;
}

/* Session Key Challenge Message off the wire: 243 bytes from at, returning where the next byte lies */
static size_t decode_session_key_challenge_message(SessionKeyChallengeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 243; i++) { record->challenge[i] = wire[at++]; }

  return at;
}

/* what was read of Session Key Challenge Message is what was written, byte for byte */
static void equal_session_key_challenge_message(const SessionKeyChallengeMessage *read, const SessionKeyChallengeMessage *written) {
  for (size_t i = 0; i < 243; i++) { assert(read->challenge[i] == written->challenge[i]); }
}

/* Session Key Challenge Message: written and read back, then read and written back */
static void check_session_key_challenge_message(void) {
  SessionKeyChallengeMessage sent;
  SessionKeyChallengeMessage got;
  uint8_t wire[243];
  uint8_t again[243];

  any_session_key_challenge_message(&sent);
  assert(encode_session_key_challenge_message(&sent, wire, 0) == 243);
  assert(decode_session_key_challenge_message(&got, wire, 0) == 243);
  equal_session_key_challenge_message(&got, &sent);

  for (size_t i = 0; i < 243; i++) { wire[i] = arbitrary(); }
  assert(decode_session_key_challenge_message(&got, wire, 0) == 243);
  assert(encode_session_key_challenge_message(&got, again, 0) == 243);
  for (size_t i = 0; i < 243; i++) { assert(again[i] == wire[i]); }
}

/* ---- Download Date: 12 bytes ------------------------------------------------- */

/* Download Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} DownloadDate;

/* any Download Date at all: every byte one the checker chooses */
static void any_download_date(DownloadDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Download Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_download_date(const DownloadDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Download Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_download_date(DownloadDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Download Date is what was written, byte for byte */
static void equal_download_date(const DownloadDate *read, const DownloadDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Download Date: written and read back, then read and written back */
static void check_download_date(void) {
  DownloadDate sent;
  DownloadDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_download_date(&sent);
  assert(encode_download_date(&sent, wire, 0) == 12);
  assert(decode_download_date(&got, wire, 0) == 12);
  equal_download_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_download_date(&got, wire, 0) == 12);
  assert(encode_download_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Date: 12 bytes ---------------------------------------------------------- */

/* Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} Date;

/* any Date at all: every byte one the checker chooses */
static void any_date(Date *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_date(const Date *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_date(Date *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Date is what was written, byte for byte */
static void equal_date(const Date *read, const Date *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Date: written and read back, then read and written back */
static void check_date(void) {
  Date sent;
  Date got;
  uint8_t wire[12];
  uint8_t again[12];

  any_date(&sent);
  assert(encode_date(&sent, wire, 0) == 12);
  assert(decode_date(&got, wire, 0) == 12);
  equal_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_date(&got, wire, 0) == 12);
  assert(encode_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Name P 5: 5 bytes -------------------------------------------- */

/* Defines the instrument which represents this contract. */
typedef struct {
  uint8_t instrument_name_p_5_length_byte;    /* byte 0 */
  uint8_t instrument_name_p_5_characters[4];  /* bytes 1 to 4 */
} InstrumentNameP5;

/* any Instrument Name P 5 at all: every byte one the checker chooses */
static void any_instrument_name_p5(InstrumentNameP5 *record) {
  record->instrument_name_p_5_length_byte = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instrument_name_p_5_characters[i] = arbitrary(); }
}

/* Instrument Name P 5 to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_instrument_name_p5(const InstrumentNameP5 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->instrument_name_p_5_length_byte;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_name_p_5_characters[i]; }

  return at;
}

/* Instrument Name P 5 off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_instrument_name_p5(InstrumentNameP5 *record, const uint8_t *wire, size_t at) {
  record->instrument_name_p_5_length_byte = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instrument_name_p_5_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Name P 5 is what was written, byte for byte */
static void equal_instrument_name_p5(const InstrumentNameP5 *read, const InstrumentNameP5 *written) {
  assert(read->instrument_name_p_5_length_byte == written->instrument_name_p_5_length_byte);
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_name_p_5_characters[i] == written->instrument_name_p_5_characters[i]); }
}

/* Instrument Name P 5: written and read back, then read and written back */
static void check_instrument_name_p5(void) {
  InstrumentNameP5 sent;
  InstrumentNameP5 got;
  uint8_t wire[5];
  uint8_t again[5];

  any_instrument_name_p5(&sent);
  assert(encode_instrument_name_p5(&sent, wire, 0) == 5);
  assert(decode_instrument_name_p5(&got, wire, 0) == 5);
  equal_instrument_name_p5(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_name_p5(&got, wire, 0) == 5);
  assert(encode_instrument_name_p5(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Secondary Date: 12 bytes ------------------------------------------------ */

/* Secondary Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} SecondaryDate;

/* any Secondary Date at all: every byte one the checker chooses */
static void any_secondary_date(SecondaryDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Secondary Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_secondary_date(const SecondaryDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Secondary Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_secondary_date(SecondaryDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Secondary Date is what was written, byte for byte */
static void equal_secondary_date(const SecondaryDate *read, const SecondaryDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Secondary Date: written and read back, then read and written back */
static void check_secondary_date(void) {
  SecondaryDate sent;
  SecondaryDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_secondary_date(&sent);
  assert(encode_secondary_date(&sent, wire, 0) == 12);
  assert(decode_secondary_date(&got, wire, 0) == 12);
  equal_secondary_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_secondary_date(&got, wire, 0) == 12);
  assert(encode_secondary_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Secondary Instrument Name P 5: 5 bytes ---------------------------------- */

/* For strategy type products such as Product spreads, represents the instrument name of the second leg of the contract. */
typedef struct {
  uint8_t secondary_instrument_name_p_5_length_byte;    /* byte 0 */
  uint8_t secondary_instrument_name_p_5_characters[4];  /* bytes 1 to 4 */
} SecondaryInstrumentNameP5;

/* any Secondary Instrument Name P 5 at all: every byte one the checker chooses */
static void any_secondary_instrument_name_p5(SecondaryInstrumentNameP5 *record) {
  record->secondary_instrument_name_p_5_length_byte = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->secondary_instrument_name_p_5_characters[i] = arbitrary(); }
}

/* Secondary Instrument Name P 5 to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_secondary_instrument_name_p5(const SecondaryInstrumentNameP5 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->secondary_instrument_name_p_5_length_byte;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_instrument_name_p_5_characters[i]; }

  return at;
}

/* Secondary Instrument Name P 5 off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_secondary_instrument_name_p5(SecondaryInstrumentNameP5 *record, const uint8_t *wire, size_t at) {
  record->secondary_instrument_name_p_5_length_byte = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->secondary_instrument_name_p_5_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Secondary Instrument Name P 5 is what was written, byte for byte */
static void equal_secondary_instrument_name_p5(const SecondaryInstrumentNameP5 *read, const SecondaryInstrumentNameP5 *written) {
  assert(read->secondary_instrument_name_p_5_length_byte == written->secondary_instrument_name_p_5_length_byte);
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_instrument_name_p_5_characters[i] == written->secondary_instrument_name_p_5_characters[i]); }
}

/* Secondary Instrument Name P 5: written and read back, then read and written back */
static void check_secondary_instrument_name_p5(void) {
  SecondaryInstrumentNameP5 sent;
  SecondaryInstrumentNameP5 got;
  uint8_t wire[5];
  uint8_t again[5];

  any_secondary_instrument_name_p5(&sent);
  assert(encode_secondary_instrument_name_p5(&sent, wire, 0) == 5);
  assert(decode_secondary_instrument_name_p5(&got, wire, 0) == 5);
  equal_secondary_instrument_name_p5(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_secondary_instrument_name_p5(&got, wire, 0) == 5);
  assert(encode_secondary_instrument_name_p5(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contract: 48 bytes ------------------------------------------------------ */

/* Contract */
typedef struct {
  uint8_t identifier_prefix_i_4[4];                         /* bytes 0 to 3 */
  Date date;                                                /* bytes 4 to 15 */
  InstrumentNameP5 instrument_name_p_5;                     /* bytes 16 to 20 */
  uint8_t strike[8];                                        /* bytes 21 to 28 */
  uint8_t call_put_c_1;                                     /* byte 29 */
  SecondaryDate secondary_date;                             /* bytes 30 to 41 */
  SecondaryInstrumentNameP5 secondary_instrument_name_p_5;  /* bytes 42 to 46 */
  uint8_t is_delta_option;                                  /* byte 47 */
} Contract;

/* any Contract at all: every byte one the checker chooses */
static void any_contract(Contract *record) {
  for (size_t i = 0; i < 4; i++) { record->identifier_prefix_i_4[i] = arbitrary(); }
  any_date(&record->date);
  any_instrument_name_p5(&record->instrument_name_p_5);
  for (size_t i = 0; i < 8; i++) { record->strike[i] = arbitrary(); }
  record->call_put_c_1 = arbitrary();
  any_secondary_date(&record->secondary_date);
  any_secondary_instrument_name_p5(&record->secondary_instrument_name_p_5);
  record->is_delta_option = arbitrary();
}

/* Contract to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_contract(const Contract *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->identifier_prefix_i_4[i]; }
  at = encode_date(&record->date, wire, at);
  at = encode_instrument_name_p5(&record->instrument_name_p_5, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike[i]; }
  wire[at++] = record->call_put_c_1;
  at = encode_secondary_date(&record->secondary_date, wire, at);
  at = encode_secondary_instrument_name_p5(&record->secondary_instrument_name_p_5, wire, at);
  wire[at++] = record->is_delta_option;

  return at;
}

/* Contract off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_contract(Contract *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->identifier_prefix_i_4[i] = wire[at++]; }
  at = decode_date(&record->date, wire, at);
  at = decode_instrument_name_p5(&record->instrument_name_p_5, wire, at);
  for (size_t i = 0; i < 8; i++) { record->strike[i] = wire[at++]; }
  record->call_put_c_1 = wire[at++];
  at = decode_secondary_date(&record->secondary_date, wire, at);
  at = decode_secondary_instrument_name_p5(&record->secondary_instrument_name_p_5, wire, at);
  record->is_delta_option = wire[at++];

  return at;
}

/* what was read of Contract is what was written, byte for byte */
static void equal_contract(const Contract *read, const Contract *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->identifier_prefix_i_4[i] == written->identifier_prefix_i_4[i]); }
  equal_date(&read->date, &written->date);
  equal_instrument_name_p5(&read->instrument_name_p_5, &written->instrument_name_p_5);
  for (size_t i = 0; i < 8; i++) { assert(read->strike[i] == written->strike[i]); }
  assert(read->call_put_c_1 == written->call_put_c_1);
  equal_secondary_date(&read->secondary_date, &written->secondary_date);
  equal_secondary_instrument_name_p5(&read->secondary_instrument_name_p_5, &written->secondary_instrument_name_p_5);
  assert(read->is_delta_option == written->is_delta_option);
}

/* Contract: written and read back, then read and written back */
static void check_contract(void) {
  Contract sent;
  Contract got;
  uint8_t wire[48];
  uint8_t again[48];

  any_contract(&sent);
  assert(encode_contract(&sent, wire, 0) == 48);
  assert(decode_contract(&got, wire, 0) == 48);
  equal_contract(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_contract(&got, wire, 0) == 48);
  assert(encode_contract(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Display Data: 80 bytes ------------------------------------------- */

/* Market Display Data */
typedef struct {
  uint8_t display_sequence[4];            /* bytes 0 to 3 */
  Contract contract;                      /* bytes 4 to 51 */
  uint8_t open_price[8];                  /* bytes 52 to 59 */
  uint8_t instrument_sequence[4];         /* bytes 60 to 63 */
  uint8_t date_sequence[4];               /* bytes 64 to 67 */
  uint8_t strike_sequence[4];             /* bytes 68 to 71 */
  uint8_t second_instrument_sequence[4];  /* bytes 72 to 75 */
  uint8_t second_date_sequence[4];        /* bytes 76 to 79 */
} MarketDisplayData;

/* any Market Display Data at all: every byte one the checker chooses */
static void any_market_display_data(MarketDisplayData *record) {
  for (size_t i = 0; i < 4; i++) { record->display_sequence[i] = arbitrary(); }
  any_contract(&record->contract);
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->date_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->second_instrument_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->second_date_sequence[i] = arbitrary(); }
}

/* Market Display Data to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_market_display_data(const MarketDisplayData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_sequence[i]; }
  at = encode_contract(&record->contract, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second_instrument_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second_date_sequence[i]; }

  return at;
}

/* Market Display Data off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_market_display_data(MarketDisplayData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->display_sequence[i] = wire[at++]; }
  at = decode_contract(&record->contract, wire, at);
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->date_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->second_instrument_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->second_date_sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Market Display Data is what was written, byte for byte */
static void equal_market_display_data(const MarketDisplayData *read, const MarketDisplayData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->display_sequence[i] == written->display_sequence[i]); }
  equal_contract(&read->contract, &written->contract);
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_sequence[i] == written->instrument_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->date_sequence[i] == written->date_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_sequence[i] == written->strike_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->second_instrument_sequence[i] == written->second_instrument_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->second_date_sequence[i] == written->second_date_sequence[i]); }
}

/* Market Display Data: written and read back, then read and written back */
static void check_market_display_data(void) {
  MarketDisplayData sent;
  MarketDisplayData got;
  uint8_t wire[80];
  uint8_t again[80];

  any_market_display_data(&sent);
  assert(encode_market_display_data(&sent, wire, 0) == 80);
  assert(decode_market_display_data(&got, wire, 0) == 80);
  equal_market_display_data(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_market_display_data(&got, wire, 0) == 80);
  assert(encode_market_display_data(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Isin Code: 13 bytes ----------------------------------------------------- */

/* ISIN number of the instrument. */
typedef struct {
  uint8_t isin_code_length_byte;     /* byte 0 */
  uint8_t isin_code_characters[12];  /* bytes 1 to 12 */
} IsinCode;

/* any Isin Code at all: every byte one the checker chooses */
static void any_isin_code(IsinCode *record) {
  record->isin_code_length_byte = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->isin_code_characters[i] = arbitrary(); }
}

/* Isin Code to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_isin_code(const IsinCode *record, uint8_t *wire, size_t at) {
  wire[at++] = record->isin_code_length_byte;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->isin_code_characters[i]; }

  return at;
}

/* Isin Code off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_isin_code(IsinCode *record, const uint8_t *wire, size_t at) {
  record->isin_code_length_byte = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->isin_code_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Isin Code is what was written, byte for byte */
static void equal_isin_code(const IsinCode *read, const IsinCode *written) {
  assert(read->isin_code_length_byte == written->isin_code_length_byte);
  for (size_t i = 0; i < 12; i++) { assert(read->isin_code_characters[i] == written->isin_code_characters[i]); }
}

/* Isin Code: written and read back, then read and written back */
static void check_isin_code(void) {
  IsinCode sent;
  IsinCode got;
  uint8_t wire[13];
  uint8_t again[13];

  any_isin_code(&sent);
  assert(encode_isin_code(&sent, wire, 0) == 13);
  assert(decode_isin_code(&got, wire, 0) == 13);
  equal_isin_code(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_isin_code(&got, wire, 0) == 13);
  assert(encode_isin_code(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Description P 62: 62 bytes ---------------------------------------------- */

/* A Description of the instrument. */
typedef struct {
  uint8_t description_p_62_length_byte;     /* byte 0 */
  uint8_t description_p_62_characters[61];  /* bytes 1 to 61 */
} DescriptionP62;

/* any Description P 62 at all: every byte one the checker chooses */
static void any_description_p62(DescriptionP62 *record) {
  record->description_p_62_length_byte = arbitrary();
  for (size_t i = 0; i < 61; i++) { record->description_p_62_characters[i] = arbitrary(); }
}

/* Description P 62 to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_description_p62(const DescriptionP62 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->description_p_62_length_byte;
  for (size_t i = 0; i < 61; i++) { wire[at++] = record->description_p_62_characters[i]; }

  return at;
}

/* Description P 62 off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_description_p62(DescriptionP62 *record, const uint8_t *wire, size_t at) {
  record->description_p_62_length_byte = wire[at++];
  for (size_t i = 0; i < 61; i++) { record->description_p_62_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Description P 62 is what was written, byte for byte */
static void equal_description_p62(const DescriptionP62 *read, const DescriptionP62 *written) {
  assert(read->description_p_62_length_byte == written->description_p_62_length_byte);
  for (size_t i = 0; i < 61; i++) { assert(read->description_p_62_characters[i] == written->description_p_62_characters[i]); }
}

/* Description P 62: written and read back, then read and written back */
static void check_description_p62(void) {
  DescriptionP62 sent;
  DescriptionP62 got;
  uint8_t wire[62];
  uint8_t again[62];

  any_description_p62(&sent);
  assert(encode_description_p62(&sent, wire, 0) == 62);
  assert(decode_description_p62(&got, wire, 0) == 62);
  equal_description_p62(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_description_p62(&got, wire, 0) == 62);
  assert(encode_description_p62(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Maturity Date: 12 bytes ------------------------------------------------- */

/* Maturity Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} MaturityDate;

/* any Maturity Date at all: every byte one the checker chooses */
static void any_maturity_date(MaturityDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Maturity Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_maturity_date(const MaturityDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Maturity Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_maturity_date(MaturityDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Maturity Date is what was written, byte for byte */
static void equal_maturity_date(const MaturityDate *read, const MaturityDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Maturity Date: written and read back, then read and written back */
static void check_maturity_date(void) {
  MaturityDate sent;
  MaturityDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_maturity_date(&sent);
  assert(encode_maturity_date(&sent, wire, 0) == 12);
  assert(decode_maturity_date(&got, wire, 0) == 12);
  equal_maturity_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_maturity_date(&got, wire, 0) == 12);
  assert(encode_maturity_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Date: 12 bytes ---------------------------------------------------- */

/* Issue Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} IssueDate;

/* any Issue Date at all: every byte one the checker chooses */
static void any_issue_date(IssueDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Issue Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_issue_date(const IssueDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Issue Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_issue_date(IssueDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Issue Date is what was written, byte for byte */
static void equal_issue_date(const IssueDate *read, const IssueDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Issue Date: written and read back, then read and written back */
static void check_issue_date(void) {
  IssueDate sent;
  IssueDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_issue_date(&sent);
  assert(encode_issue_date(&sent, wire, 0) == 12);
  assert(decode_issue_date(&got, wire, 0) == 12);
  equal_issue_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_date(&got, wire, 0) == 12);
  assert(encode_issue_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Description: 60 bytes --------------------------------------------- */

/* Indicates the group make up for this instrument. */
typedef struct {
  uint8_t group_description_length_byte;     /* byte 0 */
  uint8_t group_description_characters[59];  /* bytes 1 to 59 */
} GroupDescription;

/* any Group Description at all: every byte one the checker chooses */
static void any_group_description(GroupDescription *record) {
  record->group_description_length_byte = arbitrary();
  for (size_t i = 0; i < 59; i++) { record->group_description_characters[i] = arbitrary(); }
}

/* Group Description to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_group_description(const GroupDescription *record, uint8_t *wire, size_t at) {
  wire[at++] = record->group_description_length_byte;
  for (size_t i = 0; i < 59; i++) { wire[at++] = record->group_description_characters[i]; }

  return at;
}

/* Group Description off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_group_description(GroupDescription *record, const uint8_t *wire, size_t at) {
  record->group_description_length_byte = wire[at++];
  for (size_t i = 0; i < 59; i++) { record->group_description_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Group Description is what was written, byte for byte */
static void equal_group_description(const GroupDescription *read, const GroupDescription *written) {
  assert(read->group_description_length_byte == written->group_description_length_byte);
  for (size_t i = 0; i < 59; i++) { assert(read->group_description_characters[i] == written->group_description_characters[i]); }
}

/* Group Description: written and read back, then read and written back */
static void check_group_description(void) {
  GroupDescription sent;
  GroupDescription got;
  uint8_t wire[60];
  uint8_t again[60];

  any_group_description(&sent);
  assert(encode_group_description(&sent, wire, 0) == 60);
  assert(decode_group_description(&got, wire, 0) == 60);
  equal_group_description(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_group_description(&got, wire, 0) == 60);
  assert(encode_group_description(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- First Trade Reference: 10 bytes ----------------------------------------- */

/* Indicates the reference number of the first trade on this instrument. */
typedef struct {
  uint8_t first_trade_reference_length_byte;    /* byte 0 */
  uint8_t first_trade_reference_characters[9];  /* bytes 1 to 9 */
} FirstTradeReference;

/* any First Trade Reference at all: every byte one the checker chooses */
static void any_first_trade_reference(FirstTradeReference *record) {
  record->first_trade_reference_length_byte = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->first_trade_reference_characters[i] = arbitrary(); }
}

/* First Trade Reference to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_first_trade_reference(const FirstTradeReference *record, uint8_t *wire, size_t at) {
  wire[at++] = record->first_trade_reference_length_byte;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->first_trade_reference_characters[i]; }

  return at;
}

/* First Trade Reference off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_first_trade_reference(FirstTradeReference *record, const uint8_t *wire, size_t at) {
  record->first_trade_reference_length_byte = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->first_trade_reference_characters[i] = wire[at++]; }

  return at;
}

/* what was read of First Trade Reference is what was written, byte for byte */
static void equal_first_trade_reference(const FirstTradeReference *read, const FirstTradeReference *written) {
  assert(read->first_trade_reference_length_byte == written->first_trade_reference_length_byte);
  for (size_t i = 0; i < 9; i++) { assert(read->first_trade_reference_characters[i] == written->first_trade_reference_characters[i]); }
}

/* First Trade Reference: written and read back, then read and written back */
static void check_first_trade_reference(void) {
  FirstTradeReference sent;
  FirstTradeReference got;
  uint8_t wire[10];
  uint8_t again[10];

  any_first_trade_reference(&sent);
  assert(encode_first_trade_reference(&sent, wire, 0) == 10);
  assert(decode_first_trade_reference(&got, wire, 0) == 10);
  equal_first_trade_reference(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_first_trade_reference(&got, wire, 0) == 10);
  assert(encode_first_trade_reference(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Display Name: 30 bytes -------------------------------------------------- */

/* This field allows the exchange to indicate how an instrument should be presented. */
typedef struct {
  uint8_t display_name_length_byte;     /* byte 0 */
  uint8_t display_name_characters[29];  /* bytes 1 to 29 */
} DisplayName;

/* any Display Name at all: every byte one the checker chooses */
static void any_display_name(DisplayName *record) {
  record->display_name_length_byte = arbitrary();
  for (size_t i = 0; i < 29; i++) { record->display_name_characters[i] = arbitrary(); }
}

/* Display Name to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_display_name(const DisplayName *record, uint8_t *wire, size_t at) {
  wire[at++] = record->display_name_length_byte;
  for (size_t i = 0; i < 29; i++) { wire[at++] = record->display_name_characters[i]; }

  return at;
}

/* Display Name off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_display_name(DisplayName *record, const uint8_t *wire, size_t at) {
  record->display_name_length_byte = wire[at++];
  for (size_t i = 0; i < 29; i++) { record->display_name_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Display Name is what was written, byte for byte */
static void equal_display_name(const DisplayName *read, const DisplayName *written) {
  assert(read->display_name_length_byte == written->display_name_length_byte);
  for (size_t i = 0; i < 29; i++) { assert(read->display_name_characters[i] == written->display_name_characters[i]); }
}

/* Display Name: written and read back, then read and written back */
static void check_display_name(void) {
  DisplayName sent;
  DisplayName got;
  uint8_t wire[30];
  uint8_t again[30];

  any_display_name(&sent);
  assert(encode_display_name(&sent, wire, 0) == 30);
  assert(decode_display_name(&got, wire, 0) == 30);
  equal_display_name(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_display_name(&got, wire, 0) == 30);
  assert(encode_display_name(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Classification: 30 bytes ------------------------------------------------ */

/* This field defines the instrument classification to which the bonds belongs to. */
typedef struct {
  uint8_t classification_length_byte;     /* byte 0 */
  uint8_t classification_characters[29];  /* bytes 1 to 29 */
} Classification;

/* any Classification at all: every byte one the checker chooses */
static void any_classification(Classification *record) {
  record->classification_length_byte = arbitrary();
  for (size_t i = 0; i < 29; i++) { record->classification_characters[i] = arbitrary(); }
}

/* Classification to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_classification(const Classification *record, uint8_t *wire, size_t at) {
  wire[at++] = record->classification_length_byte;
  for (size_t i = 0; i < 29; i++) { wire[at++] = record->classification_characters[i]; }

  return at;
}

/* Classification off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_classification(Classification *record, const uint8_t *wire, size_t at) {
  record->classification_length_byte = wire[at++];
  for (size_t i = 0; i < 29; i++) { record->classification_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Classification is what was written, byte for byte */
static void equal_classification(const Classification *read, const Classification *written) {
  assert(read->classification_length_byte == written->classification_length_byte);
  for (size_t i = 0; i < 29; i++) { assert(read->classification_characters[i] == written->classification_characters[i]); }
}

/* Classification: written and read back, then read and written back */
static void check_classification(void) {
  Classification sent;
  Classification got;
  uint8_t wire[30];
  uint8_t again[30];

  any_classification(&sent);
  assert(encode_classification(&sent, wire, 0) == 30);
  assert(decode_classification(&got, wire, 0) == 30);
  equal_classification(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_classification(&got, wire, 0) == 30);
  assert(encode_classification(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vetting Agent Name: 30 bytes -------------------------------------------- */

/* The name of any vetting agent for this instrument. */
typedef struct {
  uint8_t vetting_agent_name_length_byte;     /* byte 0 */
  uint8_t vetting_agent_name_characters[29];  /* bytes 1 to 29 */
} VettingAgentName;

/* any Vetting Agent Name at all: every byte one the checker chooses */
static void any_vetting_agent_name(VettingAgentName *record) {
  record->vetting_agent_name_length_byte = arbitrary();
  for (size_t i = 0; i < 29; i++) { record->vetting_agent_name_characters[i] = arbitrary(); }
}

/* Vetting Agent Name to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_vetting_agent_name(const VettingAgentName *record, uint8_t *wire, size_t at) {
  wire[at++] = record->vetting_agent_name_length_byte;
  for (size_t i = 0; i < 29; i++) { wire[at++] = record->vetting_agent_name_characters[i]; }

  return at;
}

/* Vetting Agent Name off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_vetting_agent_name(VettingAgentName *record, const uint8_t *wire, size_t at) {
  record->vetting_agent_name_length_byte = wire[at++];
  for (size_t i = 0; i < 29; i++) { record->vetting_agent_name_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Vetting Agent Name is what was written, byte for byte */
static void equal_vetting_agent_name(const VettingAgentName *read, const VettingAgentName *written) {
  assert(read->vetting_agent_name_length_byte == written->vetting_agent_name_length_byte);
  for (size_t i = 0; i < 29; i++) { assert(read->vetting_agent_name_characters[i] == written->vetting_agent_name_characters[i]); }
}

/* Vetting Agent Name: written and read back, then read and written back */
static void check_vetting_agent_name(void) {
  VettingAgentName sent;
  VettingAgentName got;
  uint8_t wire[30];
  uint8_t again[30];

  any_vetting_agent_name(&sent);
  assert(encode_vetting_agent_name(&sent, wire, 0) == 30);
  assert(decode_vetting_agent_name(&got, wire, 0) == 30);
  equal_vetting_agent_name(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_vetting_agent_name(&got, wire, 0) == 30);
  assert(encode_vetting_agent_name(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vetting Agent Contact: 30 bytes ----------------------------------------- */

/* Contact information for the vetting agent. */
typedef struct {
  uint8_t vetting_agent_contact_length_byte;     /* byte 0 */
  uint8_t vetting_agent_contact_characters[29];  /* bytes 1 to 29 */
} VettingAgentContact;

/* any Vetting Agent Contact at all: every byte one the checker chooses */
static void any_vetting_agent_contact(VettingAgentContact *record) {
  record->vetting_agent_contact_length_byte = arbitrary();
  for (size_t i = 0; i < 29; i++) { record->vetting_agent_contact_characters[i] = arbitrary(); }
}

/* Vetting Agent Contact to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_vetting_agent_contact(const VettingAgentContact *record, uint8_t *wire, size_t at) {
  wire[at++] = record->vetting_agent_contact_length_byte;
  for (size_t i = 0; i < 29; i++) { wire[at++] = record->vetting_agent_contact_characters[i]; }

  return at;
}

/* Vetting Agent Contact off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_vetting_agent_contact(VettingAgentContact *record, const uint8_t *wire, size_t at) {
  record->vetting_agent_contact_length_byte = wire[at++];
  for (size_t i = 0; i < 29; i++) { record->vetting_agent_contact_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Vetting Agent Contact is what was written, byte for byte */
static void equal_vetting_agent_contact(const VettingAgentContact *read, const VettingAgentContact *written) {
  assert(read->vetting_agent_contact_length_byte == written->vetting_agent_contact_length_byte);
  for (size_t i = 0; i < 29; i++) { assert(read->vetting_agent_contact_characters[i] == written->vetting_agent_contact_characters[i]); }
}

/* Vetting Agent Contact: written and read back, then read and written back */
static void check_vetting_agent_contact(void) {
  VettingAgentContact sent;
  VettingAgentContact got;
  uint8_t wire[30];
  uint8_t again[30];

  any_vetting_agent_contact(&sent);
  assert(encode_vetting_agent_contact(&sent, wire, 0) == 30);
  assert(decode_vetting_agent_contact(&got, wire, 0) == 30);
  equal_vetting_agent_contact(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_vetting_agent_contact(&got, wire, 0) == 30);
  assert(encode_vetting_agent_contact(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sector: 30 bytes -------------------------------------------------------- */

/* Describes a market sector for a security. */
typedef struct {
  uint8_t sector_length_byte;     /* byte 0 */
  uint8_t sector_characters[29];  /* bytes 1 to 29 */
} Sector;

/* any Sector at all: every byte one the checker chooses */
static void any_sector(Sector *record) {
  record->sector_length_byte = arbitrary();
  for (size_t i = 0; i < 29; i++) { record->sector_characters[i] = arbitrary(); }
}

/* Sector to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_sector(const Sector *record, uint8_t *wire, size_t at) {
  wire[at++] = record->sector_length_byte;
  for (size_t i = 0; i < 29; i++) { wire[at++] = record->sector_characters[i]; }

  return at;
}

/* Sector off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_sector(Sector *record, const uint8_t *wire, size_t at) {
  record->sector_length_byte = wire[at++];
  for (size_t i = 0; i < 29; i++) { record->sector_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Sector is what was written, byte for byte */
static void equal_sector(const Sector *read, const Sector *written) {
  assert(read->sector_length_byte == written->sector_length_byte);
  for (size_t i = 0; i < 29; i++) { assert(read->sector_characters[i] == written->sector_characters[i]); }
}

/* Sector: written and read back, then read and written back */
static void check_sector(void) {
  Sector sent;
  Sector got;
  uint8_t wire[30];
  uint8_t again[30];

  any_sector(&sent);
  assert(encode_sector(&sent, wire, 0) == 30);
  assert(decode_sector(&got, wire, 0) == 30);
  equal_sector(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_sector(&got, wire, 0) == 30);
  assert(encode_sector(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Type: 30 bytes ------------------------------------------------- */

/* Categorizes securities into their various types. */
typedef struct {
  uint8_t security_type_length_byte;     /* byte 0 */
  uint8_t security_type_characters[29];  /* bytes 1 to 29 */
} SecurityType;

/* any Security Type at all: every byte one the checker chooses */
static void any_security_type(SecurityType *record) {
  record->security_type_length_byte = arbitrary();
  for (size_t i = 0; i < 29; i++) { record->security_type_characters[i] = arbitrary(); }
}

/* Security Type to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_security_type(const SecurityType *record, uint8_t *wire, size_t at) {
  wire[at++] = record->security_type_length_byte;
  for (size_t i = 0; i < 29; i++) { wire[at++] = record->security_type_characters[i]; }

  return at;
}

/* Security Type off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_security_type(SecurityType *record, const uint8_t *wire, size_t at) {
  record->security_type_length_byte = wire[at++];
  for (size_t i = 0; i < 29; i++) { record->security_type_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Security Type is what was written, byte for byte */
static void equal_security_type(const SecurityType *read, const SecurityType *written) {
  assert(read->security_type_length_byte == written->security_type_length_byte);
  for (size_t i = 0; i < 29; i++) { assert(read->security_type_characters[i] == written->security_type_characters[i]); }
}

/* Security Type: written and read back, then read and written back */
static void check_security_type(void) {
  SecurityType sent;
  SecurityType got;
  uint8_t wire[30];
  uint8_t again[30];

  any_security_type(&sent);
  assert(encode_security_type(&sent, wire, 0) == 30);
  assert(decode_security_type(&got, wire, 0) == 30);
  equal_security_type(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_security_type(&got, wire, 0) == 30);
  assert(encode_security_type(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instruments Data: 486 bytes --------------------------------------------- */

/* Instruments Data */
typedef struct {
  uint8_t instrument_sequence[4];             /* bytes 0 to 3 */
  uint8_t trading_session_sequence[4];        /* bytes 4 to 7 */
  uint8_t unused_4[4];                        /* bytes 8 to 11 */
  uint8_t instrument_group_sequence[4];       /* bytes 12 to 15 */
  uint8_t future_fee_sequence[4];             /* bytes 16 to 19 */
  uint8_t option_fee_sequence[4];             /* bytes 20 to 23 */
  uint8_t delivery_fee_sequence[4];           /* bytes 24 to 27 */
  uint8_t market_number_c_1;                  /* byte 28 */
  uint8_t market_shard_number_c_1;            /* byte 29 */
  InstrumentNameP5 instrument_name_p_5;       /* bytes 30 to 34 */
  uint8_t instrument_type_number_c_1;         /* byte 35 */
  IsinCode isin_code;                         /* bytes 36 to 48 */
  DescriptionP62 description_p_62;            /* bytes 49 to 110 */
  uint8_t on_screen;                          /* byte 111 */
  MaturityDate maturity_date;                 /* bytes 112 to 123 */
  uint8_t second_unused_4[4];                 /* bytes 124 to 127 */
  uint8_t nominal_divisor[4];                 /* bytes 128 to 131 */
  IssueDate issue_date;                       /* bytes 132 to 143 */
  uint8_t linked_to_floating_rate;            /* byte 144 */
  uint8_t unused_1;                           /* byte 145 */
  uint8_t underlying[4];                      /* bytes 146 to 149 */
  uint8_t options_exercise_is_percentage;     /* byte 150 */
  uint8_t options_exercise_cost[8];           /* bytes 151 to 158 */
  uint8_t group_margin[8];                    /* bytes 159 to 166 */
  uint8_t vat;                                /* byte 167 */
  uint8_t settlement_margin[8];               /* bytes 168 to 175 */
  uint8_t physical_settlement;                /* byte 176 */
  GroupDescription group_description;         /* bytes 177 to 236 */
  uint8_t third_unused_4[4];                  /* bytes 237 to 240 */
  uint8_t reference_inflation_rate[8];        /* bytes 241 to 248 */
  uint8_t minimum_initiation_fee[8];          /* bytes 249 to 256 */
  FirstTradeReference first_trade_reference;  /* bytes 257 to 266 */
  uint8_t unused_5[5];                        /* bytes 267 to 271 */
  CountryCode country_code;                   /* bytes 272 to 275 */
  DisplayName display_name;                   /* bytes 276 to 305 */
  uint8_t number_of_days_in_a_year[4];        /* bytes 306 to 309 */
  uint8_t bond_formula_decimal_places[4];     /* bytes 310 to 313 */
  uint8_t coupon_rate[8];                     /* bytes 314 to 321 */
  Classification classification;              /* bytes 322 to 351 */
  uint8_t settlement_days[4];                 /* bytes 352 to 355 */
  uint8_t validated_at_csd;                   /* byte 356 */
  uint8_t proprietary_trading_allowed;        /* byte 357 */
  VettingAgentName vetting_agent_name;        /* bytes 358 to 387 */
  VettingAgentContact vetting_agent_contact;  /* bytes 388 to 417 */
  uint8_t share_holding_percentage_limit[8];  /* bytes 418 to 425 */
  Sector sector;                              /* bytes 426 to 455 */
  SecurityType security_type;                 /* bytes 456 to 485 */
} InstrumentsData;

/* any Instruments Data at all: every byte one the checker chooses */
static void any_instruments_data(InstrumentsData *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unused_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_group_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->future_fee_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_fee_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->delivery_fee_sequence[i] = arbitrary(); }
  record->market_number_c_1 = arbitrary();
  record->market_shard_number_c_1 = arbitrary();
  any_instrument_name_p5(&record->instrument_name_p_5);
  record->instrument_type_number_c_1 = arbitrary();
  any_isin_code(&record->isin_code);
  any_description_p62(&record->description_p_62);
  record->on_screen = arbitrary();
  any_maturity_date(&record->maturity_date);
  for (size_t i = 0; i < 4; i++) { record->second_unused_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nominal_divisor[i] = arbitrary(); }
  any_issue_date(&record->issue_date);
  record->linked_to_floating_rate = arbitrary();
  record->unused_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->underlying[i] = arbitrary(); }
  record->options_exercise_is_percentage = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->options_exercise_cost[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->group_margin[i] = arbitrary(); }
  record->vat = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->settlement_margin[i] = arbitrary(); }
  record->physical_settlement = arbitrary();
  any_group_description(&record->group_description);
  for (size_t i = 0; i < 4; i++) { record->third_unused_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_inflation_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_initiation_fee[i] = arbitrary(); }
  any_first_trade_reference(&record->first_trade_reference);
  for (size_t i = 0; i < 5; i++) { record->unused_5[i] = arbitrary(); }
  any_country_code(&record->country_code);
  any_display_name(&record->display_name);
  for (size_t i = 0; i < 4; i++) { record->number_of_days_in_a_year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bond_formula_decimal_places[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->coupon_rate[i] = arbitrary(); }
  any_classification(&record->classification);
  for (size_t i = 0; i < 4; i++) { record->settlement_days[i] = arbitrary(); }
  record->validated_at_csd = arbitrary();
  record->proprietary_trading_allowed = arbitrary();
  any_vetting_agent_name(&record->vetting_agent_name);
  any_vetting_agent_contact(&record->vetting_agent_contact);
  for (size_t i = 0; i < 8; i++) { record->share_holding_percentage_limit[i] = arbitrary(); }
  any_sector(&record->sector);
  any_security_type(&record->security_type);
}

/* Instruments Data to the wire: 486 bytes from at, returning where the next byte goes */
static size_t encode_instruments_data(const InstrumentsData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unused_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_group_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->future_fee_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_fee_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delivery_fee_sequence[i]; }
  wire[at++] = record->market_number_c_1;
  wire[at++] = record->market_shard_number_c_1;
  at = encode_instrument_name_p5(&record->instrument_name_p_5, wire, at);
  wire[at++] = record->instrument_type_number_c_1;
  at = encode_isin_code(&record->isin_code, wire, at);
  at = encode_description_p62(&record->description_p_62, wire, at);
  wire[at++] = record->on_screen;
  at = encode_maturity_date(&record->maturity_date, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->second_unused_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nominal_divisor[i]; }
  at = encode_issue_date(&record->issue_date, wire, at);
  wire[at++] = record->linked_to_floating_rate;
  wire[at++] = record->unused_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->underlying[i]; }
  wire[at++] = record->options_exercise_is_percentage;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->options_exercise_cost[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->group_margin[i]; }
  wire[at++] = record->vat;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->settlement_margin[i]; }
  wire[at++] = record->physical_settlement;
  at = encode_group_description(&record->group_description, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->third_unused_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_inflation_rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_initiation_fee[i]; }
  at = encode_first_trade_reference(&record->first_trade_reference, wire, at);
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->unused_5[i]; }
  at = encode_country_code(&record->country_code, wire, at);
  at = encode_display_name(&record->display_name, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_days_in_a_year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bond_formula_decimal_places[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->coupon_rate[i]; }
  at = encode_classification(&record->classification, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settlement_days[i]; }
  wire[at++] = record->validated_at_csd;
  wire[at++] = record->proprietary_trading_allowed;
  at = encode_vetting_agent_name(&record->vetting_agent_name, wire, at);
  at = encode_vetting_agent_contact(&record->vetting_agent_contact, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->share_holding_percentage_limit[i]; }
  at = encode_sector(&record->sector, wire, at);
  at = encode_security_type(&record->security_type, wire, at);

  return at;
}

/* Instruments Data off the wire: 486 bytes from at, returning where the next byte lies */
static size_t decode_instruments_data(InstrumentsData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unused_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_group_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->future_fee_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_fee_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->delivery_fee_sequence[i] = wire[at++]; }
  record->market_number_c_1 = wire[at++];
  record->market_shard_number_c_1 = wire[at++];
  at = decode_instrument_name_p5(&record->instrument_name_p_5, wire, at);
  record->instrument_type_number_c_1 = wire[at++];
  at = decode_isin_code(&record->isin_code, wire, at);
  at = decode_description_p62(&record->description_p_62, wire, at);
  record->on_screen = wire[at++];
  at = decode_maturity_date(&record->maturity_date, wire, at);
  for (size_t i = 0; i < 4; i++) { record->second_unused_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nominal_divisor[i] = wire[at++]; }
  at = decode_issue_date(&record->issue_date, wire, at);
  record->linked_to_floating_rate = wire[at++];
  record->unused_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->underlying[i] = wire[at++]; }
  record->options_exercise_is_percentage = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->options_exercise_cost[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->group_margin[i] = wire[at++]; }
  record->vat = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->settlement_margin[i] = wire[at++]; }
  record->physical_settlement = wire[at++];
  at = decode_group_description(&record->group_description, wire, at);
  for (size_t i = 0; i < 4; i++) { record->third_unused_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_inflation_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_initiation_fee[i] = wire[at++]; }
  at = decode_first_trade_reference(&record->first_trade_reference, wire, at);
  for (size_t i = 0; i < 5; i++) { record->unused_5[i] = wire[at++]; }
  at = decode_country_code(&record->country_code, wire, at);
  at = decode_display_name(&record->display_name, wire, at);
  for (size_t i = 0; i < 4; i++) { record->number_of_days_in_a_year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bond_formula_decimal_places[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->coupon_rate[i] = wire[at++]; }
  at = decode_classification(&record->classification, wire, at);
  for (size_t i = 0; i < 4; i++) { record->settlement_days[i] = wire[at++]; }
  record->validated_at_csd = wire[at++];
  record->proprietary_trading_allowed = wire[at++];
  at = decode_vetting_agent_name(&record->vetting_agent_name, wire, at);
  at = decode_vetting_agent_contact(&record->vetting_agent_contact, wire, at);
  for (size_t i = 0; i < 8; i++) { record->share_holding_percentage_limit[i] = wire[at++]; }
  at = decode_sector(&record->sector, wire, at);
  at = decode_security_type(&record->security_type, wire, at);

  return at;
}

/* what was read of Instruments Data is what was written, byte for byte */
static void equal_instruments_data(const InstrumentsData *read, const InstrumentsData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_sequence[i] == written->instrument_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_sequence[i] == written->trading_session_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unused_4[i] == written->unused_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_group_sequence[i] == written->instrument_group_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->future_fee_sequence[i] == written->future_fee_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_fee_sequence[i] == written->option_fee_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->delivery_fee_sequence[i] == written->delivery_fee_sequence[i]); }
  assert(read->market_number_c_1 == written->market_number_c_1);
  assert(read->market_shard_number_c_1 == written->market_shard_number_c_1);
  equal_instrument_name_p5(&read->instrument_name_p_5, &written->instrument_name_p_5);
  assert(read->instrument_type_number_c_1 == written->instrument_type_number_c_1);
  equal_isin_code(&read->isin_code, &written->isin_code);
  equal_description_p62(&read->description_p_62, &written->description_p_62);
  assert(read->on_screen == written->on_screen);
  equal_maturity_date(&read->maturity_date, &written->maturity_date);
  for (size_t i = 0; i < 4; i++) { assert(read->second_unused_4[i] == written->second_unused_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nominal_divisor[i] == written->nominal_divisor[i]); }
  equal_issue_date(&read->issue_date, &written->issue_date);
  assert(read->linked_to_floating_rate == written->linked_to_floating_rate);
  assert(read->unused_1 == written->unused_1);
  for (size_t i = 0; i < 4; i++) { assert(read->underlying[i] == written->underlying[i]); }
  assert(read->options_exercise_is_percentage == written->options_exercise_is_percentage);
  for (size_t i = 0; i < 8; i++) { assert(read->options_exercise_cost[i] == written->options_exercise_cost[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->group_margin[i] == written->group_margin[i]); }
  assert(read->vat == written->vat);
  for (size_t i = 0; i < 8; i++) { assert(read->settlement_margin[i] == written->settlement_margin[i]); }
  assert(read->physical_settlement == written->physical_settlement);
  equal_group_description(&read->group_description, &written->group_description);
  for (size_t i = 0; i < 4; i++) { assert(read->third_unused_4[i] == written->third_unused_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_inflation_rate[i] == written->reference_inflation_rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_initiation_fee[i] == written->minimum_initiation_fee[i]); }
  equal_first_trade_reference(&read->first_trade_reference, &written->first_trade_reference);
  for (size_t i = 0; i < 5; i++) { assert(read->unused_5[i] == written->unused_5[i]); }
  equal_country_code(&read->country_code, &written->country_code);
  equal_display_name(&read->display_name, &written->display_name);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_days_in_a_year[i] == written->number_of_days_in_a_year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bond_formula_decimal_places[i] == written->bond_formula_decimal_places[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  equal_classification(&read->classification, &written->classification);
  for (size_t i = 0; i < 4; i++) { assert(read->settlement_days[i] == written->settlement_days[i]); }
  assert(read->validated_at_csd == written->validated_at_csd);
  assert(read->proprietary_trading_allowed == written->proprietary_trading_allowed);
  equal_vetting_agent_name(&read->vetting_agent_name, &written->vetting_agent_name);
  equal_vetting_agent_contact(&read->vetting_agent_contact, &written->vetting_agent_contact);
  for (size_t i = 0; i < 8; i++) { assert(read->share_holding_percentage_limit[i] == written->share_holding_percentage_limit[i]); }
  equal_sector(&read->sector, &written->sector);
  equal_security_type(&read->security_type, &written->security_type);
}

/* Instruments Data: written and read back, then read and written back */
static void check_instruments_data(void) {
  InstrumentsData sent;
  InstrumentsData got;
  uint8_t wire[486];
  uint8_t again[486];

  any_instruments_data(&sent);
  assert(encode_instruments_data(&sent, wire, 0) == 486);
  assert(decode_instruments_data(&got, wire, 0) == 486);
  equal_instruments_data(&got, &sent);

  for (size_t i = 0; i < 486; i++) { wire[i] = arbitrary(); }
  assert(decode_instruments_data(&got, wire, 0) == 486);
  assert(encode_instruments_data(&got, again, 0) == 486);
  for (size_t i = 0; i < 486; i++) { assert(again[i] == wire[i]); }
}

/* ---- Expiry Date: 12 bytes --------------------------------------------------- */

/* Expiry Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} ExpiryDate;

/* any Expiry Date at all: every byte one the checker chooses */
static void any_expiry_date(ExpiryDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Expiry Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_expiry_date(const ExpiryDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Expiry Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_expiry_date(ExpiryDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Expiry Date is what was written, byte for byte */
static void equal_expiry_date(const ExpiryDate *read, const ExpiryDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Expiry Date: written and read back, then read and written back */
static void check_expiry_date(void) {
  ExpiryDate sent;
  ExpiryDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_expiry_date(&sent);
  assert(encode_expiry_date(&sent, wire, 0) == 12);
  assert(decode_expiry_date(&got, wire, 0) == 12);
  equal_expiry_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_expiry_date(&got, wire, 0) == 12);
  assert(encode_expiry_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Valuation Date: 12 bytes ------------------------------------------------ */

/* Valuation Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} ValuationDate;

/* any Valuation Date at all: every byte one the checker chooses */
static void any_valuation_date(ValuationDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Valuation Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_valuation_date(const ValuationDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Valuation Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_valuation_date(ValuationDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Valuation Date is what was written, byte for byte */
static void equal_valuation_date(const ValuationDate *read, const ValuationDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Valuation Date: written and read back, then read and written back */
static void check_valuation_date(void) {
  ValuationDate sent;
  ValuationDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_valuation_date(&sent);
  assert(encode_valuation_date(&sent, wire, 0) == 12);
  assert(decode_valuation_date(&got, wire, 0) == 12);
  equal_valuation_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_valuation_date(&got, wire, 0) == 12);
  assert(encode_valuation_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearance Date: 12 bytes ------------------------------------------------ */

/* Clearance Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} ClearanceDate;

/* any Clearance Date at all: every byte one the checker chooses */
static void any_clearance_date(ClearanceDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Clearance Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_clearance_date(const ClearanceDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Clearance Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_clearance_date(ClearanceDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Clearance Date is what was written, byte for byte */
static void equal_clearance_date(const ClearanceDate *read, const ClearanceDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Clearance Date: written and read back, then read and written back */
static void check_clearance_date(void) {
  ClearanceDate sent;
  ClearanceDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_clearance_date(&sent);
  assert(encode_clearance_date(&sent, wire, 0) == 12);
  assert(decode_clearance_date(&got, wire, 0) == 12);
  equal_clearance_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_clearance_date(&got, wire, 0) == 12);
  assert(encode_clearance_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contract Dates: 243 bytes ----------------------------------------------- */

/* Contract Dates */
typedef struct {
  uint8_t instrument_sequence[4];                          /* bytes 0 to 3 */
  uint8_t contract_date_sequence[4];                       /* bytes 4 to 7 */
  uint8_t trading_session_sequence[4];                     /* bytes 8 to 11 */
  ExpiryDate expiry_date;                                  /* bytes 12 to 23 */
  ValuationDate valuation_date;                            /* bytes 24 to 35 */
  uint8_t nominal[8];                                      /* bytes 36 to 43 */
  uint8_t strike_interval[8];                              /* bytes 44 to 51 */
  uint8_t strike_interval_off_screen[8];                   /* bytes 52 to 59 */
  uint8_t spread_margin[8];                                /* bytes 60 to 67 */
  uint8_t lot_size[4];                                     /* bytes 68 to 71 */
  uint8_t option_lot_size[4];                              /* bytes 72 to 75 */
  uint8_t big_depth;                                       /* byte 76 */
  uint8_t price_rate;                                      /* byte 77 */
  uint8_t max_change[8];                                   /* bytes 78 to 85 */
  uint8_t max_days_move[8];                                /* bytes 86 to 93 */
  uint8_t max_gap[8];                                      /* bytes 94 to 101 */
  uint8_t unused_1;                                        /* byte 102 */
  uint8_t options_allowed;                                 /* byte 103 */
  uint8_t deltas_allowed;                                  /* byte 104 */
  uint8_t spreads_allowed;                                 /* byte 105 */
  uint8_t initial_margin[8];                               /* bytes 106 to 113 */
  uint8_t quote_format_decimal_places[4];                  /* bytes 114 to 117 */
  uint8_t price_format_decimal_places[4];                  /* bytes 118 to 121 */
  uint8_t option_premium_format_decimal_places[4];         /* bytes 122 to 125 */
  uint8_t price_multiplier[2];                             /* bytes 126 to 127 */
  ClearanceDate clearance_date;                            /* bytes 128 to 139 */
  uint8_t vsr[8];                                          /* bytes 140 to 147 */
  uint8_t rpve[8];                                         /* bytes 148 to 155 */
  uint8_t volatility_rounding_places[4];                   /* bytes 156 to 159 */
  uint8_t can_trade_options_onscreen;                      /* byte 160 */
  uint8_t can_trade_options_report_only;                   /* byte 161 */
  uint8_t can_trade_onscreen;                              /* byte 162 */
  uint8_t can_trade_report_only;                           /* byte 163 */
  uint8_t price_interval[8];                               /* bytes 164 to 171 */
  uint8_t minimum_valid_bid_volume_on_screen[4];           /* bytes 172 to 175 */
  uint8_t minimum_valid_bid_volume_off_screen[4];          /* bytes 176 to 179 */
  uint8_t minimum_valid_bid_volume_on_screen_options[4];   /* bytes 180 to 183 */
  uint8_t minimum_valid_bid_volume_off_screen_options[4];  /* bytes 184 to 187 */
  uint8_t all_or_nothing_allowed;                          /* byte 188 */
  uint8_t at_best_orders_allowed;                          /* byte 189 */
  uint8_t stop_orders_allowed;                             /* byte 190 */
  uint8_t ice_berg_orders_allowed;                         /* byte 191 */
  uint8_t hold_over_orders_allowed;                        /* byte 192 */
  uint8_t at_close_orders_allowed;                         /* byte 193 */
  uint8_t future_anonymous;                                /* byte 194 */
  uint8_t option_anonymous;                                /* byte 195 */
  uint8_t unused_17[17];                                   /* bytes 196 to 212 */
  uint8_t rfq_allowed;                                     /* byte 213 */
  uint8_t quantity_tick_size[4];                           /* bytes 214 to 217 */
  uint8_t unused_8[8];                                     /* bytes 218 to 225 */
  uint8_t minimum_all_or_nothing_quantity[8];              /* bytes 226 to 233 */
  uint8_t minimum_iceberg_quantity[8];                     /* bytes 234 to 241 */
  uint8_t good_till_cancelled_allowed;                     /* byte 242 */
} ContractDates;

/* any Contract Dates at all: every byte one the checker chooses */
static void any_contract_dates(ContractDates *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_date_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trading_session_sequence[i] = arbitrary(); }
  any_expiry_date(&record->expiry_date);
  any_valuation_date(&record->valuation_date);
  for (size_t i = 0; i < 8; i++) { record->nominal[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_interval_off_screen[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->spread_margin[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_lot_size[i] = arbitrary(); }
  record->big_depth = arbitrary();
  record->price_rate = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->max_change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_days_move[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_gap[i] = arbitrary(); }
  record->unused_1 = arbitrary();
  record->options_allowed = arbitrary();
  record->deltas_allowed = arbitrary();
  record->spreads_allowed = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->initial_margin[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quote_format_decimal_places[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price_format_decimal_places[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->option_premium_format_decimal_places[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->price_multiplier[i] = arbitrary(); }
  any_clearance_date(&record->clearance_date);
  for (size_t i = 0; i < 8; i++) { record->vsr[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->rpve[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->volatility_rounding_places[i] = arbitrary(); }
  record->can_trade_options_onscreen = arbitrary();
  record->can_trade_options_report_only = arbitrary();
  record->can_trade_onscreen = arbitrary();
  record->can_trade_report_only = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_valid_bid_volume_on_screen[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_valid_bid_volume_off_screen[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_valid_bid_volume_on_screen_options[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_valid_bid_volume_off_screen_options[i] = arbitrary(); }
  record->all_or_nothing_allowed = arbitrary();
  record->at_best_orders_allowed = arbitrary();
  record->stop_orders_allowed = arbitrary();
  record->ice_berg_orders_allowed = arbitrary();
  record->hold_over_orders_allowed = arbitrary();
  record->at_close_orders_allowed = arbitrary();
  record->future_anonymous = arbitrary();
  record->option_anonymous = arbitrary();
  for (size_t i = 0; i < 17; i++) { record->unused_17[i] = arbitrary(); }
  record->rfq_allowed = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->unused_8[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_all_or_nothing_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_iceberg_quantity[i] = arbitrary(); }
  record->good_till_cancelled_allowed = arbitrary();
}

/* Contract Dates to the wire: 243 bytes from at, returning where the next byte goes */
static size_t encode_contract_dates(const ContractDates *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_date_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_sequence[i]; }
  at = encode_expiry_date(&record->expiry_date, wire, at);
  at = encode_valuation_date(&record->valuation_date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nominal[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_interval[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_interval_off_screen[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spread_margin[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_lot_size[i]; }
  wire[at++] = record->big_depth;
  wire[at++] = record->price_rate;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_days_move[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_gap[i]; }
  wire[at++] = record->unused_1;
  wire[at++] = record->options_allowed;
  wire[at++] = record->deltas_allowed;
  wire[at++] = record->spreads_allowed;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->initial_margin[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quote_format_decimal_places[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price_format_decimal_places[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->option_premium_format_decimal_places[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->price_multiplier[i]; }
  at = encode_clearance_date(&record->clearance_date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vsr[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rpve[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->volatility_rounding_places[i]; }
  wire[at++] = record->can_trade_options_onscreen;
  wire[at++] = record->can_trade_options_report_only;
  wire[at++] = record->can_trade_onscreen;
  wire[at++] = record->can_trade_report_only;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_interval[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_valid_bid_volume_on_screen[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_valid_bid_volume_off_screen[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_valid_bid_volume_on_screen_options[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_valid_bid_volume_off_screen_options[i]; }
  wire[at++] = record->all_or_nothing_allowed;
  wire[at++] = record->at_best_orders_allowed;
  wire[at++] = record->stop_orders_allowed;
  wire[at++] = record->ice_berg_orders_allowed;
  wire[at++] = record->hold_over_orders_allowed;
  wire[at++] = record->at_close_orders_allowed;
  wire[at++] = record->future_anonymous;
  wire[at++] = record->option_anonymous;
  for (size_t i = 0; i < 17; i++) { wire[at++] = record->unused_17[i]; }
  wire[at++] = record->rfq_allowed;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity_tick_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->unused_8[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_all_or_nothing_quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_iceberg_quantity[i]; }
  wire[at++] = record->good_till_cancelled_allowed;

  return at;
}

/* Contract Dates off the wire: 243 bytes from at, returning where the next byte lies */
static size_t decode_contract_dates(ContractDates *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_date_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trading_session_sequence[i] = wire[at++]; }
  at = decode_expiry_date(&record->expiry_date, wire, at);
  at = decode_valuation_date(&record->valuation_date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->nominal[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_interval_off_screen[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->spread_margin[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_lot_size[i] = wire[at++]; }
  record->big_depth = wire[at++];
  record->price_rate = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->max_change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_days_move[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_gap[i] = wire[at++]; }
  record->unused_1 = wire[at++];
  record->options_allowed = wire[at++];
  record->deltas_allowed = wire[at++];
  record->spreads_allowed = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->initial_margin[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quote_format_decimal_places[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price_format_decimal_places[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->option_premium_format_decimal_places[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->price_multiplier[i] = wire[at++]; }
  at = decode_clearance_date(&record->clearance_date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->vsr[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->rpve[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->volatility_rounding_places[i] = wire[at++]; }
  record->can_trade_options_onscreen = wire[at++];
  record->can_trade_options_report_only = wire[at++];
  record->can_trade_onscreen = wire[at++];
  record->can_trade_report_only = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_valid_bid_volume_on_screen[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_valid_bid_volume_off_screen[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_valid_bid_volume_on_screen_options[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_valid_bid_volume_off_screen_options[i] = wire[at++]; }
  record->all_or_nothing_allowed = wire[at++];
  record->at_best_orders_allowed = wire[at++];
  record->stop_orders_allowed = wire[at++];
  record->ice_berg_orders_allowed = wire[at++];
  record->hold_over_orders_allowed = wire[at++];
  record->at_close_orders_allowed = wire[at++];
  record->future_anonymous = wire[at++];
  record->option_anonymous = wire[at++];
  for (size_t i = 0; i < 17; i++) { record->unused_17[i] = wire[at++]; }
  record->rfq_allowed = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity_tick_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->unused_8[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_all_or_nothing_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_iceberg_quantity[i] = wire[at++]; }
  record->good_till_cancelled_allowed = wire[at++];

  return at;
}

/* what was read of Contract Dates is what was written, byte for byte */
static void equal_contract_dates(const ContractDates *read, const ContractDates *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_sequence[i] == written->instrument_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_date_sequence[i] == written->contract_date_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_sequence[i] == written->trading_session_sequence[i]); }
  equal_expiry_date(&read->expiry_date, &written->expiry_date);
  equal_valuation_date(&read->valuation_date, &written->valuation_date);
  for (size_t i = 0; i < 8; i++) { assert(read->nominal[i] == written->nominal[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_interval[i] == written->strike_interval[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_interval_off_screen[i] == written->strike_interval_off_screen[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->spread_margin[i] == written->spread_margin[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_lot_size[i] == written->option_lot_size[i]); }
  assert(read->big_depth == written->big_depth);
  assert(read->price_rate == written->price_rate);
  for (size_t i = 0; i < 8; i++) { assert(read->max_change[i] == written->max_change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_days_move[i] == written->max_days_move[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_gap[i] == written->max_gap[i]); }
  assert(read->unused_1 == written->unused_1);
  assert(read->options_allowed == written->options_allowed);
  assert(read->deltas_allowed == written->deltas_allowed);
  assert(read->spreads_allowed == written->spreads_allowed);
  for (size_t i = 0; i < 8; i++) { assert(read->initial_margin[i] == written->initial_margin[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quote_format_decimal_places[i] == written->quote_format_decimal_places[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price_format_decimal_places[i] == written->price_format_decimal_places[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->option_premium_format_decimal_places[i] == written->option_premium_format_decimal_places[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->price_multiplier[i] == written->price_multiplier[i]); }
  equal_clearance_date(&read->clearance_date, &written->clearance_date);
  for (size_t i = 0; i < 8; i++) { assert(read->vsr[i] == written->vsr[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->rpve[i] == written->rpve[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->volatility_rounding_places[i] == written->volatility_rounding_places[i]); }
  assert(read->can_trade_options_onscreen == written->can_trade_options_onscreen);
  assert(read->can_trade_options_report_only == written->can_trade_options_report_only);
  assert(read->can_trade_onscreen == written->can_trade_onscreen);
  assert(read->can_trade_report_only == written->can_trade_report_only);
  for (size_t i = 0; i < 8; i++) { assert(read->price_interval[i] == written->price_interval[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_valid_bid_volume_on_screen[i] == written->minimum_valid_bid_volume_on_screen[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_valid_bid_volume_off_screen[i] == written->minimum_valid_bid_volume_off_screen[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_valid_bid_volume_on_screen_options[i] == written->minimum_valid_bid_volume_on_screen_options[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_valid_bid_volume_off_screen_options[i] == written->minimum_valid_bid_volume_off_screen_options[i]); }
  assert(read->all_or_nothing_allowed == written->all_or_nothing_allowed);
  assert(read->at_best_orders_allowed == written->at_best_orders_allowed);
  assert(read->stop_orders_allowed == written->stop_orders_allowed);
  assert(read->ice_berg_orders_allowed == written->ice_berg_orders_allowed);
  assert(read->hold_over_orders_allowed == written->hold_over_orders_allowed);
  assert(read->at_close_orders_allowed == written->at_close_orders_allowed);
  assert(read->future_anonymous == written->future_anonymous);
  assert(read->option_anonymous == written->option_anonymous);
  for (size_t i = 0; i < 17; i++) { assert(read->unused_17[i] == written->unused_17[i]); }
  assert(read->rfq_allowed == written->rfq_allowed);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity_tick_size[i] == written->quantity_tick_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->unused_8[i] == written->unused_8[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_all_or_nothing_quantity[i] == written->minimum_all_or_nothing_quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_iceberg_quantity[i] == written->minimum_iceberg_quantity[i]); }
  assert(read->good_till_cancelled_allowed == written->good_till_cancelled_allowed);
}

/* Contract Dates: written and read back, then read and written back */
static void check_contract_dates(void) {
  ContractDates sent;
  ContractDates got;
  uint8_t wire[243];
  uint8_t again[243];

  any_contract_dates(&sent);
  assert(encode_contract_dates(&sent, wire, 0) == 243);
  assert(decode_contract_dates(&got, wire, 0) == 243);
  equal_contract_dates(&got, &sent);

  for (size_t i = 0; i < 243; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_dates(&got, wire, 0) == 243);
  assert(encode_contract_dates(&got, again, 0) == 243);
  for (size_t i = 0; i < 243; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Expiry Date: 12 bytes -------------------------------------------- */

/* Strike Expiry Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} StrikeExpiryDate;

/* any Strike Expiry Date at all: every byte one the checker chooses */
static void any_strike_expiry_date(StrikeExpiryDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Strike Expiry Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_strike_expiry_date(const StrikeExpiryDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Strike Expiry Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_strike_expiry_date(StrikeExpiryDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Strike Expiry Date is what was written, byte for byte */
static void equal_strike_expiry_date(const StrikeExpiryDate *read, const StrikeExpiryDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Strike Expiry Date: written and read back, then read and written back */
static void check_strike_expiry_date(void) {
  StrikeExpiryDate sent;
  StrikeExpiryDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_strike_expiry_date(&sent);
  assert(encode_strike_expiry_date(&sent, wire, 0) == 12);
  assert(decode_strike_expiry_date(&got, wire, 0) == 12);
  equal_strike_expiry_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_expiry_date(&got, wire, 0) == 12);
  assert(encode_strike_expiry_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strike Data: 30 bytes --------------------------------------------------- */

/* Strike Data */
typedef struct {
  uint8_t strike_sequence_number[4];    /* bytes 0 to 3 */
  uint8_t contract_date_sequence[4];    /* bytes 4 to 7 */
  uint8_t strike[8];                    /* bytes 8 to 15 */
  StrikeExpiryDate strike_expiry_date;  /* bytes 16 to 27 */
  uint8_t deltas;                       /* byte 28 */
  uint8_t call_or_put;                  /* byte 29 */
} StrikeData;

/* any Strike Data at all: every byte one the checker chooses */
static void any_strike_data(StrikeData *record) {
  for (size_t i = 0; i < 4; i++) { record->strike_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->contract_date_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike[i] = arbitrary(); }
  any_strike_expiry_date(&record->strike_expiry_date);
  record->deltas = arbitrary();
  record->call_or_put = arbitrary();
}

/* Strike Data to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_strike_data(const StrikeData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->contract_date_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike[i]; }
  at = encode_strike_expiry_date(&record->strike_expiry_date, wire, at);
  wire[at++] = record->deltas;
  wire[at++] = record->call_or_put;

  return at;
}

/* Strike Data off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_strike_data(StrikeData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->strike_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->contract_date_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike[i] = wire[at++]; }
  at = decode_strike_expiry_date(&record->strike_expiry_date, wire, at);
  record->deltas = wire[at++];
  record->call_or_put = wire[at++];

  return at;
}

/* what was read of Strike Data is what was written, byte for byte */
static void equal_strike_data(const StrikeData *read, const StrikeData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->strike_sequence_number[i] == written->strike_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->contract_date_sequence[i] == written->contract_date_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike[i] == written->strike[i]); }
  equal_strike_expiry_date(&read->strike_expiry_date, &written->strike_expiry_date);
  assert(read->deltas == written->deltas);
  assert(read->call_or_put == written->call_or_put);
}

/* Strike Data: written and read back, then read and written back */
static void check_strike_data(void) {
  StrikeData sent;
  StrikeData got;
  uint8_t wire[30];
  uint8_t again[30];

  any_strike_data(&sent);
  assert(encode_strike_data(&sent, wire, 0) == 30);
  assert(decode_strike_data(&got, wire, 0) == 30);
  equal_strike_data(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_strike_data(&got, wire, 0) == 30);
  assert(encode_strike_data(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Code P 5: 5 bytes ------------------------------------------------ */

/* Member code for this member. */
typedef struct {
  uint8_t member_code_p_5_length_byte;    /* byte 0 */
  uint8_t member_code_p_5_characters[4];  /* bytes 1 to 4 */
} MemberCodeP5;

/* any Member Code P 5 at all: every byte one the checker chooses */
static void any_member_code_p5(MemberCodeP5 *record) {
  record->member_code_p_5_length_byte = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member_code_p_5_characters[i] = arbitrary(); }
}

/* Member Code P 5 to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_member_code_p5(const MemberCodeP5 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->member_code_p_5_length_byte;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_code_p_5_characters[i]; }

  return at;
}

/* Member Code P 5 off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_member_code_p5(MemberCodeP5 *record, const uint8_t *wire, size_t at) {
  record->member_code_p_5_length_byte = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member_code_p_5_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Member Code P 5 is what was written, byte for byte */
static void equal_member_code_p5(const MemberCodeP5 *read, const MemberCodeP5 *written) {
  assert(read->member_code_p_5_length_byte == written->member_code_p_5_length_byte);
  for (size_t i = 0; i < 4; i++) { assert(read->member_code_p_5_characters[i] == written->member_code_p_5_characters[i]); }
}

/* Member Code P 5: written and read back, then read and written back */
static void check_member_code_p5(void) {
  MemberCodeP5 sent;
  MemberCodeP5 got;
  uint8_t wire[5];
  uint8_t again[5];

  any_member_code_p5(&sent);
  assert(encode_member_code_p5(&sent, wire, 0) == 5);
  assert(decode_member_code_p5(&got, wire, 0) == 5);
  equal_member_code_p5(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_member_code_p5(&got, wire, 0) == 5);
  assert(encode_member_code_p5(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Description P 50: 50 bytes ---------------------------------------------- */

/* Name or Description of this member. */
typedef struct {
  uint8_t description_p_50_length_byte;     /* byte 0 */
  uint8_t description_p_50_characters[49];  /* bytes 1 to 49 */
} DescriptionP50;

/* any Description P 50 at all: every byte one the checker chooses */
static void any_description_p50(DescriptionP50 *record) {
  record->description_p_50_length_byte = arbitrary();
  for (size_t i = 0; i < 49; i++) { record->description_p_50_characters[i] = arbitrary(); }
}

/* Description P 50 to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_description_p50(const DescriptionP50 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->description_p_50_length_byte;
  for (size_t i = 0; i < 49; i++) { wire[at++] = record->description_p_50_characters[i]; }

  return at;
}

/* Description P 50 off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_description_p50(DescriptionP50 *record, const uint8_t *wire, size_t at) {
  record->description_p_50_length_byte = wire[at++];
  for (size_t i = 0; i < 49; i++) { record->description_p_50_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Description P 50 is what was written, byte for byte */
static void equal_description_p50(const DescriptionP50 *read, const DescriptionP50 *written) {
  assert(read->description_p_50_length_byte == written->description_p_50_length_byte);
  for (size_t i = 0; i < 49; i++) { assert(read->description_p_50_characters[i] == written->description_p_50_characters[i]); }
}

/* Description P 50: written and read back, then read and written back */
static void check_description_p50(void) {
  DescriptionP50 sent;
  DescriptionP50 got;
  uint8_t wire[50];
  uint8_t again[50];

  any_description_p50(&sent);
  assert(encode_description_p50(&sent, wire, 0) == 50);
  assert(decode_description_p50(&got, wire, 0) == 50);
  equal_description_p50(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_description_p50(&got, wire, 0) == 50);
  assert(encode_description_p50(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sor Account: 17 bytes --------------------------------------------------- */

/* SOR Account Number for the Member. */
typedef struct {
  uint8_t sor_account_length_byte;     /* byte 0 */
  uint8_t sor_account_characters[16];  /* bytes 1 to 16 */
} SorAccount;

/* any Sor Account at all: every byte one the checker chooses */
static void any_sor_account(SorAccount *record) {
  record->sor_account_length_byte = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->sor_account_characters[i] = arbitrary(); }
}

/* Sor Account to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_sor_account(const SorAccount *record, uint8_t *wire, size_t at) {
  wire[at++] = record->sor_account_length_byte;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->sor_account_characters[i]; }

  return at;
}

/* Sor Account off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_sor_account(SorAccount *record, const uint8_t *wire, size_t at) {
  record->sor_account_length_byte = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->sor_account_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Sor Account is what was written, byte for byte */
static void equal_sor_account(const SorAccount *read, const SorAccount *written) {
  assert(read->sor_account_length_byte == written->sor_account_length_byte);
  for (size_t i = 0; i < 16; i++) { assert(read->sor_account_characters[i] == written->sor_account_characters[i]); }
}

/* Sor Account: written and read back, then read and written back */
static void check_sor_account(void) {
  SorAccount sent;
  SorAccount got;
  uint8_t wire[17];
  uint8_t again[17];

  any_sor_account(&sent);
  assert(encode_sor_account(&sent, wire, 0) == 17);
  assert(decode_sor_account(&got, wire, 0) == 17);
  equal_sor_account(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_sor_account(&got, wire, 0) == 17);
  assert(encode_sor_account(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Member Data: 96 bytes --------------------------------------------------- */

/* Member Data */
typedef struct {
  uint8_t member_sequence[4];           /* bytes 0 to 3 */
  uint8_t master_member_sequence[4];    /* bytes 4 to 7 */
  uint8_t clearing_member_sequence[4];  /* bytes 8 to 11 */
  MemberCodeP5 member_code_p_5;         /* bytes 12 to 16 */
  DescriptionP50 description_p_50;      /* bytes 17 to 66 */
  uint8_t unused_4[4];                  /* bytes 67 to 70 */
  SorAccount sor_account;               /* bytes 71 to 87 */
  uint8_t unused_8[8];                  /* bytes 88 to 95 */
} MemberData;

/* any Member Data at all: every byte one the checker chooses */
static void any_member_data(MemberData *record) {
  for (size_t i = 0; i < 4; i++) { record->member_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->master_member_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_member_sequence[i] = arbitrary(); }
  any_member_code_p5(&record->member_code_p_5);
  any_description_p50(&record->description_p_50);
  for (size_t i = 0; i < 4; i++) { record->unused_4[i] = arbitrary(); }
  any_sor_account(&record->sor_account);
  for (size_t i = 0; i < 8; i++) { record->unused_8[i] = arbitrary(); }
}

/* Member Data to the wire: 96 bytes from at, returning where the next byte goes */
static size_t encode_member_data(const MemberData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->master_member_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_member_sequence[i]; }
  at = encode_member_code_p5(&record->member_code_p_5, wire, at);
  at = encode_description_p50(&record->description_p_50, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unused_4[i]; }
  at = encode_sor_account(&record->sor_account, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->unused_8[i]; }

  return at;
}

/* Member Data off the wire: 96 bytes from at, returning where the next byte lies */
static size_t decode_member_data(MemberData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->member_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->master_member_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_member_sequence[i] = wire[at++]; }
  at = decode_member_code_p5(&record->member_code_p_5, wire, at);
  at = decode_description_p50(&record->description_p_50, wire, at);
  for (size_t i = 0; i < 4; i++) { record->unused_4[i] = wire[at++]; }
  at = decode_sor_account(&record->sor_account, wire, at);
  for (size_t i = 0; i < 8; i++) { record->unused_8[i] = wire[at++]; }

  return at;
}

/* what was read of Member Data is what was written, byte for byte */
static void equal_member_data(const MemberData *read, const MemberData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->member_sequence[i] == written->member_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->master_member_sequence[i] == written->master_member_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_member_sequence[i] == written->clearing_member_sequence[i]); }
  equal_member_code_p5(&read->member_code_p_5, &written->member_code_p_5);
  equal_description_p50(&read->description_p_50, &written->description_p_50);
  for (size_t i = 0; i < 4; i++) { assert(read->unused_4[i] == written->unused_4[i]); }
  equal_sor_account(&read->sor_account, &written->sor_account);
  for (size_t i = 0; i < 8; i++) { assert(read->unused_8[i] == written->unused_8[i]); }
}

/* Member Data: written and read back, then read and written back */
static void check_member_data(void) {
  MemberData sent;
  MemberData got;
  uint8_t wire[96];
  uint8_t again[96];

  any_member_data(&sent);
  assert(encode_member_data(&sent, wire, 0) == 96);
  assert(decode_member_data(&got, wire, 0) == 96);
  equal_member_data(&got, &sent);

  for (size_t i = 0; i < 96; i++) { wire[i] = arbitrary(); }
  assert(decode_member_data(&got, wire, 0) == 96);
  assert(encode_member_data(&got, again, 0) == 96);
  for (size_t i = 0; i < 96; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mtm Data: 160 bytes ----------------------------------------------------- */

/* MTM Data */
typedef struct {
  uint8_t instrument_sequence[4];   /* bytes 0 to 3 */
  uint8_t date_sequence[4];         /* bytes 4 to 7 */
  uint8_t strike_sequence[4];       /* bytes 8 to 11 */
  Contract contract;                /* bytes 12 to 59 */
  uint8_t days_closing_price[8];    /* bytes 60 to 67 */
  uint8_t days_closing_rate[8];     /* bytes 68 to 75 */
  uint8_t open_interest[8];         /* bytes 76 to 83 */
  Date date;                        /* bytes 84 to 95 */
  uint8_t spot_price[8];            /* bytes 96 to 103 */
  uint8_t volatility[8];            /* bytes 104 to 111 */
  uint8_t high_price[8];            /* bytes 112 to 119 */
  uint8_t low_price[8];             /* bytes 120 to 127 */
  uint8_t days_volume_d_8[8];       /* bytes 128 to 135 */
  uint8_t shares_in_issue[8];       /* bytes 136 to 143 */
  uint8_t open_price[8];            /* bytes 144 to 151 */
  uint8_t previous_close_price[8];  /* bytes 152 to 159 */
} MtmData;

/* any Mtm Data at all: every byte one the checker chooses */
static void any_mtm_data(MtmData *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->date_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_sequence[i] = arbitrary(); }
  any_contract(&record->contract);
  for (size_t i = 0; i < 8; i++) { record->days_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->days_closing_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
  any_date(&record->date);
  for (size_t i = 0; i < 8; i++) { record->spot_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->days_volume_d_8[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->shares_in_issue[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_close_price[i] = arbitrary(); }
}

/* Mtm Data to the wire: 160 bytes from at, returning where the next byte goes */
static size_t encode_mtm_data(const MtmData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_sequence[i]; }
  at = encode_contract(&record->contract, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->days_closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->days_closing_rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }
  at = encode_date(&record->date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->spot_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volatility[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->days_volume_d_8[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->shares_in_issue[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_close_price[i]; }

  return at;
}

/* Mtm Data off the wire: 160 bytes from at, returning where the next byte lies */
static size_t decode_mtm_data(MtmData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->date_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_sequence[i] = wire[at++]; }
  at = decode_contract(&record->contract, wire, at);
  for (size_t i = 0; i < 8; i++) { record->days_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->days_closing_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }
  at = decode_date(&record->date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->spot_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volatility[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->days_volume_d_8[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->shares_in_issue[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_close_price[i] = wire[at++]; }

  return at;
}

/* what was read of Mtm Data is what was written, byte for byte */
static void equal_mtm_data(const MtmData *read, const MtmData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_sequence[i] == written->instrument_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->date_sequence[i] == written->date_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_sequence[i] == written->strike_sequence[i]); }
  equal_contract(&read->contract, &written->contract);
  for (size_t i = 0; i < 8; i++) { assert(read->days_closing_price[i] == written->days_closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->days_closing_rate[i] == written->days_closing_rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  equal_date(&read->date, &written->date);
  for (size_t i = 0; i < 8; i++) { assert(read->spot_price[i] == written->spot_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volatility[i] == written->volatility[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->days_volume_d_8[i] == written->days_volume_d_8[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->shares_in_issue[i] == written->shares_in_issue[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_close_price[i] == written->previous_close_price[i]); }
}

/* Mtm Data: written and read back, then read and written back */
static void check_mtm_data(void) {
  MtmData sent;
  MtmData got;
  uint8_t wire[160];
  uint8_t again[160];

  any_mtm_data(&sent);
  assert(encode_mtm_data(&sent, wire, 0) == 160);
  assert(decode_mtm_data(&got, wire, 0) == 160);
  equal_mtm_data(&got, &sent);

  for (size_t i = 0; i < 160; i++) { wire[i] = arbitrary(); }
  assert(decode_mtm_data(&got, wire, 0) == 160);
  assert(encode_mtm_data(&got, again, 0) == 160);
  for (size_t i = 0; i < 160; i++) { assert(again[i] == wire[i]); }
}

/* ---- Holiday Date: 12 bytes -------------------------------------------------- */

/* Holiday Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} HolidayDate;

/* any Holiday Date at all: every byte one the checker chooses */
static void any_holiday_date(HolidayDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Holiday Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_holiday_date(const HolidayDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Holiday Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_holiday_date(HolidayDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Holiday Date is what was written, byte for byte */
static void equal_holiday_date(const HolidayDate *read, const HolidayDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Holiday Date: written and read back, then read and written back */
static void check_holiday_date(void) {
  HolidayDate sent;
  HolidayDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_holiday_date(&sent);
  assert(encode_holiday_date(&sent, wire, 0) == 12);
  assert(decode_holiday_date(&got, wire, 0) == 12);
  equal_holiday_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_holiday_date(&got, wire, 0) == 12);
  assert(encode_holiday_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Holiday Data: 23 bytes -------------------------------------------------- */

/* Holiday Data */
typedef struct {
  uint8_t holiday_sequence[4];   /* bytes 0 to 3 */
  CountryCode country_code;      /* bytes 4 to 7 */
  HolidayDate holiday_date;      /* bytes 8 to 19 */
  uint8_t reminder_only;         /* byte 20 */
  uint8_t is_early_close;        /* byte 21 */
  uint8_t is_futures_close_out;  /* byte 22 */
} HolidayData;

/* any Holiday Data at all: every byte one the checker chooses */
static void any_holiday_data(HolidayData *record) {
  for (size_t i = 0; i < 4; i++) { record->holiday_sequence[i] = arbitrary(); }
  any_country_code(&record->country_code);
  any_holiday_date(&record->holiday_date);
  record->reminder_only = arbitrary();
  record->is_early_close = arbitrary();
  record->is_futures_close_out = arbitrary();
}

/* Holiday Data to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_holiday_data(const HolidayData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->holiday_sequence[i]; }
  at = encode_country_code(&record->country_code, wire, at);
  at = encode_holiday_date(&record->holiday_date, wire, at);
  wire[at++] = record->reminder_only;
  wire[at++] = record->is_early_close;
  wire[at++] = record->is_futures_close_out;

  return at;
}

/* Holiday Data off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_holiday_data(HolidayData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->holiday_sequence[i] = wire[at++]; }
  at = decode_country_code(&record->country_code, wire, at);
  at = decode_holiday_date(&record->holiday_date, wire, at);
  record->reminder_only = wire[at++];
  record->is_early_close = wire[at++];
  record->is_futures_close_out = wire[at++];

  return at;
}

/* what was read of Holiday Data is what was written, byte for byte */
static void equal_holiday_data(const HolidayData *read, const HolidayData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->holiday_sequence[i] == written->holiday_sequence[i]); }
  equal_country_code(&read->country_code, &written->country_code);
  equal_holiday_date(&read->holiday_date, &written->holiday_date);
  assert(read->reminder_only == written->reminder_only);
  assert(read->is_early_close == written->is_early_close);
  assert(read->is_futures_close_out == written->is_futures_close_out);
}

/* Holiday Data: written and read back, then read and written back */
static void check_holiday_data(void) {
  HolidayData sent;
  HolidayData got;
  uint8_t wire[23];
  uint8_t again[23];

  any_holiday_data(&sent);
  assert(encode_holiday_data(&sent, wire, 0) == 23);
  assert(decode_holiday_data(&got, wire, 0) == 23);
  equal_holiday_data(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_holiday_data(&got, wire, 0) == 23);
  assert(encode_holiday_data(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Type Code: 10 bytes ------------------------------------------ */

/* Indicates the instrument type code. */
typedef struct {
  uint8_t instrument_type_code_length_byte;    /* byte 0 */
  uint8_t instrument_type_code_characters[9];  /* bytes 1 to 9 */
} InstrumentTypeCode;

/* any Instrument Type Code at all: every byte one the checker chooses */
static void any_instrument_type_code(InstrumentTypeCode *record) {
  record->instrument_type_code_length_byte = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->instrument_type_code_characters[i] = arbitrary(); }
}

/* Instrument Type Code to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_instrument_type_code(const InstrumentTypeCode *record, uint8_t *wire, size_t at) {
  wire[at++] = record->instrument_type_code_length_byte;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->instrument_type_code_characters[i]; }

  return at;
}

/* Instrument Type Code off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_instrument_type_code(InstrumentTypeCode *record, const uint8_t *wire, size_t at) {
  record->instrument_type_code_length_byte = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->instrument_type_code_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Type Code is what was written, byte for byte */
static void equal_instrument_type_code(const InstrumentTypeCode *read, const InstrumentTypeCode *written) {
  assert(read->instrument_type_code_length_byte == written->instrument_type_code_length_byte);
  for (size_t i = 0; i < 9; i++) { assert(read->instrument_type_code_characters[i] == written->instrument_type_code_characters[i]); }
}

/* Instrument Type Code: written and read back, then read and written back */
static void check_instrument_type_code(void) {
  InstrumentTypeCode sent;
  InstrumentTypeCode got;
  uint8_t wire[10];
  uint8_t again[10];

  any_instrument_type_code(&sent);
  assert(encode_instrument_type_code(&sent, wire, 0) == 10);
  assert(decode_instrument_type_code(&got, wire, 0) == 10);
  equal_instrument_type_code(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_type_code(&got, wire, 0) == 10);
  assert(encode_instrument_type_code(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Type Name: 25 bytes ------------------------------------------ */

/* A description of the instrument type. */
typedef struct {
  uint8_t instrument_type_name_length_byte;     /* byte 0 */
  uint8_t instrument_type_name_characters[24];  /* bytes 1 to 24 */
} InstrumentTypeName;

/* any Instrument Type Name at all: every byte one the checker chooses */
static void any_instrument_type_name(InstrumentTypeName *record) {
  record->instrument_type_name_length_byte = arbitrary();
  for (size_t i = 0; i < 24; i++) { record->instrument_type_name_characters[i] = arbitrary(); }
}

/* Instrument Type Name to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_instrument_type_name(const InstrumentTypeName *record, uint8_t *wire, size_t at) {
  wire[at++] = record->instrument_type_name_length_byte;
  for (size_t i = 0; i < 24; i++) { wire[at++] = record->instrument_type_name_characters[i]; }

  return at;
}

/* Instrument Type Name off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_instrument_type_name(InstrumentTypeName *record, const uint8_t *wire, size_t at) {
  record->instrument_type_name_length_byte = wire[at++];
  for (size_t i = 0; i < 24; i++) { record->instrument_type_name_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Instrument Type Name is what was written, byte for byte */
static void equal_instrument_type_name(const InstrumentTypeName *read, const InstrumentTypeName *written) {
  assert(read->instrument_type_name_length_byte == written->instrument_type_name_length_byte);
  for (size_t i = 0; i < 24; i++) { assert(read->instrument_type_name_characters[i] == written->instrument_type_name_characters[i]); }
}

/* Instrument Type Name: written and read back, then read and written back */
static void check_instrument_type_name(void) {
  InstrumentTypeName sent;
  InstrumentTypeName got;
  uint8_t wire[25];
  uint8_t again[25];

  any_instrument_type_name(&sent);
  assert(encode_instrument_type_name(&sent, wire, 0) == 25);
  assert(decode_instrument_type_name(&got, wire, 0) == 25);
  equal_instrument_type_name(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_type_name(&got, wire, 0) == 25);
  assert(encode_instrument_type_name(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Instrument Types: 48 bytes ---------------------------------------------- */

/* Instrument Types */
typedef struct {
  uint8_t instrument_type_sequence[4];      /* bytes 0 to 3 */
  uint8_t unused_4[4];                      /* bytes 4 to 7 */
  uint8_t instrument_type_number_i_4[4];    /* bytes 8 to 11 */
  uint8_t identifier_prefix_c_1;            /* byte 12 */
  InstrumentTypeCode instrument_type_code;  /* bytes 13 to 22 */
  InstrumentTypeName instrument_type_name;  /* bytes 23 to 47 */
} InstrumentTypes;

/* any Instrument Types at all: every byte one the checker chooses */
static void any_instrument_types(InstrumentTypes *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_type_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->unused_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_type_number_i_4[i] = arbitrary(); }
  record->identifier_prefix_c_1 = arbitrary();
  any_instrument_type_code(&record->instrument_type_code);
  any_instrument_type_name(&record->instrument_type_name);
}

/* Instrument Types to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_instrument_types(const InstrumentTypes *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_type_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unused_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_type_number_i_4[i]; }
  wire[at++] = record->identifier_prefix_c_1;
  at = encode_instrument_type_code(&record->instrument_type_code, wire, at);
  at = encode_instrument_type_name(&record->instrument_type_name, wire, at);

  return at;
}

/* Instrument Types off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_instrument_types(InstrumentTypes *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_type_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->unused_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_type_number_i_4[i] = wire[at++]; }
  record->identifier_prefix_c_1 = wire[at++];
  at = decode_instrument_type_code(&record->instrument_type_code, wire, at);
  at = decode_instrument_type_name(&record->instrument_type_name, wire, at);

  return at;
}

/* what was read of Instrument Types is what was written, byte for byte */
static void equal_instrument_types(const InstrumentTypes *read, const InstrumentTypes *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_type_sequence[i] == written->instrument_type_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->unused_4[i] == written->unused_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_type_number_i_4[i] == written->instrument_type_number_i_4[i]); }
  assert(read->identifier_prefix_c_1 == written->identifier_prefix_c_1);
  equal_instrument_type_code(&read->instrument_type_code, &written->instrument_type_code);
  equal_instrument_type_name(&read->instrument_type_name, &written->instrument_type_name);
}

/* Instrument Types: written and read back, then read and written back */
static void check_instrument_types(void) {
  InstrumentTypes sent;
  InstrumentTypes got;
  uint8_t wire[48];
  uint8_t again[48];

  any_instrument_types(&sent);
  assert(encode_instrument_types(&sent, wire, 0) == 48);
  assert(decode_instrument_types(&got, wire, 0) == 48);
  equal_instrument_types(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_instrument_types(&got, wire, 0) == 48);
  assert(encode_instrument_types(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Member Code: 6 bytes ------------------------------------------- */

/* This is the code used for the clearing member. */
typedef struct {
  uint8_t clearing_member_code_length_byte;    /* byte 0 */
  uint8_t clearing_member_code_characters[5];  /* bytes 1 to 5 */
} ClearingMemberCode;

/* any Clearing Member Code at all: every byte one the checker chooses */
static void any_clearing_member_code(ClearingMemberCode *record) {
  record->clearing_member_code_length_byte = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->clearing_member_code_characters[i] = arbitrary(); }
}

/* Clearing Member Code to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_clearing_member_code(const ClearingMemberCode *record, uint8_t *wire, size_t at) {
  wire[at++] = record->clearing_member_code_length_byte;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->clearing_member_code_characters[i]; }

  return at;
}

/* Clearing Member Code off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_clearing_member_code(ClearingMemberCode *record, const uint8_t *wire, size_t at) {
  record->clearing_member_code_length_byte = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->clearing_member_code_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Member Code is what was written, byte for byte */
static void equal_clearing_member_code(const ClearingMemberCode *read, const ClearingMemberCode *written) {
  assert(read->clearing_member_code_length_byte == written->clearing_member_code_length_byte);
  for (size_t i = 0; i < 5; i++) { assert(read->clearing_member_code_characters[i] == written->clearing_member_code_characters[i]); }
}

/* Clearing Member Code: written and read back, then read and written back */
static void check_clearing_member_code(void) {
  ClearingMemberCode sent;
  ClearingMemberCode got;
  uint8_t wire[6];
  uint8_t again[6];

  any_clearing_member_code(&sent);
  assert(encode_clearing_member_code(&sent, wire, 0) == 6);
  assert(decode_clearing_member_code(&got, wire, 0) == 6);
  equal_clearing_member_code(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_member_code(&got, wire, 0) == 6);
  assert(encode_clearing_member_code(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Member Description: 50 bytes ----------------------------------- */

/* This is the Description of the clearing member. */
typedef struct {
  uint8_t clearing_member_description_length_byte;     /* byte 0 */
  uint8_t clearing_member_description_characters[49];  /* bytes 1 to 49 */
} ClearingMemberDescription;

/* any Clearing Member Description at all: every byte one the checker chooses */
static void any_clearing_member_description(ClearingMemberDescription *record) {
  record->clearing_member_description_length_byte = arbitrary();
  for (size_t i = 0; i < 49; i++) { record->clearing_member_description_characters[i] = arbitrary(); }
}

/* Clearing Member Description to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_clearing_member_description(const ClearingMemberDescription *record, uint8_t *wire, size_t at) {
  wire[at++] = record->clearing_member_description_length_byte;
  for (size_t i = 0; i < 49; i++) { wire[at++] = record->clearing_member_description_characters[i]; }

  return at;
}

/* Clearing Member Description off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_clearing_member_description(ClearingMemberDescription *record, const uint8_t *wire, size_t at) {
  record->clearing_member_description_length_byte = wire[at++];
  for (size_t i = 0; i < 49; i++) { record->clearing_member_description_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Clearing Member Description is what was written, byte for byte */
static void equal_clearing_member_description(const ClearingMemberDescription *read, const ClearingMemberDescription *written) {
  assert(read->clearing_member_description_length_byte == written->clearing_member_description_length_byte);
  for (size_t i = 0; i < 49; i++) { assert(read->clearing_member_description_characters[i] == written->clearing_member_description_characters[i]); }
}

/* Clearing Member Description: written and read back, then read and written back */
static void check_clearing_member_description(void) {
  ClearingMemberDescription sent;
  ClearingMemberDescription got;
  uint8_t wire[50];
  uint8_t again[50];

  any_clearing_member_description(&sent);
  assert(encode_clearing_member_description(&sent, wire, 0) == 50);
  assert(decode_clearing_member_description(&got, wire, 0) == 50);
  equal_clearing_member_description(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_member_description(&got, wire, 0) == 50);
  assert(encode_clearing_member_description(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Clearing Member Data: 60 bytes ------------------------------------------ */

/* Clearing Member Data */
typedef struct {
  uint8_t clearing_member_sequence[4];                    /* bytes 0 to 3 */
  ClearingMemberCode clearing_member_code;                /* bytes 4 to 9 */
  ClearingMemberDescription clearing_member_description;  /* bytes 10 to 59 */
} ClearingMemberData;

/* any Clearing Member Data at all: every byte one the checker chooses */
static void any_clearing_member_data(ClearingMemberData *record) {
  for (size_t i = 0; i < 4; i++) { record->clearing_member_sequence[i] = arbitrary(); }
  any_clearing_member_code(&record->clearing_member_code);
  any_clearing_member_description(&record->clearing_member_description);
}

/* Clearing Member Data to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_clearing_member_data(const ClearingMemberData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_member_sequence[i]; }
  at = encode_clearing_member_code(&record->clearing_member_code, wire, at);
  at = encode_clearing_member_description(&record->clearing_member_description, wire, at);

  return at;
}

/* Clearing Member Data off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_clearing_member_data(ClearingMemberData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->clearing_member_sequence[i] = wire[at++]; }
  at = decode_clearing_member_code(&record->clearing_member_code, wire, at);
  at = decode_clearing_member_description(&record->clearing_member_description, wire, at);

  return at;
}

/* what was read of Clearing Member Data is what was written, byte for byte */
static void equal_clearing_member_data(const ClearingMemberData *read, const ClearingMemberData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_member_sequence[i] == written->clearing_member_sequence[i]); }
  equal_clearing_member_code(&read->clearing_member_code, &written->clearing_member_code);
  equal_clearing_member_description(&read->clearing_member_description, &written->clearing_member_description);
}

/* Clearing Member Data: written and read back, then read and written back */
static void check_clearing_member_data(void) {
  ClearingMemberData sent;
  ClearingMemberData got;
  uint8_t wire[60];
  uint8_t again[60];

  any_clearing_member_data(&sent);
  assert(encode_clearing_member_data(&sent, wire, 0) == 60);
  assert(decode_clearing_member_data(&got, wire, 0) == 60);
  equal_clearing_member_data(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_clearing_member_data(&got, wire, 0) == 60);
  assert(encode_clearing_member_data(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Announcement Date: 12 bytes --------------------------------------------- */

/* Announcement Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} AnnouncementDate;

/* any Announcement Date at all: every byte one the checker chooses */
static void any_announcement_date(AnnouncementDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Announcement Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_announcement_date(const AnnouncementDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Announcement Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_announcement_date(AnnouncementDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Announcement Date is what was written, byte for byte */
static void equal_announcement_date(const AnnouncementDate *read, const AnnouncementDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Announcement Date: written and read back, then read and written back */
static void check_announcement_date(void) {
  AnnouncementDate sent;
  AnnouncementDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_announcement_date(&sent);
  assert(encode_announcement_date(&sent, wire, 0) == 12);
  assert(decode_announcement_date(&got, wire, 0) == 12);
  equal_announcement_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_announcement_date(&got, wire, 0) == 12);
  assert(encode_announcement_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Announcement Time: 4 bytes ---------------------------------------------- */

/* Announcement Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} AnnouncementTime;

/* any Announcement Time at all: every byte one the checker chooses */
static void any_announcement_time(AnnouncementTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Announcement Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_announcement_time(const AnnouncementTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Announcement Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_announcement_time(AnnouncementTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Announcement Time is what was written, byte for byte */
static void equal_announcement_time(const AnnouncementTime *read, const AnnouncementTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Announcement Time: written and read back, then read and written back */
static void check_announcement_time(void) {
  AnnouncementTime sent;
  AnnouncementTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_announcement_time(&sent);
  assert(encode_announcement_time(&sent, wire, 0) == 4);
  assert(decode_announcement_time(&got, wire, 0) == 4);
  equal_announcement_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_announcement_time(&got, wire, 0) == 4);
  assert(encode_announcement_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Announcement: 255 bytes ------------------------------------------------- */

/* Announcement as sent by the exchange. */
typedef struct {
  uint8_t announcement_length_byte;      /* byte 0 */
  uint8_t announcement_characters[254];  /* bytes 1 to 254 */
} Announcement;

/* any Announcement at all: every byte one the checker chooses */
static void any_announcement(Announcement *record) {
  record->announcement_length_byte = arbitrary();
  for (size_t i = 0; i < 254; i++) { record->announcement_characters[i] = arbitrary(); }
}

/* Announcement to the wire: 255 bytes from at, returning where the next byte goes */
static size_t encode_announcement(const Announcement *record, uint8_t *wire, size_t at) {
  wire[at++] = record->announcement_length_byte;
  for (size_t i = 0; i < 254; i++) { wire[at++] = record->announcement_characters[i]; }

  return at;
}

/* Announcement off the wire: 255 bytes from at, returning where the next byte lies */
static size_t decode_announcement(Announcement *record, const uint8_t *wire, size_t at) {
  record->announcement_length_byte = wire[at++];
  for (size_t i = 0; i < 254; i++) { record->announcement_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Announcement is what was written, byte for byte */
static void equal_announcement(const Announcement *read, const Announcement *written) {
  assert(read->announcement_length_byte == written->announcement_length_byte);
  for (size_t i = 0; i < 254; i++) { assert(read->announcement_characters[i] == written->announcement_characters[i]); }
}

/* Announcement: written and read back, then read and written back */
static void check_announcement(void) {
  Announcement sent;
  Announcement got;
  uint8_t wire[255];
  uint8_t again[255];

  any_announcement(&sent);
  assert(encode_announcement(&sent, wire, 0) == 255);
  assert(decode_announcement(&got, wire, 0) == 255);
  equal_announcement(&got, &sent);

  for (size_t i = 0; i < 255; i++) { wire[i] = arbitrary(); }
  assert(decode_announcement(&got, wire, 0) == 255);
  assert(encode_announcement(&got, again, 0) == 255);
  for (size_t i = 0; i < 255; i++) { assert(again[i] == wire[i]); }
}

/* ---- Exchange Announcements: 279 bytes --------------------------------------- */

/* Exchange Announcements */
typedef struct {
  uint8_t id_market[4];                /* bytes 0 to 3 */
  uint8_t announcement_sequence[4];    /* bytes 4 to 7 */
  AnnouncementDate announcement_date;  /* bytes 8 to 19 */
  AnnouncementTime announcement_time;  /* bytes 20 to 23 */
  Announcement announcement;           /* bytes 24 to 278 */
} ExchangeAnnouncements;

/* any Exchange Announcements at all: every byte one the checker chooses */
static void any_exchange_announcements(ExchangeAnnouncements *record) {
  for (size_t i = 0; i < 4; i++) { record->id_market[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->announcement_sequence[i] = arbitrary(); }
  any_announcement_date(&record->announcement_date);
  any_announcement_time(&record->announcement_time);
  any_announcement(&record->announcement);
}

/* Exchange Announcements to the wire: 279 bytes from at, returning where the next byte goes */
static size_t encode_exchange_announcements(const ExchangeAnnouncements *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->id_market[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->announcement_sequence[i]; }
  at = encode_announcement_date(&record->announcement_date, wire, at);
  at = encode_announcement_time(&record->announcement_time, wire, at);
  at = encode_announcement(&record->announcement, wire, at);

  return at;
}

/* Exchange Announcements off the wire: 279 bytes from at, returning where the next byte lies */
static size_t decode_exchange_announcements(ExchangeAnnouncements *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->id_market[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->announcement_sequence[i] = wire[at++]; }
  at = decode_announcement_date(&record->announcement_date, wire, at);
  at = decode_announcement_time(&record->announcement_time, wire, at);
  at = decode_announcement(&record->announcement, wire, at);

  return at;
}

/* what was read of Exchange Announcements is what was written, byte for byte */
static void equal_exchange_announcements(const ExchangeAnnouncements *read, const ExchangeAnnouncements *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->id_market[i] == written->id_market[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->announcement_sequence[i] == written->announcement_sequence[i]); }
  equal_announcement_date(&read->announcement_date, &written->announcement_date);
  equal_announcement_time(&read->announcement_time, &written->announcement_time);
  equal_announcement(&read->announcement, &written->announcement);
}

/* Exchange Announcements: written and read back, then read and written back */
static void check_exchange_announcements(void) {
  ExchangeAnnouncements sent;
  ExchangeAnnouncements got;
  uint8_t wire[279];
  uint8_t again[279];

  any_exchange_announcements(&sent);
  assert(encode_exchange_announcements(&sent, wire, 0) == 279);
  assert(decode_exchange_announcements(&got, wire, 0) == 279);
  equal_exchange_announcements(&got, &sent);

  for (size_t i = 0; i < 279; i++) { wire[i] = arbitrary(); }
  assert(decode_exchange_announcements(&got, wire, 0) == 279);
  assert(encode_exchange_announcements(&got, again, 0) == 279);
  for (size_t i = 0; i < 279; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Category Value: 50 bytes ---------------------------------------- */

/* Indicates the value which is associated with the category type. */
typedef struct {
  uint8_t message_category_value_length_byte;     /* byte 0 */
  uint8_t message_category_value_characters[49];  /* bytes 1 to 49 */
} MessageCategoryValue;

/* any Message Category Value at all: every byte one the checker chooses */
static void any_message_category_value(MessageCategoryValue *record) {
  record->message_category_value_length_byte = arbitrary();
  for (size_t i = 0; i < 49; i++) { record->message_category_value_characters[i] = arbitrary(); }
}

/* Message Category Value to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_message_category_value(const MessageCategoryValue *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_category_value_length_byte;
  for (size_t i = 0; i < 49; i++) { wire[at++] = record->message_category_value_characters[i]; }

  return at;
}

/* Message Category Value off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_message_category_value(MessageCategoryValue *record, const uint8_t *wire, size_t at) {
  record->message_category_value_length_byte = wire[at++];
  for (size_t i = 0; i < 49; i++) { record->message_category_value_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Message Category Value is what was written, byte for byte */
static void equal_message_category_value(const MessageCategoryValue *read, const MessageCategoryValue *written) {
  assert(read->message_category_value_length_byte == written->message_category_value_length_byte);
  for (size_t i = 0; i < 49; i++) { assert(read->message_category_value_characters[i] == written->message_category_value_characters[i]); }
}

/* Message Category Value: written and read back, then read and written back */
static void check_message_category_value(void) {
  MessageCategoryValue sent;
  MessageCategoryValue got;
  uint8_t wire[50];
  uint8_t again[50];

  any_message_category_value(&sent);
  assert(encode_message_category_value(&sent, wire, 0) == 50);
  assert(decode_message_category_value(&got, wire, 0) == 50);
  equal_message_category_value(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_message_category_value(&got, wire, 0) == 50);
  assert(encode_message_category_value(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message P 255: 255 bytes ------------------------------------------------ */

/* Indicates the text for this segment of the news message. */
typedef struct {
  uint8_t message_p_255_length_byte;      /* byte 0 */
  uint8_t message_p_255_characters[254];  /* bytes 1 to 254 */
} MessageP255;

/* any Message P 255 at all: every byte one the checker chooses */
static void any_message_p255(MessageP255 *record) {
  record->message_p_255_length_byte = arbitrary();
  for (size_t i = 0; i < 254; i++) { record->message_p_255_characters[i] = arbitrary(); }
}

/* Message P 255 to the wire: 255 bytes from at, returning where the next byte goes */
static size_t encode_message_p255(const MessageP255 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_p_255_length_byte;
  for (size_t i = 0; i < 254; i++) { wire[at++] = record->message_p_255_characters[i]; }

  return at;
}

/* Message P 255 off the wire: 255 bytes from at, returning where the next byte lies */
static size_t decode_message_p255(MessageP255 *record, const uint8_t *wire, size_t at) {
  record->message_p_255_length_byte = wire[at++];
  for (size_t i = 0; i < 254; i++) { record->message_p_255_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Message P 255 is what was written, byte for byte */
static void equal_message_p255(const MessageP255 *read, const MessageP255 *written) {
  assert(read->message_p_255_length_byte == written->message_p_255_length_byte);
  for (size_t i = 0; i < 254; i++) { assert(read->message_p_255_characters[i] == written->message_p_255_characters[i]); }
}

/* Message P 255: written and read back, then read and written back */
static void check_message_p255(void) {
  MessageP255 sent;
  MessageP255 got;
  uint8_t wire[255];
  uint8_t again[255];

  any_message_p255(&sent);
  assert(encode_message_p255(&sent, wire, 0) == 255);
  assert(decode_message_p255(&got, wire, 0) == 255);
  equal_message_p255(&got, &sent);

  for (size_t i = 0; i < 255; i++) { wire[i] = arbitrary(); }
  assert(decode_message_p255(&got, wire, 0) == 255);
  assert(encode_message_p255(&got, again, 0) == 255);
  for (size_t i = 0; i < 255; i++) { assert(again[i] == wire[i]); }
}

/* ---- News Service: 329 bytes ------------------------------------------------- */

/* News Service */
typedef struct {
  Date date;                                    /* bytes 0 to 11 */
  Time time;                                    /* bytes 12 to 15 */
  uint8_t message_category_type[2];             /* bytes 16 to 17 */
  MessageCategoryValue message_category_value;  /* bytes 18 to 67 */
  uint8_t news_number[2];                       /* bytes 68 to 69 */
  uint8_t total_number_of_segments[2];          /* bytes 70 to 71 */
  uint8_t segment_number[2];                    /* bytes 72 to 73 */
  MessageP255 message_p_255;                    /* bytes 74 to 328 */
} NewsService;

/* any News Service at all: every byte one the checker chooses */
static void any_news_service(NewsService *record) {
  any_date(&record->date);
  any_time(&record->time);
  for (size_t i = 0; i < 2; i++) { record->message_category_type[i] = arbitrary(); }
  any_message_category_value(&record->message_category_value);
  for (size_t i = 0; i < 2; i++) { record->news_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->total_number_of_segments[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->segment_number[i] = arbitrary(); }
  any_message_p255(&record->message_p_255);
}

/* News Service to the wire: 329 bytes from at, returning where the next byte goes */
static size_t encode_news_service(const NewsService *record, uint8_t *wire, size_t at) {
  at = encode_date(&record->date, wire, at);
  at = encode_time(&record->time, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_category_type[i]; }
  at = encode_message_category_value(&record->message_category_value, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->news_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->total_number_of_segments[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->segment_number[i]; }
  at = encode_message_p255(&record->message_p_255, wire, at);

  return at;
}

/* News Service off the wire: 329 bytes from at, returning where the next byte lies */
static size_t decode_news_service(NewsService *record, const uint8_t *wire, size_t at) {
  at = decode_date(&record->date, wire, at);
  at = decode_time(&record->time, wire, at);
  for (size_t i = 0; i < 2; i++) { record->message_category_type[i] = wire[at++]; }
  at = decode_message_category_value(&record->message_category_value, wire, at);
  for (size_t i = 0; i < 2; i++) { record->news_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->total_number_of_segments[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->segment_number[i] = wire[at++]; }
  at = decode_message_p255(&record->message_p_255, wire, at);

  return at;
}

/* what was read of News Service is what was written, byte for byte */
static void equal_news_service(const NewsService *read, const NewsService *written) {
  equal_date(&read->date, &written->date);
  equal_time(&read->time, &written->time);
  for (size_t i = 0; i < 2; i++) { assert(read->message_category_type[i] == written->message_category_type[i]); }
  equal_message_category_value(&read->message_category_value, &written->message_category_value);
  for (size_t i = 0; i < 2; i++) { assert(read->news_number[i] == written->news_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->total_number_of_segments[i] == written->total_number_of_segments[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->segment_number[i] == written->segment_number[i]); }
  equal_message_p255(&read->message_p_255, &written->message_p_255);
}

/* News Service: written and read back, then read and written back */
static void check_news_service(void) {
  NewsService sent;
  NewsService got;
  uint8_t wire[329];
  uint8_t again[329];

  any_news_service(&sent);
  assert(encode_news_service(&sent, wire, 0) == 329);
  assert(decode_news_service(&got, wire, 0) == 329);
  equal_news_service(&got, &sent);

  for (size_t i = 0; i < 329; i++) { wire[i] = arbitrary(); }
  assert(decode_news_service(&got, wire, 0) == 329);
  assert(encode_news_service(&got, again, 0) == 329);
  for (size_t i = 0; i < 329; i++) { assert(again[i] == wire[i]); }
}

/* ---- Coupon Date: 12 bytes --------------------------------------------------- */

/* Coupon Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} CouponDate;

/* any Coupon Date at all: every byte one the checker chooses */
static void any_coupon_date(CouponDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Coupon Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_coupon_date(const CouponDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Coupon Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_coupon_date(CouponDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Coupon Date is what was written, byte for byte */
static void equal_coupon_date(const CouponDate *read, const CouponDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Coupon Date: written and read back, then read and written back */
static void check_coupon_date(void) {
  CouponDate sent;
  CouponDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_coupon_date(&sent);
  assert(encode_coupon_date(&sent, wire, 0) == 12);
  assert(decode_coupon_date(&got, wire, 0) == 12);
  equal_coupon_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_coupon_date(&got, wire, 0) == 12);
  assert(encode_coupon_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Books Close Date: 12 bytes ---------------------------------------------- */

/* Books Close Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} BooksCloseDate;

/* any Books Close Date at all: every byte one the checker chooses */
static void any_books_close_date(BooksCloseDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Books Close Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_books_close_date(const BooksCloseDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Books Close Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_books_close_date(BooksCloseDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Books Close Date is what was written, byte for byte */
static void equal_books_close_date(const BooksCloseDate *read, const BooksCloseDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Books Close Date: written and read back, then read and written back */
static void check_books_close_date(void) {
  BooksCloseDate sent;
  BooksCloseDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_books_close_date(&sent);
  assert(encode_books_close_date(&sent, wire, 0) == 12);
  assert(decode_books_close_date(&got, wire, 0) == 12);
  equal_books_close_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_books_close_date(&got, wire, 0) == 12);
  assert(encode_books_close_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Coupon Information: 48 bytes -------------------------------------------- */

/* Coupon Information */
typedef struct {
  uint8_t coupon_sequence[4];       /* bytes 0 to 3 */
  uint8_t instrument_sequence[4];   /* bytes 4 to 7 */
  CouponDate coupon_date;           /* bytes 8 to 19 */
  BooksCloseDate books_close_date;  /* bytes 20 to 31 */
  uint8_t coupon_rate[8];           /* bytes 32 to 39 */
  uint8_t redemption_value[8];      /* bytes 40 to 47 */
} CouponInformation;

/* any Coupon Information at all: every byte one the checker chooses */
static void any_coupon_information(CouponInformation *record) {
  for (size_t i = 0; i < 4; i++) { record->coupon_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = arbitrary(); }
  any_coupon_date(&record->coupon_date);
  any_books_close_date(&record->books_close_date);
  for (size_t i = 0; i < 8; i++) { record->coupon_rate[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->redemption_value[i] = arbitrary(); }
}

/* Coupon Information to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_coupon_information(const CouponInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->coupon_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_sequence[i]; }
  at = encode_coupon_date(&record->coupon_date, wire, at);
  at = encode_books_close_date(&record->books_close_date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->coupon_rate[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->redemption_value[i]; }

  return at;
}

/* Coupon Information off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_coupon_information(CouponInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->coupon_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = wire[at++]; }
  at = decode_coupon_date(&record->coupon_date, wire, at);
  at = decode_books_close_date(&record->books_close_date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->coupon_rate[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->redemption_value[i] = wire[at++]; }

  return at;
}

/* what was read of Coupon Information is what was written, byte for byte */
static void equal_coupon_information(const CouponInformation *read, const CouponInformation *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->coupon_sequence[i] == written->coupon_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_sequence[i] == written->instrument_sequence[i]); }
  equal_coupon_date(&read->coupon_date, &written->coupon_date);
  equal_books_close_date(&read->books_close_date, &written->books_close_date);
  for (size_t i = 0; i < 8; i++) { assert(read->coupon_rate[i] == written->coupon_rate[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->redemption_value[i] == written->redemption_value[i]); }
}

/* Coupon Information: written and read back, then read and written back */
static void check_coupon_information(void) {
  CouponInformation sent;
  CouponInformation got;
  uint8_t wire[48];
  uint8_t again[48];

  any_coupon_information(&sent);
  assert(encode_coupon_information(&sent, wire, 0) == 48);
  assert(decode_coupon_information(&got, wire, 0) == 48);
  equal_coupon_information(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_coupon_information(&got, wire, 0) == 48);
  assert(encode_coupon_information(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Name: 56 bytes ------------------------------------------ */

/* Indicates the name of the trading session. */
typedef struct {
  uint8_t trading_session_name_length_byte;     /* byte 0 */
  uint8_t trading_session_name_characters[55];  /* bytes 1 to 55 */
} TradingSessionName;

/* any Trading Session Name at all: every byte one the checker chooses */
static void any_trading_session_name(TradingSessionName *record) {
  record->trading_session_name_length_byte = arbitrary();
  for (size_t i = 0; i < 55; i++) { record->trading_session_name_characters[i] = arbitrary(); }
}

/* Trading Session Name to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_name(const TradingSessionName *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_session_name_length_byte;
  for (size_t i = 0; i < 55; i++) { wire[at++] = record->trading_session_name_characters[i]; }

  return at;
}

/* Trading Session Name off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_name(TradingSessionName *record, const uint8_t *wire, size_t at) {
  record->trading_session_name_length_byte = wire[at++];
  for (size_t i = 0; i < 55; i++) { record->trading_session_name_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Session Name is what was written, byte for byte */
static void equal_trading_session_name(const TradingSessionName *read, const TradingSessionName *written) {
  assert(read->trading_session_name_length_byte == written->trading_session_name_length_byte);
  for (size_t i = 0; i < 55; i++) { assert(read->trading_session_name_characters[i] == written->trading_session_name_characters[i]); }
}

/* Trading Session Name: written and read back, then read and written back */
static void check_trading_session_name(void) {
  TradingSessionName sent;
  TradingSessionName got;
  uint8_t wire[56];
  uint8_t again[56];

  any_trading_session_name(&sent);
  assert(encode_trading_session_name(&sent, wire, 0) == 56);
  assert(decode_trading_session_name(&got, wire, 0) == 56);
  equal_trading_session_name(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_name(&got, wire, 0) == 56);
  assert(encode_trading_session_name(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Auction Start Time: 4 bytes ------------------------------------- */

/* Opening Auction Start Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} OpeningAuctionStartTime;

/* any Opening Auction Start Time at all: every byte one the checker chooses */
static void any_opening_auction_start_time(OpeningAuctionStartTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Opening Auction Start Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_opening_auction_start_time(const OpeningAuctionStartTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Opening Auction Start Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_opening_auction_start_time(OpeningAuctionStartTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Opening Auction Start Time is what was written, byte for byte */
static void equal_opening_auction_start_time(const OpeningAuctionStartTime *read, const OpeningAuctionStartTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Opening Auction Start Time: written and read back, then read and written back */
static void check_opening_auction_start_time(void) {
  OpeningAuctionStartTime sent;
  OpeningAuctionStartTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_opening_auction_start_time(&sent);
  assert(encode_opening_auction_start_time(&sent, wire, 0) == 4);
  assert(decode_opening_auction_start_time(&got, wire, 0) == 4);
  equal_opening_auction_start_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_auction_start_time(&got, wire, 0) == 4);
  assert(encode_opening_auction_start_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Opening Auction Close Time: 4 bytes ------------------------------------- */

/* Opening Auction Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} OpeningAuctionCloseTime;

/* any Opening Auction Close Time at all: every byte one the checker chooses */
static void any_opening_auction_close_time(OpeningAuctionCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Opening Auction Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_opening_auction_close_time(const OpeningAuctionCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Opening Auction Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_opening_auction_close_time(OpeningAuctionCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Opening Auction Close Time is what was written, byte for byte */
static void equal_opening_auction_close_time(const OpeningAuctionCloseTime *read, const OpeningAuctionCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Opening Auction Close Time: written and read back, then read and written back */
static void check_opening_auction_close_time(void) {
  OpeningAuctionCloseTime sent;
  OpeningAuctionCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_opening_auction_close_time(&sent);
  assert(encode_opening_auction_close_time(&sent, wire, 0) == 4);
  assert(decode_opening_auction_close_time(&got, wire, 0) == 4);
  equal_opening_auction_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_opening_auction_close_time(&got, wire, 0) == 4);
  assert(encode_opening_auction_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Auction Start Time: 4 bytes ------------------------------------- */

/* Closing Auction Start Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} ClosingAuctionStartTime;

/* any Closing Auction Start Time at all: every byte one the checker chooses */
static void any_closing_auction_start_time(ClosingAuctionStartTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Closing Auction Start Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_closing_auction_start_time(const ClosingAuctionStartTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Closing Auction Start Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_closing_auction_start_time(ClosingAuctionStartTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Closing Auction Start Time is what was written, byte for byte */
static void equal_closing_auction_start_time(const ClosingAuctionStartTime *read, const ClosingAuctionStartTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Closing Auction Start Time: written and read back, then read and written back */
static void check_closing_auction_start_time(void) {
  ClosingAuctionStartTime sent;
  ClosingAuctionStartTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_closing_auction_start_time(&sent);
  assert(encode_closing_auction_start_time(&sent, wire, 0) == 4);
  assert(decode_closing_auction_start_time(&got, wire, 0) == 4);
  equal_closing_auction_start_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_auction_start_time(&got, wire, 0) == 4);
  assert(encode_closing_auction_start_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Closing Auction Close Time: 4 bytes ------------------------------------- */

/* Closing Auction Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} ClosingAuctionCloseTime;

/* any Closing Auction Close Time at all: every byte one the checker chooses */
static void any_closing_auction_close_time(ClosingAuctionCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Closing Auction Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_closing_auction_close_time(const ClosingAuctionCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Closing Auction Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_closing_auction_close_time(ClosingAuctionCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Closing Auction Close Time is what was written, byte for byte */
static void equal_closing_auction_close_time(const ClosingAuctionCloseTime *read, const ClosingAuctionCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Closing Auction Close Time: written and read back, then read and written back */
static void check_closing_auction_close_time(void) {
  ClosingAuctionCloseTime sent;
  ClosingAuctionCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_closing_auction_close_time(&sent);
  assert(encode_closing_auction_close_time(&sent, wire, 0) == 4);
  assert(decode_closing_auction_close_time(&got, wire, 0) == 4);
  equal_closing_auction_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_closing_auction_close_time(&got, wire, 0) == 4);
  assert(encode_closing_auction_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contract Open Time: 4 bytes --------------------------------------------- */

/* Contract Open Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} ContractOpenTime;

/* any Contract Open Time at all: every byte one the checker chooses */
static void any_contract_open_time(ContractOpenTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Contract Open Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_contract_open_time(const ContractOpenTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Contract Open Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_contract_open_time(ContractOpenTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Contract Open Time is what was written, byte for byte */
static void equal_contract_open_time(const ContractOpenTime *read, const ContractOpenTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Contract Open Time: written and read back, then read and written back */
static void check_contract_open_time(void) {
  ContractOpenTime sent;
  ContractOpenTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_contract_open_time(&sent);
  assert(encode_contract_open_time(&sent, wire, 0) == 4);
  assert(decode_contract_open_time(&got, wire, 0) == 4);
  equal_contract_open_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_open_time(&got, wire, 0) == 4);
  assert(encode_contract_open_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Contract Close Time: 4 bytes -------------------------------------------- */

/* Contract Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} ContractCloseTime;

/* any Contract Close Time at all: every byte one the checker chooses */
static void any_contract_close_time(ContractCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Contract Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_contract_close_time(const ContractCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Contract Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_contract_close_time(ContractCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Contract Close Time is what was written, byte for byte */
static void equal_contract_close_time(const ContractCloseTime *read, const ContractCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Contract Close Time: written and read back, then read and written back */
static void check_contract_close_time(void) {
  ContractCloseTime sent;
  ContractCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_contract_close_time(&sent);
  assert(encode_contract_close_time(&sent, wire, 0) == 4);
  assert(decode_contract_close_time(&got, wire, 0) == 4);
  equal_contract_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_close_time(&got, wire, 0) == 4);
  assert(encode_contract_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Intraday Auction One Start Time: 4 bytes -------------------------------- */

/* Intraday Auction One Start Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} IntradayAuctionOneStartTime;

/* any Intraday Auction One Start Time at all: every byte one the checker chooses */
static void any_intraday_auction_one_start_time(IntradayAuctionOneStartTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Intraday Auction One Start Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_intraday_auction_one_start_time(const IntradayAuctionOneStartTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Intraday Auction One Start Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_intraday_auction_one_start_time(IntradayAuctionOneStartTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Intraday Auction One Start Time is what was written, byte for byte */
static void equal_intraday_auction_one_start_time(const IntradayAuctionOneStartTime *read, const IntradayAuctionOneStartTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Intraday Auction One Start Time: written and read back, then read and written back */
static void check_intraday_auction_one_start_time(void) {
  IntradayAuctionOneStartTime sent;
  IntradayAuctionOneStartTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_intraday_auction_one_start_time(&sent);
  assert(encode_intraday_auction_one_start_time(&sent, wire, 0) == 4);
  assert(decode_intraday_auction_one_start_time(&got, wire, 0) == 4);
  equal_intraday_auction_one_start_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_intraday_auction_one_start_time(&got, wire, 0) == 4);
  assert(encode_intraday_auction_one_start_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Intraday Auction One Auction Close Time: 4 bytes ------------------------ */

/* Intraday Auction One Auction Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} IntradayAuctionOneAuctionCloseTime;

/* any Intraday Auction One Auction Close Time at all: every byte one the checker chooses */
static void any_intraday_auction_one_auction_close_time(IntradayAuctionOneAuctionCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Intraday Auction One Auction Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_intraday_auction_one_auction_close_time(const IntradayAuctionOneAuctionCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Intraday Auction One Auction Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_intraday_auction_one_auction_close_time(IntradayAuctionOneAuctionCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Intraday Auction One Auction Close Time is what was written, byte for byte */
static void equal_intraday_auction_one_auction_close_time(const IntradayAuctionOneAuctionCloseTime *read, const IntradayAuctionOneAuctionCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Intraday Auction One Auction Close Time: written and read back, then read and written back */
static void check_intraday_auction_one_auction_close_time(void) {
  IntradayAuctionOneAuctionCloseTime sent;
  IntradayAuctionOneAuctionCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_intraday_auction_one_auction_close_time(&sent);
  assert(encode_intraday_auction_one_auction_close_time(&sent, wire, 0) == 4);
  assert(decode_intraday_auction_one_auction_close_time(&got, wire, 0) == 4);
  equal_intraday_auction_one_auction_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_intraday_auction_one_auction_close_time(&got, wire, 0) == 4);
  assert(encode_intraday_auction_one_auction_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Intraday Auction Two Start Time: 4 bytes -------------------------------- */

/* Intraday Auction Two Start Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} IntradayAuctionTwoStartTime;

/* any Intraday Auction Two Start Time at all: every byte one the checker chooses */
static void any_intraday_auction_two_start_time(IntradayAuctionTwoStartTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Intraday Auction Two Start Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_intraday_auction_two_start_time(const IntradayAuctionTwoStartTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Intraday Auction Two Start Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_intraday_auction_two_start_time(IntradayAuctionTwoStartTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Intraday Auction Two Start Time is what was written, byte for byte */
static void equal_intraday_auction_two_start_time(const IntradayAuctionTwoStartTime *read, const IntradayAuctionTwoStartTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Intraday Auction Two Start Time: written and read back, then read and written back */
static void check_intraday_auction_two_start_time(void) {
  IntradayAuctionTwoStartTime sent;
  IntradayAuctionTwoStartTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_intraday_auction_two_start_time(&sent);
  assert(encode_intraday_auction_two_start_time(&sent, wire, 0) == 4);
  assert(decode_intraday_auction_two_start_time(&got, wire, 0) == 4);
  equal_intraday_auction_two_start_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_intraday_auction_two_start_time(&got, wire, 0) == 4);
  assert(encode_intraday_auction_two_start_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Intraday Auction Two Auction Close Time: 4 bytes ------------------------ */

/* Intraday Auction Two Auction Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} IntradayAuctionTwoAuctionCloseTime;

/* any Intraday Auction Two Auction Close Time at all: every byte one the checker chooses */
static void any_intraday_auction_two_auction_close_time(IntradayAuctionTwoAuctionCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Intraday Auction Two Auction Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_intraday_auction_two_auction_close_time(const IntradayAuctionTwoAuctionCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Intraday Auction Two Auction Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_intraday_auction_two_auction_close_time(IntradayAuctionTwoAuctionCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Intraday Auction Two Auction Close Time is what was written, byte for byte */
static void equal_intraday_auction_two_auction_close_time(const IntradayAuctionTwoAuctionCloseTime *read, const IntradayAuctionTwoAuctionCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Intraday Auction Two Auction Close Time: written and read back, then read and written back */
static void check_intraday_auction_two_auction_close_time(void) {
  IntradayAuctionTwoAuctionCloseTime sent;
  IntradayAuctionTwoAuctionCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_intraday_auction_two_auction_close_time(&sent);
  assert(encode_intraday_auction_two_auction_close_time(&sent, wire, 0) == 4);
  assert(decode_intraday_auction_two_auction_close_time(&got, wire, 0) == 4);
  equal_intraday_auction_two_auction_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_intraday_auction_two_auction_close_time(&got, wire, 0) == 4);
  assert(encode_intraday_auction_two_auction_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Intraday Auction Three Start Time: 4 bytes ------------------------------ */

/* Intraday Auction Three Start Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} IntradayAuctionThreeStartTime;

/* any Intraday Auction Three Start Time at all: every byte one the checker chooses */
static void any_intraday_auction_three_start_time(IntradayAuctionThreeStartTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Intraday Auction Three Start Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_intraday_auction_three_start_time(const IntradayAuctionThreeStartTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Intraday Auction Three Start Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_intraday_auction_three_start_time(IntradayAuctionThreeStartTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Intraday Auction Three Start Time is what was written, byte for byte */
static void equal_intraday_auction_three_start_time(const IntradayAuctionThreeStartTime *read, const IntradayAuctionThreeStartTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Intraday Auction Three Start Time: written and read back, then read and written back */
static void check_intraday_auction_three_start_time(void) {
  IntradayAuctionThreeStartTime sent;
  IntradayAuctionThreeStartTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_intraday_auction_three_start_time(&sent);
  assert(encode_intraday_auction_three_start_time(&sent, wire, 0) == 4);
  assert(decode_intraday_auction_three_start_time(&got, wire, 0) == 4);
  equal_intraday_auction_three_start_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_intraday_auction_three_start_time(&got, wire, 0) == 4);
  assert(encode_intraday_auction_three_start_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Intraday Auction Three Auction Close Time: 4 bytes ---------------------- */

/* Intraday Auction Three Auction Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} IntradayAuctionThreeAuctionCloseTime;

/* any Intraday Auction Three Auction Close Time at all: every byte one the checker chooses */
static void any_intraday_auction_three_auction_close_time(IntradayAuctionThreeAuctionCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Intraday Auction Three Auction Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_intraday_auction_three_auction_close_time(const IntradayAuctionThreeAuctionCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Intraday Auction Three Auction Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_intraday_auction_three_auction_close_time(IntradayAuctionThreeAuctionCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Intraday Auction Three Auction Close Time is what was written, byte for byte */
static void equal_intraday_auction_three_auction_close_time(const IntradayAuctionThreeAuctionCloseTime *read, const IntradayAuctionThreeAuctionCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Intraday Auction Three Auction Close Time: written and read back, then read and written back */
static void check_intraday_auction_three_auction_close_time(void) {
  IntradayAuctionThreeAuctionCloseTime sent;
  IntradayAuctionThreeAuctionCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_intraday_auction_three_auction_close_time(&sent);
  assert(encode_intraday_auction_three_auction_close_time(&sent, wire, 0) == 4);
  assert(decode_intraday_auction_three_auction_close_time(&got, wire, 0) == 4);
  equal_intraday_auction_three_auction_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_intraday_auction_three_auction_close_time(&got, wire, 0) == 4);
  assert(encode_intraday_auction_three_auction_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Overnight Admin Open Time: 4 bytes -------------------------------------- */

/* Overnight Admin Open Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} OvernightAdminOpenTime;

/* any Overnight Admin Open Time at all: every byte one the checker chooses */
static void any_overnight_admin_open_time(OvernightAdminOpenTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Overnight Admin Open Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_overnight_admin_open_time(const OvernightAdminOpenTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Overnight Admin Open Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_overnight_admin_open_time(OvernightAdminOpenTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Overnight Admin Open Time is what was written, byte for byte */
static void equal_overnight_admin_open_time(const OvernightAdminOpenTime *read, const OvernightAdminOpenTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Overnight Admin Open Time: written and read back, then read and written back */
static void check_overnight_admin_open_time(void) {
  OvernightAdminOpenTime sent;
  OvernightAdminOpenTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_overnight_admin_open_time(&sent);
  assert(encode_overnight_admin_open_time(&sent, wire, 0) == 4);
  assert(decode_overnight_admin_open_time(&got, wire, 0) == 4);
  equal_overnight_admin_open_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_overnight_admin_open_time(&got, wire, 0) == 4);
  assert(encode_overnight_admin_open_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Overnight Admin Close Time: 4 bytes ------------------------------------- */

/* Overnight Admin Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} OvernightAdminCloseTime;

/* any Overnight Admin Close Time at all: every byte one the checker chooses */
static void any_overnight_admin_close_time(OvernightAdminCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Overnight Admin Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_overnight_admin_close_time(const OvernightAdminCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Overnight Admin Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_overnight_admin_close_time(OvernightAdminCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Overnight Admin Close Time is what was written, byte for byte */
static void equal_overnight_admin_close_time(const OvernightAdminCloseTime *read, const OvernightAdminCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Overnight Admin Close Time: written and read back, then read and written back */
static void check_overnight_admin_close_time(void) {
  OvernightAdminCloseTime sent;
  OvernightAdminCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_overnight_admin_close_time(&sent);
  assert(encode_overnight_admin_close_time(&sent, wire, 0) == 4);
  assert(decode_overnight_admin_close_time(&got, wire, 0) == 4);
  equal_overnight_admin_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_overnight_admin_close_time(&got, wire, 0) == 4);
  assert(encode_overnight_admin_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Admin Period Close Time: 4 bytes ---------------------------------------- */

/* Admin Period Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} AdminPeriodCloseTime;

/* any Admin Period Close Time at all: every byte one the checker chooses */
static void any_admin_period_close_time(AdminPeriodCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Admin Period Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_admin_period_close_time(const AdminPeriodCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Admin Period Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_admin_period_close_time(AdminPeriodCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Admin Period Close Time is what was written, byte for byte */
static void equal_admin_period_close_time(const AdminPeriodCloseTime *read, const AdminPeriodCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Admin Period Close Time: written and read back, then read and written back */
static void check_admin_period_close_time(void) {
  AdminPeriodCloseTime sent;
  AdminPeriodCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_admin_period_close_time(&sent);
  assert(encode_admin_period_close_time(&sent, wire, 0) == 4);
  assert(decode_admin_period_close_time(&got, wire, 0) == 4);
  equal_admin_period_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_admin_period_close_time(&got, wire, 0) == 4);
  assert(encode_admin_period_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Pre Open Order Entry Open Time: 4 bytes --------------------------------- */

/* Pre-open order entry Open Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} PreOpenOrderEntryOpenTime;

/* any Pre Open Order Entry Open Time at all: every byte one the checker chooses */
static void any_pre_open_order_entry_open_time(PreOpenOrderEntryOpenTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Pre Open Order Entry Open Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_pre_open_order_entry_open_time(const PreOpenOrderEntryOpenTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Pre Open Order Entry Open Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_pre_open_order_entry_open_time(PreOpenOrderEntryOpenTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Pre Open Order Entry Open Time is what was written, byte for byte */
static void equal_pre_open_order_entry_open_time(const PreOpenOrderEntryOpenTime *read, const PreOpenOrderEntryOpenTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Pre Open Order Entry Open Time: written and read back, then read and written back */
static void check_pre_open_order_entry_open_time(void) {
  PreOpenOrderEntryOpenTime sent;
  PreOpenOrderEntryOpenTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_pre_open_order_entry_open_time(&sent);
  assert(encode_pre_open_order_entry_open_time(&sent, wire, 0) == 4);
  assert(decode_pre_open_order_entry_open_time(&got, wire, 0) == 4);
  equal_pre_open_order_entry_open_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_pre_open_order_entry_open_time(&got, wire, 0) == 4);
  assert(encode_pre_open_order_entry_open_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Pre Open Order Entry Close Time: 4 bytes -------------------------------- */

/* Pre-open order entry Close Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} PreOpenOrderEntryCloseTime;

/* any Pre Open Order Entry Close Time at all: every byte one the checker chooses */
static void any_pre_open_order_entry_close_time(PreOpenOrderEntryCloseTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Pre Open Order Entry Close Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_pre_open_order_entry_close_time(const PreOpenOrderEntryCloseTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Pre Open Order Entry Close Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_pre_open_order_entry_close_time(PreOpenOrderEntryCloseTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Pre Open Order Entry Close Time is what was written, byte for byte */
static void equal_pre_open_order_entry_close_time(const PreOpenOrderEntryCloseTime *read, const PreOpenOrderEntryCloseTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Pre Open Order Entry Close Time: written and read back, then read and written back */
static void check_pre_open_order_entry_close_time(void) {
  PreOpenOrderEntryCloseTime sent;
  PreOpenOrderEntryCloseTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_pre_open_order_entry_close_time(&sent);
  assert(encode_pre_open_order_entry_close_time(&sent, wire, 0) == 4);
  assert(decode_pre_open_order_entry_close_time(&got, wire, 0) == 4);
  equal_pre_open_order_entry_close_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_pre_open_order_entry_close_time(&got, wire, 0) == 4);
  assert(encode_pre_open_order_entry_close_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Sessions: 144 bytes --------------------------------------------- */

/* Trading Sessions */
typedef struct {
  uint8_t trading_session_sequence[4];                                             /* bytes 0 to 3 */
  TradingSessionName trading_session_name;                                         /* bytes 4 to 59 */
  OpeningAuctionStartTime opening_auction_start_time;                              /* bytes 60 to 63 */
  OpeningAuctionCloseTime opening_auction_close_time;                              /* bytes 64 to 67 */
  ClosingAuctionStartTime closing_auction_start_time;                              /* bytes 68 to 71 */
  ClosingAuctionCloseTime closing_auction_close_time;                              /* bytes 72 to 75 */
  ContractOpenTime contract_open_time;                                             /* bytes 76 to 79 */
  ContractCloseTime contract_close_time;                                           /* bytes 80 to 83 */
  IntradayAuctionOneStartTime intraday_auction_one_start_time;                     /* bytes 84 to 87 */
  IntradayAuctionOneAuctionCloseTime intraday_auction_one_auction_close_time;      /* bytes 88 to 91 */
  IntradayAuctionTwoStartTime intraday_auction_two_start_time;                     /* bytes 92 to 95 */
  IntradayAuctionTwoAuctionCloseTime intraday_auction_two_auction_close_time;      /* bytes 96 to 99 */
  IntradayAuctionThreeStartTime intraday_auction_three_start_time;                 /* bytes 100 to 103 */
  IntradayAuctionThreeAuctionCloseTime intraday_auction_three_auction_close_time;  /* bytes 104 to 107 */
  OvernightAdminOpenTime overnight_admin_open_time;                                /* bytes 108 to 111 */
  OvernightAdminCloseTime overnight_admin_close_time;                              /* bytes 112 to 115 */
  AdminPeriodCloseTime admin_period_close_time;                                    /* bytes 116 to 119 */
  uint8_t unused_8[8];                                                             /* bytes 120 to 127 */
  PreOpenOrderEntryOpenTime pre_open_order_entry_open_time;                        /* bytes 128 to 131 */
  PreOpenOrderEntryCloseTime pre_open_order_entry_close_time;                      /* bytes 132 to 135 */
  uint8_t second_unused_8[8];                                                      /* bytes 136 to 143 */
} TradingSessions;

/* any Trading Sessions at all: every byte one the checker chooses */
static void any_trading_sessions(TradingSessions *record) {
  for (size_t i = 0; i < 4; i++) { record->trading_session_sequence[i] = arbitrary(); }
  any_trading_session_name(&record->trading_session_name);
  any_opening_auction_start_time(&record->opening_auction_start_time);
  any_opening_auction_close_time(&record->opening_auction_close_time);
  any_closing_auction_start_time(&record->closing_auction_start_time);
  any_closing_auction_close_time(&record->closing_auction_close_time);
  any_contract_open_time(&record->contract_open_time);
  any_contract_close_time(&record->contract_close_time);
  any_intraday_auction_one_start_time(&record->intraday_auction_one_start_time);
  any_intraday_auction_one_auction_close_time(&record->intraday_auction_one_auction_close_time);
  any_intraday_auction_two_start_time(&record->intraday_auction_two_start_time);
  any_intraday_auction_two_auction_close_time(&record->intraday_auction_two_auction_close_time);
  any_intraday_auction_three_start_time(&record->intraday_auction_three_start_time);
  any_intraday_auction_three_auction_close_time(&record->intraday_auction_three_auction_close_time);
  any_overnight_admin_open_time(&record->overnight_admin_open_time);
  any_overnight_admin_close_time(&record->overnight_admin_close_time);
  any_admin_period_close_time(&record->admin_period_close_time);
  for (size_t i = 0; i < 8; i++) { record->unused_8[i] = arbitrary(); }
  any_pre_open_order_entry_open_time(&record->pre_open_order_entry_open_time);
  any_pre_open_order_entry_close_time(&record->pre_open_order_entry_close_time);
  for (size_t i = 0; i < 8; i++) { record->second_unused_8[i] = arbitrary(); }
}

/* Trading Sessions to the wire: 144 bytes from at, returning where the next byte goes */
static size_t encode_trading_sessions(const TradingSessions *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trading_session_sequence[i]; }
  at = encode_trading_session_name(&record->trading_session_name, wire, at);
  at = encode_opening_auction_start_time(&record->opening_auction_start_time, wire, at);
  at = encode_opening_auction_close_time(&record->opening_auction_close_time, wire, at);
  at = encode_closing_auction_start_time(&record->closing_auction_start_time, wire, at);
  at = encode_closing_auction_close_time(&record->closing_auction_close_time, wire, at);
  at = encode_contract_open_time(&record->contract_open_time, wire, at);
  at = encode_contract_close_time(&record->contract_close_time, wire, at);
  at = encode_intraday_auction_one_start_time(&record->intraday_auction_one_start_time, wire, at);
  at = encode_intraday_auction_one_auction_close_time(&record->intraday_auction_one_auction_close_time, wire, at);
  at = encode_intraday_auction_two_start_time(&record->intraday_auction_two_start_time, wire, at);
  at = encode_intraday_auction_two_auction_close_time(&record->intraday_auction_two_auction_close_time, wire, at);
  at = encode_intraday_auction_three_start_time(&record->intraday_auction_three_start_time, wire, at);
  at = encode_intraday_auction_three_auction_close_time(&record->intraday_auction_three_auction_close_time, wire, at);
  at = encode_overnight_admin_open_time(&record->overnight_admin_open_time, wire, at);
  at = encode_overnight_admin_close_time(&record->overnight_admin_close_time, wire, at);
  at = encode_admin_period_close_time(&record->admin_period_close_time, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->unused_8[i]; }
  at = encode_pre_open_order_entry_open_time(&record->pre_open_order_entry_open_time, wire, at);
  at = encode_pre_open_order_entry_close_time(&record->pre_open_order_entry_close_time, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->second_unused_8[i]; }

  return at;
}

/* Trading Sessions off the wire: 144 bytes from at, returning where the next byte lies */
static size_t decode_trading_sessions(TradingSessions *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trading_session_sequence[i] = wire[at++]; }
  at = decode_trading_session_name(&record->trading_session_name, wire, at);
  at = decode_opening_auction_start_time(&record->opening_auction_start_time, wire, at);
  at = decode_opening_auction_close_time(&record->opening_auction_close_time, wire, at);
  at = decode_closing_auction_start_time(&record->closing_auction_start_time, wire, at);
  at = decode_closing_auction_close_time(&record->closing_auction_close_time, wire, at);
  at = decode_contract_open_time(&record->contract_open_time, wire, at);
  at = decode_contract_close_time(&record->contract_close_time, wire, at);
  at = decode_intraday_auction_one_start_time(&record->intraday_auction_one_start_time, wire, at);
  at = decode_intraday_auction_one_auction_close_time(&record->intraday_auction_one_auction_close_time, wire, at);
  at = decode_intraday_auction_two_start_time(&record->intraday_auction_two_start_time, wire, at);
  at = decode_intraday_auction_two_auction_close_time(&record->intraday_auction_two_auction_close_time, wire, at);
  at = decode_intraday_auction_three_start_time(&record->intraday_auction_three_start_time, wire, at);
  at = decode_intraday_auction_three_auction_close_time(&record->intraday_auction_three_auction_close_time, wire, at);
  at = decode_overnight_admin_open_time(&record->overnight_admin_open_time, wire, at);
  at = decode_overnight_admin_close_time(&record->overnight_admin_close_time, wire, at);
  at = decode_admin_period_close_time(&record->admin_period_close_time, wire, at);
  for (size_t i = 0; i < 8; i++) { record->unused_8[i] = wire[at++]; }
  at = decode_pre_open_order_entry_open_time(&record->pre_open_order_entry_open_time, wire, at);
  at = decode_pre_open_order_entry_close_time(&record->pre_open_order_entry_close_time, wire, at);
  for (size_t i = 0; i < 8; i++) { record->second_unused_8[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Sessions is what was written, byte for byte */
static void equal_trading_sessions(const TradingSessions *read, const TradingSessions *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trading_session_sequence[i] == written->trading_session_sequence[i]); }
  equal_trading_session_name(&read->trading_session_name, &written->trading_session_name);
  equal_opening_auction_start_time(&read->opening_auction_start_time, &written->opening_auction_start_time);
  equal_opening_auction_close_time(&read->opening_auction_close_time, &written->opening_auction_close_time);
  equal_closing_auction_start_time(&read->closing_auction_start_time, &written->closing_auction_start_time);
  equal_closing_auction_close_time(&read->closing_auction_close_time, &written->closing_auction_close_time);
  equal_contract_open_time(&read->contract_open_time, &written->contract_open_time);
  equal_contract_close_time(&read->contract_close_time, &written->contract_close_time);
  equal_intraday_auction_one_start_time(&read->intraday_auction_one_start_time, &written->intraday_auction_one_start_time);
  equal_intraday_auction_one_auction_close_time(&read->intraday_auction_one_auction_close_time, &written->intraday_auction_one_auction_close_time);
  equal_intraday_auction_two_start_time(&read->intraday_auction_two_start_time, &written->intraday_auction_two_start_time);
  equal_intraday_auction_two_auction_close_time(&read->intraday_auction_two_auction_close_time, &written->intraday_auction_two_auction_close_time);
  equal_intraday_auction_three_start_time(&read->intraday_auction_three_start_time, &written->intraday_auction_three_start_time);
  equal_intraday_auction_three_auction_close_time(&read->intraday_auction_three_auction_close_time, &written->intraday_auction_three_auction_close_time);
  equal_overnight_admin_open_time(&read->overnight_admin_open_time, &written->overnight_admin_open_time);
  equal_overnight_admin_close_time(&read->overnight_admin_close_time, &written->overnight_admin_close_time);
  equal_admin_period_close_time(&read->admin_period_close_time, &written->admin_period_close_time);
  for (size_t i = 0; i < 8; i++) { assert(read->unused_8[i] == written->unused_8[i]); }
  equal_pre_open_order_entry_open_time(&read->pre_open_order_entry_open_time, &written->pre_open_order_entry_open_time);
  equal_pre_open_order_entry_close_time(&read->pre_open_order_entry_close_time, &written->pre_open_order_entry_close_time);
  for (size_t i = 0; i < 8; i++) { assert(read->second_unused_8[i] == written->second_unused_8[i]); }
}

/* Trading Sessions: written and read back, then read and written back */
static void check_trading_sessions(void) {
  TradingSessions sent;
  TradingSessions got;
  uint8_t wire[144];
  uint8_t again[144];

  any_trading_sessions(&sent);
  assert(encode_trading_sessions(&sent, wire, 0) == 144);
  assert(decode_trading_sessions(&got, wire, 0) == 144);
  equal_trading_sessions(&got, &sent);

  for (size_t i = 0; i < 144; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_sessions(&got, wire, 0) == 144);
  assert(encode_trading_sessions(&got, again, 0) == 144);
  for (size_t i = 0; i < 144; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Time: 4 bytes ---------------------------------------------------- */

/* Update Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} UpdateTime;

/* any Update Time at all: every byte one the checker chooses */
static void any_update_time(UpdateTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Update Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_update_time(const UpdateTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Update Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_update_time(UpdateTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Update Time is what was written, byte for byte */
static void equal_update_time(const UpdateTime *read, const UpdateTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Update Time: written and read back, then read and written back */
static void check_update_time(void) {
  UpdateTime sent;
  UpdateTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_update_time(&sent);
  assert(encode_update_time(&sent, wire, 0) == 4);
  assert(decode_update_time(&got, wire, 0) == 4);
  equal_update_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_update_time(&got, wire, 0) == 4);
  assert(encode_update_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update Date: 12 bytes --------------------------------------------------- */

/* Update Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} UpdateDate;

/* any Update Date at all: every byte one the checker chooses */
static void any_update_date(UpdateDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Update Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_update_date(const UpdateDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Update Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_update_date(UpdateDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Update Date is what was written, byte for byte */
static void equal_update_date(const UpdateDate *read, const UpdateDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Update Date: written and read back, then read and written back */
static void check_update_date(void) {
  UpdateDate sent;
  UpdateDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_update_date(&sent);
  assert(encode_update_date(&sent, wire, 0) == 12);
  assert(decode_update_date(&got, wire, 0) == 12);
  equal_update_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_update_date(&got, wire, 0) == 12);
  assert(encode_update_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indices Price Data: 44 bytes -------------------------------------------- */

/* Indices Price Data */
typedef struct {
  uint8_t indices_sequence[4];       /* bytes 0 to 3 */
  uint8_t opening_price[8];          /* bytes 4 to 11 */
  uint8_t index_price[8];            /* bytes 12 to 19 */
  UpdateTime update_time;            /* bytes 20 to 23 */
  UpdateDate update_date;            /* bytes 24 to 35 */
  uint8_t market_capitalisation[8];  /* bytes 36 to 43 */
} IndicesPriceData;

/* any Indices Price Data at all: every byte one the checker chooses */
static void any_indices_price_data(IndicesPriceData *record) {
  for (size_t i = 0; i < 4; i++) { record->indices_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = arbitrary(); }
  any_update_time(&record->update_time);
  any_update_date(&record->update_date);
  for (size_t i = 0; i < 8; i++) { record->market_capitalisation[i] = arbitrary(); }
}

/* Indices Price Data to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_indices_price_data(const IndicesPriceData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indices_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_price[i]; }
  at = encode_update_time(&record->update_time, wire, at);
  at = encode_update_date(&record->update_date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_capitalisation[i]; }

  return at;
}

/* Indices Price Data off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_indices_price_data(IndicesPriceData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->indices_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = wire[at++]; }
  at = decode_update_time(&record->update_time, wire, at);
  at = decode_update_date(&record->update_date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->market_capitalisation[i] = wire[at++]; }

  return at;
}

/* what was read of Indices Price Data is what was written, byte for byte */
static void equal_indices_price_data(const IndicesPriceData *read, const IndicesPriceData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->indices_sequence[i] == written->indices_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_price[i] == written->index_price[i]); }
  equal_update_time(&read->update_time, &written->update_time);
  equal_update_date(&read->update_date, &written->update_date);
  for (size_t i = 0; i < 8; i++) { assert(read->market_capitalisation[i] == written->market_capitalisation[i]); }
}

/* Indices Price Data: written and read back, then read and written back */
static void check_indices_price_data(void) {
  IndicesPriceData sent;
  IndicesPriceData got;
  uint8_t wire[44];
  uint8_t again[44];

  any_indices_price_data(&sent);
  assert(encode_indices_price_data(&sent, wire, 0) == 44);
  assert(decode_indices_price_data(&got, wire, 0) == 44);
  equal_indices_price_data(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_indices_price_data(&got, wire, 0) == 44);
  assert(encode_indices_price_data(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indices Code: 20 bytes -------------------------------------------------- */

/* Indicates the short code for this index. */
typedef struct {
  uint8_t indices_code_length_byte;     /* byte 0 */
  uint8_t indices_code_characters[19];  /* bytes 1 to 19 */
} IndicesCode;

/* any Indices Code at all: every byte one the checker chooses */
static void any_indices_code(IndicesCode *record) {
  record->indices_code_length_byte = arbitrary();
  for (size_t i = 0; i < 19; i++) { record->indices_code_characters[i] = arbitrary(); }
}

/* Indices Code to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_indices_code(const IndicesCode *record, uint8_t *wire, size_t at) {
  wire[at++] = record->indices_code_length_byte;
  for (size_t i = 0; i < 19; i++) { wire[at++] = record->indices_code_characters[i]; }

  return at;
}

/* Indices Code off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_indices_code(IndicesCode *record, const uint8_t *wire, size_t at) {
  record->indices_code_length_byte = wire[at++];
  for (size_t i = 0; i < 19; i++) { record->indices_code_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Indices Code is what was written, byte for byte */
static void equal_indices_code(const IndicesCode *read, const IndicesCode *written) {
  assert(read->indices_code_length_byte == written->indices_code_length_byte);
  for (size_t i = 0; i < 19; i++) { assert(read->indices_code_characters[i] == written->indices_code_characters[i]); }
}

/* Indices Code: written and read back, then read and written back */
static void check_indices_code(void) {
  IndicesCode sent;
  IndicesCode got;
  uint8_t wire[20];
  uint8_t again[20];

  any_indices_code(&sent);
  assert(encode_indices_code(&sent, wire, 0) == 20);
  assert(decode_indices_code(&got, wire, 0) == 20);
  equal_indices_code(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_indices_code(&got, wire, 0) == 20);
  assert(encode_indices_code(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indices Description: 50 bytes ------------------------------------------- */

/* Provides a description for the index. */
typedef struct {
  uint8_t indices_description_length_byte;     /* byte 0 */
  uint8_t indices_description_characters[49];  /* bytes 1 to 49 */
} IndicesDescription;

/* any Indices Description at all: every byte one the checker chooses */
static void any_indices_description(IndicesDescription *record) {
  record->indices_description_length_byte = arbitrary();
  for (size_t i = 0; i < 49; i++) { record->indices_description_characters[i] = arbitrary(); }
}

/* Indices Description to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_indices_description(const IndicesDescription *record, uint8_t *wire, size_t at) {
  wire[at++] = record->indices_description_length_byte;
  for (size_t i = 0; i < 49; i++) { wire[at++] = record->indices_description_characters[i]; }

  return at;
}

/* Indices Description off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_indices_description(IndicesDescription *record, const uint8_t *wire, size_t at) {
  record->indices_description_length_byte = wire[at++];
  for (size_t i = 0; i < 49; i++) { record->indices_description_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Indices Description is what was written, byte for byte */
static void equal_indices_description(const IndicesDescription *read, const IndicesDescription *written) {
  assert(read->indices_description_length_byte == written->indices_description_length_byte);
  for (size_t i = 0; i < 49; i++) { assert(read->indices_description_characters[i] == written->indices_description_characters[i]); }
}

/* Indices Description: written and read back, then read and written back */
static void check_indices_description(void) {
  IndicesDescription sent;
  IndicesDescription got;
  uint8_t wire[50];
  uint8_t again[50];

  any_indices_description(&sent);
  assert(encode_indices_description(&sent, wire, 0) == 50);
  assert(decode_indices_description(&got, wire, 0) == 50);
  equal_indices_description(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_indices_description(&got, wire, 0) == 50);
  assert(encode_indices_description(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indices Data: 104 bytes ------------------------------------------------- */

/* Indices Data */
typedef struct {
  uint8_t indices_sequence[4];             /* bytes 0 to 3 */
  IndicesCode indices_code;                /* bytes 4 to 23 */
  IndicesDescription indices_description;  /* bytes 24 to 73 */
  Classification classification;           /* bytes 74 to 103 */
} IndicesData;

/* any Indices Data at all: every byte one the checker chooses */
static void any_indices_data(IndicesData *record) {
  for (size_t i = 0; i < 4; i++) { record->indices_sequence[i] = arbitrary(); }
  any_indices_code(&record->indices_code);
  any_indices_description(&record->indices_description);
  any_classification(&record->classification);
}

/* Indices Data to the wire: 104 bytes from at, returning where the next byte goes */
static size_t encode_indices_data(const IndicesData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indices_sequence[i]; }
  at = encode_indices_code(&record->indices_code, wire, at);
  at = encode_indices_description(&record->indices_description, wire, at);
  at = encode_classification(&record->classification, wire, at);

  return at;
}

/* Indices Data off the wire: 104 bytes from at, returning where the next byte lies */
static size_t decode_indices_data(IndicesData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->indices_sequence[i] = wire[at++]; }
  at = decode_indices_code(&record->indices_code, wire, at);
  at = decode_indices_description(&record->indices_description, wire, at);
  at = decode_classification(&record->classification, wire, at);

  return at;
}

/* what was read of Indices Data is what was written, byte for byte */
static void equal_indices_data(const IndicesData *read, const IndicesData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->indices_sequence[i] == written->indices_sequence[i]); }
  equal_indices_code(&read->indices_code, &written->indices_code);
  equal_indices_description(&read->indices_description, &written->indices_description);
  equal_classification(&read->classification, &written->classification);
}

/* Indices Data: written and read back, then read and written back */
static void check_indices_data(void) {
  IndicesData sent;
  IndicesData got;
  uint8_t wire[104];
  uint8_t again[104];

  any_indices_data(&sent);
  assert(encode_indices_data(&sent, wire, 0) == 104);
  assert(decode_indices_data(&got, wire, 0) == 104);
  equal_indices_data(&got, &sent);

  for (size_t i = 0; i < 104; i++) { wire[i] = arbitrary(); }
  assert(decode_indices_data(&got, wire, 0) == 104);
  assert(encode_indices_data(&got, again, 0) == 104);
  for (size_t i = 0; i < 104; i++) { assert(again[i] == wire[i]); }
}

/* ---- Shares In Issue Data: 40 bytes ------------------------------------------ */

/* Shares in Issue Data */
typedef struct {
  uint8_t shares_in_issue_sequence[4];  /* bytes 0 to 3 */
  uint8_t instrument_sequence[4];       /* bytes 4 to 7 */
  uint8_t balance[8];                   /* bytes 8 to 15 */
  uint8_t current_value[8];             /* bytes 16 to 23 */
  uint8_t previous_balance[8];          /* bytes 24 to 31 */
  uint8_t previous_value[8];            /* bytes 32 to 39 */
} SharesInIssueData;

/* any Shares In Issue Data at all: every byte one the checker chooses */
static void any_shares_in_issue_data(SharesInIssueData *record) {
  for (size_t i = 0; i < 4; i++) { record->shares_in_issue_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->balance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->current_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_balance[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_value[i] = arbitrary(); }
}

/* Shares In Issue Data to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_shares_in_issue_data(const SharesInIssueData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->shares_in_issue_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_sequence[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->balance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->current_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_balance[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_value[i]; }

  return at;
}

/* Shares In Issue Data off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_shares_in_issue_data(SharesInIssueData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->shares_in_issue_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->balance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->current_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_balance[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_value[i] = wire[at++]; }

  return at;
}

/* what was read of Shares In Issue Data is what was written, byte for byte */
static void equal_shares_in_issue_data(const SharesInIssueData *read, const SharesInIssueData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->shares_in_issue_sequence[i] == written->shares_in_issue_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_sequence[i] == written->instrument_sequence[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->balance[i] == written->balance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->current_value[i] == written->current_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_balance[i] == written->previous_balance[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_value[i] == written->previous_value[i]); }
}

/* Shares In Issue Data: written and read back, then read and written back */
static void check_shares_in_issue_data(void) {
  SharesInIssueData sent;
  SharesInIssueData got;
  uint8_t wire[40];
  uint8_t again[40];

  any_shares_in_issue_data(&sent);
  assert(encode_shares_in_issue_data(&sent, wire, 0) == 40);
  assert(decode_shares_in_issue_data(&got, wire, 0) == 40);
  equal_shares_in_issue_data(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_shares_in_issue_data(&got, wire, 0) == 40);
  assert(encode_shares_in_issue_data(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Date: 12 bytes ---------------------------------------------------- */

/* Trade Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} TradeDate;

/* any Trade Date at all: every byte one the checker chooses */
static void any_trade_date(TradeDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Trade Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_trade_date(const TradeDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Trade Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_trade_date(TradeDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Date is what was written, byte for byte */
static void equal_trade_date(const TradeDate *read, const TradeDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Trade Date: written and read back, then read and written back */
static void check_trade_date(void) {
  TradeDate sent;
  TradeDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_trade_date(&sent);
  assert(encode_trade_date(&sent, wire, 0) == 12);
  assert(decode_trade_date(&got, wire, 0) == 12);
  equal_trade_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_date(&got, wire, 0) == 12);
  assert(encode_trade_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Data: 36 bytes ---------------------------------------------------- */

/* Index Data */
typedef struct {
  uint8_t index_data_sequence[4];    /* bytes 0 to 3 */
  uint8_t indices_sequence[4];       /* bytes 4 to 7 */
  TradeDate trade_date;              /* bytes 8 to 19 */
  uint8_t index_value[8];            /* bytes 20 to 27 */
  uint8_t market_capitalization[8];  /* bytes 28 to 35 */
} IndexData;

/* any Index Data at all: every byte one the checker chooses */
static void any_index_data(IndexData *record) {
  for (size_t i = 0; i < 4; i++) { record->index_data_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indices_sequence[i] = arbitrary(); }
  any_trade_date(&record->trade_date);
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->market_capitalization[i] = arbitrary(); }
}

/* Index Data to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_index_data(const IndexData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_data_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indices_sequence[i]; }
  at = encode_trade_date(&record->trade_date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_value[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_capitalization[i]; }

  return at;
}

/* Index Data off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_index_data(IndexData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->index_data_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indices_sequence[i] = wire[at++]; }
  at = decode_trade_date(&record->trade_date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->index_value[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->market_capitalization[i] = wire[at++]; }

  return at;
}

/* what was read of Index Data is what was written, byte for byte */
static void equal_index_data(const IndexData *read, const IndexData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->index_data_sequence[i] == written->index_data_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indices_sequence[i] == written->indices_sequence[i]); }
  equal_trade_date(&read->trade_date, &written->trade_date);
  for (size_t i = 0; i < 8; i++) { assert(read->index_value[i] == written->index_value[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->market_capitalization[i] == written->market_capitalization[i]); }
}

/* Index Data: written and read back, then read and written back */
static void check_index_data(void) {
  IndexData sent;
  IndexData got;
  uint8_t wire[36];
  uint8_t again[36];

  any_index_data(&sent);
  assert(encode_index_data(&sent, wire, 0) == 36);
  assert(decode_index_data(&got, wire, 0) == 36);
  equal_index_data(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_index_data(&got, wire, 0) == 36);
  assert(encode_index_data(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Constituents Data: 12 bytes --------------------------------------- */

/* Index Constituents Data */
typedef struct {
  uint8_t index_instrument_sequence[4];  /* bytes 0 to 3 */
  uint8_t indices_sequence[4];           /* bytes 4 to 7 */
  uint8_t instrument_sequence[4];        /* bytes 8 to 11 */
} IndexConstituentsData;

/* any Index Constituents Data at all: every byte one the checker chooses */
static void any_index_constituents_data(IndexConstituentsData *record) {
  for (size_t i = 0; i < 4; i++) { record->index_instrument_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->indices_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = arbitrary(); }
}

/* Index Constituents Data to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_index_constituents_data(const IndexConstituentsData *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->index_instrument_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->indices_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_sequence[i]; }

  return at;
}

/* Index Constituents Data off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_index_constituents_data(IndexConstituentsData *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->index_instrument_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->indices_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_sequence[i] = wire[at++]; }

  return at;
}

/* what was read of Index Constituents Data is what was written, byte for byte */
static void equal_index_constituents_data(const IndexConstituentsData *read, const IndexConstituentsData *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->index_instrument_sequence[i] == written->index_instrument_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->indices_sequence[i] == written->indices_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_sequence[i] == written->instrument_sequence[i]); }
}

/* Index Constituents Data: written and read back, then read and written back */
static void check_index_constituents_data(void) {
  IndexConstituentsData sent;
  IndexConstituentsData got;
  uint8_t wire[12];
  uint8_t again[12];

  any_index_constituents_data(&sent);
  assert(encode_index_constituents_data(&sent, wire, 0) == 12);
  assert(decode_index_constituents_data(&got, wire, 0) == 12);
  equal_index_constituents_data(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_index_constituents_data(&got, wire, 0) == 12);
  assert(encode_index_constituents_data(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Secondary Expiry Date: 12 bytes ----------------------------------------- */

/* Secondary Expiry Date */
typedef struct {
  uint8_t year[4];   /* bytes 0 to 3 */
  uint8_t month[4];  /* bytes 4 to 7 */
  uint8_t day[4];    /* bytes 8 to 11 */
} SecondaryExpiryDate;

/* any Secondary Expiry Date at all: every byte one the checker chooses */
static void any_secondary_expiry_date(SecondaryExpiryDate *record) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->month[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->day[i] = arbitrary(); }
}

/* Secondary Expiry Date to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_secondary_expiry_date(const SecondaryExpiryDate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->year[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->month[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->day[i]; }

  return at;
}

/* Secondary Expiry Date off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_secondary_expiry_date(SecondaryExpiryDate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->year[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->month[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->day[i] = wire[at++]; }

  return at;
}

/* what was read of Secondary Expiry Date is what was written, byte for byte */
static void equal_secondary_expiry_date(const SecondaryExpiryDate *read, const SecondaryExpiryDate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->year[i] == written->year[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->month[i] == written->month[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->day[i] == written->day[i]); }
}

/* Secondary Expiry Date: written and read back, then read and written back */
static void check_secondary_expiry_date(void) {
  SecondaryExpiryDate sent;
  SecondaryExpiryDate got;
  uint8_t wire[12];
  uint8_t again[12];

  any_secondary_expiry_date(&sent);
  assert(encode_secondary_expiry_date(&sent, wire, 0) == 12);
  assert(decode_secondary_expiry_date(&got, wire, 0) == 12);
  equal_secondary_expiry_date(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_secondary_expiry_date(&got, wire, 0) == 12);
  assert(encode_secondary_expiry_date(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Contract: 48 bytes ------------------------------------------------ */

/* Order Contract */
typedef struct {
  uint8_t identifier_prefix_b_4[4];           /* bytes 0 to 3 */
  ExpiryDate expiry_date;                     /* bytes 4 to 15 */
  uint8_t instrument_name_b_5[5];             /* bytes 16 to 20 */
  uint8_t strike[8];                          /* bytes 21 to 28 */
  uint8_t call_put_b_1;                       /* byte 29 */
  SecondaryExpiryDate secondary_expiry_date;  /* bytes 30 to 41 */
  uint8_t secondary_instrument_name_b_5[5];   /* bytes 42 to 46 */
  uint8_t is_delta_option;                    /* byte 47 */
} OrderContract;

/* any Order Contract at all: every byte one the checker chooses */
static void any_order_contract(OrderContract *record) {
  for (size_t i = 0; i < 4; i++) { record->identifier_prefix_b_4[i] = arbitrary(); }
  any_expiry_date(&record->expiry_date);
  for (size_t i = 0; i < 5; i++) { record->instrument_name_b_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike[i] = arbitrary(); }
  record->call_put_b_1 = arbitrary();
  any_secondary_expiry_date(&record->secondary_expiry_date);
  for (size_t i = 0; i < 5; i++) { record->secondary_instrument_name_b_5[i] = arbitrary(); }
  record->is_delta_option = arbitrary();
}

/* Order Contract to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_order_contract(const OrderContract *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->identifier_prefix_b_4[i]; }
  at = encode_expiry_date(&record->expiry_date, wire, at);
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->instrument_name_b_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike[i]; }
  wire[at++] = record->call_put_b_1;
  at = encode_secondary_expiry_date(&record->secondary_expiry_date, wire, at);
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->secondary_instrument_name_b_5[i]; }
  wire[at++] = record->is_delta_option;

  return at;
}

/* Order Contract off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_order_contract(OrderContract *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->identifier_prefix_b_4[i] = wire[at++]; }
  at = decode_expiry_date(&record->expiry_date, wire, at);
  for (size_t i = 0; i < 5; i++) { record->instrument_name_b_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike[i] = wire[at++]; }
  record->call_put_b_1 = wire[at++];
  at = decode_secondary_expiry_date(&record->secondary_expiry_date, wire, at);
  for (size_t i = 0; i < 5; i++) { record->secondary_instrument_name_b_5[i] = wire[at++]; }
  record->is_delta_option = wire[at++];

  return at;
}

/* what was read of Order Contract is what was written, byte for byte */
static void equal_order_contract(const OrderContract *read, const OrderContract *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->identifier_prefix_b_4[i] == written->identifier_prefix_b_4[i]); }
  equal_expiry_date(&read->expiry_date, &written->expiry_date);
  for (size_t i = 0; i < 5; i++) { assert(read->instrument_name_b_5[i] == written->instrument_name_b_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike[i] == written->strike[i]); }
  assert(read->call_put_b_1 == written->call_put_b_1);
  equal_secondary_expiry_date(&read->secondary_expiry_date, &written->secondary_expiry_date);
  for (size_t i = 0; i < 5; i++) { assert(read->secondary_instrument_name_b_5[i] == written->secondary_instrument_name_b_5[i]); }
  assert(read->is_delta_option == written->is_delta_option);
}

/* Order Contract: written and read back, then read and written back */
static void check_order_contract(void) {
  OrderContract sent;
  OrderContract got;
  uint8_t wire[48];
  uint8_t again[48];

  any_order_contract(&sent);
  assert(encode_order_contract(&sent, wire, 0) == 48);
  assert(decode_order_contract(&got, wire, 0) == 48);
  equal_order_contract(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_order_contract(&got, wire, 0) == 48);
  assert(encode_order_contract(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Completed Trade Message: 156 bytes -------------------------------------- */

/* Sent when an order has been matched or trading has occurred between two parties. */
typedef struct {
  OrderContract order_contract;       /* bytes 0 to 47 */
  uint8_t sequence_number[4];         /* bytes 48 to 51 */
  uint8_t price[8];                   /* bytes 52 to 59 */
  uint8_t quantity_d_8[8];            /* bytes 60 to 67 */
  uint8_t open_price[8];              /* bytes 68 to 75 */
  uint8_t previous_closing_price[8];  /* bytes 76 to 83 */
  uint8_t closing_price[8];           /* bytes 84 to 91 */
  uint8_t change[8];                  /* bytes 92 to 99 */
  uint8_t open_interest[8];           /* bytes 100 to 107 */
  uint8_t low[8];                     /* bytes 108 to 115 */
  uint8_t high[8];                    /* bytes 116 to 123 */
  uint8_t day_volume[8];              /* bytes 124 to 131 */
  uint8_t vwap[8];                    /* bytes 132 to 139 */
  uint8_t trade_type[4];              /* bytes 140 to 143 */
  TradeDate trade_date;               /* bytes 144 to 155 */
} CompletedTradeMessage;

/* any Completed Trade Message at all: every byte one the checker chooses */
static void any_completed_trade_message(CompletedTradeMessage *record) {
  any_order_contract(&record->order_contract);
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity_d_8[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->previous_closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->change[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->day_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_type[i] = arbitrary(); }
  any_trade_date(&record->trade_date);
}

/* Completed Trade Message to the wire: 156 bytes from at, returning where the next byte goes */
static size_t encode_completed_trade_message(const CompletedTradeMessage *record, uint8_t *wire, size_t at) {
  at = encode_order_contract(&record->order_contract, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity_d_8[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->previous_closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->change[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->day_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_type[i]; }
  at = encode_trade_date(&record->trade_date, wire, at);

  return at;
}

/* Completed Trade Message off the wire: 156 bytes from at, returning where the next byte lies */
static size_t decode_completed_trade_message(CompletedTradeMessage *record, const uint8_t *wire, size_t at) {
  at = decode_order_contract(&record->order_contract, wire, at);
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity_d_8[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->previous_closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->change[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->day_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_type[i] = wire[at++]; }
  at = decode_trade_date(&record->trade_date, wire, at);

  return at;
}

/* what was read of Completed Trade Message is what was written, byte for byte */
static void equal_completed_trade_message(const CompletedTradeMessage *read, const CompletedTradeMessage *written) {
  equal_order_contract(&read->order_contract, &written->order_contract);
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity_d_8[i] == written->quantity_d_8[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_price[i] == written->open_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->previous_closing_price[i] == written->previous_closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->change[i] == written->change[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low[i] == written->low[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high[i] == written->high[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->day_volume[i] == written->day_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_type[i] == written->trade_type[i]); }
  equal_trade_date(&read->trade_date, &written->trade_date);
}

/* Completed Trade Message: written and read back, then read and written back */
static void check_completed_trade_message(void) {
  CompletedTradeMessage sent;
  CompletedTradeMessage got;
  uint8_t wire[156];
  uint8_t again[156];

  any_completed_trade_message(&sent);
  assert(encode_completed_trade_message(&sent, wire, 0) == 156);
  assert(decode_completed_trade_message(&got, wire, 0) == 156);
  equal_completed_trade_message(&got, &sent);

  for (size_t i = 0; i < 156; i++) { wire[i] = arbitrary(); }
  assert(decode_completed_trade_message(&got, wire, 0) == 156);
  assert(encode_completed_trade_message(&got, again, 0) == 156);
  for (size_t i = 0; i < 156; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Dealt Time: 4 bytes ------------------------------------------------ */

/* Last Dealt Time */
typedef struct {
  uint8_t hours;     /* byte 0 */
  uint8_t minutes;   /* byte 1 */
  uint8_t seconds;   /* byte 2 */
  uint8_t unused_1;  /* byte 3 */
} LastDealtTime;

/* any Last Dealt Time at all: every byte one the checker chooses */
static void any_last_dealt_time(LastDealtTime *record) {
  record->hours = arbitrary();
  record->minutes = arbitrary();
  record->seconds = arbitrary();
  record->unused_1 = arbitrary();
}

/* Last Dealt Time to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_last_dealt_time(const LastDealtTime *record, uint8_t *wire, size_t at) {
  wire[at++] = record->hours;
  wire[at++] = record->minutes;
  wire[at++] = record->seconds;
  wire[at++] = record->unused_1;

  return at;
}

/* Last Dealt Time off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_last_dealt_time(LastDealtTime *record, const uint8_t *wire, size_t at) {
  record->hours = wire[at++];
  record->minutes = wire[at++];
  record->seconds = wire[at++];
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Last Dealt Time is what was written, byte for byte */
static void equal_last_dealt_time(const LastDealtTime *read, const LastDealtTime *written) {
  assert(read->hours == written->hours);
  assert(read->minutes == written->minutes);
  assert(read->seconds == written->seconds);
  assert(read->unused_1 == written->unused_1);
}

/* Last Dealt Time: written and read back, then read and written back */
static void check_last_dealt_time(void) {
  LastDealtTime sent;
  LastDealtTime got;
  uint8_t wire[4];
  uint8_t again[4];

  any_last_dealt_time(&sent);
  assert(encode_last_dealt_time(&sent, wire, 0) == 4);
  assert(decode_last_dealt_time(&got, wire, 0) == 4);
  equal_last_dealt_time(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_last_dealt_time(&got, wire, 0) == 4);
  assert(encode_last_dealt_time(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Display: 204 bytes ------------------------------------------------------ */

/* Display */
typedef struct {
  uint8_t trading_anonymous;                       /* byte 0 */
  Contract contract;                               /* bytes 1 to 48 */
  uint8_t mid_price[8];                            /* bytes 49 to 56 */
  uint8_t last_dealt_price[8];                     /* bytes 57 to 64 */
  LastDealtTime last_dealt_time;                   /* bytes 65 to 68 */
  uint8_t deal_volume[8];                          /* bytes 69 to 76 */
  uint8_t high_price[8];                           /* bytes 77 to 84 */
  uint8_t low_price[8];                            /* bytes 85 to 92 */
  uint8_t days_volume_i_8[8];                      /* bytes 93 to 100 */
  uint8_t last_order_qty[4];                       /* bytes 101 to 104 */
  uint8_t last_order_buy_sell;                     /* byte 105 */
  uint8_t last_order_price[8];                     /* bytes 106 to 113 */
  uint8_t number_of_depth;                         /* byte 114 */
  uint8_t open_interest[8];                        /* bytes 115 to 122 */
  uint8_t change[8];                               /* bytes 123 to 130 */
  uint8_t auction;                                 /* byte 131 */
  uint8_t contract_status;                         /* byte 132 */
  uint8_t odd_lot;                                 /* byte 133 */
  uint8_t last_traded_quantity[8];                 /* bytes 134 to 141 */
  uint8_t date_sequence[4];                        /* bytes 142 to 145 */
  uint8_t secondary_contract_date_sequence[4];     /* bytes 146 to 149 */
  uint8_t strike_sequence[4];                      /* bytes 150 to 153 */
  uint8_t market_shard_global_sequence_number[4];  /* bytes 154 to 157 */
  uint8_t stack_sequence_number[4];                /* bytes 158 to 161 */
  uint8_t unused_21[21];                           /* bytes 162 to 182 */
  UpdateTime update_time;                          /* bytes 183 to 186 */
  uint8_t vwap[8];                                 /* bytes 187 to 194 */
  uint8_t closing_price[8];                        /* bytes 195 to 202 */
  uint8_t reserved_1;                              /* byte 203 */
} Display;

/* any Display at all: every byte one the checker chooses */
static void any_display(Display *record) {
  record->trading_anonymous = arbitrary();
  any_contract(&record->contract);
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->last_dealt_price[i] = arbitrary(); }
  any_last_dealt_time(&record->last_dealt_time);
  for (size_t i = 0; i < 8; i++) { record->deal_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->days_volume_i_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_order_qty[i] = arbitrary(); }
  record->last_order_buy_sell = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_order_price[i] = arbitrary(); }
  record->number_of_depth = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->change[i] = arbitrary(); }
  record->auction = arbitrary();
  record->contract_status = arbitrary();
  record->odd_lot = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_traded_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->date_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_contract_date_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_shard_global_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->stack_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 21; i++) { record->unused_21[i] = arbitrary(); }
  any_update_time(&record->update_time);
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Display to the wire: 204 bytes from at, returning where the next byte goes */
static size_t encode_display(const Display *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_anonymous;
  at = encode_contract(&record->contract, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_dealt_price[i]; }
  at = encode_last_dealt_time(&record->last_dealt_time, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->deal_volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->days_volume_i_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_order_qty[i]; }
  wire[at++] = record->last_order_buy_sell;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_order_price[i]; }
  wire[at++] = record->number_of_depth;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->open_interest[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->change[i]; }
  wire[at++] = record->auction;
  wire[at++] = record->contract_status;
  wire[at++] = record->odd_lot;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_traded_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_contract_date_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_shard_global_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->stack_sequence_number[i]; }
  for (size_t i = 0; i < 21; i++) { wire[at++] = record->unused_21[i]; }
  at = encode_update_time(&record->update_time, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->vwap[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Display off the wire: 204 bytes from at, returning where the next byte lies */
static size_t decode_display(Display *record, const uint8_t *wire, size_t at) {
  record->trading_anonymous = wire[at++];
  at = decode_contract(&record->contract, wire, at);
  for (size_t i = 0; i < 8; i++) { record->mid_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->last_dealt_price[i] = wire[at++]; }
  at = decode_last_dealt_time(&record->last_dealt_time, wire, at);
  for (size_t i = 0; i < 8; i++) { record->deal_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->days_volume_i_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_order_qty[i] = wire[at++]; }
  record->last_order_buy_sell = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_order_price[i] = wire[at++]; }
  record->number_of_depth = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->open_interest[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->change[i] = wire[at++]; }
  record->auction = wire[at++];
  record->contract_status = wire[at++];
  record->odd_lot = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_traded_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->date_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_contract_date_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_shard_global_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->stack_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 21; i++) { record->unused_21[i] = wire[at++]; }
  at = decode_update_time(&record->update_time, wire, at);
  for (size_t i = 0; i < 8; i++) { record->vwap[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_price[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Display is what was written, byte for byte */
static void equal_display(const Display *read, const Display *written) {
  assert(read->trading_anonymous == written->trading_anonymous);
  equal_contract(&read->contract, &written->contract);
  for (size_t i = 0; i < 8; i++) { assert(read->mid_price[i] == written->mid_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->last_dealt_price[i] == written->last_dealt_price[i]); }
  equal_last_dealt_time(&read->last_dealt_time, &written->last_dealt_time);
  for (size_t i = 0; i < 8; i++) { assert(read->deal_volume[i] == written->deal_volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_price[i] == written->high_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_price[i] == written->low_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->days_volume_i_8[i] == written->days_volume_i_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_order_qty[i] == written->last_order_qty[i]); }
  assert(read->last_order_buy_sell == written->last_order_buy_sell);
  for (size_t i = 0; i < 8; i++) { assert(read->last_order_price[i] == written->last_order_price[i]); }
  assert(read->number_of_depth == written->number_of_depth);
  for (size_t i = 0; i < 8; i++) { assert(read->open_interest[i] == written->open_interest[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->change[i] == written->change[i]); }
  assert(read->auction == written->auction);
  assert(read->contract_status == written->contract_status);
  assert(read->odd_lot == written->odd_lot);
  for (size_t i = 0; i < 8; i++) { assert(read->last_traded_quantity[i] == written->last_traded_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->date_sequence[i] == written->date_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_contract_date_sequence[i] == written->secondary_contract_date_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_sequence[i] == written->strike_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_shard_global_sequence_number[i] == written->market_shard_global_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->stack_sequence_number[i] == written->stack_sequence_number[i]); }
  for (size_t i = 0; i < 21; i++) { assert(read->unused_21[i] == written->unused_21[i]); }
  equal_update_time(&read->update_time, &written->update_time);
  for (size_t i = 0; i < 8; i++) { assert(read->vwap[i] == written->vwap[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Display: written and read back, then read and written back */
static void check_display(void) {
  Display sent;
  Display got;
  uint8_t wire[204];
  uint8_t again[204];

  any_display(&sent);
  assert(encode_display(&sent, wire, 0) == 204);
  assert(decode_display(&got, wire, 0) == 204);
  equal_display(&got, &sent);

  for (size_t i = 0; i < 204; i++) { wire[i] = arbitrary(); }
  assert(decode_display(&got, wire, 0) == 204);
  assert(encode_display(&got, again, 0) == 204);
  for (size_t i = 0; i < 204; i++) { assert(again[i] == wire[i]); }
}

/* ---- Buy Who Member: 6 bytes ------------------------------------------------- */

/* Member bidding */
typedef struct {
  uint8_t buy_who_length_byte;    /* byte 0 */
  uint8_t buy_who_characters[5];  /* bytes 1 to 5 */
} BuyWhoMember;

/* any Buy Who Member at all: every byte one the checker chooses */
static void any_buy_who_member(BuyWhoMember *record) {
  record->buy_who_length_byte = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->buy_who_characters[i] = arbitrary(); }
}

/* Buy Who Member to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_buy_who_member(const BuyWhoMember *record, uint8_t *wire, size_t at) {
  wire[at++] = record->buy_who_length_byte;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->buy_who_characters[i]; }

  return at;
}

/* Buy Who Member off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_buy_who_member(BuyWhoMember *record, const uint8_t *wire, size_t at) {
  record->buy_who_length_byte = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->buy_who_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Buy Who Member is what was written, byte for byte */
static void equal_buy_who_member(const BuyWhoMember *read, const BuyWhoMember *written) {
  assert(read->buy_who_length_byte == written->buy_who_length_byte);
  for (size_t i = 0; i < 5; i++) { assert(read->buy_who_characters[i] == written->buy_who_characters[i]); }
}

/* Buy Who Member: written and read back, then read and written back */
static void check_buy_who_member(void) {
  BuyWhoMember sent;
  BuyWhoMember got;
  uint8_t wire[6];
  uint8_t again[6];

  any_buy_who_member(&sent);
  assert(encode_buy_who_member(&sent, wire, 0) == 6);
  assert(decode_buy_who_member(&got, wire, 0) == 6);
  equal_buy_who_member(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_buy_who_member(&got, wire, 0) == 6);
  assert(encode_buy_who_member(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Buy Who Unique Member: 6 bytes ------------------------------------------ */

/* Anonymous contract: length byte 0, then the unique member number */
typedef struct {
  uint8_t buy_who_length_byte;      /* byte 0 */
  uint8_t unique_member_number[4];  /* bytes 1 to 4 */
  uint8_t unused_1;                 /* byte 5 */
} BuyWhoUniqueMember;

/* any Buy Who Unique Member at all: every byte one the checker chooses */
static void any_buy_who_unique_member(BuyWhoUniqueMember *record) {
  record->buy_who_length_byte = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->unique_member_number[i] = arbitrary(); }
  record->unused_1 = arbitrary();
}

/* Buy Who Unique Member to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_buy_who_unique_member(const BuyWhoUniqueMember *record, uint8_t *wire, size_t at) {
  wire[at++] = record->buy_who_length_byte;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unique_member_number[i]; }
  wire[at++] = record->unused_1;

  return at;
}

/* Buy Who Unique Member off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_buy_who_unique_member(BuyWhoUniqueMember *record, const uint8_t *wire, size_t at) {
  record->buy_who_length_byte = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->unique_member_number[i] = wire[at++]; }
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Buy Who Unique Member is what was written, byte for byte */
static void equal_buy_who_unique_member(const BuyWhoUniqueMember *read, const BuyWhoUniqueMember *written) {
  assert(read->buy_who_length_byte == written->buy_who_length_byte);
  for (size_t i = 0; i < 4; i++) { assert(read->unique_member_number[i] == written->unique_member_number[i]); }
  assert(read->unused_1 == written->unused_1);
}

/* Buy Who Unique Member: written and read back, then read and written back */
static void check_buy_who_unique_member(void) {
  BuyWhoUniqueMember sent;
  BuyWhoUniqueMember got;
  uint8_t wire[6];
  uint8_t again[6];

  any_buy_who_unique_member(&sent);
  assert(encode_buy_who_unique_member(&sent, wire, 0) == 6);
  assert(decode_buy_who_unique_member(&got, wire, 0) == 6);
  equal_buy_who_unique_member(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_buy_who_unique_member(&got, wire, 0) == 6);
  assert(encode_buy_who_unique_member(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sell Who Member: 6 bytes ------------------------------------------------ */

/* Member asking */
typedef struct {
  uint8_t sell_who_length_byte;    /* byte 0 */
  uint8_t sell_who_characters[5];  /* bytes 1 to 5 */
} SellWhoMember;

/* any Sell Who Member at all: every byte one the checker chooses */
static void any_sell_who_member(SellWhoMember *record) {
  record->sell_who_length_byte = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->sell_who_characters[i] = arbitrary(); }
}

/* Sell Who Member to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_sell_who_member(const SellWhoMember *record, uint8_t *wire, size_t at) {
  wire[at++] = record->sell_who_length_byte;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sell_who_characters[i]; }

  return at;
}

/* Sell Who Member off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_sell_who_member(SellWhoMember *record, const uint8_t *wire, size_t at) {
  record->sell_who_length_byte = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->sell_who_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Sell Who Member is what was written, byte for byte */
static void equal_sell_who_member(const SellWhoMember *read, const SellWhoMember *written) {
  assert(read->sell_who_length_byte == written->sell_who_length_byte);
  for (size_t i = 0; i < 5; i++) { assert(read->sell_who_characters[i] == written->sell_who_characters[i]); }
}

/* Sell Who Member: written and read back, then read and written back */
static void check_sell_who_member(void) {
  SellWhoMember sent;
  SellWhoMember got;
  uint8_t wire[6];
  uint8_t again[6];

  any_sell_who_member(&sent);
  assert(encode_sell_who_member(&sent, wire, 0) == 6);
  assert(decode_sell_who_member(&got, wire, 0) == 6);
  equal_sell_who_member(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_sell_who_member(&got, wire, 0) == 6);
  assert(encode_sell_who_member(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sell Who Unique Member: 6 bytes ----------------------------------------- */

/* Anonymous contract: length byte 0, then the unique member number */
typedef struct {
  uint8_t sell_who_length_byte;     /* byte 0 */
  uint8_t unique_member_number[4];  /* bytes 1 to 4 */
  uint8_t unused_1;                 /* byte 5 */
} SellWhoUniqueMember;

/* any Sell Who Unique Member at all: every byte one the checker chooses */
static void any_sell_who_unique_member(SellWhoUniqueMember *record) {
  record->sell_who_length_byte = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->unique_member_number[i] = arbitrary(); }
  record->unused_1 = arbitrary();
}

/* Sell Who Unique Member to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_sell_who_unique_member(const SellWhoUniqueMember *record, uint8_t *wire, size_t at) {
  wire[at++] = record->sell_who_length_byte;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->unique_member_number[i]; }
  wire[at++] = record->unused_1;

  return at;
}

/* Sell Who Unique Member off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_sell_who_unique_member(SellWhoUniqueMember *record, const uint8_t *wire, size_t at) {
  record->sell_who_length_byte = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->unique_member_number[i] = wire[at++]; }
  record->unused_1 = wire[at++];

  return at;
}

/* what was read of Sell Who Unique Member is what was written, byte for byte */
static void equal_sell_who_unique_member(const SellWhoUniqueMember *read, const SellWhoUniqueMember *written) {
  assert(read->sell_who_length_byte == written->sell_who_length_byte);
  for (size_t i = 0; i < 4; i++) { assert(read->unique_member_number[i] == written->unique_member_number[i]); }
  assert(read->unused_1 == written->unused_1);
}

/* Sell Who Unique Member: written and read back, then read and written back */
static void check_sell_who_unique_member(void) {
  SellWhoUniqueMember sent;
  SellWhoUniqueMember got;
  uint8_t wire[6];
  uint8_t again[6];

  any_sell_who_unique_member(&sent);
  assert(encode_sell_who_unique_member(&sent, wire, 0) == 6);
  assert(decode_sell_who_unique_member(&got, wire, 0) == 6);
  equal_sell_who_unique_member(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_sell_who_unique_member(&got, wire, 0) == 6);
  assert(encode_sell_who_unique_member(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Index Sequence Number: 4 bytes ------------------------------------------ */

/* Indicates the sequence number of the index. */
typedef struct {
  uint8_t index_sequence_number_length_byte;    /* byte 0 */
  uint8_t index_sequence_number_characters[3];  /* bytes 1 to 3 */
} IndexSequenceNumber;

/* any Index Sequence Number at all: every byte one the checker chooses */
static void any_index_sequence_number(IndexSequenceNumber *record) {
  record->index_sequence_number_length_byte = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->index_sequence_number_characters[i] = arbitrary(); }
}

/* Index Sequence Number to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_index_sequence_number(const IndexSequenceNumber *record, uint8_t *wire, size_t at) {
  wire[at++] = record->index_sequence_number_length_byte;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->index_sequence_number_characters[i]; }

  return at;
}

/* Index Sequence Number off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_index_sequence_number(IndexSequenceNumber *record, const uint8_t *wire, size_t at) {
  record->index_sequence_number_length_byte = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->index_sequence_number_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Index Sequence Number is what was written, byte for byte */
static void equal_index_sequence_number(const IndexSequenceNumber *read, const IndexSequenceNumber *written) {
  assert(read->index_sequence_number_length_byte == written->index_sequence_number_length_byte);
  for (size_t i = 0; i < 3; i++) { assert(read->index_sequence_number_characters[i] == written->index_sequence_number_characters[i]); }
}

/* Index Sequence Number: written and read back, then read and written back */
static void check_index_sequence_number(void) {
  IndexSequenceNumber sent;
  IndexSequenceNumber got;
  uint8_t wire[4];
  uint8_t again[4];

  any_index_sequence_number(&sent);
  assert(encode_index_sequence_number(&sent, wire, 0) == 4);
  assert(decode_index_sequence_number(&got, wire, 0) == 4);
  equal_index_sequence_number(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_index_sequence_number(&got, wire, 0) == 4);
  assert(encode_index_sequence_number(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indices Message: 44 bytes ----------------------------------------------- */

/* Each Index will be sent in this format. */
typedef struct {
  IndexSequenceNumber index_sequence_number;  /* bytes 0 to 3 */
  uint8_t opening_price[8];                   /* bytes 4 to 11 */
  uint8_t index_price[8];                     /* bytes 12 to 19 */
  UpdateTime update_time;                     /* bytes 20 to 23 */
  UpdateDate update_date;                     /* bytes 24 to 35 */
  uint8_t market_capitalisation[8];           /* bytes 36 to 43 */
} IndicesMessage;

/* any Indices Message at all: every byte one the checker chooses */
static void any_indices_message(IndicesMessage *record) {
  any_index_sequence_number(&record->index_sequence_number);
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = arbitrary(); }
  any_update_time(&record->update_time);
  any_update_date(&record->update_date);
  for (size_t i = 0; i < 8; i++) { record->market_capitalisation[i] = arbitrary(); }
}

/* Indices Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_indices_message(const IndicesMessage *record, uint8_t *wire, size_t at) {
  at = encode_index_sequence_number(&record->index_sequence_number, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->index_price[i]; }
  at = encode_update_time(&record->update_time, wire, at);
  at = encode_update_date(&record->update_date, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->market_capitalisation[i]; }

  return at;
}

/* Indices Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_indices_message(IndicesMessage *record, const uint8_t *wire, size_t at) {
  at = decode_index_sequence_number(&record->index_sequence_number, wire, at);
  for (size_t i = 0; i < 8; i++) { record->opening_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->index_price[i] = wire[at++]; }
  at = decode_update_time(&record->update_time, wire, at);
  at = decode_update_date(&record->update_date, wire, at);
  for (size_t i = 0; i < 8; i++) { record->market_capitalisation[i] = wire[at++]; }

  return at;
}

/* what was read of Indices Message is what was written, byte for byte */
static void equal_indices_message(const IndicesMessage *read, const IndicesMessage *written) {
  equal_index_sequence_number(&read->index_sequence_number, &written->index_sequence_number);
  for (size_t i = 0; i < 8; i++) { assert(read->opening_price[i] == written->opening_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->index_price[i] == written->index_price[i]); }
  equal_update_time(&read->update_time, &written->update_time);
  equal_update_date(&read->update_date, &written->update_date);
  for (size_t i = 0; i < 8; i++) { assert(read->market_capitalisation[i] == written->market_capitalisation[i]); }
}

/* Indices Message: written and read back, then read and written back */
static void check_indices_message(void) {
  IndicesMessage sent;
  IndicesMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_indices_message(&sent);
  assert(encode_indices_message(&sent, wire, 0) == 44);
  assert(decode_indices_message(&got, wire, 0) == 44);
  equal_indices_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_indices_message(&got, wire, 0) == 44);
  assert(encode_indices_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message P 250: 250 bytes ------------------------------------------------ */

/* A Description of the error. */
typedef struct {
  uint8_t message_p_250_length_byte;      /* byte 0 */
  uint8_t message_p_250_characters[249];  /* bytes 1 to 249 */
} MessageP250;

/* any Message P 250 at all: every byte one the checker chooses */
static void any_message_p250(MessageP250 *record) {
  record->message_p_250_length_byte = arbitrary();
  for (size_t i = 0; i < 249; i++) { record->message_p_250_characters[i] = arbitrary(); }
}

/* Message P 250 to the wire: 250 bytes from at, returning where the next byte goes */
static size_t encode_message_p250(const MessageP250 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->message_p_250_length_byte;
  for (size_t i = 0; i < 249; i++) { wire[at++] = record->message_p_250_characters[i]; }

  return at;
}

/* Message P 250 off the wire: 250 bytes from at, returning where the next byte lies */
static size_t decode_message_p250(MessageP250 *record, const uint8_t *wire, size_t at) {
  record->message_p_250_length_byte = wire[at++];
  for (size_t i = 0; i < 249; i++) { record->message_p_250_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Message P 250 is what was written, byte for byte */
static void equal_message_p250(const MessageP250 *read, const MessageP250 *written) {
  assert(read->message_p_250_length_byte == written->message_p_250_length_byte);
  for (size_t i = 0; i < 249; i++) { assert(read->message_p_250_characters[i] == written->message_p_250_characters[i]); }
}

/* Message P 250: written and read back, then read and written back */
static void check_message_p250(void) {
  MessageP250 sent;
  MessageP250 got;
  uint8_t wire[250];
  uint8_t again[250];

  any_message_p250(&sent);
  assert(encode_message_p250(&sent, wire, 0) == 250);
  assert(decode_message_p250(&got, wire, 0) == 250);
  equal_message_p250(&got, &sent);

  for (size_t i = 0; i < 250; i++) { wire[i] = arbitrary(); }
  assert(decode_message_p250(&got, wire, 0) == 250);
  assert(encode_message_p250(&got, again, 0) == 250);
  for (size_t i = 0; i < 250; i++) { assert(again[i] == wire[i]); }
}

/* ---- Exchange Announcements Message: 263 bytes ------------------------------- */

/* Error and information messages. */
typedef struct {
  uint8_t market_number_i_4[4];            /* bytes 0 to 3 */
  uint8_t market_shard_number_i_4[4];      /* bytes 4 to 7 */
  uint8_t error_number[4];                 /* bytes 8 to 11 */
  uint8_t information_or_error_indicator;  /* byte 12 */
  MessageP250 message_p_250;               /* bytes 13 to 262 */
} ExchangeAnnouncementsMessage;

/* any Exchange Announcements Message at all: every byte one the checker chooses */
static void any_exchange_announcements_message(ExchangeAnnouncementsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->market_number_i_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_shard_number_i_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->error_number[i] = arbitrary(); }
  record->information_or_error_indicator = arbitrary();
  any_message_p250(&record->message_p_250);
}

/* Exchange Announcements Message to the wire: 263 bytes from at, returning where the next byte goes */
static size_t encode_exchange_announcements_message(const ExchangeAnnouncementsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_number_i_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_shard_number_i_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->error_number[i]; }
  wire[at++] = record->information_or_error_indicator;
  at = encode_message_p250(&record->message_p_250, wire, at);

  return at;
}

/* Exchange Announcements Message off the wire: 263 bytes from at, returning where the next byte lies */
static size_t decode_exchange_announcements_message(ExchangeAnnouncementsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_number_i_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_shard_number_i_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->error_number[i] = wire[at++]; }
  record->information_or_error_indicator = wire[at++];
  at = decode_message_p250(&record->message_p_250, wire, at);

  return at;
}

/* what was read of Exchange Announcements Message is what was written, byte for byte */
static void equal_exchange_announcements_message(const ExchangeAnnouncementsMessage *read, const ExchangeAnnouncementsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_number_i_4[i] == written->market_number_i_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_shard_number_i_4[i] == written->market_shard_number_i_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->error_number[i] == written->error_number[i]); }
  assert(read->information_or_error_indicator == written->information_or_error_indicator);
  equal_message_p250(&read->message_p_250, &written->message_p_250);
}

/* Exchange Announcements Message: written and read back, then read and written back */
static void check_exchange_announcements_message(void) {
  ExchangeAnnouncementsMessage sent;
  ExchangeAnnouncementsMessage got;
  uint8_t wire[263];
  uint8_t again[263];

  any_exchange_announcements_message(&sent);
  assert(encode_exchange_announcements_message(&sent, wire, 0) == 263);
  assert(decode_exchange_announcements_message(&got, wire, 0) == 263);
  equal_exchange_announcements_message(&got, &sent);

  for (size_t i = 0; i < 263; i++) { wire[i] = arbitrary(); }
  assert(decode_exchange_announcements_message(&got, wire, 0) == 263);
  assert(encode_exchange_announcements_message(&got, again, 0) == 263);
  for (size_t i = 0; i < 263; i++) { assert(again[i] == wire[i]); }
}

/* ---- Notification Of Failure Message: 12 bytes ------------------------------- */

/* Sent on the failure or the recovery of the exchange trading system. */
typedef struct {
  uint8_t failure_notice_identifier[4];  /* bytes 0 to 3 */
  uint8_t market_number_i_4[4];          /* bytes 4 to 7 */
  uint8_t market_shard_number_i_4[4];    /* bytes 8 to 11 */
} NotificationOfFailureMessage;

/* any Notification Of Failure Message at all: every byte one the checker chooses */
static void any_notification_of_failure_message(NotificationOfFailureMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->failure_notice_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_number_i_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_shard_number_i_4[i] = arbitrary(); }
}

/* Notification Of Failure Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_notification_of_failure_message(const NotificationOfFailureMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->failure_notice_identifier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_number_i_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_shard_number_i_4[i]; }

  return at;
}

/* Notification Of Failure Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_notification_of_failure_message(NotificationOfFailureMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->failure_notice_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_number_i_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_shard_number_i_4[i] = wire[at++]; }

  return at;
}

/* what was read of Notification Of Failure Message is what was written, byte for byte */
static void equal_notification_of_failure_message(const NotificationOfFailureMessage *read, const NotificationOfFailureMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->failure_notice_identifier[i] == written->failure_notice_identifier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_number_i_4[i] == written->market_number_i_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_shard_number_i_4[i] == written->market_shard_number_i_4[i]); }
}

/* Notification Of Failure Message: written and read back, then read and written back */
static void check_notification_of_failure_message(void) {
  NotificationOfFailureMessage sent;
  NotificationOfFailureMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_notification_of_failure_message(&sent);
  assert(encode_notification_of_failure_message(&sent, wire, 0) == 12);
  assert(decode_notification_of_failure_message(&got, wire, 0) == 12);
  equal_notification_of_failure_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_notification_of_failure_message(&got, wire, 0) == 12);
  assert(encode_notification_of_failure_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reference Message Type: 3 bytes ----------------------------------------- */

/* Indicates the message type of the incoming message this reject is in response to. */
typedef struct {
  uint8_t reference_message_type_length_byte;    /* byte 0 */
  uint8_t reference_message_type_characters[2];  /* bytes 1 to 2 */
} ReferenceMessageType;

/* any Reference Message Type at all: every byte one the checker chooses */
static void any_reference_message_type(ReferenceMessageType *record) {
  record->reference_message_type_length_byte = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->reference_message_type_characters[i] = arbitrary(); }
}

/* Reference Message Type to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_reference_message_type(const ReferenceMessageType *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reference_message_type_length_byte;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reference_message_type_characters[i]; }

  return at;
}

/* Reference Message Type off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_reference_message_type(ReferenceMessageType *record, const uint8_t *wire, size_t at) {
  record->reference_message_type_length_byte = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->reference_message_type_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Reference Message Type is what was written, byte for byte */
static void equal_reference_message_type(const ReferenceMessageType *read, const ReferenceMessageType *written) {
  assert(read->reference_message_type_length_byte == written->reference_message_type_length_byte);
  for (size_t i = 0; i < 2; i++) { assert(read->reference_message_type_characters[i] == written->reference_message_type_characters[i]); }
}

/* Reference Message Type: written and read back, then read and written back */
static void check_reference_message_type(void) {
  ReferenceMessageType sent;
  ReferenceMessageType got;
  uint8_t wire[3];
  uint8_t again[3];

  any_reference_message_type(&sent);
  assert(encode_reference_message_type(&sent, wire, 0) == 3);
  assert(decode_reference_message_type(&got, wire, 0) == 3);
  equal_reference_message_type(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_reference_message_type(&got, wire, 0) == 3);
  assert(encode_reference_message_type(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Text P 250: 250 bytes --------------------------------------------------- */

/* The text of the rejection message. */
typedef struct {
  uint8_t text_p_250_length_byte;      /* byte 0 */
  uint8_t text_p_250_characters[249];  /* bytes 1 to 249 */
} TextP250;

/* any Text P 250 at all: every byte one the checker chooses */
static void any_text_p250(TextP250 *record) {
  record->text_p_250_length_byte = arbitrary();
  for (size_t i = 0; i < 249; i++) { record->text_p_250_characters[i] = arbitrary(); }
}

/* Text P 250 to the wire: 250 bytes from at, returning where the next byte goes */
static size_t encode_text_p250(const TextP250 *record, uint8_t *wire, size_t at) {
  wire[at++] = record->text_p_250_length_byte;
  for (size_t i = 0; i < 249; i++) { wire[at++] = record->text_p_250_characters[i]; }

  return at;
}

/* Text P 250 off the wire: 250 bytes from at, returning where the next byte lies */
static size_t decode_text_p250(TextP250 *record, const uint8_t *wire, size_t at) {
  record->text_p_250_length_byte = wire[at++];
  for (size_t i = 0; i < 249; i++) { record->text_p_250_characters[i] = wire[at++]; }

  return at;
}

/* what was read of Text P 250 is what was written, byte for byte */
static void equal_text_p250(const TextP250 *read, const TextP250 *written) {
  assert(read->text_p_250_length_byte == written->text_p_250_length_byte);
  for (size_t i = 0; i < 249; i++) { assert(read->text_p_250_characters[i] == written->text_p_250_characters[i]); }
}

/* Text P 250: written and read back, then read and written back */
static void check_text_p250(void) {
  TextP250 sent;
  TextP250 got;
  uint8_t wire[250];
  uint8_t again[250];

  any_text_p250(&sent);
  assert(encode_text_p250(&sent, wire, 0) == 250);
  assert(decode_text_p250(&got, wire, 0) == 250);
  equal_text_p250(&got, &sent);

  for (size_t i = 0; i < 250; i++) { wire[i] = arbitrary(); }
  assert(decode_text_p250(&got, wire, 0) == 250);
  assert(encode_text_p250(&got, again, 0) == 250);
  for (size_t i = 0; i < 250; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Message Reject Message: 257 bytes ------------------------------ */

/* Returned in response to an incoming message to indicate a failure to process this message for some business validation failure. */
typedef struct {
  uint8_t reference_sequence_number[4];         /* bytes 0 to 3 */
  ReferenceMessageType reference_message_type;  /* bytes 4 to 6 */
  TextP250 text_p_250;                          /* bytes 7 to 256 */
} BusinessMessageRejectMessage;

/* any Business Message Reject Message at all: every byte one the checker chooses */
static void any_business_message_reject_message(BusinessMessageRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->reference_sequence_number[i] = arbitrary(); }
  any_reference_message_type(&record->reference_message_type);
  any_text_p250(&record->text_p_250);
}

/* Business Message Reject Message to the wire: 257 bytes from at, returning where the next byte goes */
static size_t encode_business_message_reject_message(const BusinessMessageRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reference_sequence_number[i]; }
  at = encode_reference_message_type(&record->reference_message_type, wire, at);
  at = encode_text_p250(&record->text_p_250, wire, at);

  return at;
}

/* Business Message Reject Message off the wire: 257 bytes from at, returning where the next byte lies */
static size_t decode_business_message_reject_message(BusinessMessageRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->reference_sequence_number[i] = wire[at++]; }
  at = decode_reference_message_type(&record->reference_message_type, wire, at);
  at = decode_text_p250(&record->text_p_250, wire, at);

  return at;
}

/* what was read of Business Message Reject Message is what was written, byte for byte */
static void equal_business_message_reject_message(const BusinessMessageRejectMessage *read, const BusinessMessageRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->reference_sequence_number[i] == written->reference_sequence_number[i]); }
  equal_reference_message_type(&read->reference_message_type, &written->reference_message_type);
  equal_text_p250(&read->text_p_250, &written->text_p_250);
}

/* Business Message Reject Message: written and read back, then read and written back */
static void check_business_message_reject_message(void) {
  BusinessMessageRejectMessage sent;
  BusinessMessageRejectMessage got;
  uint8_t wire[257];
  uint8_t again[257];

  any_business_message_reject_message(&sent);
  assert(encode_business_message_reject_message(&sent, wire, 0) == 257);
  assert(decode_business_message_reject_message(&got, wire, 0) == 257);
  equal_business_message_reject_message(&got, &sent);

  for (size_t i = 0; i < 257; i++) { wire[i] = arbitrary(); }
  assert(decode_business_message_reject_message(&got, wire, 0) == 257);
  assert(encode_business_message_reject_message(&got, again, 0) == 257);
  for (size_t i = 0; i < 257; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_transport_header();
  check_user_name();
  check_time();
  check_server_message_header();
  check_today_date();
  check_country_code();
  check_previous_business_day();
  check_text_p50();
  check_member_code_p6();
  check_session_key_challenge_message();
  check_download_date();
  check_date();
  check_instrument_name_p5();
  check_secondary_date();
  check_secondary_instrument_name_p5();
  check_contract();
  check_market_display_data();
  check_isin_code();
  check_description_p62();
  check_maturity_date();
  check_issue_date();
  check_group_description();
  check_first_trade_reference();
  check_display_name();
  check_classification();
  check_vetting_agent_name();
  check_vetting_agent_contact();
  check_sector();
  check_security_type();
  check_instruments_data();
  check_expiry_date();
  check_valuation_date();
  check_clearance_date();
  check_contract_dates();
  check_strike_expiry_date();
  check_strike_data();
  check_member_code_p5();
  check_description_p50();
  check_sor_account();
  check_member_data();
  check_mtm_data();
  check_holiday_date();
  check_holiday_data();
  check_instrument_type_code();
  check_instrument_type_name();
  check_instrument_types();
  check_clearing_member_code();
  check_clearing_member_description();
  check_clearing_member_data();
  check_announcement_date();
  check_announcement_time();
  check_announcement();
  check_exchange_announcements();
  check_message_category_value();
  check_message_p255();
  check_news_service();
  check_coupon_date();
  check_books_close_date();
  check_coupon_information();
  check_trading_session_name();
  check_opening_auction_start_time();
  check_opening_auction_close_time();
  check_closing_auction_start_time();
  check_closing_auction_close_time();
  check_contract_open_time();
  check_contract_close_time();
  check_intraday_auction_one_start_time();
  check_intraday_auction_one_auction_close_time();
  check_intraday_auction_two_start_time();
  check_intraday_auction_two_auction_close_time();
  check_intraday_auction_three_start_time();
  check_intraday_auction_three_auction_close_time();
  check_overnight_admin_open_time();
  check_overnight_admin_close_time();
  check_admin_period_close_time();
  check_pre_open_order_entry_open_time();
  check_pre_open_order_entry_close_time();
  check_trading_sessions();
  check_update_time();
  check_update_date();
  check_indices_price_data();
  check_indices_code();
  check_indices_description();
  check_indices_data();
  check_shares_in_issue_data();
  check_trade_date();
  check_index_data();
  check_index_constituents_data();
  check_secondary_expiry_date();
  check_order_contract();
  check_completed_trade_message();
  check_last_dealt_time();
  check_display();
  check_buy_who_member();
  check_buy_who_unique_member();
  check_sell_who_member();
  check_sell_who_unique_member();
  check_index_sequence_number();
  check_indices_message();
  check_message_p250();
  check_exchange_announcements_message();
  check_notification_of_failure_message();
  check_reference_message_type();
  check_text_p250();
  check_business_message_reject_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
