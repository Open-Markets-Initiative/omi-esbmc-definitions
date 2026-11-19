// nairobi/nairobibonds/marketdata/NairobiBonds_MarketData_v2_14_Client.c
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
 *   - a run of a stated number of entries
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

/* ---- Client Message Header: 29 bytes ----------------------------------------- */

/* Table 2: Message Header */
typedef struct {
  uint8_t sequence_number[4];   /* bytes 0 to 3 */
  UserName user_name;           /* bytes 4 to 19 */
  uint8_t user_number[4];       /* bytes 20 to 23 */
  Time time;                    /* bytes 24 to 27 */
  uint8_t client_message_type;  /* byte 28 */
} ClientMessageHeader;

/* any Client Message Header at all: every byte one the checker chooses */
static void any_client_message_header(ClientMessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  any_user_name(&record->user_name);
  for (size_t i = 0; i < 4; i++) { record->user_number[i] = arbitrary(); }
  any_time(&record->time);
  record->client_message_type = arbitrary();
}

/* Client Message Header to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_client_message_header(const ClientMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  at = encode_user_name(&record->user_name, wire, at);
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->user_number[i]; }
  at = encode_time(&record->time, wire, at);
  wire[at++] = record->client_message_type;

  return at;
}

/* Client Message Header off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_client_message_header(ClientMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  at = decode_user_name(&record->user_name, wire, at);
  for (size_t i = 0; i < 4; i++) { record->user_number[i] = wire[at++]; }
  at = decode_time(&record->time, wire, at);
  record->client_message_type = wire[at++];

  return at;
}

/* what was read of Client Message Header is what was written, byte for byte */
static void equal_client_message_header(const ClientMessageHeader *read, const ClientMessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  equal_user_name(&read->user_name, &written->user_name);
  for (size_t i = 0; i < 4; i++) { assert(read->user_number[i] == written->user_number[i]); }
  equal_time(&read->time, &written->time);
  assert(read->client_message_type == written->client_message_type);
}

/* Client Message Header: written and read back, then read and written back */
static void check_client_message_header(void) {
  ClientMessageHeader sent;
  ClientMessageHeader got;
  uint8_t wire[29];
  uint8_t again[29];

  any_client_message_header(&sent);
  assert(encode_client_message_header(&sent, wire, 0) == 29);
  assert(decode_client_message_header(&got, wire, 0) == 29);
  equal_client_message_header(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_client_message_header(&got, wire, 0) == 29);
  assert(encode_client_message_header(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Log In Message: 624 bytes ----------------------------------------------- */

/* Log in message. */
typedef struct {
  uint8_t encrypted_password[312];  /* bytes 0 to 311 */
  uint8_t new_password[312];        /* bytes 312 to 623 */
} LogInMessage;

/* any Log In Message at all: every byte one the checker chooses */
static void any_log_in_message(LogInMessage *record) {
  for (size_t i = 0; i < 312; i++) { record->encrypted_password[i] = arbitrary(); }
  for (size_t i = 0; i < 312; i++) { record->new_password[i] = arbitrary(); }
}

/* Log In Message to the wire: 624 bytes from at, returning where the next byte goes */
static size_t encode_log_in_message(const LogInMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 312; i++) { wire[at++] = record->encrypted_password[i]; }
  for (size_t i = 0; i < 312; i++) { wire[at++] = record->new_password[i]; }

  return at;
}

/* Log In Message off the wire: 624 bytes from at, returning where the next byte lies */
static size_t decode_log_in_message(LogInMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 312; i++) { record->encrypted_password[i] = wire[at++]; }
  for (size_t i = 0; i < 312; i++) { record->new_password[i] = wire[at++]; }

  return at;
}

/* what was read of Log In Message is what was written, byte for byte */
static void equal_log_in_message(const LogInMessage *read, const LogInMessage *written) {
  for (size_t i = 0; i < 312; i++) { assert(read->encrypted_password[i] == written->encrypted_password[i]); }
  for (size_t i = 0; i < 312; i++) { assert(read->new_password[i] == written->new_password[i]); }
}

/* Log In Message: written and read back, then read and written back */
static void check_log_in_message(void) {
  LogInMessage sent;
  LogInMessage got;
  uint8_t wire[624];
  uint8_t again[624];

  any_log_in_message(&sent);
  assert(encode_log_in_message(&sent, wire, 0) == 624);
  assert(decode_log_in_message(&got, wire, 0) == 624);
  equal_log_in_message(&got, &sent);

  for (size_t i = 0; i < 624; i++) { wire[i] = arbitrary(); }
  assert(decode_log_in_message(&got, wire, 0) == 624);
  assert(encode_log_in_message(&got, again, 0) == 624);
  for (size_t i = 0; i < 624; i++) { assert(again[i] == wire[i]); }
}

/* ---- Re Request Message: 12 bytes -------------------------------------------- */

/* Re-Request of 59 messages. */
typedef struct {
  uint8_t from_sequence[4];            /* bytes 0 to 3 */
  uint8_t to_sequence[4];              /* bytes 4 to 7 */
  uint8_t market_shard_number_i_4[4];  /* bytes 8 to 11 */
} ReRequestMessage;

/* any Re Request Message at all: every byte one the checker chooses */
static void any_re_request_message(ReRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->from_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->to_sequence[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_shard_number_i_4[i] = arbitrary(); }
}

/* Re Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_re_request_message(const ReRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->from_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->to_sequence[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_shard_number_i_4[i]; }

  return at;
}

/* Re Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_re_request_message(ReRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->from_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->to_sequence[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_shard_number_i_4[i] = wire[at++]; }

  return at;
}

/* what was read of Re Request Message is what was written, byte for byte */
static void equal_re_request_message(const ReRequestMessage *read, const ReRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->from_sequence[i] == written->from_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->to_sequence[i] == written->to_sequence[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_shard_number_i_4[i] == written->market_shard_number_i_4[i]); }
}

/* Re Request Message: written and read back, then read and written back */
static void check_re_request_message(void) {
  ReRequestMessage sent;
  ReRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_re_request_message(&sent);
  assert(encode_re_request_message(&sent, wire, 0) == 12);
  assert(decode_re_request_message(&got, wire, 0) == 12);
  equal_re_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_re_request_message(&got, wire, 0) == 12);
  assert(encode_re_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
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

/* ---- Request Data Retrieval Message: 24 bytes -------------------------------- */

/* Allows users to request data from the system. */
typedef struct {
  uint8_t data_type;            /* byte 0 */
  uint8_t unused_1;             /* byte 1 */
  uint8_t last_piece_of_chunk;  /* byte 2 */
  uint8_t re_request;           /* byte 3 */
  uint8_t action[4];            /* bytes 4 to 7 */
  uint8_t specific_record[4];   /* bytes 8 to 11 */
  DownloadDate download_date;   /* bytes 12 to 23 */
} RequestDataRetrievalMessage;

/* any Request Data Retrieval Message at all: every byte one the checker chooses */
static void any_request_data_retrieval_message(RequestDataRetrievalMessage *record) {
  record->data_type = arbitrary();
  record->unused_1 = arbitrary();
  record->last_piece_of_chunk = arbitrary();
  record->re_request = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->action[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->specific_record[i] = arbitrary(); }
  any_download_date(&record->download_date);
}

/* Request Data Retrieval Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_request_data_retrieval_message(const RequestDataRetrievalMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->data_type;
  wire[at++] = record->unused_1;
  wire[at++] = record->last_piece_of_chunk;
  wire[at++] = record->re_request;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->action[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->specific_record[i]; }
  at = encode_download_date(&record->download_date, wire, at);

  return at;
}

/* Request Data Retrieval Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_request_data_retrieval_message(RequestDataRetrievalMessage *record, const uint8_t *wire, size_t at) {
  record->data_type = wire[at++];
  record->unused_1 = wire[at++];
  record->last_piece_of_chunk = wire[at++];
  record->re_request = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->action[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->specific_record[i] = wire[at++]; }
  at = decode_download_date(&record->download_date, wire, at);

  return at;
}

/* what was read of Request Data Retrieval Message is what was written, byte for byte */
static void equal_request_data_retrieval_message(const RequestDataRetrievalMessage *read, const RequestDataRetrievalMessage *written) {
  assert(read->data_type == written->data_type);
  assert(read->unused_1 == written->unused_1);
  assert(read->last_piece_of_chunk == written->last_piece_of_chunk);
  assert(read->re_request == written->re_request);
  for (size_t i = 0; i < 4; i++) { assert(read->action[i] == written->action[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->specific_record[i] == written->specific_record[i]); }
  equal_download_date(&read->download_date, &written->download_date);
}

/* Request Data Retrieval Message: written and read back, then read and written back */
static void check_request_data_retrieval_message(void) {
  RequestDataRetrievalMessage sent;
  RequestDataRetrievalMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_request_data_retrieval_message(&sent);
  assert(encode_request_data_retrieval_message(&sent, wire, 0) == 24);
  assert(decode_request_data_retrieval_message(&got, wire, 0) == 24);
  equal_request_data_retrieval_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_request_data_retrieval_message(&got, wire, 0) == 24);
  assert(encode_request_data_retrieval_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
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

/* ---- Contract Name: 48 bytes ------------------------------------------------- */

/* Contract Name */
typedef struct {
  uint8_t identifier_prefix_i_4[4];                         /* bytes 0 to 3 */
  Date date;                                                /* bytes 4 to 15 */
  InstrumentNameP5 instrument_name_p_5;                     /* bytes 16 to 20 */
  uint8_t strike[8];                                        /* bytes 21 to 28 */
  uint8_t call_put_c_1;                                     /* byte 29 */
  SecondaryDate secondary_date;                             /* bytes 30 to 41 */
  SecondaryInstrumentNameP5 secondary_instrument_name_p_5;  /* bytes 42 to 46 */
  uint8_t is_delta_option;                                  /* byte 47 */
} ContractName;

/* any Contract Name at all: every byte one the checker chooses */
static void any_contract_name(ContractName *record) {
  for (size_t i = 0; i < 4; i++) { record->identifier_prefix_i_4[i] = arbitrary(); }
  any_date(&record->date);
  any_instrument_name_p5(&record->instrument_name_p_5);
  for (size_t i = 0; i < 8; i++) { record->strike[i] = arbitrary(); }
  record->call_put_c_1 = arbitrary();
  any_secondary_date(&record->secondary_date);
  any_secondary_instrument_name_p5(&record->secondary_instrument_name_p_5);
  record->is_delta_option = arbitrary();
}

/* Contract Name to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_contract_name(const ContractName *record, uint8_t *wire, size_t at) {
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

/* Contract Name off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_contract_name(ContractName *record, const uint8_t *wire, size_t at) {
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

/* what was read of Contract Name is what was written, byte for byte */
static void equal_contract_name(const ContractName *read, const ContractName *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->identifier_prefix_i_4[i] == written->identifier_prefix_i_4[i]); }
  equal_date(&read->date, &written->date);
  equal_instrument_name_p5(&read->instrument_name_p_5, &written->instrument_name_p_5);
  for (size_t i = 0; i < 8; i++) { assert(read->strike[i] == written->strike[i]); }
  assert(read->call_put_c_1 == written->call_put_c_1);
  equal_secondary_date(&read->secondary_date, &written->secondary_date);
  equal_secondary_instrument_name_p5(&read->secondary_instrument_name_p_5, &written->secondary_instrument_name_p_5);
  assert(read->is_delta_option == written->is_delta_option);
}

/* Contract Name: written and read back, then read and written back */
static void check_contract_name(void) {
  ContractName sent;
  ContractName got;
  uint8_t wire[48];
  uint8_t again[48];

  any_contract_name(&sent);
  assert(encode_contract_name(&sent, wire, 0) == 48);
  assert(decode_contract_name(&got, wire, 0) == 48);
  equal_contract_name(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_contract_name(&got, wire, 0) == 48);
  assert(encode_contract_name(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request Daily Trend Message: 48 bytes ----------------------------------- */

/* Request the on screen trade history for a contract for the current trading session. */
typedef struct {
  ContractName contract_name;  /* bytes 0 to 47 */
} RequestDailyTrendMessage;

/* any Request Daily Trend Message at all: every byte one the checker chooses */
static void any_request_daily_trend_message(RequestDailyTrendMessage *record) {
  any_contract_name(&record->contract_name);
}

/* Request Daily Trend Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_request_daily_trend_message(const RequestDailyTrendMessage *record, uint8_t *wire, size_t at) {
  at = encode_contract_name(&record->contract_name, wire, at);

  return at;
}

/* Request Daily Trend Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_request_daily_trend_message(RequestDailyTrendMessage *record, const uint8_t *wire, size_t at) {
  at = decode_contract_name(&record->contract_name, wire, at);

  return at;
}

/* what was read of Request Daily Trend Message is what was written, byte for byte */
static void equal_request_daily_trend_message(const RequestDailyTrendMessage *read, const RequestDailyTrendMessage *written) {
  equal_contract_name(&read->contract_name, &written->contract_name);
}

/* Request Daily Trend Message: written and read back, then read and written back */
static void check_request_daily_trend_message(void) {
  RequestDailyTrendMessage sent;
  RequestDailyTrendMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_request_daily_trend_message(&sent);
  assert(encode_request_daily_trend_message(&sent, wire, 0) == 48);
  assert(decode_request_daily_trend_message(&got, wire, 0) == 48);
  equal_request_daily_trend_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_request_daily_trend_message(&got, wire, 0) == 48);
  assert(encode_request_daily_trend_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Contract Subscription Message: 48 bytes -------------------------- */

/* Subscribe to Display Updates on the contracts listed. */
typedef struct {
  ContractName contract_name;  /* bytes 0 to 47 */
} OptionContractSubscriptionMessage;

/* any Option Contract Subscription Message at all: every byte one the checker chooses */
static void any_option_contract_subscription_message(OptionContractSubscriptionMessage *record) {
  any_contract_name(&record->contract_name);
}

/* Option Contract Subscription Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_option_contract_subscription_message(const OptionContractSubscriptionMessage *record, uint8_t *wire, size_t at) {
  at = encode_contract_name(&record->contract_name, wire, at);

  return at;
}

/* Option Contract Subscription Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_option_contract_subscription_message(OptionContractSubscriptionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_contract_name(&record->contract_name, wire, at);

  return at;
}

/* what was read of Option Contract Subscription Message is what was written, byte for byte */
static void equal_option_contract_subscription_message(const OptionContractSubscriptionMessage *read, const OptionContractSubscriptionMessage *written) {
  equal_contract_name(&read->contract_name, &written->contract_name);
}

/* Option Contract Subscription Message: written and read back, then read and written back */
static void check_option_contract_subscription_message(void) {
  OptionContractSubscriptionMessage sent;
  OptionContractSubscriptionMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_option_contract_subscription_message(&sent);
  assert(encode_option_contract_subscription_message(&sent, wire, 0) == 48);
  assert(decode_option_contract_subscription_message(&got, wire, 0) == 48);
  equal_option_contract_subscription_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_option_contract_subscription_message(&got, wire, 0) == 48);
  assert(encode_option_contract_subscription_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Subscribing To Indices Service Message: 1 byte -------------------------- */

/* Subscribe or unsubscribe from the indices service. */
typedef struct {
  uint8_t subscribe;  /* byte 0 */
} SubscribingToIndicesServiceMessage;

/* any Subscribing To Indices Service Message at all: every byte one the checker chooses */
static void any_subscribing_to_indices_service_message(SubscribingToIndicesServiceMessage *record) {
  record->subscribe = arbitrary();
}

/* Subscribing To Indices Service Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_subscribing_to_indices_service_message(const SubscribingToIndicesServiceMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->subscribe;

  return at;
}

/* Subscribing To Indices Service Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_subscribing_to_indices_service_message(SubscribingToIndicesServiceMessage *record, const uint8_t *wire, size_t at) {
  record->subscribe = wire[at++];

  return at;
}

/* what was read of Subscribing To Indices Service Message is what was written, byte for byte */
static void equal_subscribing_to_indices_service_message(const SubscribingToIndicesServiceMessage *read, const SubscribingToIndicesServiceMessage *written) {
  assert(read->subscribe == written->subscribe);
}

/* Subscribing To Indices Service Message: written and read back, then read and written back */
static void check_subscribing_to_indices_service_message(void) {
  SubscribingToIndicesServiceMessage sent;
  SubscribingToIndicesServiceMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_subscribing_to_indices_service_message(&sent);
  assert(encode_subscribing_to_indices_service_message(&sent, wire, 0) == 1);
  assert(decode_subscribing_to_indices_service_message(&got, wire, 0) == 1);
  equal_subscribing_to_indices_service_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_subscribing_to_indices_service_message(&got, wire, 0) == 1);
  assert(encode_subscribing_to_indices_service_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Option Statistics Request Message: 48 bytes ----------------------------- */

/* Request a Display Update with information for all option contracts traded since the beginning of the trading session. */
typedef struct {
  ContractName contract_name;  /* bytes 0 to 47 */
} OptionStatisticsRequestMessage;

/* any Option Statistics Request Message at all: every byte one the checker chooses */
static void any_option_statistics_request_message(OptionStatisticsRequestMessage *record) {
  any_contract_name(&record->contract_name);
}

/* Option Statistics Request Message to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_option_statistics_request_message(const OptionStatisticsRequestMessage *record, uint8_t *wire, size_t at) {
  at = encode_contract_name(&record->contract_name, wire, at);

  return at;
}

/* Option Statistics Request Message off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_option_statistics_request_message(OptionStatisticsRequestMessage *record, const uint8_t *wire, size_t at) {
  at = decode_contract_name(&record->contract_name, wire, at);

  return at;
}

/* what was read of Option Statistics Request Message is what was written, byte for byte */
static void equal_option_statistics_request_message(const OptionStatisticsRequestMessage *read, const OptionStatisticsRequestMessage *written) {
  equal_contract_name(&read->contract_name, &written->contract_name);
}

/* Option Statistics Request Message: written and read back, then read and written back */
static void check_option_statistics_request_message(void) {
  OptionStatisticsRequestMessage sent;
  OptionStatisticsRequestMessage got;
  uint8_t wire[48];
  uint8_t again[48];

  any_option_statistics_request_message(&sent);
  assert(encode_option_statistics_request_message(&sent, wire, 0) == 48);
  assert(decode_option_statistics_request_message(&got, wire, 0) == 48);
  equal_option_statistics_request_message(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_option_statistics_request_message(&got, wire, 0) == 48);
  assert(encode_option_statistics_request_message(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_transport_header();
  check_user_name();
  check_time();
  check_client_message_header();
  check_log_in_message();
  check_re_request_message();
  check_download_date();
  check_request_data_retrieval_message();
  check_date();
  check_instrument_name_p5();
  check_secondary_date();
  check_secondary_instrument_name_p5();
  check_contract();
  check_contract_name();
  check_request_daily_trend_message();
  check_option_contract_subscription_message();
  check_subscribing_to_indices_service_message();
  check_option_statistics_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
