// ice/icefutures/bgw/IceFutures_Bgw_v7_0.c
/*
 * Intercontinental Exchange Binary Order Gateway
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
 *   - a field read in bits
 *   - a field present only on a condition
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

/* ---- Simple Open Framing Header: 4 bytes ------------------------------------- */

/* Simple Open Framing Header */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t encoding_type[2];   /* bytes 2 to 3 */
} SimpleOpenFramingHeader;

/* any Simple Open Framing Header at all: every byte one the checker chooses */
static void any_simple_open_framing_header(SimpleOpenFramingHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = arbitrary(); }
}

/* Simple Open Framing Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_simple_open_framing_header(const SimpleOpenFramingHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->encoding_type[i]; }

  return at;
}

/* Simple Open Framing Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_simple_open_framing_header(SimpleOpenFramingHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Open Framing Header is what was written, byte for byte */
static void equal_simple_open_framing_header(const SimpleOpenFramingHeader *read, const SimpleOpenFramingHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->encoding_type[i] == written->encoding_type[i]); }
}

/* Simple Open Framing Header: written and read back, then read and written back */
static void check_simple_open_framing_header(void) {
  SimpleOpenFramingHeader sent;
  SimpleOpenFramingHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_simple_open_framing_header(&sent);
  assert(encode_simple_open_framing_header(&sent, wire, 0) == 4);
  assert(decode_simple_open_framing_header(&got, wire, 0) == 4);
  equal_simple_open_framing_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_open_framing_header(&got, wire, 0) == 4);
  assert(encode_simple_open_framing_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Framing Header: 4 bytes ------------------------------------------------- */

/* SimpleOpenFramingHeaderMessage */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t encoding_type[2];   /* bytes 2 to 3 */
} FramingHeader;

/* any Framing Header at all: every byte one the checker chooses */
static void any_framing_header(FramingHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = arbitrary(); }
}

/* Framing Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_framing_header(const FramingHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->encoding_type[i]; }

  return at;
}

/* Framing Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_framing_header(FramingHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->encoding_type[i] = wire[at++]; }

  return at;
}

/* what was read of Framing Header is what was written, byte for byte */
static void equal_framing_header(const FramingHeader *read, const FramingHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->encoding_type[i] == written->encoding_type[i]); }
}

/* Framing Header: written and read back, then read and written back */
static void check_framing_header(void) {
  FramingHeader sent;
  FramingHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_framing_header(&sent);
  assert(encode_framing_header(&sent, wire, 0) == 4);
  assert(decode_framing_header(&got, wire, 0) == 4);
  equal_framing_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_framing_header(&got, wire, 0) == 4);
  assert(encode_framing_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Open Framing Header Message: 4 bytes ----------------------------- */

/* SimpleOpenFramingHeaderMessage */
typedef struct {
  FramingHeader framing_header;  /* bytes 0 to 3 */
} SimpleOpenFramingHeaderMessage;

/* any Simple Open Framing Header Message at all: every byte one the checker chooses */
static void any_simple_open_framing_header_message(SimpleOpenFramingHeaderMessage *record) {
  any_framing_header(&record->framing_header);
}

/* Simple Open Framing Header Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_simple_open_framing_header_message(const SimpleOpenFramingHeaderMessage *record, uint8_t *wire, size_t at) {
  at = encode_framing_header(&record->framing_header, wire, at);

  return at;
}

/* Simple Open Framing Header Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_simple_open_framing_header_message(SimpleOpenFramingHeaderMessage *record, const uint8_t *wire, size_t at) {
  at = decode_framing_header(&record->framing_header, wire, at);

  return at;
}

/* what was read of Simple Open Framing Header Message is what was written, byte for byte */
static void equal_simple_open_framing_header_message(const SimpleOpenFramingHeaderMessage *read, const SimpleOpenFramingHeaderMessage *written) {
  equal_framing_header(&read->framing_header, &written->framing_header);
}

/* Simple Open Framing Header Message: written and read back, then read and written back */
static void check_simple_open_framing_header_message(void) {
  SimpleOpenFramingHeaderMessage sent;
  SimpleOpenFramingHeaderMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_simple_open_framing_header_message(&sent);
  assert(encode_simple_open_framing_header_message(&sent, wire, 0) == 4);
  assert(decode_simple_open_framing_header_message(&got, wire, 0) == 4);
  equal_simple_open_framing_header_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_open_framing_header_message(&got, wire, 0) == 4);
  assert(encode_simple_open_framing_header_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Request Message: 236 bytes ---------------------------------------- */

/* LogonRequestMessage */
typedef struct {
  uint8_t user_id[20];              /* bytes 0 to 19 */
  uint8_t client_id[4];             /* bytes 20 to 23 */
  uint8_t heart_beat_interval[2];   /* bytes 24 to 25 */
  uint8_t application_name[30];     /* bytes 26 to 55 */
  uint8_t application_version[50];  /* bytes 56 to 105 */
  uint8_t application_vendor[30];   /* bytes 106 to 135 */
  uint8_t raw_data[50];             /* bytes 136 to 185 */
  uint8_t ip_session_token[50];     /* bytes 186 to 235 */
} LogonRequestMessage;

/* any Logon Request Message at all: every byte one the checker chooses */
static void any_logon_request_message(LogonRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->heart_beat_interval[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->application_name[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->application_version[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->application_vendor[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->raw_data[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->ip_session_token[i] = arbitrary(); }
}

/* Logon Request Message to the wire: 236 bytes from at, returning where the next byte goes */
static size_t encode_logon_request_message(const LogonRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->heart_beat_interval[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->application_name[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->application_version[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->application_vendor[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->raw_data[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->ip_session_token[i]; }

  return at;
}

/* Logon Request Message off the wire: 236 bytes from at, returning where the next byte lies */
static size_t decode_logon_request_message(LogonRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->heart_beat_interval[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->application_name[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->application_version[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->application_vendor[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->raw_data[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->ip_session_token[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Request Message is what was written, byte for byte */
static void equal_logon_request_message(const LogonRequestMessage *read, const LogonRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->heart_beat_interval[i] == written->heart_beat_interval[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->application_name[i] == written->application_name[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->application_version[i] == written->application_version[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->application_vendor[i] == written->application_vendor[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->raw_data[i] == written->raw_data[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->ip_session_token[i] == written->ip_session_token[i]); }
}

/* Logon Request Message: written and read back, then read and written back */
static void check_logon_request_message(void) {
  LogonRequestMessage sent;
  LogonRequestMessage got;
  uint8_t wire[236];
  uint8_t again[236];

  any_logon_request_message(&sent);
  assert(encode_logon_request_message(&sent, wire, 0) == 236);
  assert(decode_logon_request_message(&got, wire, 0) == 236);
  equal_logon_request_message(&got, &sent);

  for (size_t i = 0; i < 236; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_request_message(&got, wire, 0) == 236);
  assert(encode_logon_request_message(&got, again, 0) == 236);
  for (size_t i = 0; i < 236; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Report Message: 127 bytes ----------------------------------------- */

/* LogonReportMessage */
typedef struct {
  uint8_t user_id[20];             /* bytes 0 to 19 */
  uint8_t heart_beat_interval[2];  /* bytes 20 to 21 */
  uint8_t severity_level;          /* byte 22 */
  uint8_t exchange_code[4];        /* bytes 23 to 26 */
  uint8_t text[100];               /* bytes 27 to 126 */
} LogonReportMessage;

/* any Logon Report Message at all: every byte one the checker chooses */
static void any_logon_report_message(LogonReportMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->heart_beat_interval[i] = arbitrary(); }
  record->severity_level = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Logon Report Message to the wire: 127 bytes from at, returning where the next byte goes */
static size_t encode_logon_report_message(const LogonReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->heart_beat_interval[i]; }
  wire[at++] = record->severity_level;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Logon Report Message off the wire: 127 bytes from at, returning where the next byte lies */
static size_t decode_logon_report_message(LogonReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->heart_beat_interval[i] = wire[at++]; }
  record->severity_level = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Report Message is what was written, byte for byte */
static void equal_logon_report_message(const LogonReportMessage *read, const LogonReportMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->heart_beat_interval[i] == written->heart_beat_interval[i]); }
  assert(read->severity_level == written->severity_level);
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Logon Report Message: written and read back, then read and written back */
static void check_logon_report_message(void) {
  LogonReportMessage sent;
  LogonReportMessage got;
  uint8_t wire[127];
  uint8_t again[127];

  any_logon_report_message(&sent);
  assert(encode_logon_report_message(&sent, wire, 0) == 127);
  assert(decode_logon_report_message(&got, wire, 0) == 127);
  equal_logon_report_message(&got, &sent);

  for (size_t i = 0; i < 127; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_report_message(&got, wire, 0) == 127);
  assert(encode_logon_report_message(&got, again, 0) == 127);
  for (size_t i = 0; i < 127; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Request Message: 20 bytes ---------------------------------------- */

/* LogoutRequestMessage */
typedef struct {
  uint8_t user_id[20];  /* bytes 0 to 19 */
} LogoutRequestMessage;

/* any Logout Request Message at all: every byte one the checker chooses */
static void any_logout_request_message(LogoutRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = arbitrary(); }
}

/* Logout Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_logout_request_message(const LogoutRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->user_id[i]; }

  return at;
}

/* Logout Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_logout_request_message(LogoutRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Request Message is what was written, byte for byte */
static void equal_logout_request_message(const LogoutRequestMessage *read, const LogoutRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->user_id[i] == written->user_id[i]); }
}

/* Logout Request Message: written and read back, then read and written back */
static void check_logout_request_message(void) {
  LogoutRequestMessage sent;
  LogoutRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_logout_request_message(&sent);
  assert(encode_logout_request_message(&sent, wire, 0) == 20);
  assert(decode_logout_request_message(&got, wire, 0) == 20);
  equal_logout_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_request_message(&got, wire, 0) == 20);
  assert(encode_logout_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Report Message: 124 bytes ---------------------------------------- */

/* LogoutReportMessage */
typedef struct {
  uint8_t user_id[20];       /* bytes 0 to 19 */
  uint8_t exchange_code[4];  /* bytes 20 to 23 */
  uint8_t text[100];         /* bytes 24 to 123 */
} LogoutReportMessage;

/* any Logout Report Message at all: every byte one the checker chooses */
static void any_logout_report_message(LogoutReportMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Logout Report Message to the wire: 124 bytes from at, returning where the next byte goes */
static size_t encode_logout_report_message(const LogoutReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Logout Report Message off the wire: 124 bytes from at, returning where the next byte lies */
static size_t decode_logout_report_message(LogoutReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Report Message is what was written, byte for byte */
static void equal_logout_report_message(const LogoutReportMessage *read, const LogoutReportMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->user_id[i] == written->user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Logout Report Message: written and read back, then read and written back */
static void check_logout_report_message(void) {
  LogoutReportMessage sent;
  LogoutReportMessage got;
  uint8_t wire[124];
  uint8_t again[124];

  any_logout_report_message(&sent);
  assert(encode_logout_report_message(&sent, wire, 0) == 124);
  assert(decode_logout_report_message(&got, wire, 0) == 124);
  equal_logout_report_message(&got, &sent);

  for (size_t i = 0; i < 124; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_report_message(&got, wire, 0) == 124);
  assert(encode_logout_report_message(&got, again, 0) == 124);
  for (size_t i = 0; i < 124; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Message: 129 bytes ------------------------------------------------ */

/* ErrorMessage */
typedef struct {
  uint8_t ref_sequence_id[4];            /* bytes 0 to 3 */
  uint8_t severity_level;                /* byte 4 */
  uint8_t supported_schema_version[20];  /* bytes 5 to 24 */
  uint8_t exchange_code[4];              /* bytes 25 to 28 */
  uint8_t text[100];                     /* bytes 29 to 128 */
} ErrorMessage;

/* any Error Message at all: every byte one the checker chooses */
static void any_error_message(ErrorMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->ref_sequence_id[i] = arbitrary(); }
  record->severity_level = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->supported_schema_version[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Error Message to the wire: 129 bytes from at, returning where the next byte goes */
static size_t encode_error_message(const ErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_sequence_id[i]; }
  wire[at++] = record->severity_level;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->supported_schema_version[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Error Message off the wire: 129 bytes from at, returning where the next byte lies */
static size_t decode_error_message(ErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->ref_sequence_id[i] = wire[at++]; }
  record->severity_level = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->supported_schema_version[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Error Message is what was written, byte for byte */
static void equal_error_message(const ErrorMessage *read, const ErrorMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->ref_sequence_id[i] == written->ref_sequence_id[i]); }
  assert(read->severity_level == written->severity_level);
  for (size_t i = 0; i < 20; i++) { assert(read->supported_schema_version[i] == written->supported_schema_version[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Error Message: written and read back, then read and written back */
static void check_error_message(void) {
  ErrorMessage sent;
  ErrorMessage got;
  uint8_t wire[129];
  uint8_t again[129];

  any_error_message(&sent);
  assert(encode_error_message(&sent, wire, 0) == 129);
  assert(decode_error_message(&got, wire, 0) == 129);
  equal_error_message(&got, &sent);

  for (size_t i = 0; i < 129; i++) { wire[i] = arbitrary(); }
  assert(decode_error_message(&got, wire, 0) == 129);
  assert(encode_error_message(&got, again, 0) == 129);
  for (size_t i = 0; i < 129; i++) { assert(again[i] == wire[i]); }
}

/* ---- Group Size Encoding: 4 bytes -------------------------------------------- */

/* GroupSizeEncoding */
typedef struct {
  uint8_t block_length[2];  /* bytes 0 to 1 */
  uint8_t num_in_group[2];  /* bytes 2 to 3 */
} GroupSizeEncoding;

/* any Group Size Encoding at all: every byte one the checker chooses */
static void any_group_size_encoding(GroupSizeEncoding *record) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->num_in_group[i] = arbitrary(); }
}

/* Group Size Encoding to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_group_size_encoding(const GroupSizeEncoding *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->block_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->num_in_group[i]; }

  return at;
}

/* Group Size Encoding off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_group_size_encoding(GroupSizeEncoding *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->block_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->num_in_group[i] = wire[at++]; }

  return at;
}

/* what was read of Group Size Encoding is what was written, byte for byte */
static void equal_group_size_encoding(const GroupSizeEncoding *read, const GroupSizeEncoding *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->block_length[i] == written->block_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->num_in_group[i] == written->num_in_group[i]); }
}

/* Group Size Encoding: written and read back, then read and written back */
static void check_group_size_encoding(void) {
  GroupSizeEncoding sent;
  GroupSizeEncoding got;
  uint8_t wire[4];
  uint8_t again[4];

  any_group_size_encoding(&sent);
  assert(encode_group_size_encoding(&sent, wire, 0) == 4);
  assert(decode_group_size_encoding(&got, wire, 0) == 4);
  equal_group_size_encoding(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_group_size_encoding(&got, wire, 0) == 4);
  assert(encode_group_size_encoding(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Definition Reject Message: 115 bytes --------------------------- */

/* SecurityDefinitionRejectMessage */
typedef struct {
  uint8_t security_req_id[4];      /* bytes 0 to 3 */
  uint8_t security_response_type;  /* byte 4 */
  uint8_t security_request_type;   /* byte 5 */
  uint8_t market_type_id[4];       /* bytes 6 to 9 */
  uint8_t security_type_optional;  /* byte 10 */
  uint8_t exchange_code[4];        /* bytes 11 to 14 */
  uint8_t text[100];               /* bytes 15 to 114 */
} SecurityDefinitionRejectMessage;

/* any Security Definition Reject Message at all: every byte one the checker chooses */
static void any_security_definition_reject_message(SecurityDefinitionRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = arbitrary(); }
  record->security_response_type = arbitrary();
  record->security_request_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->market_type_id[i] = arbitrary(); }
  record->security_type_optional = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Security Definition Reject Message to the wire: 115 bytes from at, returning where the next byte goes */
static size_t encode_security_definition_reject_message(const SecurityDefinitionRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_req_id[i]; }
  wire[at++] = record->security_response_type;
  wire[at++] = record->security_request_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_type_id[i]; }
  wire[at++] = record->security_type_optional;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Security Definition Reject Message off the wire: 115 bytes from at, returning where the next byte lies */
static size_t decode_security_definition_reject_message(SecurityDefinitionRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = wire[at++]; }
  record->security_response_type = wire[at++];
  record->security_request_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->market_type_id[i] = wire[at++]; }
  record->security_type_optional = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Security Definition Reject Message is what was written, byte for byte */
static void equal_security_definition_reject_message(const SecurityDefinitionRejectMessage *read, const SecurityDefinitionRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_req_id[i] == written->security_req_id[i]); }
  assert(read->security_response_type == written->security_response_type);
  assert(read->security_request_type == written->security_request_type);
  for (size_t i = 0; i < 4; i++) { assert(read->market_type_id[i] == written->market_type_id[i]); }
  assert(read->security_type_optional == written->security_type_optional);
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Security Definition Reject Message: written and read back, then read and written back */
static void check_security_definition_reject_message(void) {
  SecurityDefinitionRejectMessage sent;
  SecurityDefinitionRejectMessage got;
  uint8_t wire[115];
  uint8_t again[115];

  any_security_definition_reject_message(&sent);
  assert(encode_security_definition_reject_message(&sent, wire, 0) == 115);
  assert(decode_security_definition_reject_message(&got, wire, 0) == 115);
  equal_security_definition_reject_message(&got, &sent);

  for (size_t i = 0; i < 115; i++) { wire[i] = arbitrary(); }
  assert(decode_security_definition_reject_message(&got, wire, 0) == 115);
  assert(encode_security_definition_reject_message(&got, again, 0) == 115);
  for (size_t i = 0; i < 115; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Definition Request Message: 9 bytes ---------------------------- */

/* SecurityDefinitionRequestMessage */
typedef struct {
  uint8_t security_req_id[4];     /* bytes 0 to 3 */
  uint8_t security_request_type;  /* byte 4 */
  uint8_t market_type_id[4];      /* bytes 5 to 8 */
} SecurityDefinitionRequestMessage;

/* any Security Definition Request Message at all: every byte one the checker chooses */
static void any_security_definition_request_message(SecurityDefinitionRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = arbitrary(); }
  record->security_request_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->market_type_id[i] = arbitrary(); }
}

/* Security Definition Request Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_security_definition_request_message(const SecurityDefinitionRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_req_id[i]; }
  wire[at++] = record->security_request_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_type_id[i]; }

  return at;
}

/* Security Definition Request Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_security_definition_request_message(SecurityDefinitionRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = wire[at++]; }
  record->security_request_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->market_type_id[i] = wire[at++]; }

  return at;
}

/* what was read of Security Definition Request Message is what was written, byte for byte */
static void equal_security_definition_request_message(const SecurityDefinitionRequestMessage *read, const SecurityDefinitionRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_req_id[i] == written->security_req_id[i]); }
  assert(read->security_request_type == written->security_request_type);
  for (size_t i = 0; i < 4; i++) { assert(read->market_type_id[i] == written->market_type_id[i]); }
}

/* Security Definition Request Message: written and read back, then read and written back */
static void check_security_definition_request_message(void) {
  SecurityDefinitionRequestMessage sent;
  SecurityDefinitionRequestMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_security_definition_request_message(&sent);
  assert(encode_security_definition_request_message(&sent, wire, 0) == 9);
  assert(decode_security_definition_request_message(&got, wire, 0) == 9);
  equal_security_definition_request_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_security_definition_request_message(&got, wire, 0) == 9);
  assert(encode_security_definition_request_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trader Logon Request Message: 106 bytes --------------------------------- */

/* TraderLogonRequestMessage */
typedef struct {
  uint8_t originator_user_id[20];     /* bytes 0 to 19 */
  uint8_t direct_electronic_access;   /* byte 20 */
  uint8_t trading_capacity;           /* byte 21 */
  uint8_t liquidity_provision;        /* byte 22 */
  uint8_t commodity_deriv_indicator;  /* byte 23 */
  uint8_t investment_decision[8];     /* bytes 24 to 31 */
  uint8_t execution_decision[8];      /* bytes 32 to 39 */
  uint8_t client_id_code[8];          /* bytes 40 to 47 */
  uint8_t mifid_id[8];                /* bytes 48 to 55 */
  uint8_t raw_data[50];               /* bytes 56 to 105 */
} TraderLogonRequestMessage;

/* any Trader Logon Request Message at all: every byte one the checker chooses */
static void any_trader_logon_request_message(TraderLogonRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  record->direct_electronic_access = arbitrary();
  record->trading_capacity = arbitrary();
  record->liquidity_provision = arbitrary();
  record->commodity_deriv_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->investment_decision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_decision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_id_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mifid_id[i] = arbitrary(); }
  for (size_t i = 0; i < 50; i++) { record->raw_data[i] = arbitrary(); }
}

/* Trader Logon Request Message to the wire: 106 bytes from at, returning where the next byte goes */
static size_t encode_trader_logon_request_message(const TraderLogonRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  wire[at++] = record->direct_electronic_access;
  wire[at++] = record->trading_capacity;
  wire[at++] = record->liquidity_provision;
  wire[at++] = record->commodity_deriv_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_decision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_decision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_id_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mifid_id[i]; }
  for (size_t i = 0; i < 50; i++) { wire[at++] = record->raw_data[i]; }

  return at;
}

/* Trader Logon Request Message off the wire: 106 bytes from at, returning where the next byte lies */
static size_t decode_trader_logon_request_message(TraderLogonRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  record->direct_electronic_access = wire[at++];
  record->trading_capacity = wire[at++];
  record->liquidity_provision = wire[at++];
  record->commodity_deriv_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->investment_decision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_decision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_id_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mifid_id[i] = wire[at++]; }
  for (size_t i = 0; i < 50; i++) { record->raw_data[i] = wire[at++]; }

  return at;
}

/* what was read of Trader Logon Request Message is what was written, byte for byte */
static void equal_trader_logon_request_message(const TraderLogonRequestMessage *read, const TraderLogonRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  assert(read->direct_electronic_access == written->direct_electronic_access);
  assert(read->trading_capacity == written->trading_capacity);
  assert(read->liquidity_provision == written->liquidity_provision);
  assert(read->commodity_deriv_indicator == written->commodity_deriv_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->investment_decision[i] == written->investment_decision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_decision[i] == written->execution_decision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_id_code[i] == written->client_id_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mifid_id[i] == written->mifid_id[i]); }
  for (size_t i = 0; i < 50; i++) { assert(read->raw_data[i] == written->raw_data[i]); }
}

/* Trader Logon Request Message: written and read back, then read and written back */
static void check_trader_logon_request_message(void) {
  TraderLogonRequestMessage sent;
  TraderLogonRequestMessage got;
  uint8_t wire[106];
  uint8_t again[106];

  any_trader_logon_request_message(&sent);
  assert(encode_trader_logon_request_message(&sent, wire, 0) == 106);
  assert(decode_trader_logon_request_message(&got, wire, 0) == 106);
  equal_trader_logon_request_message(&got, &sent);

  for (size_t i = 0; i < 106; i++) { wire[i] = arbitrary(); }
  assert(decode_trader_logon_request_message(&got, wire, 0) == 106);
  assert(encode_trader_logon_request_message(&got, again, 0) == 106);
  for (size_t i = 0; i < 106; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trader Logon Report Message: 128 bytes ---------------------------------- */

/* TraderLogonReportMessage */
typedef struct {
  uint8_t originator_user_id[20];  /* bytes 0 to 19 */
  uint8_t client_id[4];            /* bytes 20 to 23 */
  uint8_t exchange_code[4];        /* bytes 24 to 27 */
  uint8_t text[100];               /* bytes 28 to 127 */
} TraderLogonReportMessage;

/* any Trader Logon Report Message at all: every byte one the checker chooses */
static void any_trader_logon_report_message(TraderLogonReportMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Trader Logon Report Message to the wire: 128 bytes from at, returning where the next byte goes */
static size_t encode_trader_logon_report_message(const TraderLogonReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Trader Logon Report Message off the wire: 128 bytes from at, returning where the next byte lies */
static size_t decode_trader_logon_report_message(TraderLogonReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Trader Logon Report Message is what was written, byte for byte */
static void equal_trader_logon_report_message(const TraderLogonReportMessage *read, const TraderLogonReportMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Trader Logon Report Message: written and read back, then read and written back */
static void check_trader_logon_report_message(void) {
  TraderLogonReportMessage sent;
  TraderLogonReportMessage got;
  uint8_t wire[128];
  uint8_t again[128];

  any_trader_logon_report_message(&sent);
  assert(encode_trader_logon_report_message(&sent, wire, 0) == 128);
  assert(decode_trader_logon_report_message(&got, wire, 0) == 128);
  equal_trader_logon_report_message(&got, &sent);

  for (size_t i = 0; i < 128; i++) { wire[i] = arbitrary(); }
  assert(decode_trader_logon_report_message(&got, wire, 0) == 128);
  assert(encode_trader_logon_report_message(&got, again, 0) == 128);
  for (size_t i = 0; i < 128; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trader Logout Request Message: 20 bytes --------------------------------- */

/* TraderLogoutRequestMessage */
typedef struct {
  uint8_t originator_user_id[20];  /* bytes 0 to 19 */
} TraderLogoutRequestMessage;

/* any Trader Logout Request Message at all: every byte one the checker chooses */
static void any_trader_logout_request_message(TraderLogoutRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
}

/* Trader Logout Request Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_trader_logout_request_message(const TraderLogoutRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }

  return at;
}

/* Trader Logout Request Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_trader_logout_request_message(TraderLogoutRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trader Logout Request Message is what was written, byte for byte */
static void equal_trader_logout_request_message(const TraderLogoutRequestMessage *read, const TraderLogoutRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
}

/* Trader Logout Request Message: written and read back, then read and written back */
static void check_trader_logout_request_message(void) {
  TraderLogoutRequestMessage sent;
  TraderLogoutRequestMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_trader_logout_request_message(&sent);
  assert(encode_trader_logout_request_message(&sent, wire, 0) == 20);
  assert(decode_trader_logout_request_message(&got, wire, 0) == 20);
  equal_trader_logout_request_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_trader_logout_request_message(&got, wire, 0) == 20);
  assert(encode_trader_logout_request_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trader Logout Report Message: 124 bytes --------------------------------- */

/* TraderLogoutReportMessage */
typedef struct {
  uint8_t originator_user_id[20];  /* bytes 0 to 19 */
  uint8_t exchange_code[4];        /* bytes 20 to 23 */
  uint8_t text[100];               /* bytes 24 to 123 */
} TraderLogoutReportMessage;

/* any Trader Logout Report Message at all: every byte one the checker chooses */
static void any_trader_logout_report_message(TraderLogoutReportMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Trader Logout Report Message to the wire: 124 bytes from at, returning where the next byte goes */
static size_t encode_trader_logout_report_message(const TraderLogoutReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Trader Logout Report Message off the wire: 124 bytes from at, returning where the next byte lies */
static size_t decode_trader_logout_report_message(TraderLogoutReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Trader Logout Report Message is what was written, byte for byte */
static void equal_trader_logout_report_message(const TraderLogoutReportMessage *read, const TraderLogoutReportMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Trader Logout Report Message: written and read back, then read and written back */
static void check_trader_logout_report_message(void) {
  TraderLogoutReportMessage sent;
  TraderLogoutReportMessage got;
  uint8_t wire[124];
  uint8_t again[124];

  any_trader_logout_report_message(&sent);
  assert(encode_trader_logout_report_message(&sent, wire, 0) == 124);
  assert(decode_trader_logout_report_message(&got, wire, 0) == 124);
  equal_trader_logout_report_message(&got, &sent);

  for (size_t i = 0; i < 124; i++) { wire[i] = arbitrary(); }
  assert(decode_trader_logout_report_message(&got, wire, 0) == 124);
  assert(encode_trader_logout_report_message(&got, again, 0) == 124);
  for (size_t i = 0; i < 124; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Request Message: 327 bytes ------------------------------------ */

/* NewOrderRequestMessage */
typedef struct {
  uint8_t price_optional[8];                  /* bytes 0 to 7 */
  uint8_t order_qty[8];                       /* bytes 8 to 15 */
  uint8_t symbol[4];                          /* bytes 16 to 19 */
  uint8_t time_in_force;                      /* byte 20 */
  uint8_t side;                               /* byte 21 */
  uint8_t originator_user_id[20];             /* bytes 22 to 41 */
  uint8_t ord_type;                           /* byte 42 */
  uint8_t manual_order_indicator;             /* byte 43 */
  uint8_t cl_ord_id[8];                       /* bytes 44 to 51 */
  uint8_t max_show[8];                        /* bytes 52 to 59 */
  uint8_t stop_px[8];                         /* bytes 60 to 67 */
  uint8_t give_up_clearing_firm[4];           /* bytes 68 to 71 */
  uint8_t clearing_firm[4];                   /* bytes 72 to 75 */
  uint8_t self_match_prevention_id[8];        /* bytes 76 to 83 */
  uint8_t expire_date[2];                     /* bytes 84 to 85 */
  uint8_t self_match_prevention_instruction;  /* byte 86 */
  uint8_t exec_inst;                          /* byte 87 */
  uint8_t direct_electronic_access;           /* byte 88 */
  uint8_t trading_capacity;                   /* byte 89 */
  uint8_t liquidity_provision;                /* byte 90 */
  uint8_t commodity_deriv_indicator;          /* byte 91 */
  uint8_t investment_decision[8];             /* bytes 92 to 99 */
  uint8_t execution_decision[8];              /* bytes 100 to 107 */
  uint8_t client_id_code[8];                  /* bytes 108 to 115 */
  uint8_t mifid_id[8];                        /* bytes 116 to 123 */
  uint8_t cust_order_handling_inst;           /* byte 124 */
  uint8_t position_effect;                    /* byte 125 */
  uint8_t alloc_handl_inst;                   /* byte 126 */
  uint8_t price_type;                         /* byte 127 */
  uint8_t clearing_account[14];               /* bytes 128 to 141 */
  uint8_t customer_account_ref_id[12];        /* bytes 142 to 153 */
  uint8_t memo[30];                           /* bytes 154 to 183 */
  uint8_t allocation_account[20];             /* bytes 184 to 203 */
  uint8_t on_behalf_of_comp_id[41];           /* bytes 204 to 244 */
  uint8_t on_behalf_of_sub_id[41];            /* bytes 245 to 285 */
  uint8_t on_behalf_of_location_id[41];       /* bytes 286 to 326 */
} NewOrderRequestMessage;

/* any New Order Request Message at all: every byte one the checker chooses */
static void any_new_order_request_message(NewOrderRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_show[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expire_date[i] = arbitrary(); }
  record->self_match_prevention_instruction = arbitrary();
  record->exec_inst = arbitrary();
  record->direct_electronic_access = arbitrary();
  record->trading_capacity = arbitrary();
  record->liquidity_provision = arbitrary();
  record->commodity_deriv_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->investment_decision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_decision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_id_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mifid_id[i] = arbitrary(); }
  record->cust_order_handling_inst = arbitrary();
  record->position_effect = arbitrary();
  record->alloc_handl_inst = arbitrary();
  record->price_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->customer_account_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->memo[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->allocation_account[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_comp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_location_id[i] = arbitrary(); }
}

/* New Order Request Message to the wire: 327 bytes from at, returning where the next byte goes */
static size_t encode_new_order_request_message(const NewOrderRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->side;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_show[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expire_date[i]; }
  wire[at++] = record->self_match_prevention_instruction;
  wire[at++] = record->exec_inst;
  wire[at++] = record->direct_electronic_access;
  wire[at++] = record->trading_capacity;
  wire[at++] = record->liquidity_provision;
  wire[at++] = record->commodity_deriv_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_decision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_decision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_id_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mifid_id[i]; }
  wire[at++] = record->cust_order_handling_inst;
  wire[at++] = record->position_effect;
  wire[at++] = record->alloc_handl_inst;
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->customer_account_ref_id[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->memo[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->allocation_account[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_comp_id[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_sub_id[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_location_id[i]; }

  return at;
}

/* New Order Request Message off the wire: 327 bytes from at, returning where the next byte lies */
static size_t decode_new_order_request_message(NewOrderRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_show[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expire_date[i] = wire[at++]; }
  record->self_match_prevention_instruction = wire[at++];
  record->exec_inst = wire[at++];
  record->direct_electronic_access = wire[at++];
  record->trading_capacity = wire[at++];
  record->liquidity_provision = wire[at++];
  record->commodity_deriv_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->investment_decision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_decision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_id_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mifid_id[i] = wire[at++]; }
  record->cust_order_handling_inst = wire[at++];
  record->position_effect = wire[at++];
  record->alloc_handl_inst = wire[at++];
  record->price_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->customer_account_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->memo[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->allocation_account[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_comp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_location_id[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Request Message is what was written, byte for byte */
static void equal_new_order_request_message(const NewOrderRequestMessage *read, const NewOrderRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->side == written->side);
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_show[i] == written->max_show[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_clearing_firm[i] == written->give_up_clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
  assert(read->self_match_prevention_instruction == written->self_match_prevention_instruction);
  assert(read->exec_inst == written->exec_inst);
  assert(read->direct_electronic_access == written->direct_electronic_access);
  assert(read->trading_capacity == written->trading_capacity);
  assert(read->liquidity_provision == written->liquidity_provision);
  assert(read->commodity_deriv_indicator == written->commodity_deriv_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->investment_decision[i] == written->investment_decision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_decision[i] == written->execution_decision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_id_code[i] == written->client_id_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mifid_id[i] == written->mifid_id[i]); }
  assert(read->cust_order_handling_inst == written->cust_order_handling_inst);
  assert(read->position_effect == written->position_effect);
  assert(read->alloc_handl_inst == written->alloc_handl_inst);
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 14; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->customer_account_ref_id[i] == written->customer_account_ref_id[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->memo[i] == written->memo[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->allocation_account[i] == written->allocation_account[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_comp_id[i] == written->on_behalf_of_comp_id[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_sub_id[i] == written->on_behalf_of_sub_id[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_location_id[i] == written->on_behalf_of_location_id[i]); }
}

/* New Order Request Message: written and read back, then read and written back */
static void check_new_order_request_message(void) {
  NewOrderRequestMessage sent;
  NewOrderRequestMessage got;
  uint8_t wire[327];
  uint8_t again[327];

  any_new_order_request_message(&sent);
  assert(encode_new_order_request_message(&sent, wire, 0) == 327);
  assert(decode_new_order_request_message(&got, wire, 0) == 327);
  equal_new_order_request_message(&got, &sent);

  for (size_t i = 0; i < 327; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_request_message(&got, wire, 0) == 327);
  assert(encode_new_order_request_message(&got, again, 0) == 327);
  for (size_t i = 0; i < 327; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Replace Request Message: 333 bytes ------------------------------- */

/* CancelReplaceRequestMessage */
typedef struct {
  uint8_t price_optional[8];                  /* bytes 0 to 7 */
  uint8_t order_qty[8];                       /* bytes 8 to 15 */
  uint8_t symbol[4];                          /* bytes 16 to 19 */
  uint8_t time_in_force;                      /* byte 20 */
  uint8_t side;                               /* byte 21 */
  uint8_t originator_user_id[20];             /* bytes 22 to 41 */
  uint8_t ord_type;                           /* byte 42 */
  uint8_t manual_order_indicator;             /* byte 43 */
  uint8_t cl_ord_id[8];                       /* bytes 44 to 51 */
  uint8_t orig_cl_ord_id[8];                  /* bytes 52 to 59 */
  uint8_t max_show[8];                        /* bytes 60 to 67 */
  uint8_t stop_px[8];                         /* bytes 68 to 75 */
  uint8_t give_up_clearing_firm[4];           /* bytes 76 to 79 */
  uint8_t clearing_firm[4];                   /* bytes 80 to 83 */
  uint8_t self_match_prevention_id[8];        /* bytes 84 to 91 */
  uint8_t expire_date[2];                     /* bytes 92 to 93 */
  uint8_t self_match_prevention_instruction;  /* byte 94 */
  uint8_t exec_inst;                          /* byte 95 */
  uint8_t direct_electronic_access;           /* byte 96 */
  uint8_t trading_capacity;                   /* byte 97 */
  uint8_t liquidity_provision;                /* byte 98 */
  uint8_t commodity_deriv_indicator;          /* byte 99 */
  uint8_t investment_decision[8];             /* bytes 100 to 107 */
  uint8_t execution_decision[8];              /* bytes 108 to 115 */
  uint8_t client_id_code[8];                  /* bytes 116 to 123 */
  uint8_t mifid_id[8];                        /* bytes 124 to 131 */
  uint8_t alloc_handl_inst;                   /* byte 132 */
  uint8_t price_type;                         /* byte 133 */
  uint8_t clearing_account[14];               /* bytes 134 to 147 */
  uint8_t customer_account_ref_id[12];        /* bytes 148 to 159 */
  uint8_t memo[30];                           /* bytes 160 to 189 */
  uint8_t allocation_account[20];             /* bytes 190 to 209 */
  uint8_t on_behalf_of_comp_id[41];           /* bytes 210 to 250 */
  uint8_t on_behalf_of_sub_id[41];            /* bytes 251 to 291 */
  uint8_t on_behalf_of_location_id[41];       /* bytes 292 to 332 */
} CancelReplaceRequestMessage;

/* any Cancel Replace Request Message at all: every byte one the checker chooses */
static void any_cancel_replace_request_message(CancelReplaceRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->manual_order_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->max_show[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expire_date[i] = arbitrary(); }
  record->self_match_prevention_instruction = arbitrary();
  record->exec_inst = arbitrary();
  record->direct_electronic_access = arbitrary();
  record->trading_capacity = arbitrary();
  record->liquidity_provision = arbitrary();
  record->commodity_deriv_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->investment_decision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_decision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_id_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mifid_id[i] = arbitrary(); }
  record->alloc_handl_inst = arbitrary();
  record->price_type = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->clearing_account[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->customer_account_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->memo[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->allocation_account[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_comp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_location_id[i] = arbitrary(); }
}

/* Cancel Replace Request Message to the wire: 333 bytes from at, returning where the next byte goes */
static size_t encode_cancel_replace_request_message(const CancelReplaceRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->side;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->manual_order_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_show[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expire_date[i]; }
  wire[at++] = record->self_match_prevention_instruction;
  wire[at++] = record->exec_inst;
  wire[at++] = record->direct_electronic_access;
  wire[at++] = record->trading_capacity;
  wire[at++] = record->liquidity_provision;
  wire[at++] = record->commodity_deriv_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_decision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_decision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_id_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mifid_id[i]; }
  wire[at++] = record->alloc_handl_inst;
  wire[at++] = record->price_type;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->clearing_account[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->customer_account_ref_id[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->memo[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->allocation_account[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_comp_id[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_sub_id[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_location_id[i]; }

  return at;
}

/* Cancel Replace Request Message off the wire: 333 bytes from at, returning where the next byte lies */
static size_t decode_cancel_replace_request_message(CancelReplaceRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->manual_order_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->max_show[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expire_date[i] = wire[at++]; }
  record->self_match_prevention_instruction = wire[at++];
  record->exec_inst = wire[at++];
  record->direct_electronic_access = wire[at++];
  record->trading_capacity = wire[at++];
  record->liquidity_provision = wire[at++];
  record->commodity_deriv_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->investment_decision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_decision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_id_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mifid_id[i] = wire[at++]; }
  record->alloc_handl_inst = wire[at++];
  record->price_type = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->clearing_account[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->customer_account_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->memo[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->allocation_account[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_comp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_location_id[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Replace Request Message is what was written, byte for byte */
static void equal_cancel_replace_request_message(const CancelReplaceRequestMessage *read, const CancelReplaceRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->side == written->side);
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->manual_order_indicator == written->manual_order_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->max_show[i] == written->max_show[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_clearing_firm[i] == written->give_up_clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm[i] == written->clearing_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
  assert(read->self_match_prevention_instruction == written->self_match_prevention_instruction);
  assert(read->exec_inst == written->exec_inst);
  assert(read->direct_electronic_access == written->direct_electronic_access);
  assert(read->trading_capacity == written->trading_capacity);
  assert(read->liquidity_provision == written->liquidity_provision);
  assert(read->commodity_deriv_indicator == written->commodity_deriv_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->investment_decision[i] == written->investment_decision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_decision[i] == written->execution_decision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_id_code[i] == written->client_id_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mifid_id[i] == written->mifid_id[i]); }
  assert(read->alloc_handl_inst == written->alloc_handl_inst);
  assert(read->price_type == written->price_type);
  for (size_t i = 0; i < 14; i++) { assert(read->clearing_account[i] == written->clearing_account[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->customer_account_ref_id[i] == written->customer_account_ref_id[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->memo[i] == written->memo[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->allocation_account[i] == written->allocation_account[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_comp_id[i] == written->on_behalf_of_comp_id[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_sub_id[i] == written->on_behalf_of_sub_id[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_location_id[i] == written->on_behalf_of_location_id[i]); }
}

/* Cancel Replace Request Message: written and read back, then read and written back */
static void check_cancel_replace_request_message(void) {
  CancelReplaceRequestMessage sent;
  CancelReplaceRequestMessage got;
  uint8_t wire[333];
  uint8_t again[333];

  any_cancel_replace_request_message(&sent);
  assert(encode_cancel_replace_request_message(&sent, wire, 0) == 333);
  assert(decode_cancel_replace_request_message(&got, wire, 0) == 333);
  equal_cancel_replace_request_message(&got, &sent);

  for (size_t i = 0; i < 333; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_replace_request_message(&got, wire, 0) == 333);
  assert(encode_cancel_replace_request_message(&got, again, 0) == 333);
  for (size_t i = 0; i < 333; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Request Message: 41 bytes ---------------------------------------- */

/* CancelRequestMessage */
typedef struct {
  uint8_t symbol[4];               /* bytes 0 to 3 */
  uint8_t originator_user_id[20];  /* bytes 4 to 23 */
  uint8_t cl_ord_id[8];            /* bytes 24 to 31 */
  uint8_t orig_cl_ord_id[8];       /* bytes 32 to 39 */
  uint8_t side;                    /* byte 40 */
} CancelRequestMessage;

/* any Cancel Request Message at all: every byte one the checker chooses */
static void any_cancel_request_message(CancelRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->side = arbitrary();
}

/* Cancel Request Message to the wire: 41 bytes from at, returning where the next byte goes */
static size_t encode_cancel_request_message(const CancelRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->side;

  return at;
}

/* Cancel Request Message off the wire: 41 bytes from at, returning where the next byte lies */
static size_t decode_cancel_request_message(CancelRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of Cancel Request Message is what was written, byte for byte */
static void equal_cancel_request_message(const CancelRequestMessage *read, const CancelRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->side == written->side);
}

/* Cancel Request Message: written and read back, then read and written back */
static void check_cancel_request_message(void) {
  CancelRequestMessage sent;
  CancelRequestMessage got;
  uint8_t wire[41];
  uint8_t again[41];

  any_cancel_request_message(&sent);
  assert(encode_cancel_request_message(&sent, wire, 0) == 41);
  assert(decode_cancel_request_message(&got, wire, 0) == 41);
  equal_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 41; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_request_message(&got, wire, 0) == 41);
  assert(encode_cancel_request_message(&got, again, 0) == 41);
  for (size_t i = 0; i < 41; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Request Message: 182 bytes ---------------------------------------- */

/* QuoteRequestMessage */
typedef struct {
  uint8_t originator_user_id[20];         /* bytes 0 to 19 */
  uint8_t side_optional;                  /* byte 20 */
  uint8_t order_qty_optional[8];          /* bytes 21 to 28 */
  uint8_t rfq_req_id[8];                  /* bytes 29 to 36 */
  uint8_t symbol[4];                      /* bytes 37 to 40 */
  uint8_t clearing_firm_optional[4];      /* bytes 41 to 44 */
  uint8_t clearing_account_optional[14];  /* bytes 45 to 58 */
  uint8_t on_behalf_of_comp_id[41];       /* bytes 59 to 99 */
  uint8_t on_behalf_of_sub_id[41];        /* bytes 100 to 140 */
  uint8_t on_behalf_of_location_id[41];   /* bytes 141 to 181 */
} QuoteRequestMessage;

/* any Quote Request Message at all: every byte one the checker chooses */
static void any_quote_request_message(QuoteRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  record->side_optional = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_qty_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->rfq_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->clearing_account_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_comp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_id[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_location_id[i] = arbitrary(); }
}

/* Quote Request Message to the wire: 182 bytes from at, returning where the next byte goes */
static size_t encode_quote_request_message(const QuoteRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  wire[at++] = record->side_optional;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rfq_req_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm_optional[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->clearing_account_optional[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_comp_id[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_sub_id[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_location_id[i]; }

  return at;
}

/* Quote Request Message off the wire: 182 bytes from at, returning where the next byte lies */
static size_t decode_quote_request_message(QuoteRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  record->side_optional = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_qty_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->rfq_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->clearing_account_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_comp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_id[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_location_id[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Request Message is what was written, byte for byte */
static void equal_quote_request_message(const QuoteRequestMessage *read, const QuoteRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  assert(read->side_optional == written->side_optional);
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty_optional[i] == written->order_qty_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->rfq_req_id[i] == written->rfq_req_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm_optional[i] == written->clearing_firm_optional[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->clearing_account_optional[i] == written->clearing_account_optional[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_comp_id[i] == written->on_behalf_of_comp_id[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_sub_id[i] == written->on_behalf_of_sub_id[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_location_id[i] == written->on_behalf_of_location_id[i]); }
}

/* Quote Request Message: written and read back, then read and written back */
static void check_quote_request_message(void) {
  QuoteRequestMessage sent;
  QuoteRequestMessage got;
  uint8_t wire[182];
  uint8_t again[182];

  any_quote_request_message(&sent);
  assert(encode_quote_request_message(&sent, wire, 0) == 182);
  assert(decode_quote_request_message(&got, wire, 0) == 182);
  equal_quote_request_message(&got, &sent);

  for (size_t i = 0; i < 182; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_request_message(&got, wire, 0) == 182);
  assert(encode_quote_request_message(&got, again, 0) == 182);
  for (size_t i = 0; i < 182; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Cancel Request Message: 89 bytes ----------------------------- */

/* OrderMassCancelRequestMessage */
typedef struct {
  uint8_t originator_user_id[20];             /* bytes 0 to 19 */
  uint8_t ord_type_optional;                  /* byte 20 */
  uint8_t side_optional;                      /* byte 21 */
  uint8_t symbol_optional[4];                 /* bytes 22 to 25 */
  uint8_t cl_ord_id[8];                       /* bytes 26 to 33 */
  uint8_t market_type_i_d_optional[4];        /* bytes 34 to 37 */
  uint8_t price_optional[8];                  /* bytes 38 to 45 */
  uint8_t mass_cancel_request_type;           /* byte 46 */
  uint8_t time_in_force_optional;             /* byte 47 */
  uint8_t on_behalf_of_sub_i_d_optional[41];  /* bytes 48 to 88 */
} OrderMassCancelRequestMessage;

/* any Order Mass Cancel Request Message at all: every byte one the checker chooses */
static void any_order_mass_cancel_request_message(OrderMassCancelRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  record->ord_type_optional = arbitrary();
  record->side_optional = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_type_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  record->mass_cancel_request_type = arbitrary();
  record->time_in_force_optional = arbitrary();
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_i_d_optional[i] = arbitrary(); }
}

/* Order Mass Cancel Request Message to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_cancel_request_message(const OrderMassCancelRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  wire[at++] = record->ord_type_optional;
  wire[at++] = record->side_optional;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_type_i_d_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  wire[at++] = record->mass_cancel_request_type;
  wire[at++] = record->time_in_force_optional;
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_sub_i_d_optional[i]; }

  return at;
}

/* Order Mass Cancel Request Message off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_cancel_request_message(OrderMassCancelRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  record->ord_type_optional = wire[at++];
  record->side_optional = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_type_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  record->mass_cancel_request_type = wire[at++];
  record->time_in_force_optional = wire[at++];
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_i_d_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Order Mass Cancel Request Message is what was written, byte for byte */
static void equal_order_mass_cancel_request_message(const OrderMassCancelRequestMessage *read, const OrderMassCancelRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  assert(read->ord_type_optional == written->ord_type_optional);
  assert(read->side_optional == written->side_optional);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_optional[i] == written->symbol_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_type_i_d_optional[i] == written->market_type_i_d_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  assert(read->mass_cancel_request_type == written->mass_cancel_request_type);
  assert(read->time_in_force_optional == written->time_in_force_optional);
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_sub_i_d_optional[i] == written->on_behalf_of_sub_i_d_optional[i]); }
}

/* Order Mass Cancel Request Message: written and read back, then read and written back */
static void check_order_mass_cancel_request_message(void) {
  OrderMassCancelRequestMessage sent;
  OrderMassCancelRequestMessage got;
  uint8_t wire[89];
  uint8_t again[89];

  any_order_mass_cancel_request_message(&sent);
  assert(encode_order_mass_cancel_request_message(&sent, wire, 0) == 89);
  assert(decode_order_mass_cancel_request_message(&got, wire, 0) == 89);
  equal_order_mass_cancel_request_message(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_cancel_request_message(&got, wire, 0) == 89);
  assert(encode_order_mass_cancel_request_message(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Definition Request Create Flex Message: 28 bytes --------------- */

/* SecurityDefinitionRequest_CreateFlexMessage */
typedef struct {
  uint8_t security_req_id[4];       /* bytes 0 to 3 */
  uint8_t security_request_type;    /* byte 4 */
  uint8_t market_type_id[4];        /* bytes 5 to 8 */
  uint8_t security_type;            /* byte 9 */
  uint8_t maturity_date[2];         /* bytes 10 to 11 */
  uint8_t product_i_d_optional[4];  /* bytes 12 to 15 */
  uint8_t symbol_optional[4];       /* bytes 16 to 19 */
  uint8_t strike_price[8];          /* bytes 20 to 27 */
} SecurityDefinitionRequestCreateFlexMessage;

/* any Security Definition Request Create Flex Message at all: every byte one the checker chooses */
static void any_security_definition_request_create_flex_message(SecurityDefinitionRequestCreateFlexMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = arbitrary(); }
  record->security_request_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->market_type_id[i] = arbitrary(); }
  record->security_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->product_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
}

/* Security Definition Request Create Flex Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_security_definition_request_create_flex_message(const SecurityDefinitionRequestCreateFlexMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_req_id[i]; }
  wire[at++] = record->security_request_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_type_id[i]; }
  wire[at++] = record->security_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->product_i_d_optional[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }

  return at;
}

/* Security Definition Request Create Flex Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_security_definition_request_create_flex_message(SecurityDefinitionRequestCreateFlexMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = wire[at++]; }
  record->security_request_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->market_type_id[i] = wire[at++]; }
  record->security_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->product_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }

  return at;
}

/* what was read of Security Definition Request Create Flex Message is what was written, byte for byte */
static void equal_security_definition_request_create_flex_message(const SecurityDefinitionRequestCreateFlexMessage *read, const SecurityDefinitionRequestCreateFlexMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_req_id[i] == written->security_req_id[i]); }
  assert(read->security_request_type == written->security_request_type);
  for (size_t i = 0; i < 4; i++) { assert(read->market_type_id[i] == written->market_type_id[i]); }
  assert(read->security_type == written->security_type);
  for (size_t i = 0; i < 2; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->product_i_d_optional[i] == written->product_i_d_optional[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_optional[i] == written->symbol_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
}

/* Security Definition Request Create Flex Message: written and read back, then read and written back */
static void check_security_definition_request_create_flex_message(void) {
  SecurityDefinitionRequestCreateFlexMessage sent;
  SecurityDefinitionRequestCreateFlexMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_security_definition_request_create_flex_message(&sent);
  assert(encode_security_definition_request_create_flex_message(&sent, wire, 0) == 28);
  assert(decode_security_definition_request_create_flex_message(&got, wire, 0) == 28);
  equal_security_definition_request_create_flex_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_security_definition_request_create_flex_message(&got, wire, 0) == 28);
  assert(encode_security_definition_request_create_flex_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Exec I D order Exec Id: 20 bytes ---------------------------------------- */

/* ExecutionReport_NewMessage */
typedef struct {
  uint8_t system_id[8];                    /* bytes 0 to 7 */
  uint8_t system_sequence_id[4];           /* bytes 8 to 11 */
  uint8_t transact_time_utc_timestamp[8];  /* bytes 12 to 19 */
} ExecIDOrderExecId;

/* any Exec I D order Exec Id at all: every byte one the checker chooses */
static void any_exec_i_d_order_exec_id(ExecIDOrderExecId *record) {
  for (size_t i = 0; i < 8; i++) { record->system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->system_sequence_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time_utc_timestamp[i] = arbitrary(); }
}

/* Exec I D order Exec Id to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_exec_i_d_order_exec_id(const ExecIDOrderExecId *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->system_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->system_sequence_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time_utc_timestamp[i]; }

  return at;
}

/* Exec I D order Exec Id off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_exec_i_d_order_exec_id(ExecIDOrderExecId *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->system_sequence_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time_utc_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Exec I D order Exec Id is what was written, byte for byte */
static void equal_exec_i_d_order_exec_id(const ExecIDOrderExecId *read, const ExecIDOrderExecId *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->system_id[i] == written->system_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->system_sequence_id[i] == written->system_sequence_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time_utc_timestamp[i] == written->transact_time_utc_timestamp[i]); }
}

/* Exec I D order Exec Id: written and read back, then read and written back */
static void check_exec_i_d_order_exec_id(void) {
  ExecIDOrderExecId sent;
  ExecIDOrderExecId got;
  uint8_t wire[20];
  uint8_t again[20];

  any_exec_i_d_order_exec_id(&sent);
  assert(encode_exec_i_d_order_exec_id(&sent, wire, 0) == 20);
  assert(decode_exec_i_d_order_exec_id(&got, wire, 0) == 20);
  equal_exec_i_d_order_exec_id(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_exec_i_d_order_exec_id(&got, wire, 0) == 20);
  assert(encode_exec_i_d_order_exec_id(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Orig Order Id: 16 bytes ------------------------------------------------- */

/* ExecutionReport_NewMessage */
typedef struct {
  uint8_t original_system_id[8];           /* bytes 0 to 7 */
  uint8_t original_creation_timestamp[8];  /* bytes 8 to 15 */
} OrigOrderId;

/* any Orig Order Id at all: every byte one the checker chooses */
static void any_orig_order_id(OrigOrderId *record) {
  for (size_t i = 0; i < 8; i++) { record->original_system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->original_creation_timestamp[i] = arbitrary(); }
}

/* Orig Order Id to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_orig_order_id(const OrigOrderId *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_system_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->original_creation_timestamp[i]; }

  return at;
}

/* Orig Order Id off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_orig_order_id(OrigOrderId *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->original_system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->original_creation_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Orig Order Id is what was written, byte for byte */
static void equal_orig_order_id(const OrigOrderId *read, const OrigOrderId *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->original_system_id[i] == written->original_system_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->original_creation_timestamp[i] == written->original_creation_timestamp[i]); }
}

/* Orig Order Id: written and read back, then read and written back */
static void check_orig_order_id(void) {
  OrigOrderId sent;
  OrigOrderId got;
  uint8_t wire[16];
  uint8_t again[16];

  any_orig_order_id(&sent);
  assert(encode_orig_order_id(&sent, wire, 0) == 16);
  assert(decode_orig_order_id(&got, wire, 0) == 16);
  equal_orig_order_id(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_orig_order_id(&got, wire, 0) == 16);
  assert(encode_orig_order_id(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report New Message: 133 bytes --------------------------------- */

/* ExecutionReport_NewMessage */
typedef struct {
  uint8_t originator_user_id[20];            /* bytes 0 to 19 */
  ExecIDOrderExecId exec_i_d_order_exec_id;  /* bytes 20 to 39 */
  uint8_t cl_ord_id[8];                      /* bytes 40 to 47 */
  uint8_t symbol[4];                         /* bytes 48 to 51 */
  uint8_t ord_type;                          /* byte 52 */
  uint8_t side;                              /* byte 53 */
  OrigOrderId orig_order_id;                 /* bytes 54 to 69 */
  uint8_t leaves_qty[8];                     /* bytes 70 to 77 */
  uint8_t price_optional[8];                 /* bytes 78 to 85 */
  uint8_t me_acceptance_time[8];             /* bytes 86 to 93 */
  uint8_t time_priority[8];                  /* bytes 94 to 101 */
  uint8_t order_status;                      /* byte 102 */
  uint8_t memo[30];                          /* bytes 103 to 132 */
} ExecutionReportNewMessage;

/* any Execution Report New Message at all: every byte one the checker chooses */
static void any_execution_report_new_message(ExecutionReportNewMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  any_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id);
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->side = arbitrary();
  any_orig_order_id(&record->orig_order_id);
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->me_acceptance_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_priority[i] = arbitrary(); }
  record->order_status = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->memo[i] = arbitrary(); }
}

/* Execution Report New Message to the wire: 133 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_new_message(const ExecutionReportNewMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  at = encode_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->side;
  at = encode_orig_order_id(&record->orig_order_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->me_acceptance_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_priority[i]; }
  wire[at++] = record->order_status;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->memo[i]; }

  return at;
}

/* Execution Report New Message off the wire: 133 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_new_message(ExecutionReportNewMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  at = decode_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->side = wire[at++];
  at = decode_orig_order_id(&record->orig_order_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->me_acceptance_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_priority[i] = wire[at++]; }
  record->order_status = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->memo[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report New Message is what was written, byte for byte */
static void equal_execution_report_new_message(const ExecutionReportNewMessage *read, const ExecutionReportNewMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  equal_exec_i_d_order_exec_id(&read->exec_i_d_order_exec_id, &written->exec_i_d_order_exec_id);
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->side == written->side);
  equal_orig_order_id(&read->orig_order_id, &written->orig_order_id);
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->me_acceptance_time[i] == written->me_acceptance_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_priority[i] == written->time_priority[i]); }
  assert(read->order_status == written->order_status);
  for (size_t i = 0; i < 30; i++) { assert(read->memo[i] == written->memo[i]); }
}

/* Execution Report New Message: written and read back, then read and written back */
static void check_execution_report_new_message(void) {
  ExecutionReportNewMessage sent;
  ExecutionReportNewMessage got;
  uint8_t wire[133];
  uint8_t again[133];

  any_execution_report_new_message(&sent);
  assert(encode_execution_report_new_message(&sent, wire, 0) == 133);
  assert(decode_execution_report_new_message(&got, wire, 0) == 133);
  equal_execution_report_new_message(&got, &sent);

  for (size_t i = 0; i < 133; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_new_message(&got, wire, 0) == 133);
  assert(encode_execution_report_new_message(&got, again, 0) == 133);
  for (size_t i = 0; i < 133; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Cancel Message: 199 bytes ------------------------------ */

/* ExecutionReport_CancelMessage */
typedef struct {
  uint8_t originator_user_id[20];            /* bytes 0 to 19 */
  ExecIDOrderExecId exec_i_d_order_exec_id;  /* bytes 20 to 39 */
  uint8_t cl_ord_id[8];                      /* bytes 40 to 47 */
  uint8_t symbol[4];                         /* bytes 48 to 51 */
  uint8_t ord_type;                          /* byte 52 */
  uint8_t side;                              /* byte 53 */
  OrigOrderId orig_order_id;                 /* bytes 54 to 69 */
  uint8_t orig_cl_ord_i_d_optional[8];       /* bytes 70 to 77 */
  uint8_t me_acceptance_time[8];             /* bytes 78 to 85 */
  uint8_t exchange_code[4];                  /* bytes 86 to 89 */
  uint8_t cancel_reason;                     /* byte 90 */
  uint8_t cross_i_d_optional[8];             /* bytes 91 to 98 */
  uint8_t text[100];                         /* bytes 99 to 198 */
} ExecutionReportCancelMessage;

/* any Execution Report Cancel Message at all: every byte one the checker chooses */
static void any_execution_report_cancel_message(ExecutionReportCancelMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  any_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id);
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->side = arbitrary();
  any_orig_order_id(&record->orig_order_id);
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->me_acceptance_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->cross_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Execution Report Cancel Message to the wire: 199 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_cancel_message(const ExecutionReportCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  at = encode_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->side;
  at = encode_orig_order_id(&record->orig_order_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_i_d_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->me_acceptance_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  wire[at++] = record->cancel_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cross_i_d_optional[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Execution Report Cancel Message off the wire: 199 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_cancel_message(ExecutionReportCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  at = decode_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->side = wire[at++];
  at = decode_orig_order_id(&record->orig_order_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->me_acceptance_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  record->cancel_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->cross_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Cancel Message is what was written, byte for byte */
static void equal_execution_report_cancel_message(const ExecutionReportCancelMessage *read, const ExecutionReportCancelMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  equal_exec_i_d_order_exec_id(&read->exec_i_d_order_exec_id, &written->exec_i_d_order_exec_id);
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->side == written->side);
  equal_orig_order_id(&read->orig_order_id, &written->orig_order_id);
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_i_d_optional[i] == written->orig_cl_ord_i_d_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->me_acceptance_time[i] == written->me_acceptance_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  assert(read->cancel_reason == written->cancel_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->cross_i_d_optional[i] == written->cross_i_d_optional[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Execution Report Cancel Message: written and read back, then read and written back */
static void check_execution_report_cancel_message(void) {
  ExecutionReportCancelMessage sent;
  ExecutionReportCancelMessage got;
  uint8_t wire[199];
  uint8_t again[199];

  any_execution_report_cancel_message(&sent);
  assert(encode_execution_report_cancel_message(&sent, wire, 0) == 199);
  assert(decode_execution_report_cancel_message(&got, wire, 0) == 199);
  equal_execution_report_cancel_message(&got, &sent);

  for (size_t i = 0; i < 199; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_cancel_message(&got, wire, 0) == 199);
  assert(encode_execution_report_cancel_message(&got, again, 0) == 199);
  for (size_t i = 0; i < 199; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Reject Message: 215 bytes ------------------------------ */

/* ExecutionReport_RejectMessage */
typedef struct {
  uint8_t originator_user_id[20];            /* bytes 0 to 19 */
  ExecIDOrderExecId exec_i_d_order_exec_id;  /* bytes 20 to 39 */
  uint8_t cl_ord_id[8];                      /* bytes 40 to 47 */
  uint8_t symbol[4];                         /* bytes 48 to 51 */
  uint8_t ord_type_optional;                 /* byte 52 */
  uint8_t side;                              /* byte 53 */
  OrigOrderId orig_order_id;                 /* bytes 54 to 69 */
  uint8_t orig_cl_ord_i_d_optional[8];       /* bytes 70 to 77 */
  uint8_t order_status;                      /* byte 78 */
  uint8_t reject_response_to;                /* byte 79 */
  uint8_t reject_reason;                     /* byte 80 */
  uint8_t exchange_code[4];                  /* bytes 81 to 84 */
  uint8_t memo[30];                          /* bytes 85 to 114 */
  uint8_t text[100];                         /* bytes 115 to 214 */
} ExecutionReportRejectMessage;

/* any Execution Report Reject Message at all: every byte one the checker chooses */
static void any_execution_report_reject_message(ExecutionReportRejectMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  any_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id);
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  record->ord_type_optional = arbitrary();
  record->side = arbitrary();
  any_orig_order_id(&record->orig_order_id);
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_i_d_optional[i] = arbitrary(); }
  record->order_status = arbitrary();
  record->reject_response_to = arbitrary();
  record->reject_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->memo[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Execution Report Reject Message to the wire: 215 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_reject_message(const ExecutionReportRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  at = encode_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->ord_type_optional;
  wire[at++] = record->side;
  at = encode_orig_order_id(&record->orig_order_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_i_d_optional[i]; }
  wire[at++] = record->order_status;
  wire[at++] = record->reject_response_to;
  wire[at++] = record->reject_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->memo[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Execution Report Reject Message off the wire: 215 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_reject_message(ExecutionReportRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  at = decode_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  record->ord_type_optional = wire[at++];
  record->side = wire[at++];
  at = decode_orig_order_id(&record->orig_order_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_i_d_optional[i] = wire[at++]; }
  record->order_status = wire[at++];
  record->reject_response_to = wire[at++];
  record->reject_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->memo[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Reject Message is what was written, byte for byte */
static void equal_execution_report_reject_message(const ExecutionReportRejectMessage *read, const ExecutionReportRejectMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  equal_exec_i_d_order_exec_id(&read->exec_i_d_order_exec_id, &written->exec_i_d_order_exec_id);
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->ord_type_optional == written->ord_type_optional);
  assert(read->side == written->side);
  equal_orig_order_id(&read->orig_order_id, &written->orig_order_id);
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_i_d_optional[i] == written->orig_cl_ord_i_d_optional[i]); }
  assert(read->order_status == written->order_status);
  assert(read->reject_response_to == written->reject_response_to);
  assert(read->reject_reason == written->reject_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->memo[i] == written->memo[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Execution Report Reject Message: written and read back, then read and written back */
static void check_execution_report_reject_message(void) {
  ExecutionReportRejectMessage sent;
  ExecutionReportRejectMessage got;
  uint8_t wire[215];
  uint8_t again[215];

  any_execution_report_reject_message(&sent);
  assert(encode_execution_report_reject_message(&sent, wire, 0) == 215);
  assert(decode_execution_report_reject_message(&got, wire, 0) == 215);
  equal_execution_report_reject_message(&got, &sent);

  for (size_t i = 0; i < 215; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_reject_message(&got, wire, 0) == 215);
  assert(encode_execution_report_reject_message(&got, again, 0) == 215);
  for (size_t i = 0; i < 215; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Report Snapshot Message: 380 bytes ---------------------------- */

/* ExecutionReport_SnapshotMessage */
typedef struct {
  uint8_t originator_user_id[20];                  /* bytes 0 to 19 */
  ExecIDOrderExecId exec_i_d_order_exec_id;        /* bytes 20 to 39 */
  uint8_t cl_ord_id[8];                            /* bytes 40 to 47 */
  uint8_t symbol[4];                               /* bytes 48 to 51 */
  uint8_t ord_type;                                /* byte 52 */
  uint8_t side;                                    /* byte 53 */
  OrigOrderId orig_order_id;                       /* bytes 54 to 69 */
  uint8_t max_show[8];                             /* bytes 70 to 77 */
  uint8_t leaves_qty[8];                           /* bytes 78 to 85 */
  uint8_t cum_qty[8];                              /* bytes 86 to 93 */
  uint8_t price_optional[8];                       /* bytes 94 to 101 */
  uint8_t stop_px[8];                              /* bytes 102 to 109 */
  uint8_t expire_date[2];                          /* bytes 110 to 111 */
  uint8_t time_priority[8];                        /* bytes 112 to 119 */
  uint8_t time_in_force;                           /* byte 120 */
  uint8_t order_status;                            /* byte 121 */
  uint8_t order_state;                             /* byte 122 */
  uint8_t give_up_clearing_firm[4];                /* bytes 123 to 126 */
  uint8_t clearing_firm_optional[4];               /* bytes 127 to 130 */
  uint8_t direct_electronic_access;                /* byte 131 */
  uint8_t trading_capacity;                        /* byte 132 */
  uint8_t liquidity_provision;                     /* byte 133 */
  uint8_t commodity_deriv_indicator;               /* byte 134 */
  uint8_t investment_decision[8];                  /* bytes 135 to 142 */
  uint8_t execution_decision[8];                   /* bytes 143 to 150 */
  uint8_t client_id_code[8];                       /* bytes 151 to 158 */
  uint8_t mifid_id[8];                             /* bytes 159 to 166 */
  uint8_t self_match_prevention_id[8];             /* bytes 167 to 174 */
  uint8_t self_match_prevention_instruction;       /* byte 175 */
  uint8_t manual_order_indicator;                  /* byte 176 */
  uint8_t exec_inst;                               /* byte 177 */
  uint8_t cust_order_handling_inst;                /* byte 178 */
  uint8_t position_effect;                         /* byte 179 */
  uint8_t alloc_handl_inst;                        /* byte 180 */
  uint8_t clearing_account_optional[14];           /* bytes 181 to 194 */
  uint8_t customer_account_ref_id[12];             /* bytes 195 to 206 */
  uint8_t memo[30];                                /* bytes 207 to 236 */
  uint8_t allocation_account[20];                  /* bytes 237 to 256 */
  uint8_t on_behalf_of_comp_id[41];                /* bytes 257 to 297 */
  uint8_t on_behalf_of_sub_i_d_optional[41];       /* bytes 298 to 338 */
  uint8_t on_behalf_of_location_i_d_optional[41];  /* bytes 339 to 379 */
} ExecutionReportSnapshotMessage;

/* any Execution Report Snapshot Message at all: every byte one the checker chooses */
static void any_execution_report_snapshot_message(ExecutionReportSnapshotMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  any_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id);
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  record->ord_type = arbitrary();
  record->side = arbitrary();
  any_orig_order_id(&record->orig_order_id);
  for (size_t i = 0; i < 8; i++) { record->max_show[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->expire_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->time_priority[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->order_status = arbitrary();
  record->order_state = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_up_clearing_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm_optional[i] = arbitrary(); }
  record->direct_electronic_access = arbitrary();
  record->trading_capacity = arbitrary();
  record->liquidity_provision = arbitrary();
  record->commodity_deriv_indicator = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->investment_decision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->execution_decision[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_id_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mifid_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  record->self_match_prevention_instruction = arbitrary();
  record->manual_order_indicator = arbitrary();
  record->exec_inst = arbitrary();
  record->cust_order_handling_inst = arbitrary();
  record->position_effect = arbitrary();
  record->alloc_handl_inst = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->clearing_account_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->customer_account_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->memo[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->allocation_account[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_comp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_i_d_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_location_i_d_optional[i] = arbitrary(); }
}

/* Execution Report Snapshot Message to the wire: 380 bytes from at, returning where the next byte goes */
static size_t encode_execution_report_snapshot_message(const ExecutionReportSnapshotMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  at = encode_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  wire[at++] = record->ord_type;
  wire[at++] = record->side;
  at = encode_orig_order_id(&record->orig_order_id, wire, at);
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->max_show[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cum_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->stop_px[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->expire_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->time_priority[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->order_status;
  wire[at++] = record->order_state;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_clearing_firm[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->clearing_firm_optional[i]; }
  wire[at++] = record->direct_electronic_access;
  wire[at++] = record->trading_capacity;
  wire[at++] = record->liquidity_provision;
  wire[at++] = record->commodity_deriv_indicator;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_decision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->execution_decision[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_id_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mifid_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  wire[at++] = record->self_match_prevention_instruction;
  wire[at++] = record->manual_order_indicator;
  wire[at++] = record->exec_inst;
  wire[at++] = record->cust_order_handling_inst;
  wire[at++] = record->position_effect;
  wire[at++] = record->alloc_handl_inst;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->clearing_account_optional[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->customer_account_ref_id[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->memo[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->allocation_account[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_comp_id[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_sub_i_d_optional[i]; }
  for (size_t i = 0; i < 41; i++) { wire[at++] = record->on_behalf_of_location_i_d_optional[i]; }

  return at;
}

/* Execution Report Snapshot Message off the wire: 380 bytes from at, returning where the next byte lies */
static size_t decode_execution_report_snapshot_message(ExecutionReportSnapshotMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  at = decode_exec_i_d_order_exec_id(&record->exec_i_d_order_exec_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  record->ord_type = wire[at++];
  record->side = wire[at++];
  at = decode_orig_order_id(&record->orig_order_id, wire, at);
  for (size_t i = 0; i < 8; i++) { record->max_show[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cum_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->stop_px[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->expire_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->time_priority[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->order_status = wire[at++];
  record->order_state = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_up_clearing_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->clearing_firm_optional[i] = wire[at++]; }
  record->direct_electronic_access = wire[at++];
  record->trading_capacity = wire[at++];
  record->liquidity_provision = wire[at++];
  record->commodity_deriv_indicator = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->investment_decision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->execution_decision[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_id_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mifid_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  record->self_match_prevention_instruction = wire[at++];
  record->manual_order_indicator = wire[at++];
  record->exec_inst = wire[at++];
  record->cust_order_handling_inst = wire[at++];
  record->position_effect = wire[at++];
  record->alloc_handl_inst = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->clearing_account_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->customer_account_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->memo[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->allocation_account[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_comp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_sub_i_d_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 41; i++) { record->on_behalf_of_location_i_d_optional[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Report Snapshot Message is what was written, byte for byte */
static void equal_execution_report_snapshot_message(const ExecutionReportSnapshotMessage *read, const ExecutionReportSnapshotMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  equal_exec_i_d_order_exec_id(&read->exec_i_d_order_exec_id, &written->exec_i_d_order_exec_id);
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  assert(read->ord_type == written->ord_type);
  assert(read->side == written->side);
  equal_orig_order_id(&read->orig_order_id, &written->orig_order_id);
  for (size_t i = 0; i < 8; i++) { assert(read->max_show[i] == written->max_show[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cum_qty[i] == written->cum_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_optional[i] == written->price_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->stop_px[i] == written->stop_px[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->expire_date[i] == written->expire_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->time_priority[i] == written->time_priority[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->order_status == written->order_status);
  assert(read->order_state == written->order_state);
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_clearing_firm[i] == written->give_up_clearing_firm[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->clearing_firm_optional[i] == written->clearing_firm_optional[i]); }
  assert(read->direct_electronic_access == written->direct_electronic_access);
  assert(read->trading_capacity == written->trading_capacity);
  assert(read->liquidity_provision == written->liquidity_provision);
  assert(read->commodity_deriv_indicator == written->commodity_deriv_indicator);
  for (size_t i = 0; i < 8; i++) { assert(read->investment_decision[i] == written->investment_decision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->execution_decision[i] == written->execution_decision[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_id_code[i] == written->client_id_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mifid_id[i] == written->mifid_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  assert(read->self_match_prevention_instruction == written->self_match_prevention_instruction);
  assert(read->manual_order_indicator == written->manual_order_indicator);
  assert(read->exec_inst == written->exec_inst);
  assert(read->cust_order_handling_inst == written->cust_order_handling_inst);
  assert(read->position_effect == written->position_effect);
  assert(read->alloc_handl_inst == written->alloc_handl_inst);
  for (size_t i = 0; i < 14; i++) { assert(read->clearing_account_optional[i] == written->clearing_account_optional[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->customer_account_ref_id[i] == written->customer_account_ref_id[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->memo[i] == written->memo[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->allocation_account[i] == written->allocation_account[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_comp_id[i] == written->on_behalf_of_comp_id[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_sub_i_d_optional[i] == written->on_behalf_of_sub_i_d_optional[i]); }
  for (size_t i = 0; i < 41; i++) { assert(read->on_behalf_of_location_i_d_optional[i] == written->on_behalf_of_location_i_d_optional[i]); }
}

/* Execution Report Snapshot Message: written and read back, then read and written back */
static void check_execution_report_snapshot_message(void) {
  ExecutionReportSnapshotMessage sent;
  ExecutionReportSnapshotMessage got;
  uint8_t wire[380];
  uint8_t again[380];

  any_execution_report_snapshot_message(&sent);
  assert(encode_execution_report_snapshot_message(&sent, wire, 0) == 380);
  assert(decode_execution_report_snapshot_message(&got, wire, 0) == 380);
  equal_execution_report_snapshot_message(&got, &sent);

  for (size_t i = 0; i < 380; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_report_snapshot_message(&got, wire, 0) == 380);
  assert(encode_execution_report_snapshot_message(&got, again, 0) == 380);
  for (size_t i = 0; i < 380; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Report Message: 60 bytes ------------------------------------------ */

/* QuoteReportMessage */
typedef struct {
  uint8_t originator_user_id[20];  /* bytes 0 to 19 */
  uint8_t side_optional;           /* byte 20 */
  uint8_t symbol[4];               /* bytes 21 to 24 */
  uint8_t rfq_req_id[8];           /* bytes 25 to 32 */
  uint8_t rfq_system_id[8];        /* bytes 33 to 40 */
  uint8_t transact_time[8];        /* bytes 41 to 48 */
  uint8_t order_qty_optional[8];   /* bytes 49 to 56 */
  uint8_t quote_ack_status[2];     /* bytes 57 to 58 */
  uint8_t quote_reject_reason;     /* byte 59 */
} QuoteReportMessage;

/* any Quote Report Message at all: every byte one the checker chooses */
static void any_quote_report_message(QuoteReportMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  record->side_optional = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->rfq_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->rfq_system_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_qty_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->quote_ack_status[i] = arbitrary(); }
  record->quote_reject_reason = arbitrary();
}

/* Quote Report Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_quote_report_message(const QuoteReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  wire[at++] = record->side_optional;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rfq_req_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rfq_system_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_qty_optional[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->quote_ack_status[i]; }
  wire[at++] = record->quote_reject_reason;

  return at;
}

/* Quote Report Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_quote_report_message(QuoteReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  record->side_optional = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->rfq_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->rfq_system_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_qty_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->quote_ack_status[i] = wire[at++]; }
  record->quote_reject_reason = wire[at++];

  return at;
}

/* what was read of Quote Report Message is what was written, byte for byte */
static void equal_quote_report_message(const QuoteReportMessage *read, const QuoteReportMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  assert(read->side_optional == written->side_optional);
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->rfq_req_id[i] == written->rfq_req_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->rfq_system_id[i] == written->rfq_system_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_qty_optional[i] == written->order_qty_optional[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->quote_ack_status[i] == written->quote_ack_status[i]); }
  assert(read->quote_reject_reason == written->quote_reject_reason);
}

/* Quote Report Message: written and read back, then read and written back */
static void check_quote_report_message(void) {
  QuoteReportMessage sent;
  QuoteReportMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_quote_report_message(&sent);
  assert(encode_quote_report_message(&sent, wire, 0) == 60);
  assert(decode_quote_report_message(&got, wire, 0) == 60);
  equal_quote_report_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_report_message(&got, wire, 0) == 60);
  assert(encode_quote_report_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Cross Report Message: 145 bytes ------------------------------- */

/* NewOrderCrossReportMessage */
typedef struct {
  uint8_t originator_user_id[20];  /* bytes 0 to 19 */
  uint8_t symbol[4];               /* bytes 20 to 23 */
  uint8_t cross_id[8];             /* bytes 24 to 31 */
  uint8_t transact_time[8];        /* bytes 32 to 39 */
  uint8_t rfc_status;              /* byte 40 */
  uint8_t exchange_code[4];        /* bytes 41 to 44 */
  uint8_t text[100];               /* bytes 45 to 144 */
} NewOrderCrossReportMessage;

/* any New Order Cross Report Message at all: every byte one the checker chooses */
static void any_new_order_cross_report_message(NewOrderCrossReportMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  record->rfc_status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* New Order Cross Report Message to the wire: 145 bytes from at, returning where the next byte goes */
static size_t encode_new_order_cross_report_message(const NewOrderCrossReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  wire[at++] = record->rfc_status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* New Order Cross Report Message off the wire: 145 bytes from at, returning where the next byte lies */
static size_t decode_new_order_cross_report_message(NewOrderCrossReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  record->rfc_status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Cross Report Message is what was written, byte for byte */
static void equal_new_order_cross_report_message(const NewOrderCrossReportMessage *read, const NewOrderCrossReportMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  assert(read->rfc_status == written->rfc_status);
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* New Order Cross Report Message: written and read back, then read and written back */
static void check_new_order_cross_report_message(void) {
  NewOrderCrossReportMessage sent;
  NewOrderCrossReportMessage got;
  uint8_t wire[145];
  uint8_t again[145];

  any_new_order_cross_report_message(&sent);
  assert(encode_new_order_cross_report_message(&sent, wire, 0) == 145);
  assert(decode_new_order_cross_report_message(&got, wire, 0) == 145);
  equal_new_order_cross_report_message(&got, &sent);

  for (size_t i = 0; i < 145; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_cross_report_message(&got, wire, 0) == 145);
  assert(encode_new_order_cross_report_message(&got, again, 0) == 145);
  for (size_t i = 0; i < 145; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Cancel Report Message: 151 bytes ----------------------------- */

/* OrderMassCancelReportMessage */
typedef struct {
  uint8_t originator_user_id[20];       /* bytes 0 to 19 */
  uint8_t symbol_optional[4];           /* bytes 20 to 23 */
  uint8_t cl_ord_id[8];                 /* bytes 24 to 31 */
  uint8_t transact_time[8];             /* bytes 32 to 39 */
  uint8_t market_type_i_d_optional[4];  /* bytes 40 to 43 */
  uint8_t mass_cancel_request_type;     /* byte 44 */
  uint8_t mass_cancel_response;         /* byte 45 */
  uint8_t mass_cancel_reject_reason;    /* byte 46 */
  uint8_t exchange_code[4];             /* bytes 47 to 50 */
  uint8_t text[100];                    /* bytes 51 to 150 */
} OrderMassCancelReportMessage;

/* any Order Mass Cancel Report Message at all: every byte one the checker chooses */
static void any_order_mass_cancel_report_message(OrderMassCancelReportMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_optional[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_type_i_d_optional[i] = arbitrary(); }
  record->mass_cancel_request_type = arbitrary();
  record->mass_cancel_response = arbitrary();
  record->mass_cancel_reject_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Order Mass Cancel Report Message to the wire: 151 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_cancel_report_message(const OrderMassCancelReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->originator_user_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_optional[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->cl_ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_type_i_d_optional[i]; }
  wire[at++] = record->mass_cancel_request_type;
  wire[at++] = record->mass_cancel_response;
  wire[at++] = record->mass_cancel_reject_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Order Mass Cancel Report Message off the wire: 151 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_cancel_report_message(OrderMassCancelReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->originator_user_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_optional[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->cl_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_type_i_d_optional[i] = wire[at++]; }
  record->mass_cancel_request_type = wire[at++];
  record->mass_cancel_response = wire[at++];
  record->mass_cancel_reject_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Order Mass Cancel Report Message is what was written, byte for byte */
static void equal_order_mass_cancel_report_message(const OrderMassCancelReportMessage *read, const OrderMassCancelReportMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->originator_user_id[i] == written->originator_user_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_optional[i] == written->symbol_optional[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->cl_ord_id[i] == written->cl_ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_type_i_d_optional[i] == written->market_type_i_d_optional[i]); }
  assert(read->mass_cancel_request_type == written->mass_cancel_request_type);
  assert(read->mass_cancel_response == written->mass_cancel_response);
  assert(read->mass_cancel_reject_reason == written->mass_cancel_reject_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Order Mass Cancel Report Message: written and read back, then read and written back */
static void check_order_mass_cancel_report_message(void) {
  OrderMassCancelReportMessage sent;
  OrderMassCancelReportMessage got;
  uint8_t wire[151];
  uint8_t again[151];

  any_order_mass_cancel_report_message(&sent);
  assert(encode_order_mass_cancel_report_message(&sent, wire, 0) == 151);
  assert(decode_order_mass_cancel_report_message(&got, wire, 0) == 151);
  equal_order_mass_cancel_report_message(&got, &sent);

  for (size_t i = 0; i < 151; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_cancel_report_message(&got, wire, 0) == 151);
  assert(encode_order_mass_cancel_report_message(&got, again, 0) == 151);
  for (size_t i = 0; i < 151; i++) { assert(again[i] == wire[i]); }
}

/* ---- Resend Request Message: 8 bytes ----------------------------------------- */

/* ResendRequestMessage */
typedef struct {
  uint8_t begin_seq_no[4];  /* bytes 0 to 3 */
  uint8_t end_seq_no[4];    /* bytes 4 to 7 */
} ResendRequestMessage;

/* any Resend Request Message at all: every byte one the checker chooses */
static void any_resend_request_message(ResendRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_no[i] = arbitrary(); }
}

/* Resend Request Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_resend_request_message(const ResendRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_no[i]; }

  return at;
}

/* Resend Request Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_resend_request_message(ResendRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Resend Request Message is what was written, byte for byte */
static void equal_resend_request_message(const ResendRequestMessage *read, const ResendRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_no[i] == written->begin_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_no[i] == written->end_seq_no[i]); }
}

/* Resend Request Message: written and read back, then read and written back */
static void check_resend_request_message(void) {
  ResendRequestMessage sent;
  ResendRequestMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_resend_request_message(&sent);
  assert(encode_resend_request_message(&sent, wire, 0) == 8);
  assert(decode_resend_request_message(&got, wire, 0) == 8);
  equal_resend_request_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_resend_request_message(&got, wire, 0) == 8);
  assert(encode_resend_request_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Resend Report Message: 113 bytes ---------------------------------------- */

/* ResendReportMessage */
typedef struct {
  uint8_t begin_seq_no[4];   /* bytes 0 to 3 */
  uint8_t end_seq_no[4];     /* bytes 4 to 7 */
  uint8_t status;            /* byte 8 */
  uint8_t exchange_code[4];  /* bytes 9 to 12 */
  uint8_t text[100];         /* bytes 13 to 112 */
} ResendReportMessage;

/* any Resend Report Message at all: every byte one the checker chooses */
static void any_resend_report_message(ResendReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_seq_no[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = arbitrary(); }
  for (size_t i = 0; i < 100; i++) { record->text[i] = arbitrary(); }
}

/* Resend Report Message to the wire: 113 bytes from at, returning where the next byte goes */
static size_t encode_resend_report_message(const ResendReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->begin_seq_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_seq_no[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exchange_code[i]; }
  for (size_t i = 0; i < 100; i++) { wire[at++] = record->text[i]; }

  return at;
}

/* Resend Report Message off the wire: 113 bytes from at, returning where the next byte lies */
static size_t decode_resend_report_message(ResendReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->begin_seq_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_seq_no[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exchange_code[i] = wire[at++]; }
  for (size_t i = 0; i < 100; i++) { record->text[i] = wire[at++]; }

  return at;
}

/* what was read of Resend Report Message is what was written, byte for byte */
static void equal_resend_report_message(const ResendReportMessage *read, const ResendReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->begin_seq_no[i] == written->begin_seq_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_seq_no[i] == written->end_seq_no[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 4; i++) { assert(read->exchange_code[i] == written->exchange_code[i]); }
  for (size_t i = 0; i < 100; i++) { assert(read->text[i] == written->text[i]); }
}

/* Resend Report Message: written and read back, then read and written back */
static void check_resend_report_message(void) {
  ResendReportMessage sent;
  ResendReportMessage got;
  uint8_t wire[113];
  uint8_t again[113];

  any_resend_report_message(&sent);
  assert(encode_resend_report_message(&sent, wire, 0) == 113);
  assert(decode_resend_report_message(&got, wire, 0) == 113);
  equal_resend_report_message(&got, &sent);

  for (size_t i = 0; i < 113; i++) { wire[i] = arbitrary(); }
  assert(decode_resend_report_message(&got, wire, 0) == 113);
  assert(encode_resend_report_message(&got, again, 0) == 113);
  for (size_t i = 0; i < 113; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sequence Reset Message: 5 bytes ----------------------------------------- */

/* SequenceResetMessage */
typedef struct {
  uint8_t new_seq_no[4];  /* bytes 0 to 3 */
  uint8_t gap_fill_flag;  /* byte 4 */
} SequenceResetMessage;

/* any Sequence Reset Message at all: every byte one the checker chooses */
static void any_sequence_reset_message(SequenceResetMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->new_seq_no[i] = arbitrary(); }
  record->gap_fill_flag = arbitrary();
}

/* Sequence Reset Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_sequence_reset_message(const SequenceResetMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_seq_no[i]; }
  wire[at++] = record->gap_fill_flag;

  return at;
}

/* Sequence Reset Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_sequence_reset_message(SequenceResetMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->new_seq_no[i] = wire[at++]; }
  record->gap_fill_flag = wire[at++];

  return at;
}

/* what was read of Sequence Reset Message is what was written, byte for byte */
static void equal_sequence_reset_message(const SequenceResetMessage *read, const SequenceResetMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->new_seq_no[i] == written->new_seq_no[i]); }
  assert(read->gap_fill_flag == written->gap_fill_flag);
}

/* Sequence Reset Message: written and read back, then read and written back */
static void check_sequence_reset_message(void) {
  SequenceResetMessage sent;
  SequenceResetMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_sequence_reset_message(&sent);
  assert(encode_sequence_reset_message(&sent, wire, 0) == 5);
  assert(decode_sequence_reset_message(&got, wire, 0) == 5);
  equal_sequence_reset_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_sequence_reset_message(&got, wire, 0) == 5);
  assert(encode_sequence_reset_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_simple_open_framing_header();
  check_framing_header();
  check_simple_open_framing_header_message();
  check_logon_request_message();
  check_logon_report_message();
  check_logout_request_message();
  check_logout_report_message();
  check_error_message();
  check_group_size_encoding();
  check_security_definition_reject_message();
  check_security_definition_request_message();
  check_trader_logon_request_message();
  check_trader_logon_report_message();
  check_trader_logout_request_message();
  check_trader_logout_report_message();
  check_new_order_request_message();
  check_cancel_replace_request_message();
  check_cancel_request_message();
  check_quote_request_message();
  check_order_mass_cancel_request_message();
  check_security_definition_request_create_flex_message();
  check_exec_i_d_order_exec_id();
  check_orig_order_id();
  check_execution_report_new_message();
  check_execution_report_cancel_message();
  check_execution_report_reject_message();
  check_execution_report_snapshot_message();
  check_quote_report_message();
  check_new_order_cross_report_message();
  check_order_mass_cancel_report_message();
  check_resend_request_message();
  check_resend_report_message();
  check_sequence_reset_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
