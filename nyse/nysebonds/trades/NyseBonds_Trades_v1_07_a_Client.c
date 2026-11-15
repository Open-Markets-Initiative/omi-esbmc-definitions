// nyse/nysebonds/trades/NyseBonds_Trades_v1_07_a_Client.c
/*
 * New York Stock Exchange Trades
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

/* ---- Client Message Header: 1 byte ------------------------------------------- */

/* The single Ascii type code that opens every client message */
typedef struct {
  uint8_t client_message_type;  /* byte 0 */
} ClientMessageHeader;

/* any Client Message Header at all: every byte one the checker chooses */
static void any_client_message_header(ClientMessageHeader *record) {
  record->client_message_type = arbitrary();
}

/* Client Message Header to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_client_message_header(const ClientMessageHeader *record, uint8_t *wire, size_t at) {
  wire[at++] = record->client_message_type;

  return at;
}

/* Client Message Header off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_client_message_header(ClientMessageHeader *record, const uint8_t *wire, size_t at) {
  record->client_message_type = wire[at++];

  return at;
}

/* what was read of Client Message Header is what was written, byte for byte */
static void equal_client_message_header(const ClientMessageHeader *read, const ClientMessageHeader *written) {
  assert(read->client_message_type == written->client_message_type);
}

/* Client Message Header: written and read back, then read and written back */
static void check_client_message_header(void) {
  ClientMessageHeader sent;
  ClientMessageHeader got;
  uint8_t wire[1];
  uint8_t again[1];

  any_client_message_header(&sent);
  assert(encode_client_message_header(&sent, wire, 0) == 1);
  assert(decode_client_message_header(&got, wire, 0) == 1);
  equal_client_message_header(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_client_message_header(&got, wire, 0) == 1);
  assert(encode_client_message_header(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Message: 40 bytes ------------------------------------------------- */

/* Authenticates the subscriber and names which trade data the session subscribes to. A starting sequence number of 0 requests current data; a greater number than the exchange holds is treated as 0, and a negative one is rejected */
typedef struct {
  uint8_t username[8];                /* bytes 0 to 7 */
  uint8_t password[10];               /* bytes 8 to 17 */
  uint8_t login_sequence_number[10];  /* bytes 18 to 27 */
  uint8_t listed_subscription;        /* byte 28 */
  uint8_t etf_subscription;           /* byte 29 */
  uint8_t otc_subscription;           /* byte 30 */
  uint8_t arca_edge_subscription;     /* byte 31 */
  uint8_t bond_subscription;          /* byte 32 */
  uint8_t options_subscription;       /* byte 33 */
  uint8_t client_padding[5];          /* bytes 34 to 38 */
  uint8_t etx;                        /* byte 39 */
} LoginMessage;

/* any Login Message at all: every byte one the checker chooses */
static void any_login_message(LoginMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->login_sequence_number[i] = arbitrary(); }
  record->listed_subscription = arbitrary();
  record->etf_subscription = arbitrary();
  record->otc_subscription = arbitrary();
  record->arca_edge_subscription = arbitrary();
  record->bond_subscription = arbitrary();
  record->options_subscription = arbitrary();
  for (size_t i = 0; i < 5; i++) { record->client_padding[i] = arbitrary(); }
  record->etx = arbitrary();
}

/* Login Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_login_message(const LoginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->login_sequence_number[i]; }
  wire[at++] = record->listed_subscription;
  wire[at++] = record->etf_subscription;
  wire[at++] = record->otc_subscription;
  wire[at++] = record->arca_edge_subscription;
  wire[at++] = record->bond_subscription;
  wire[at++] = record->options_subscription;
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->client_padding[i]; }
  wire[at++] = record->etx;

  return at;
}

/* Login Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_login_message(LoginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->login_sequence_number[i] = wire[at++]; }
  record->listed_subscription = wire[at++];
  record->etf_subscription = wire[at++];
  record->otc_subscription = wire[at++];
  record->arca_edge_subscription = wire[at++];
  record->bond_subscription = wire[at++];
  record->options_subscription = wire[at++];
  for (size_t i = 0; i < 5; i++) { record->client_padding[i] = wire[at++]; }
  record->etx = wire[at++];

  return at;
}

/* what was read of Login Message is what was written, byte for byte */
static void equal_login_message(const LoginMessage *read, const LoginMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->login_sequence_number[i] == written->login_sequence_number[i]); }
  assert(read->listed_subscription == written->listed_subscription);
  assert(read->etf_subscription == written->etf_subscription);
  assert(read->otc_subscription == written->otc_subscription);
  assert(read->arca_edge_subscription == written->arca_edge_subscription);
  assert(read->bond_subscription == written->bond_subscription);
  assert(read->options_subscription == written->options_subscription);
  for (size_t i = 0; i < 5; i++) { assert(read->client_padding[i] == written->client_padding[i]); }
  assert(read->etx == written->etx);
}

/* Login Message: written and read back, then read and written back */
static void check_login_message(void) {
  LoginMessage sent;
  LoginMessage got;
  uint8_t wire[40];
  uint8_t again[40];

  any_login_message(&sent);
  assert(encode_login_message(&sent, wire, 0) == 40);
  assert(decode_login_message(&got, wire, 0) == 40);
  equal_login_message(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_login_message(&got, wire, 0) == 40);
  assert(encode_login_message(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logoff Message: 1 byte -------------------------------------------------- */

/* Closes the session. Carries only its type code and the terminator */
typedef struct {
  uint8_t etx;  /* byte 0 */
} LogoffMessage;

/* any Logoff Message at all: every byte one the checker chooses */
static void any_logoff_message(LogoffMessage *record) {
  record->etx = arbitrary();
}

/* Logoff Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_logoff_message(const LogoffMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->etx;

  return at;
}

/* Logoff Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_logoff_message(LogoffMessage *record, const uint8_t *wire, size_t at) {
  record->etx = wire[at++];

  return at;
}

/* what was read of Logoff Message is what was written, byte for byte */
static void equal_logoff_message(const LogoffMessage *read, const LogoffMessage *written) {
  assert(read->etx == written->etx);
}

/* Logoff Message: written and read back, then read and written back */
static void check_logoff_message(void) {
  LogoffMessage sent;
  LogoffMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_logoff_message(&sent);
  assert(encode_logoff_message(&sent, wire, 0) == 1);
  assert(decode_logoff_message(&got, wire, 0) == 1);
  equal_logoff_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_logoff_message(&got, wire, 0) == 1);
  assert(encode_logoff_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Response Message: 1 byte -------------------------------------- */

/* Answers a Heartbeat Request. The exchange closes the connection if no response arrives within 60 seconds. Table 9 of the specification labels the second field "Username", which is a copy and paste slip - its own description reads "Message Terminating Character" */
typedef struct {
  uint8_t etx;  /* byte 0 */
} HeartbeatResponseMessage;

/* any Heartbeat Response Message at all: every byte one the checker chooses */
static void any_heartbeat_response_message(HeartbeatResponseMessage *record) {
  record->etx = arbitrary();
}

/* Heartbeat Response Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_heartbeat_response_message(const HeartbeatResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->etx;

  return at;
}

/* Heartbeat Response Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_heartbeat_response_message(HeartbeatResponseMessage *record, const uint8_t *wire, size_t at) {
  record->etx = wire[at++];

  return at;
}

/* what was read of Heartbeat Response Message is what was written, byte for byte */
static void equal_heartbeat_response_message(const HeartbeatResponseMessage *read, const HeartbeatResponseMessage *written) {
  assert(read->etx == written->etx);
}

/* Heartbeat Response Message: written and read back, then read and written back */
static void check_heartbeat_response_message(void) {
  HeartbeatResponseMessage sent;
  HeartbeatResponseMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_heartbeat_response_message(&sent);
  assert(encode_heartbeat_response_message(&sent, wire, 0) == 1);
  assert(decode_heartbeat_response_message(&got, wire, 0) == 1);
  equal_heartbeat_response_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_response_message(&got, wire, 0) == 1);
  assert(encode_heartbeat_response_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Test Request Message: 21 bytes ------------------------------------------ */

/* Signals or tests that the Tcp connection is open. Any text given is echoed back in a Test Response */
typedef struct {
  uint8_t test_request_text[20];  /* bytes 0 to 19 */
  uint8_t etx;                    /* byte 20 */
} TestRequestMessage;

/* any Test Request Message at all: every byte one the checker chooses */
static void any_test_request_message(TestRequestMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->test_request_text[i] = arbitrary(); }
  record->etx = arbitrary();
}

/* Test Request Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_test_request_message(const TestRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->test_request_text[i]; }
  wire[at++] = record->etx;

  return at;
}

/* Test Request Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_test_request_message(TestRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->test_request_text[i] = wire[at++]; }
  record->etx = wire[at++];

  return at;
}

/* what was read of Test Request Message is what was written, byte for byte */
static void equal_test_request_message(const TestRequestMessage *read, const TestRequestMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->test_request_text[i] == written->test_request_text[i]); }
  assert(read->etx == written->etx);
}

/* Test Request Message: written and read back, then read and written back */
static void check_test_request_message(void) {
  TestRequestMessage sent;
  TestRequestMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_test_request_message(&sent);
  assert(encode_test_request_message(&sent, wire, 0) == 21);
  assert(decode_test_request_message(&got, wire, 0) == 21);
  equal_test_request_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_test_request_message(&got, wire, 0) == 21);
  assert(encode_test_request_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_client_message_header();
  check_login_message();
  check_logoff_message();
  check_heartbeat_response_message();
  check_test_request_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
