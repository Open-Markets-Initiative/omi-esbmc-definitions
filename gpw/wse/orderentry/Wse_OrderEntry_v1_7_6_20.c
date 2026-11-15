// gpw/wse/orderentry/Wse_OrderEntry_v1_7_6_20.c
/*
 * Giełda Papierów Wartościowych w Warszawie Warsaw Stock Exchange Native Order Gateway
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

/* ---- Message Header: 24 bytes ------------------------------------------------ */

/* Every order gateway message opens with the same 24 byte header */
typedef struct {
  uint8_t message_length[2];    /* bytes 0 to 1 */
  uint8_t message_type[2];      /* bytes 2 to 3 */
  uint8_t sequence_number[4];   /* bytes 4 to 7 */
  uint8_t timestamp[8];         /* bytes 8 to 15 */
  uint8_t source_timestamp[8];  /* bytes 16 to 23 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->source_timestamp[i] = arbitrary(); }
}

/* Message Header to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->source_timestamp[i]; }

  return at;
}

/* Message Header off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->source_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->source_timestamp[i] == written->source_timestamp[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[24];
  uint8_t again[24];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 24);
  assert(decode_message_header(&got, wire, 0) == 24);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 24);
  assert(encode_message_header(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login: 20 bytes --------------------------------------------------------- */

/* The login message authenticates a user establishing a connection to the trading port service. The login message must be the first message sent by the client application to request the initiation of a trading port session */
typedef struct {
  uint8_t version[2];                /* bytes 0 to 1 */
  uint8_t token[8];                  /* bytes 2 to 9 */
  uint8_t connection_id[2];          /* bytes 10 to 11 */
  uint8_t next_expected_seq_num[4];  /* bytes 12 to 15 */
  uint8_t last_sent_seq_num[4];      /* bytes 16 to 19 */
} Login;

/* any Login at all: every byte one the checker chooses */
static void any_login(Login *record) {
  for (size_t i = 0; i < 2; i++) { record->version[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->token[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->connection_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_expected_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_sent_seq_num[i] = arbitrary(); }
}

/* Login to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_login(const Login *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->version[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->token[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->connection_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_expected_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_sent_seq_num[i]; }

  return at;
}

/* Login off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_login(Login *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->version[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->token[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->connection_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_expected_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_sent_seq_num[i] = wire[at++]; }

  return at;
}

/* what was read of Login is what was written, byte for byte */
static void equal_login(const Login *read, const Login *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->version[i] == written->version[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->token[i] == written->token[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->connection_id[i] == written->connection_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_expected_seq_num[i] == written->next_expected_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_sent_seq_num[i] == written->last_sent_seq_num[i]); }
}

/* Login: written and read back, then read and written back */
static void check_login(void) {
  Login sent;
  Login got;
  uint8_t wire[20];
  uint8_t again[20];

  any_login(&sent);
  assert(encode_login(&sent, wire, 0) == 20);
  assert(decode_login(&got, wire, 0) == 20);
  equal_login(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_login(&got, wire, 0) == 20);
  assert(encode_login(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response: 11 bytes ------------------------------------------------ */

/* The login response message. The result field describes the login status, indicating whether the login was successful or not (i.e. successful login) */
typedef struct {
  uint8_t result_login_result;       /* byte 0 */
  uint8_t next_expected_seq_num[4];  /* bytes 1 to 4 */
  uint8_t last_replay_seq_num[4];    /* bytes 5 to 8 */
  uint8_t session_id[2];             /* bytes 9 to 10 */
} LoginResponse;

/* any Login Response at all: every byte one the checker chooses */
static void any_login_response(LoginResponse *record) {
  record->result_login_result = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->next_expected_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_replay_seq_num[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
}

/* Login Response to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_login_response(const LoginResponse *record, uint8_t *wire, size_t at) {
  wire[at++] = record->result_login_result;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_expected_seq_num[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_replay_seq_num[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Login Response off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_login_response(LoginResponse *record, const uint8_t *wire, size_t at) {
  record->result_login_result = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->next_expected_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_replay_seq_num[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Login Response is what was written, byte for byte */
static void equal_login_response(const LoginResponse *read, const LoginResponse *written) {
  assert(read->result_login_result == written->result_login_result);
  for (size_t i = 0; i < 4; i++) { assert(read->next_expected_seq_num[i] == written->next_expected_seq_num[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_replay_seq_num[i] == written->last_replay_seq_num[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Login Response: written and read back, then read and written back */
static void check_login_response(void) {
  LoginResponse sent;
  LoginResponse got;
  uint8_t wire[11];
  uint8_t again[11];

  any_login_response(&sent);
  assert(encode_login_response(&sent, wire, 0) == 11);
  assert(decode_login_response(&got, wire, 0) == 11);
  equal_login_response(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response(&got, wire, 0) == 11);
  assert(encode_login_response(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Connection Close: 1 byte ------------------------------------------------ */

/* The ConnectionClose message confirms the termination of a session through the trading port service */
typedef struct {
  uint8_t reason_connection_close_reason;  /* byte 0 */
} ConnectionClose;

/* any Connection Close at all: every byte one the checker chooses */
static void any_connection_close(ConnectionClose *record) {
  record->reason_connection_close_reason = arbitrary();
}

/* Connection Close to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_connection_close(const ConnectionClose *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reason_connection_close_reason;

  return at;
}

/* Connection Close off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_connection_close(ConnectionClose *record, const uint8_t *wire, size_t at) {
  record->reason_connection_close_reason = wire[at++];

  return at;
}

/* what was read of Connection Close is what was written, byte for byte */
static void equal_connection_close(const ConnectionClose *read, const ConnectionClose *written) {
  assert(read->reason_connection_close_reason == written->reason_connection_close_reason);
}

/* Connection Close: written and read back, then read and written back */
static void check_connection_close(void) {
  ConnectionClose sent;
  ConnectionClose got;
  uint8_t wire[1];
  uint8_t again[1];

  any_connection_close(&sent);
  assert(encode_connection_close(&sent, wire, 0) == 1);
  assert(decode_connection_close(&got, wire, 0) == 1);
  equal_connection_close(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_connection_close(&got, wire, 0) == 1);
  assert(encode_connection_close(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject: 5 bytes --------------------------------------------------------- */

/* The reject message is sent by the trading port service when receiving an erroneous message that cannot be further processed */
typedef struct {
  uint8_t ref_seq_num[4];  /* bytes 0 to 3 */
  uint8_t reject_reason;   /* byte 4 */
} Reject;

/* any Reject at all: every byte one the checker chooses */
static void any_reject(Reject *record) {
  for (size_t i = 0; i < 4; i++) { record->ref_seq_num[i] = arbitrary(); }
  record->reject_reason = arbitrary();
}

/* Reject to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_reject(const Reject *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_seq_num[i]; }
  wire[at++] = record->reject_reason;

  return at;
}

/* Reject off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_reject(Reject *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->ref_seq_num[i] = wire[at++]; }
  record->reject_reason = wire[at++];

  return at;
}

/* what was read of Reject is what was written, byte for byte */
static void equal_reject(const Reject *read, const Reject *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->ref_seq_num[i] == written->ref_seq_num[i]); }
  assert(read->reject_reason == written->reject_reason);
}

/* Reject: written and read back, then read and written back */
static void check_reject(void) {
  Reject sent;
  Reject got;
  uint8_t wire[5];
  uint8_t again[5];

  any_reject(&sent);
  assert(encode_reject(&sent, wire, 0) == 5);
  assert(decode_reject(&got, wire, 0) == 5);
  equal_reject(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_reject(&got, wire, 0) == 5);
  assert(encode_reject(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Test: 8 bytes ----------------------------------------------------------- */

/* The internal message for a test purpose */
typedef struct {
  uint8_t target_timestamp[8];  /* bytes 0 to 7 */
} Test;

/* any Test at all: every byte one the checker chooses */
static void any_test(Test *record) {
  for (size_t i = 0; i < 8; i++) { record->target_timestamp[i] = arbitrary(); }
}

/* Test to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_test(const Test *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->target_timestamp[i]; }

  return at;
}

/* Test off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_test(Test *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->target_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Test is what was written, byte for byte */
static void equal_test(const Test *read, const Test *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->target_timestamp[i] == written->target_timestamp[i]); }
}

/* Test: written and read back, then read and written back */
static void check_test(void) {
  Test sent;
  Test got;
  uint8_t wire[8];
  uint8_t again[8];

  any_test(&sent);
  assert(encode_test(&sent, wire, 0) == 8);
  assert(decode_test(&got, wire, 0) == 8);
  equal_test(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_test(&got, wire, 0) == 8);
  assert(encode_test(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Test Event: 201 bytes --------------------------------------------------- */

/* Test event */
typedef struct {
  uint8_t scenario_name[200];  /* bytes 0 to 199 */
  uint8_t event_type;          /* byte 200 */
} TestEvent;

/* any Test Event at all: every byte one the checker chooses */
static void any_test_event(TestEvent *record) {
  for (size_t i = 0; i < 200; i++) { record->scenario_name[i] = arbitrary(); }
  record->event_type = arbitrary();
}

/* Test Event to the wire: 201 bytes from at, returning where the next byte goes */
static size_t encode_test_event(const TestEvent *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 200; i++) { wire[at++] = record->scenario_name[i]; }
  wire[at++] = record->event_type;

  return at;
}

/* Test Event off the wire: 201 bytes from at, returning where the next byte lies */
static size_t decode_test_event(TestEvent *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 200; i++) { record->scenario_name[i] = wire[at++]; }
  record->event_type = wire[at++];

  return at;
}

/* what was read of Test Event is what was written, byte for byte */
static void equal_test_event(const TestEvent *read, const TestEvent *written) {
  for (size_t i = 0; i < 200; i++) { assert(read->scenario_name[i] == written->scenario_name[i]); }
  assert(read->event_type == written->event_type);
}

/* Test Event: written and read back, then read and written back */
static void check_test_event(void) {
  TestEvent sent;
  TestEvent got;
  uint8_t wire[201];
  uint8_t again[201];

  any_test_event(&sent);
  assert(encode_test_event(&sent, wire, 0) == 201);
  assert(decode_test_event(&got, wire, 0) == 201);
  equal_test_event(&got, &sent);

  for (size_t i = 0; i < 201; i++) { wire[i] = arbitrary(); }
  assert(decode_test_event(&got, wire, 0) == 201);
  assert(encode_test_event(&got, again, 0) == 201);
  for (size_t i = 0; i < 201; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status: 9 bytes ----------------------------------------- */

/* The Trading Session Status provides information on the status of a trading session */
typedef struct {
  uint8_t market_id[4];           /* bytes 0 to 3 */
  uint8_t date[4];                /* bytes 4 to 7 */
  uint8_t trading_session_event;  /* byte 8 */
} TradingSessionStatus;

/* any Trading Session Status at all: every byte one the checker chooses */
static void any_trading_session_status(TradingSessionStatus *record) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->date[i] = arbitrary(); }
  record->trading_session_event = arbitrary();
}

/* Trading Session Status to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status(const TradingSessionStatus *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->date[i]; }
  wire[at++] = record->trading_session_event;

  return at;
}

/* Trading Session Status off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status(TradingSessionStatus *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->date[i] = wire[at++]; }
  record->trading_session_event = wire[at++];

  return at;
}

/* what was read of Trading Session Status is what was written, byte for byte */
static void equal_trading_session_status(const TradingSessionStatus *read, const TradingSessionStatus *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->date[i] == written->date[i]); }
  assert(read->trading_session_event == written->trading_session_event);
}

/* Trading Session Status: written and read back, then read and written back */
static void check_trading_session_status(void) {
  TradingSessionStatus sent;
  TradingSessionStatus got;
  uint8_t wire[9];
  uint8_t again[9];

  any_trading_session_status(&sent);
  assert(encode_trading_session_status(&sent, wire, 0) == 9);
  assert(decode_trading_session_status(&got, wire, 0) == 9);
  equal_trading_session_status(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status(&got, wire, 0) == 9);
  assert(encode_trading_session_status(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Client: 5 bytes --------------------------------------------------------- */

/* MifidField */
typedef struct {
  uint8_t short_code[4];  /* bytes 0 to 3 */
  uint8_t qualifier;      /* byte 4 */
} Client;

/* any Client at all: every byte one the checker chooses */
static void any_client(Client *record) {
  for (size_t i = 0; i < 4; i++) { record->short_code[i] = arbitrary(); }
  record->qualifier = arbitrary();
}

/* Client to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_client(const Client *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_code[i]; }
  wire[at++] = record->qualifier;

  return at;
}

/* Client off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_client(Client *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->short_code[i] = wire[at++]; }
  record->qualifier = wire[at++];

  return at;
}

/* what was read of Client is what was written, byte for byte */
static void equal_client(const Client *read, const Client *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->short_code[i] == written->short_code[i]); }
  assert(read->qualifier == written->qualifier);
}

/* Client: written and read back, then read and written back */
static void check_client(void) {
  Client sent;
  Client got;
  uint8_t wire[5];
  uint8_t again[5];

  any_client(&sent);
  assert(encode_client(&sent, wire, 0) == 5);
  assert(decode_client(&got, wire, 0) == 5);
  equal_client(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_client(&got, wire, 0) == 5);
  assert(encode_client(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Executing Trader: 5 bytes ----------------------------------------------- */

/* MifidField */
typedef struct {
  uint8_t short_code[4];  /* bytes 0 to 3 */
  uint8_t qualifier;      /* byte 4 */
} ExecutingTrader;

/* any Executing Trader at all: every byte one the checker chooses */
static void any_executing_trader(ExecutingTrader *record) {
  for (size_t i = 0; i < 4; i++) { record->short_code[i] = arbitrary(); }
  record->qualifier = arbitrary();
}

/* Executing Trader to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_executing_trader(const ExecutingTrader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_code[i]; }
  wire[at++] = record->qualifier;

  return at;
}

/* Executing Trader off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_executing_trader(ExecutingTrader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->short_code[i] = wire[at++]; }
  record->qualifier = wire[at++];

  return at;
}

/* what was read of Executing Trader is what was written, byte for byte */
static void equal_executing_trader(const ExecutingTrader *read, const ExecutingTrader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->short_code[i] == written->short_code[i]); }
  assert(read->qualifier == written->qualifier);
}

/* Executing Trader: written and read back, then read and written back */
static void check_executing_trader(void) {
  ExecutingTrader sent;
  ExecutingTrader got;
  uint8_t wire[5];
  uint8_t again[5];

  any_executing_trader(&sent);
  assert(encode_executing_trader(&sent, wire, 0) == 5);
  assert(decode_executing_trader(&got, wire, 0) == 5);
  equal_executing_trader(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_executing_trader(&got, wire, 0) == 5);
  assert(encode_executing_trader(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Investment Decision Maker: 5 bytes -------------------------------------- */

/* MifidField */
typedef struct {
  uint8_t short_code[4];  /* bytes 0 to 3 */
  uint8_t qualifier;      /* byte 4 */
} InvestmentDecisionMaker;

/* any Investment Decision Maker at all: every byte one the checker chooses */
static void any_investment_decision_maker(InvestmentDecisionMaker *record) {
  for (size_t i = 0; i < 4; i++) { record->short_code[i] = arbitrary(); }
  record->qualifier = arbitrary();
}

/* Investment Decision Maker to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_investment_decision_maker(const InvestmentDecisionMaker *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->short_code[i]; }
  wire[at++] = record->qualifier;

  return at;
}

/* Investment Decision Maker off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_investment_decision_maker(InvestmentDecisionMaker *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->short_code[i] = wire[at++]; }
  record->qualifier = wire[at++];

  return at;
}

/* what was read of Investment Decision Maker is what was written, byte for byte */
static void equal_investment_decision_maker(const InvestmentDecisionMaker *read, const InvestmentDecisionMaker *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->short_code[i] == written->short_code[i]); }
  assert(read->qualifier == written->qualifier);
}

/* Investment Decision Maker: written and read back, then read and written back */
static void check_investment_decision_maker(void) {
  InvestmentDecisionMaker sent;
  InvestmentDecisionMaker got;
  uint8_t wire[5];
  uint8_t again[5];

  any_investment_decision_maker(&sent);
  assert(encode_investment_decision_maker(&sent, wire, 0) == 5);
  assert(decode_investment_decision_maker(&got, wire, 0) == 5);
  equal_investment_decision_maker(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_investment_decision_maker(&got, wire, 0) == 5);
  assert(encode_investment_decision_maker(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mifid Fields: 15 bytes -------------------------------------------------- */

/* MifidFields */
typedef struct {
  Client client;                                      /* bytes 0 to 4 */
  ExecutingTrader executing_trader;                   /* bytes 5 to 9 */
  InvestmentDecisionMaker investment_decision_maker;  /* bytes 10 to 14 */
} MifidFields;

/* any Mifid Fields at all: every byte one the checker chooses */
static void any_mifid_fields(MifidFields *record) {
  any_client(&record->client);
  any_executing_trader(&record->executing_trader);
  any_investment_decision_maker(&record->investment_decision_maker);
}

/* Mifid Fields to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_mifid_fields(const MifidFields *record, uint8_t *wire, size_t at) {
  at = encode_client(&record->client, wire, at);
  at = encode_executing_trader(&record->executing_trader, wire, at);
  at = encode_investment_decision_maker(&record->investment_decision_maker, wire, at);

  return at;
}

/* Mifid Fields off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_mifid_fields(MifidFields *record, const uint8_t *wire, size_t at) {
  at = decode_client(&record->client, wire, at);
  at = decode_executing_trader(&record->executing_trader, wire, at);
  at = decode_investment_decision_maker(&record->investment_decision_maker, wire, at);

  return at;
}

/* what was read of Mifid Fields is what was written, byte for byte */
static void equal_mifid_fields(const MifidFields *read, const MifidFields *written) {
  equal_client(&read->client, &written->client);
  equal_executing_trader(&read->executing_trader, &written->executing_trader);
  equal_investment_decision_maker(&read->investment_decision_maker, &written->investment_decision_maker);
}

/* Mifid Fields: written and read back, then read and written back */
static void check_mifid_fields(void) {
  MifidFields sent;
  MifidFields got;
  uint8_t wire[15];
  uint8_t again[15];

  any_mifid_fields(&sent);
  assert(encode_mifid_fields(&sent, wire, 0) == 15);
  assert(decode_mifid_fields(&got, wire, 0) == 15);
  equal_mifid_fields(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_mifid_fields(&got, wire, 0) == 15);
  assert(encode_mifid_fields(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Mass Cancel: 39 bytes --------------------------------------------- */

/* Message used to cancel multiple existing orders */
typedef struct {
  uint8_t mass_cancel_request_type;  /* byte 0 */
  uint8_t target_party_role;         /* byte 1 */
  uint8_t target_party_id[4];        /* bytes 2 to 5 */
  uint8_t market_segment_id[4];      /* bytes 6 to 9 */
  uint8_t instrument_id[4];          /* bytes 10 to 13 */
  ExecutingTrader executing_trader;  /* bytes 14 to 18 */
  uint8_t client_order_id[20];       /* bytes 19 to 38 */
} OrderMassCancel;

/* any Order Mass Cancel at all: every byte one the checker chooses */
static void any_order_mass_cancel(OrderMassCancel *record) {
  record->mass_cancel_request_type = arbitrary();
  record->target_party_role = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  any_executing_trader(&record->executing_trader);
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
}

/* Order Mass Cancel to the wire: 39 bytes from at, returning where the next byte goes */
static size_t encode_order_mass_cancel(const OrderMassCancel *record, uint8_t *wire, size_t at) {
  wire[at++] = record->mass_cancel_request_type;
  wire[at++] = record->target_party_role;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->target_party_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  at = encode_executing_trader(&record->executing_trader, wire, at);
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }

  return at;
}

/* Order Mass Cancel off the wire: 39 bytes from at, returning where the next byte lies */
static size_t decode_order_mass_cancel(OrderMassCancel *record, const uint8_t *wire, size_t at) {
  record->mass_cancel_request_type = wire[at++];
  record->target_party_role = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->target_party_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  at = decode_executing_trader(&record->executing_trader, wire, at);
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Mass Cancel is what was written, byte for byte */
static void equal_order_mass_cancel(const OrderMassCancel *read, const OrderMassCancel *written) {
  assert(read->mass_cancel_request_type == written->mass_cancel_request_type);
  assert(read->target_party_role == written->target_party_role);
  for (size_t i = 0; i < 4; i++) { assert(read->target_party_id[i] == written->target_party_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  equal_executing_trader(&read->executing_trader, &written->executing_trader);
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
}

/* Order Mass Cancel: written and read back, then read and written back */
static void check_order_mass_cancel(void) {
  OrderMassCancel sent;
  OrderMassCancel got;
  uint8_t wire[39];
  uint8_t again[39];

  any_order_mass_cancel(&sent);
  assert(encode_order_mass_cancel(&sent, wire, 0) == 39);
  assert(decode_order_mass_cancel(&got, wire, 0) == 39);
  equal_order_mass_cancel(&got, &sent);

  for (size_t i = 0; i < 39; i++) { wire[i] = arbitrary(); }
  assert(decode_order_mass_cancel(&got, wire, 0) == 39);
  assert(encode_order_mass_cancel(&got, again, 0) == 39);
  for (size_t i = 0; i < 39; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid: 16 bytes ----------------------------------------------------------- */

/* QuoteOrder */
typedef struct {
  uint8_t price[8];     /* bytes 0 to 7 */
  uint8_t quantity[8];  /* bytes 8 to 15 */
} Bid;

/* any Bid at all: every byte one the checker chooses */
static void any_bid(Bid *record) {
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
}

/* Bid to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_bid(const Bid *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Bid off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_bid(Bid *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Bid is what was written, byte for byte */
static void equal_bid(const Bid *read, const Bid *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Bid: written and read back, then read and written back */
static void check_bid(void) {
  Bid sent;
  Bid got;
  uint8_t wire[16];
  uint8_t again[16];

  any_bid(&sent);
  assert(encode_bid(&sent, wire, 0) == 16);
  assert(decode_bid(&got, wire, 0) == 16);
  equal_bid(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_bid(&got, wire, 0) == 16);
  assert(encode_bid(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask: 16 bytes ----------------------------------------------------------- */

/* QuoteOrder */
typedef struct {
  uint8_t price[8];     /* bytes 0 to 7 */
  uint8_t quantity[8];  /* bytes 8 to 15 */
} Ask;

/* any Ask at all: every byte one the checker chooses */
static void any_ask(Ask *record) {
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = arbitrary(); }
}

/* Ask to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_ask(const Ask *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Ask off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_ask(Ask *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Ask is what was written, byte for byte */
static void equal_ask(const Ask *read, const Ask *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Ask: written and read back, then read and written back */
static void check_ask(void) {
  Ask sent;
  Ask got;
  uint8_t wire[16];
  uint8_t again[16];

  any_ask(&sent);
  assert(encode_ask(&sent, wire, 0) == 16);
  assert(decode_ask(&got, wire, 0) == 16);
  equal_ask(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_ask(&got, wire, 0) == 16);
  assert(encode_ask(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote: 36 bytes --------------------------------------------------------- */

/* Quote */
typedef struct {
  uint8_t instrument_id[4];  /* bytes 0 to 3 */
  Bid bid;                   /* bytes 4 to 19 */
  Ask ask;                   /* bytes 20 to 35 */
} Quote;

/* any Quote at all: every byte one the checker chooses */
static void any_quote(Quote *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  any_bid(&record->bid);
  any_ask(&record->ask);
}

/* Quote to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_quote(const Quote *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  at = encode_bid(&record->bid, wire, at);
  at = encode_ask(&record->ask, wire, at);

  return at;
}

/* Quote off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_quote(Quote *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  at = decode_bid(&record->bid, wire, at);
  at = decode_ask(&record->ask, wire, at);

  return at;
}

/* what was read of Quote is what was written, byte for byte */
static void equal_quote(const Quote *read, const Quote *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  equal_bid(&read->bid, &written->bid);
  equal_ask(&read->ask, &written->ask);
}

/* Quote: written and read back, then read and written back */
static void check_quote(void) {
  Quote sent;
  Quote got;
  uint8_t wire[36];
  uint8_t again[36];

  any_quote(&sent);
  assert(encode_quote(&sent, wire, 0) == 36);
  assert(decode_quote(&got, wire, 0) == 36);
  equal_quote(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_quote(&got, wire, 0) == 36);
  assert(encode_quote(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Maker Command: 5 bytes ------------------------------------------- */

/* Market Maker command request */
typedef struct {
  uint8_t instrument_id[4];  /* bytes 0 to 3 */
  uint8_t action;            /* byte 4 */
} MarketMakerCommand;

/* any Market Maker Command at all: every byte one the checker chooses */
static void any_market_maker_command(MarketMakerCommand *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->action = arbitrary();
}

/* Market Maker Command to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_market_maker_command(const MarketMakerCommand *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->action;

  return at;
}

/* Market Maker Command off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_market_maker_command(MarketMakerCommand *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->action = wire[at++];

  return at;
}

/* what was read of Market Maker Command is what was written, byte for byte */
static void equal_market_maker_command(const MarketMakerCommand *read, const MarketMakerCommand *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->action == written->action);
}

/* Market Maker Command: written and read back, then read and written back */
static void check_market_maker_command(void) {
  MarketMakerCommand sent;
  MarketMakerCommand got;
  uint8_t wire[5];
  uint8_t again[5];

  any_market_maker_command(&sent);
  assert(encode_market_maker_command(&sent, wire, 0) == 5);
  assert(decode_market_maker_command(&got, wire, 0) == 5);
  equal_market_maker_command(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_market_maker_command(&got, wire, 0) == 5);
  assert(encode_market_maker_command(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Maker Command Response: 7 bytes ---------------------------------- */

/* The response to the Market Maker command */
typedef struct {
  uint8_t ref_id[4];              /* bytes 0 to 3 */
  uint8_t result_command_result;  /* byte 4 */
  uint8_t rejection_code[2];      /* bytes 5 to 6 */
} MarketMakerCommandResponse;

/* any Market Maker Command Response at all: every byte one the checker chooses */
static void any_market_maker_command_response(MarketMakerCommandResponse *record) {
  for (size_t i = 0; i < 4; i++) { record->ref_id[i] = arbitrary(); }
  record->result_command_result = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->rejection_code[i] = arbitrary(); }
}

/* Market Maker Command Response to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_market_maker_command_response(const MarketMakerCommandResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ref_id[i]; }
  wire[at++] = record->result_command_result;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->rejection_code[i]; }

  return at;
}

/* Market Maker Command Response off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_market_maker_command_response(MarketMakerCommandResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->ref_id[i] = wire[at++]; }
  record->result_command_result = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->rejection_code[i] = wire[at++]; }

  return at;
}

/* what was read of Market Maker Command Response is what was written, byte for byte */
static void equal_market_maker_command_response(const MarketMakerCommandResponse *read, const MarketMakerCommandResponse *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->ref_id[i] == written->ref_id[i]); }
  assert(read->result_command_result == written->result_command_result);
  for (size_t i = 0; i < 2; i++) { assert(read->rejection_code[i] == written->rejection_code[i]); }
}

/* Market Maker Command Response: written and read back, then read and written back */
static void check_market_maker_command_response(void) {
  MarketMakerCommandResponse sent;
  MarketMakerCommandResponse got;
  uint8_t wire[7];
  uint8_t again[7];

  any_market_maker_command_response(&sent);
  assert(encode_market_maker_command_response(&sent, wire, 0) == 7);
  assert(decode_market_maker_command_response(&got, wire, 0) == 7);
  equal_market_maker_command_response(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_market_maker_command_response(&got, wire, 0) == 7);
  assert(encode_market_maker_command_response(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Execution: 5 bytes ------------------------------------------ */

/* The information for the MM that one of the quotes has been crossed */
typedef struct {
  uint8_t instrument_id[4];                     /* bytes 0 to 3 */
  uint8_t reason_request_for_execution_reason;  /* byte 4 */
} RequestForExecution;

/* any Request For Execution at all: every byte one the checker chooses */
static void any_request_for_execution(RequestForExecution *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->reason_request_for_execution_reason = arbitrary();
}

/* Request For Execution to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_request_for_execution(const RequestForExecution *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->reason_request_for_execution_reason;

  return at;
}

/* Request For Execution off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_request_for_execution(RequestForExecution *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->reason_request_for_execution_reason = wire[at++];

  return at;
}

/* what was read of Request For Execution is what was written, byte for byte */
static void equal_request_for_execution(const RequestForExecution *read, const RequestForExecution *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->reason_request_for_execution_reason == written->reason_request_for_execution_reason);
}

/* Request For Execution: written and read back, then read and written back */
static void check_request_for_execution(void) {
  RequestForExecution sent;
  RequestForExecution got;
  uint8_t wire[5];
  uint8_t again[5];

  any_request_for_execution(&sent);
  assert(encode_request_for_execution(&sent, wire, 0) == 5);
  assert(decode_request_for_execution(&got, wire, 0) == 5);
  equal_request_for_execution(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_execution(&got, wire, 0) == 5);
  assert(encode_request_for_execution(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Offer Update: 29 bytes ---------------------------------------------- */

/* Message send during the IPO to the sell side or during the Tender Offer to the buy side */
typedef struct {
  uint8_t instrument_id[4];     /* bytes 0 to 3 */
  uint8_t update_type;          /* byte 4 */
  uint8_t total_bid_size[8];    /* bytes 5 to 12 */
  uint8_t total_offer_size[8];  /* bytes 13 to 20 */
  uint8_t bid_orders[4];        /* bytes 21 to 24 */
  uint8_t offer_orders[4];      /* bytes 25 to 28 */
} BidOfferUpdate;

/* any Bid Offer Update at all: every byte one the checker chooses */
static void any_bid_offer_update(BidOfferUpdate *record) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->update_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->total_bid_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->total_offer_size[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_orders[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->offer_orders[i] = arbitrary(); }
}

/* Bid Offer Update to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_bid_offer_update(const BidOfferUpdate *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->update_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_bid_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->total_offer_size[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_orders[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->offer_orders[i]; }

  return at;
}

/* Bid Offer Update off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_bid_offer_update(BidOfferUpdate *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->update_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->total_bid_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->total_offer_size[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_orders[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->offer_orders[i] = wire[at++]; }

  return at;
}

/* what was read of Bid Offer Update is what was written, byte for byte */
static void equal_bid_offer_update(const BidOfferUpdate *read, const BidOfferUpdate *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->update_type == written->update_type);
  for (size_t i = 0; i < 8; i++) { assert(read->total_bid_size[i] == written->total_bid_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->total_offer_size[i] == written->total_offer_size[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_orders[i] == written->bid_orders[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->offer_orders[i] == written->offer_orders[i]); }
}

/* Bid Offer Update: written and read back, then read and written back */
static void check_bid_offer_update(void) {
  BidOfferUpdate sent;
  BidOfferUpdate got;
  uint8_t wire[29];
  uint8_t again[29];

  any_bid_offer_update(&sent);
  assert(encode_bid_offer_update(&sent, wire, 0) == 29);
  assert(decode_bid_offer_update(&got, wire, 0) == 29);
  equal_bid_offer_update(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_offer_update(&got, wire, 0) == 29);
  assert(encode_bid_offer_update(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust: 4 bytes ----------------------------------------------------- */

/* Message used to inform about cancellation of previously accepted Trade */
typedef struct {
  uint8_t trade_id[4];  /* bytes 0 to 3 */
} TradeBust;

/* any Trade Bust at all: every byte one the checker chooses */
static void any_trade_bust(TradeBust *record) {
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = arbitrary(); }
}

/* Trade Bust to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust(const TradeBust *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_id[i]; }

  return at;
}

/* Trade Bust off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust(TradeBust *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->trade_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Bust is what was written, byte for byte */
static void equal_trade_bust(const TradeBust *read, const TradeBust *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->trade_id[i] == written->trade_id[i]); }
}

/* Trade Bust: written and read back, then read and written back */
static void check_trade_bust(void) {
  TradeBust sent;
  TradeBust got;
  uint8_t wire[4];
  uint8_t again[4];

  any_trade_bust(&sent);
  assert(encode_trade_bust(&sent, wire, 0) == 4);
  assert(decode_trade_bust(&got, wire, 0) == 4);
  equal_trade_bust(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust(&got, wire, 0) == 4);
  assert(encode_trade_bust(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login();
  check_login_response();
  check_connection_close();
  check_reject();
  check_test();
  check_test_event();
  check_trading_session_status();
  check_client();
  check_executing_trader();
  check_investment_decision_maker();
  check_mifid_fields();
  check_order_mass_cancel();
  check_bid();
  check_ask();
  check_quote();
  check_market_maker_command();
  check_market_maker_command_response();
  check_request_for_execution();
  check_bid_offer_update();
  check_trade_bust();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
