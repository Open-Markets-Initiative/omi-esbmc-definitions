// bme/meff/topofbook5/Meff_TopOfBook5_v1_6.c
/*
 * Bolsas y Mercados Españoles MEFF Top Of Book Five Levels
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

/* ---- Message Header: 3 bytes ------------------------------------------------- */

/* What every message carries, in either direction: its length and its type. Section 2.1 gives a published message a third field, the sequence number that lets a listener continue an interrupted session without gaps and without repeated messages, and the message tables state it as the message's own first field - which is where it is declared, since a client's Logon, Replay Request and Logout do not carry one */
typedef struct {
  uint8_t message_size[2];  /* bytes 0 to 1 */
  uint8_t message_type;     /* byte 2 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = arbitrary(); }
  record->message_type = arbitrary();
}

/* Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_size[i]; }
  wire[at++] = record->message_type;

  return at;
}

/* Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_size[i] = wire[at++]; }
  record->message_type = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_size[i] == written->message_size[i]); }
  assert(read->message_type == written->message_type);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 3);
  assert(decode_message_header(&got, wire, 0) == 3);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 3);
  assert(encode_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Response Message: 26 bytes ---------------------------------------- */

/* The Logon Response message is used by the Server to accept a new session. In this message the sequence number will always be 0 */
typedef struct {
  uint8_t sequence_number[4];           /* bytes 0 to 3 */
  uint8_t heart_bt_int;                 /* byte 4 */
  uint8_t protocol_version[6];          /* bytes 5 to 10 */
  uint8_t test_production_ind;          /* byte 11 */
  uint8_t environment_code[2];          /* bytes 12 to 13 */
  uint8_t session_date[4];              /* bytes 14 to 17 */
  uint8_t expected_sequence_number[4];  /* bytes 18 to 21 */
  uint8_t sequence_number_to[4];        /* bytes 22 to 25 */
} LogonResponseMessage;

/* any Logon Response Message at all: every byte one the checker chooses */
static void any_logon_response_message(LogonResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->heart_bt_int = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->protocol_version[i] = arbitrary(); }
  record->test_production_ind = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->environment_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expected_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number_to[i] = arbitrary(); }
}

/* Logon Response Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_logon_response_message(const LogonResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->heart_bt_int;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->protocol_version[i]; }
  wire[at++] = record->test_production_ind;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->environment_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->session_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expected_sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number_to[i]; }

  return at;
}

/* Logon Response Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_logon_response_message(LogonResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->heart_bt_int = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->protocol_version[i] = wire[at++]; }
  record->test_production_ind = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->environment_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expected_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number_to[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Response Message is what was written, byte for byte */
static void equal_logon_response_message(const LogonResponseMessage *read, const LogonResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->heart_bt_int == written->heart_bt_int);
  for (size_t i = 0; i < 6; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
  assert(read->test_production_ind == written->test_production_ind);
  for (size_t i = 0; i < 2; i++) { assert(read->environment_code[i] == written->environment_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->session_date[i] == written->session_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expected_sequence_number[i] == written->expected_sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number_to[i] == written->sequence_number_to[i]); }
}

/* Logon Response Message: written and read back, then read and written back */
static void check_logon_response_message(void) {
  LogonResponseMessage sent;
  LogonResponseMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_logon_response_message(&sent);
  assert(encode_logon_response_message(&sent, wire, 0) == 26);
  assert(decode_logon_response_message(&got, wire, 0) == 26);
  equal_logon_response_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_response_message(&got, wire, 0) == 26);
  assert(encode_logon_response_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Response Message: 5 bytes ---------------------------------------- */

/* The Logout message is used by the Server to notify the end of a session, whether it is solicited or unsolicited. It may also be the answer to a failed logon attempt (see Logon message) */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t logout_reason;       /* byte 4 */
} LogoutResponseMessage;

/* any Logout Response Message at all: every byte one the checker chooses */
static void any_logout_response_message(LogoutResponseMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->logout_reason = arbitrary();
}

/* Logout Response Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_logout_response_message(const LogoutResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->logout_reason;

  return at;
}

/* Logout Response Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_logout_response_message(LogoutResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->logout_reason = wire[at++];

  return at;
}

/* what was read of Logout Response Message is what was written, byte for byte */
static void equal_logout_response_message(const LogoutResponseMessage *read, const LogoutResponseMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->logout_reason == written->logout_reason);
}

/* Logout Response Message: written and read back, then read and written back */
static void check_logout_response_message(void) {
  LogoutResponseMessage sent;
  LogoutResponseMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_logout_response_message(&sent);
  assert(encode_logout_response_message(&sent, wire, 0) == 5);
  assert(decode_logout_response_message(&got, wire, 0) == 5);
  equal_logout_response_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_response_message(&got, wire, 0) == 5);
  assert(encode_logout_response_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Heartbeat Message: 4 bytes ---------------------------------------------- */

/* The Heartbeat message is used by the Server to indicate that the communication is active. In the Heartbeat message, the SequenceNumber of the previously received message will be repeated */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
} HeartbeatMessage;

/* any Heartbeat Message at all: every byte one the checker chooses */
static void any_heartbeat_message(HeartbeatMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Heartbeat Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_heartbeat_message(const HeartbeatMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Heartbeat Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_heartbeat_message(HeartbeatMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Heartbeat Message is what was written, byte for byte */
static void equal_heartbeat_message(const HeartbeatMessage *read, const HeartbeatMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Heartbeat Message: written and read back, then read and written back */
static void check_heartbeat_message(void) {
  HeartbeatMessage sent;
  HeartbeatMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_heartbeat_message(&sent);
  assert(encode_heartbeat_message(&sent, wire, 0) == 4);
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  equal_heartbeat_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_heartbeat_message(&got, wire, 0) == 4);
  assert(encode_heartbeat_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Network Status Message: 5 bytes ----------------------------------------- */

/* Message sent by the server with information about the connectivity between the Server and the central systems. In the Network Status message, the SequenceNumber of the previously received message will be repeated */
typedef struct {
  uint8_t sequence_number[4];    /* bytes 0 to 3 */
  uint8_t network_status_value;  /* byte 4 */
} NetworkStatusMessage;

/* any Network Status Message at all: every byte one the checker chooses */
static void any_network_status_message(NetworkStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->network_status_value = arbitrary();
}

/* Network Status Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_network_status_message(const NetworkStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->network_status_value;

  return at;
}

/* Network Status Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_network_status_message(NetworkStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->network_status_value = wire[at++];

  return at;
}

/* what was read of Network Status Message is what was written, byte for byte */
static void equal_network_status_message(const NetworkStatusMessage *read, const NetworkStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->network_status_value == written->network_status_value);
}

/* Network Status Message: written and read back, then read and written back */
static void check_network_status_message(void) {
  NetworkStatusMessage sent;
  NetworkStatusMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_network_status_message(&sent);
  assert(encode_network_status_message(&sent, wire, 0) == 5);
  assert(decode_network_status_message(&got, wire, 0) == 5);
  equal_network_status_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_network_status_message(&got, wire, 0) == 5);
  assert(encode_network_status_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Status Message: 15 bytes -------------------------------- */

/* Sent by the server to inform about the session status in each Trading Mode */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t trading_session_id;            /* byte 4 */
  uint8_t trading_session_sub_id;        /* byte 5 */
  uint8_t trad_ses_status;               /* byte 6 */
  uint8_t transaction_date_and_time[8];  /* bytes 7 to 14 */
} TradingSessionStatusMessage;

/* any Trading Session Status Message at all: every byte one the checker chooses */
static void any_trading_session_status_message(TradingSessionStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  record->trading_session_sub_id = arbitrary();
  record->trad_ses_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
}

/* Trading Session Status Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_status_message(const TradingSessionStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->trading_session_id;
  wire[at++] = record->trading_session_sub_id;
  wire[at++] = record->trad_ses_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }

  return at;
}

/* Trading Session Status Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_status_message(TradingSessionStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  record->trading_session_sub_id = wire[at++];
  record->trad_ses_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }

  return at;
}

/* what was read of Trading Session Status Message is what was written, byte for byte */
static void equal_trading_session_status_message(const TradingSessionStatusMessage *read, const TradingSessionStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  assert(read->trading_session_sub_id == written->trading_session_sub_id);
  assert(read->trad_ses_status == written->trad_ses_status);
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
}

/* Trading Session Status Message: written and read back, then read and written back */
static void check_trading_session_status_message(void) {
  TradingSessionStatusMessage sent;
  TradingSessionStatusMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_trading_session_status_message(&sent);
  assert(encode_trading_session_status_message(&sent, wire, 0) == 15);
  assert(decode_trading_session_status_message(&got, wire, 0) == 15);
  equal_trading_session_status_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_status_message(&got, wire, 0) == 15);
  assert(encode_trading_session_status_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- News Message: 82 bytes -------------------------------------------------- */

/* Used by the Server to communicate a Market Surveillance or system-wide text message */
typedef struct {
  uint8_t sequence_number[4];  /* bytes 0 to 3 */
  uint8_t news_text[78];       /* bytes 4 to 81 */
} NewsMessage;

/* any News Message at all: every byte one the checker chooses */
static void any_news_message(NewsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 78; i++) { record->news_text[i] = arbitrary(); }
}

/* News Message to the wire: 82 bytes from at, returning where the next byte goes */
static size_t encode_news_message(const NewsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 78; i++) { wire[at++] = record->news_text[i]; }

  return at;
}

/* News Message off the wire: 82 bytes from at, returning where the next byte lies */
static size_t decode_news_message(NewsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 78; i++) { record->news_text[i] = wire[at++]; }

  return at;
}

/* what was read of News Message is what was written, byte for byte */
static void equal_news_message(const NewsMessage *read, const NewsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 78; i++) { assert(read->news_text[i] == written->news_text[i]); }
}

/* News Message: written and read back, then read and written back */
static void check_news_message(void) {
  NewsMessage sent;
  NewsMessage got;
  uint8_t wire[82];
  uint8_t again[82];

  any_news_message(&sent);
  assert(encode_news_message(&sent, wire, 0) == 82);
  assert(decode_news_message(&got, wire, 0) == 82);
  equal_news_message(&got, &sent);

  for (size_t i = 0; i < 82; i++) { wire[i] = arbitrary(); }
  assert(decode_news_message(&got, wire, 0) == 82);
  assert(encode_news_message(&got, again, 0) == 82);
  for (size_t i = 0; i < 82; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security List Cancellation Report Message: 50 bytes --------------------- */

/* Message sent by the server for cancelling previously defined securities */
typedef struct {
  uint8_t sequence_number[4];    /* bytes 0 to 3 */
  uint8_t market_id[4];          /* bytes 4 to 7 */
  uint8_t market_segment_id[4];  /* bytes 8 to 11 */
  uint8_t security_code[4];      /* bytes 12 to 15 */
  uint8_t symbol[22];            /* bytes 16 to 37 */
  uint8_t symbol_isin[12];       /* bytes 38 to 49 */
} SecurityListCancellationReportMessage;

/* any Security List Cancellation Report Message at all: every byte one the checker chooses */
static void any_security_list_cancellation_report_message(SecurityListCancellationReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = arbitrary(); }
}

/* Security List Cancellation Report Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_security_list_cancellation_report_message(const SecurityListCancellationReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol_isin[i]; }

  return at;
}

/* Security List Cancellation Report Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_security_list_cancellation_report_message(SecurityListCancellationReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = wire[at++]; }

  return at;
}

/* what was read of Security List Cancellation Report Message is what was written, byte for byte */
static void equal_security_list_cancellation_report_message(const SecurityListCancellationReportMessage *read, const SecurityListCancellationReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol_isin[i] == written->symbol_isin[i]); }
}

/* Security List Cancellation Report Message: written and read back, then read and written back */
static void check_security_list_cancellation_report_message(void) {
  SecurityListCancellationReportMessage sent;
  SecurityListCancellationReportMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_security_list_cancellation_report_message(&sent);
  assert(encode_security_list_cancellation_report_message(&sent, wire, 0) == 50);
  assert(decode_security_list_cancellation_report_message(&got, wire, 0) == 50);
  equal_security_list_cancellation_report_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_cancellation_report_message(&got, wire, 0) == 50);
  assert(encode_security_list_cancellation_report_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security List Message: 713 bytes ---------------------------------------- */

/* Message sent by the server to provide the definition of one security. It shares the same layout as the Security List Update Report message, but with a different Message Type */
typedef struct {
  uint8_t sequence_number[4];                     /* bytes 0 to 3 */
  uint8_t market_id[4];                           /* bytes 4 to 7 */
  uint8_t market_segment_id[4];                   /* bytes 8 to 11 */
  uint8_t security_code[4];                       /* bytes 12 to 15 */
  uint8_t symbol[22];                             /* bytes 16 to 37 */
  uint8_t symbol_isin[12];                        /* bytes 38 to 49 */
  uint8_t fisn[35];                               /* bytes 50 to 84 */
  uint8_t issuer_lei[20];                         /* bytes 85 to 104 */
  uint8_t security_group[2];                      /* bytes 105 to 106 */
  uint8_t family_code[5];                         /* bytes 107 to 111 */
  uint8_t cfi_code[6];                            /* bytes 112 to 117 */
  uint8_t security_type[2];                       /* bytes 118 to 119 */
  uint8_t maturity_date[4];                       /* bytes 120 to 123 */
  uint8_t issue_date[4];                          /* bytes 124 to 127 */
  uint8_t contract_multiplier[8];                 /* bytes 128 to 135 */
  uint8_t li_spre[8];                             /* bytes 136 to 143 */
  uint8_t sst_ipre[8];                            /* bytes 144 to 151 */
  uint8_t li_spost[8];                            /* bytes 152 to 159 */
  uint8_t sst_ipost[8];                           /* bytes 160 to 167 */
  uint8_t liquid_instrument;                      /* byte 168 */
  uint8_t admission_requested_by_issuer;          /* byte 169 */
  uint8_t min_trade_vol[4];                       /* bytes 170 to 173 */
  uint8_t round_lot[4];                           /* bytes 174 to 177 */
  uint8_t currency[3];                            /* bytes 178 to 180 */
  uint8_t modality_mask_b_4[4];                   /* bytes 181 to 184 */
  uint8_t security_description[80];               /* bytes 185 to 264 */
  uint8_t trading_obligation;                     /* byte 265 */
  uint8_t sec_description[20];                    /* bytes 266 to 285 */
  uint8_t underlying_asset[22];                   /* bytes 286 to 307 */
  uint8_t security_sub_type[12];                  /* bytes 308 to 319 */
  uint8_t maturity_month_year[8];                 /* bytes 320 to 327 */
  uint8_t strike_price[8];                        /* bytes 328 to 335 */
  uint8_t strike_value[8];                        /* bytes 336 to 343 */
  uint8_t opt_attribute;                          /* byte 344 */
  uint8_t min_price_increment[8];                 /* bytes 345 to 352 */
  uint8_t unit_of_measure[20];                    /* bytes 353 to 372 */
  uint8_t settl_method;                           /* byte 373 */
  uint8_t exercise_style;                         /* byte 374 */
  uint8_t put_or_call;                            /* byte 375 */
  uint8_t flexible_indicator;                     /* byte 376 */
  uint8_t last_trading_day[4];                    /* bytes 377 to 380 */
  uint8_t number_of_decimals;                     /* byte 381 */
  uint8_t order_number_of_decimals;               /* byte 382 */
  uint8_t adjustments_rule;                       /* byte 383 */
  uint8_t maximum_order_size[8];                  /* bytes 384 to 391 */
  uint8_t self_match_prevention;                  /* byte 392 */
  uint8_t commodity_derivative_indicator;         /* byte 393 */
  uint8_t stock_when_underlying_is_dividend[22];  /* bytes 394 to 415 */
  uint8_t base_product[4];                        /* bytes 416 to 419 */
  uint8_t sub_product[4];                         /* bytes 420 to 423 */
  uint8_t further_sub_product[4];                 /* bytes 424 to 427 */
  uint8_t base_currency[3];                       /* bytes 428 to 430 */
  uint8_t quoted_currency[3];                     /* bytes 431 to 433 */
  uint8_t maturity_month_year_increment_units;    /* byte 434 */
  uint8_t start_maturity_month_year[8];           /* bytes 435 to 442 */
  uint8_t end_maturity_month_year[8];             /* bytes 443 to 450 */
  uint8_t maturity_month_year_increment;          /* byte 451 */
  uint8_t underlying_symbol[22];                  /* bytes 452 to 473 */
  uint8_t underlying_isin[12];                    /* bytes 474 to 485 */
  uint8_t underlying_currency[3];                 /* bytes 486 to 488 */
  uint8_t underlying_security_issuer_lei[20];     /* bytes 489 to 508 */
  uint8_t x_rolling_closing_type;                 /* byte 509 */
  uint8_t x_rolling_reference_buyer_rate;         /* byte 510 */
  uint8_t x_rolling_buyer_markup[8];              /* bytes 511 to 518 */
  uint8_t x_rolling_reference_seller_rate;        /* byte 519 */
  uint8_t x_rolling_seller_markup[8];             /* bytes 520 to 527 */
  uint8_t x_rolling_dividend_percentage[8];       /* bytes 528 to 535 */
  uint8_t x_rolling_dividend_pay_date_diff[2];    /* bytes 536 to 537 */
  uint8_t leg_symbol_1[22];                       /* bytes 538 to 559 */
  uint8_t leg_ratio_qty_1[4];                     /* bytes 560 to 563 */
  uint8_t leg_side_1;                             /* byte 564 */
  uint8_t leg_price_1[8];                         /* bytes 565 to 572 */
  uint8_t leg_symbol_2[22];                       /* bytes 573 to 594 */
  uint8_t leg_ratio_qty_2[4];                     /* bytes 595 to 598 */
  uint8_t leg_side_2;                             /* byte 599 */
  uint8_t leg_price_2[8];                         /* bytes 600 to 607 */
  uint8_t leg_symbol_3[22];                       /* bytes 608 to 629 */
  uint8_t leg_ratio_qty_3[4];                     /* bytes 630 to 633 */
  uint8_t leg_side_3;                             /* byte 634 */
  uint8_t leg_price_3[8];                         /* bytes 635 to 642 */
  uint8_t leg_symbol_4[22];                       /* bytes 643 to 664 */
  uint8_t leg_ratio_qty_4[4];                     /* bytes 665 to 668 */
  uint8_t leg_side_4;                             /* byte 669 */
  uint8_t leg_price_4[8];                         /* bytes 670 to 677 */
  uint8_t leg_symbol_5[22];                       /* bytes 678 to 699 */
  uint8_t leg_ratio_qty_5[4];                     /* bytes 700 to 703 */
  uint8_t leg_side_5;                             /* byte 704 */
  uint8_t leg_price_5[8];                         /* bytes 705 to 712 */
} SecurityListMessage;

/* any Security List Message at all: every byte one the checker chooses */
static void any_security_list_message(SecurityListMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->issuer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->family_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->li_spre[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sst_ipre[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->li_spost[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sst_ipost[i] = arbitrary(); }
  record->liquid_instrument = arbitrary();
  record->admission_requested_by_issuer = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->modality_mask_b_4[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->security_description[i] = arbitrary(); }
  record->trading_obligation = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->sec_description[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->underlying_asset[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->security_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = arbitrary(); }
  record->opt_attribute = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->unit_of_measure[i] = arbitrary(); }
  record->settl_method = arbitrary();
  record->exercise_style = arbitrary();
  record->put_or_call = arbitrary();
  record->flexible_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = arbitrary(); }
  record->number_of_decimals = arbitrary();
  record->order_number_of_decimals = arbitrary();
  record->adjustments_rule = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->maximum_order_size[i] = arbitrary(); }
  record->self_match_prevention = arbitrary();
  record->commodity_derivative_indicator = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->stock_when_underlying_is_dividend[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->quoted_currency[i] = arbitrary(); }
  record->maturity_month_year_increment_units = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->start_maturity_month_year[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_maturity_month_year[i] = arbitrary(); }
  record->maturity_month_year_increment = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->underlying_security_issuer_lei[i] = arbitrary(); }
  record->x_rolling_closing_type = arbitrary();
  record->x_rolling_reference_buyer_rate = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->x_rolling_buyer_markup[i] = arbitrary(); }
  record->x_rolling_reference_seller_rate = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->x_rolling_seller_markup[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->x_rolling_dividend_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->x_rolling_dividend_pay_date_diff[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_1[i] = arbitrary(); }
  record->leg_side_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_1[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_2[i] = arbitrary(); }
  record->leg_side_2 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_3[i] = arbitrary(); }
  record->leg_side_3 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_3[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_4[i] = arbitrary(); }
  record->leg_side_4 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_5[i] = arbitrary(); }
  record->leg_side_5 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_5[i] = arbitrary(); }
}

/* Security List Message to the wire: 713 bytes from at, returning where the next byte goes */
static size_t encode_security_list_message(const SecurityListMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol_isin[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->fisn[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->issuer_lei[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->family_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->li_spre[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sst_ipre[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->li_spost[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sst_ipost[i]; }
  wire[at++] = record->liquid_instrument;
  wire[at++] = record->admission_requested_by_issuer;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_trade_vol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->modality_mask_b_4[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->security_description[i]; }
  wire[at++] = record->trading_obligation;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sec_description[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->underlying_asset[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->security_sub_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_month_year[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_value[i]; }
  wire[at++] = record->opt_attribute;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price_increment[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->unit_of_measure[i]; }
  wire[at++] = record->settl_method;
  wire[at++] = record->exercise_style;
  wire[at++] = record->put_or_call;
  wire[at++] = record->flexible_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_day[i]; }
  wire[at++] = record->number_of_decimals;
  wire[at++] = record->order_number_of_decimals;
  wire[at++] = record->adjustments_rule;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_order_size[i]; }
  wire[at++] = record->self_match_prevention;
  wire[at++] = record->commodity_derivative_indicator;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->stock_when_underlying_is_dividend[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->base_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sub_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->further_sub_product[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->base_currency[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->quoted_currency[i]; }
  wire[at++] = record->maturity_month_year_increment_units;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_maturity_month_year[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_maturity_month_year[i]; }
  wire[at++] = record->maturity_month_year_increment;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_currency[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->underlying_security_issuer_lei[i]; }
  wire[at++] = record->x_rolling_closing_type;
  wire[at++] = record->x_rolling_reference_buyer_rate;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->x_rolling_buyer_markup[i]; }
  wire[at++] = record->x_rolling_reference_seller_rate;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->x_rolling_seller_markup[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->x_rolling_dividend_percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->x_rolling_dividend_pay_date_diff[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_1[i]; }
  wire[at++] = record->leg_side_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_1[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_2[i]; }
  wire[at++] = record->leg_side_2;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_2[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_3[i]; }
  wire[at++] = record->leg_side_3;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_3[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_4[i]; }
  wire[at++] = record->leg_side_4;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_4[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_5[i]; }
  wire[at++] = record->leg_side_5;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_5[i]; }

  return at;
}

/* Security List Message off the wire: 713 bytes from at, returning where the next byte lies */
static size_t decode_security_list_message(SecurityListMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->issuer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->family_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->li_spre[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sst_ipre[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->li_spost[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sst_ipost[i] = wire[at++]; }
  record->liquid_instrument = wire[at++];
  record->admission_requested_by_issuer = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->modality_mask_b_4[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->security_description[i] = wire[at++]; }
  record->trading_obligation = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->sec_description[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->security_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = wire[at++]; }
  record->opt_attribute = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->unit_of_measure[i] = wire[at++]; }
  record->settl_method = wire[at++];
  record->exercise_style = wire[at++];
  record->put_or_call = wire[at++];
  record->flexible_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = wire[at++]; }
  record->number_of_decimals = wire[at++];
  record->order_number_of_decimals = wire[at++];
  record->adjustments_rule = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->maximum_order_size[i] = wire[at++]; }
  record->self_match_prevention = wire[at++];
  record->commodity_derivative_indicator = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->stock_when_underlying_is_dividend[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->quoted_currency[i] = wire[at++]; }
  record->maturity_month_year_increment_units = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->start_maturity_month_year[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_maturity_month_year[i] = wire[at++]; }
  record->maturity_month_year_increment = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->underlying_security_issuer_lei[i] = wire[at++]; }
  record->x_rolling_closing_type = wire[at++];
  record->x_rolling_reference_buyer_rate = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->x_rolling_buyer_markup[i] = wire[at++]; }
  record->x_rolling_reference_seller_rate = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->x_rolling_seller_markup[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->x_rolling_dividend_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->x_rolling_dividend_pay_date_diff[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_1[i] = wire[at++]; }
  record->leg_side_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_1[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_2[i] = wire[at++]; }
  record->leg_side_2 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_3[i] = wire[at++]; }
  record->leg_side_3 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_3[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_4[i] = wire[at++]; }
  record->leg_side_4 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_5[i] = wire[at++]; }
  record->leg_side_5 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_5[i] = wire[at++]; }

  return at;
}

/* what was read of Security List Message is what was written, byte for byte */
static void equal_security_list_message(const SecurityListMessage *read, const SecurityListMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol_isin[i] == written->symbol_isin[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->fisn[i] == written->fisn[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->issuer_lei[i] == written->issuer_lei[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group[i] == written->security_group[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->family_code[i] == written->family_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_type[i] == written->security_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->li_spre[i] == written->li_spre[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sst_ipre[i] == written->sst_ipre[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->li_spost[i] == written->li_spost[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sst_ipost[i] == written->sst_ipost[i]); }
  assert(read->liquid_instrument == written->liquid_instrument);
  assert(read->admission_requested_by_issuer == written->admission_requested_by_issuer);
  for (size_t i = 0; i < 4; i++) { assert(read->min_trade_vol[i] == written->min_trade_vol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot[i] == written->round_lot[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->modality_mask_b_4[i] == written->modality_mask_b_4[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->security_description[i] == written->security_description[i]); }
  assert(read->trading_obligation == written->trading_obligation);
  for (size_t i = 0; i < 20; i++) { assert(read->sec_description[i] == written->sec_description[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->underlying_asset[i] == written->underlying_asset[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->security_sub_type[i] == written->security_sub_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_value[i] == written->strike_value[i]); }
  assert(read->opt_attribute == written->opt_attribute);
  for (size_t i = 0; i < 8; i++) { assert(read->min_price_increment[i] == written->min_price_increment[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->unit_of_measure[i] == written->unit_of_measure[i]); }
  assert(read->settl_method == written->settl_method);
  assert(read->exercise_style == written->exercise_style);
  assert(read->put_or_call == written->put_or_call);
  assert(read->flexible_indicator == written->flexible_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_day[i] == written->last_trading_day[i]); }
  assert(read->number_of_decimals == written->number_of_decimals);
  assert(read->order_number_of_decimals == written->order_number_of_decimals);
  assert(read->adjustments_rule == written->adjustments_rule);
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_order_size[i] == written->maximum_order_size[i]); }
  assert(read->self_match_prevention == written->self_match_prevention);
  assert(read->commodity_derivative_indicator == written->commodity_derivative_indicator);
  for (size_t i = 0; i < 22; i++) { assert(read->stock_when_underlying_is_dividend[i] == written->stock_when_underlying_is_dividend[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->base_product[i] == written->base_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sub_product[i] == written->sub_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->further_sub_product[i] == written->further_sub_product[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->base_currency[i] == written->base_currency[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->quoted_currency[i] == written->quoted_currency[i]); }
  assert(read->maturity_month_year_increment_units == written->maturity_month_year_increment_units);
  for (size_t i = 0; i < 8; i++) { assert(read->start_maturity_month_year[i] == written->start_maturity_month_year[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_maturity_month_year[i] == written->end_maturity_month_year[i]); }
  assert(read->maturity_month_year_increment == written->maturity_month_year_increment);
  for (size_t i = 0; i < 22; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_isin[i] == written->underlying_isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_currency[i] == written->underlying_currency[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->underlying_security_issuer_lei[i] == written->underlying_security_issuer_lei[i]); }
  assert(read->x_rolling_closing_type == written->x_rolling_closing_type);
  assert(read->x_rolling_reference_buyer_rate == written->x_rolling_reference_buyer_rate);
  for (size_t i = 0; i < 8; i++) { assert(read->x_rolling_buyer_markup[i] == written->x_rolling_buyer_markup[i]); }
  assert(read->x_rolling_reference_seller_rate == written->x_rolling_reference_seller_rate);
  for (size_t i = 0; i < 8; i++) { assert(read->x_rolling_seller_markup[i] == written->x_rolling_seller_markup[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->x_rolling_dividend_percentage[i] == written->x_rolling_dividend_percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->x_rolling_dividend_pay_date_diff[i] == written->x_rolling_dividend_pay_date_diff[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_1[i] == written->leg_symbol_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_1[i] == written->leg_ratio_qty_1[i]); }
  assert(read->leg_side_1 == written->leg_side_1);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_1[i] == written->leg_price_1[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_2[i] == written->leg_symbol_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_2[i] == written->leg_ratio_qty_2[i]); }
  assert(read->leg_side_2 == written->leg_side_2);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_2[i] == written->leg_price_2[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_3[i] == written->leg_symbol_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_3[i] == written->leg_ratio_qty_3[i]); }
  assert(read->leg_side_3 == written->leg_side_3);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_3[i] == written->leg_price_3[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_4[i] == written->leg_symbol_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_4[i] == written->leg_ratio_qty_4[i]); }
  assert(read->leg_side_4 == written->leg_side_4);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_4[i] == written->leg_price_4[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_5[i] == written->leg_symbol_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_5[i] == written->leg_ratio_qty_5[i]); }
  assert(read->leg_side_5 == written->leg_side_5);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_5[i] == written->leg_price_5[i]); }
}

/* Security List Message: written and read back, then read and written back */
static void check_security_list_message(void) {
  SecurityListMessage sent;
  SecurityListMessage got;
  uint8_t wire[713];
  uint8_t again[713];

  any_security_list_message(&sent);
  assert(encode_security_list_message(&sent, wire, 0) == 713);
  assert(decode_security_list_message(&got, wire, 0) == 713);
  equal_security_list_message(&got, &sent);

  for (size_t i = 0; i < 713; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_message(&got, wire, 0) == 713);
  assert(encode_security_list_message(&got, again, 0) == 713);
  for (size_t i = 0; i < 713; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security List Update Report Message: 713 bytes -------------------------- */

/* Message sent by the server for reporting updates, during the session, to the security definition */
typedef struct {
  uint8_t sequence_number[4];                     /* bytes 0 to 3 */
  uint8_t market_id[4];                           /* bytes 4 to 7 */
  uint8_t market_segment_id[4];                   /* bytes 8 to 11 */
  uint8_t security_code[4];                       /* bytes 12 to 15 */
  uint8_t symbol[22];                             /* bytes 16 to 37 */
  uint8_t symbol_isin[12];                        /* bytes 38 to 49 */
  uint8_t fisn[35];                               /* bytes 50 to 84 */
  uint8_t issuer_lei[20];                         /* bytes 85 to 104 */
  uint8_t security_group[2];                      /* bytes 105 to 106 */
  uint8_t family_code[5];                         /* bytes 107 to 111 */
  uint8_t cfi_code[6];                            /* bytes 112 to 117 */
  uint8_t security_type[2];                       /* bytes 118 to 119 */
  uint8_t maturity_date[4];                       /* bytes 120 to 123 */
  uint8_t issue_date[4];                          /* bytes 124 to 127 */
  uint8_t contract_multiplier[8];                 /* bytes 128 to 135 */
  uint8_t li_spre[8];                             /* bytes 136 to 143 */
  uint8_t sst_ipre[8];                            /* bytes 144 to 151 */
  uint8_t li_spost[8];                            /* bytes 152 to 159 */
  uint8_t sst_ipost[8];                           /* bytes 160 to 167 */
  uint8_t liquid_instrument;                      /* byte 168 */
  uint8_t admission_requested_by_issuer;          /* byte 169 */
  uint8_t min_trade_vol[4];                       /* bytes 170 to 173 */
  uint8_t round_lot[4];                           /* bytes 174 to 177 */
  uint8_t currency[3];                            /* bytes 178 to 180 */
  uint8_t modality_mask_b_4[4];                   /* bytes 181 to 184 */
  uint8_t security_description[80];               /* bytes 185 to 264 */
  uint8_t trading_obligation;                     /* byte 265 */
  uint8_t sec_description[20];                    /* bytes 266 to 285 */
  uint8_t underlying_asset[22];                   /* bytes 286 to 307 */
  uint8_t security_sub_type[12];                  /* bytes 308 to 319 */
  uint8_t maturity_month_year[8];                 /* bytes 320 to 327 */
  uint8_t strike_price[8];                        /* bytes 328 to 335 */
  uint8_t strike_value[8];                        /* bytes 336 to 343 */
  uint8_t opt_attribute;                          /* byte 344 */
  uint8_t min_price_increment[8];                 /* bytes 345 to 352 */
  uint8_t unit_of_measure[20];                    /* bytes 353 to 372 */
  uint8_t settl_method;                           /* byte 373 */
  uint8_t exercise_style;                         /* byte 374 */
  uint8_t put_or_call;                            /* byte 375 */
  uint8_t flexible_indicator;                     /* byte 376 */
  uint8_t last_trading_day[4];                    /* bytes 377 to 380 */
  uint8_t number_of_decimals;                     /* byte 381 */
  uint8_t order_number_of_decimals;               /* byte 382 */
  uint8_t adjustments_rule;                       /* byte 383 */
  uint8_t maximum_order_size[8];                  /* bytes 384 to 391 */
  uint8_t self_match_prevention;                  /* byte 392 */
  uint8_t commodity_derivative_indicator;         /* byte 393 */
  uint8_t stock_when_underlying_is_dividend[22];  /* bytes 394 to 415 */
  uint8_t base_product[4];                        /* bytes 416 to 419 */
  uint8_t sub_product[4];                         /* bytes 420 to 423 */
  uint8_t further_sub_product[4];                 /* bytes 424 to 427 */
  uint8_t base_currency[3];                       /* bytes 428 to 430 */
  uint8_t quoted_currency[3];                     /* bytes 431 to 433 */
  uint8_t maturity_month_year_increment_units;    /* byte 434 */
  uint8_t start_maturity_month_year[8];           /* bytes 435 to 442 */
  uint8_t end_maturity_month_year[8];             /* bytes 443 to 450 */
  uint8_t maturity_month_year_increment;          /* byte 451 */
  uint8_t underlying_symbol[22];                  /* bytes 452 to 473 */
  uint8_t underlying_isin[12];                    /* bytes 474 to 485 */
  uint8_t underlying_currency[3];                 /* bytes 486 to 488 */
  uint8_t underlying_security_issuer_lei[20];     /* bytes 489 to 508 */
  uint8_t x_rolling_closing_type;                 /* byte 509 */
  uint8_t x_rolling_reference_buyer_rate;         /* byte 510 */
  uint8_t x_rolling_buyer_markup[8];              /* bytes 511 to 518 */
  uint8_t x_rolling_reference_seller_rate;        /* byte 519 */
  uint8_t x_rolling_seller_markup[8];             /* bytes 520 to 527 */
  uint8_t x_rolling_dividend_percentage[8];       /* bytes 528 to 535 */
  uint8_t x_rolling_dividend_pay_date_diff[2];    /* bytes 536 to 537 */
  uint8_t leg_symbol_1[22];                       /* bytes 538 to 559 */
  uint8_t leg_ratio_qty_1[4];                     /* bytes 560 to 563 */
  uint8_t leg_side_1;                             /* byte 564 */
  uint8_t leg_price_1[8];                         /* bytes 565 to 572 */
  uint8_t leg_symbol_2[22];                       /* bytes 573 to 594 */
  uint8_t leg_ratio_qty_2[4];                     /* bytes 595 to 598 */
  uint8_t leg_side_2;                             /* byte 599 */
  uint8_t leg_price_2[8];                         /* bytes 600 to 607 */
  uint8_t leg_symbol_3[22];                       /* bytes 608 to 629 */
  uint8_t leg_ratio_qty_3[4];                     /* bytes 630 to 633 */
  uint8_t leg_side_3;                             /* byte 634 */
  uint8_t leg_price_3[8];                         /* bytes 635 to 642 */
  uint8_t leg_symbol_4[22];                       /* bytes 643 to 664 */
  uint8_t leg_ratio_qty_4[4];                     /* bytes 665 to 668 */
  uint8_t leg_side_4;                             /* byte 669 */
  uint8_t leg_price_4[8];                         /* bytes 670 to 677 */
  uint8_t leg_symbol_5[22];                       /* bytes 678 to 699 */
  uint8_t leg_ratio_qty_5[4];                     /* bytes 700 to 703 */
  uint8_t leg_side_5;                             /* byte 704 */
  uint8_t leg_price_5[8];                         /* bytes 705 to 712 */
} SecurityListUpdateReportMessage;

/* any Security List Update Report Message at all: every byte one the checker chooses */
static void any_security_list_update_report_message(SecurityListUpdateReportMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->issuer_lei[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->family_code[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->li_spre[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sst_ipre[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->li_spost[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sst_ipost[i] = arbitrary(); }
  record->liquid_instrument = arbitrary();
  record->admission_requested_by_issuer = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->modality_mask_b_4[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->security_description[i] = arbitrary(); }
  record->trading_obligation = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->sec_description[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->underlying_asset[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->security_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = arbitrary(); }
  record->opt_attribute = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->unit_of_measure[i] = arbitrary(); }
  record->settl_method = arbitrary();
  record->exercise_style = arbitrary();
  record->put_or_call = arbitrary();
  record->flexible_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = arbitrary(); }
  record->number_of_decimals = arbitrary();
  record->order_number_of_decimals = arbitrary();
  record->adjustments_rule = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->maximum_order_size[i] = arbitrary(); }
  record->self_match_prevention = arbitrary();
  record->commodity_derivative_indicator = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->stock_when_underlying_is_dividend[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->quoted_currency[i] = arbitrary(); }
  record->maturity_month_year_increment_units = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->start_maturity_month_year[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_maturity_month_year[i] = arbitrary(); }
  record->maturity_month_year_increment = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->underlying_security_issuer_lei[i] = arbitrary(); }
  record->x_rolling_closing_type = arbitrary();
  record->x_rolling_reference_buyer_rate = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->x_rolling_buyer_markup[i] = arbitrary(); }
  record->x_rolling_reference_seller_rate = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->x_rolling_seller_markup[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->x_rolling_dividend_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->x_rolling_dividend_pay_date_diff[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_1[i] = arbitrary(); }
  record->leg_side_1 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_1[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_2[i] = arbitrary(); }
  record->leg_side_2 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_3[i] = arbitrary(); }
  record->leg_side_3 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_3[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_4[i] = arbitrary(); }
  record->leg_side_4 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_4[i] = arbitrary(); }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_5[i] = arbitrary(); }
  record->leg_side_5 = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->leg_price_5[i] = arbitrary(); }
}

/* Security List Update Report Message to the wire: 713 bytes from at, returning where the next byte goes */
static size_t encode_security_list_update_report_message(const SecurityListUpdateReportMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->symbol_isin[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->fisn[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->issuer_lei[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->family_code[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->cfi_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->maturity_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->issue_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contract_multiplier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->li_spre[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sst_ipre[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->li_spost[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sst_ipost[i]; }
  wire[at++] = record->liquid_instrument;
  wire[at++] = record->admission_requested_by_issuer;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_trade_vol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->round_lot[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->modality_mask_b_4[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->security_description[i]; }
  wire[at++] = record->trading_obligation;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->sec_description[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->underlying_asset[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->security_sub_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_month_year[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_value[i]; }
  wire[at++] = record->opt_attribute;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->min_price_increment[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->unit_of_measure[i]; }
  wire[at++] = record->settl_method;
  wire[at++] = record->exercise_style;
  wire[at++] = record->put_or_call;
  wire[at++] = record->flexible_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_day[i]; }
  wire[at++] = record->number_of_decimals;
  wire[at++] = record->order_number_of_decimals;
  wire[at++] = record->adjustments_rule;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maximum_order_size[i]; }
  wire[at++] = record->self_match_prevention;
  wire[at++] = record->commodity_derivative_indicator;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->stock_when_underlying_is_dividend[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->base_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sub_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->further_sub_product[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->base_currency[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->quoted_currency[i]; }
  wire[at++] = record->maturity_month_year_increment_units;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_maturity_month_year[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_maturity_month_year[i]; }
  wire[at++] = record->maturity_month_year_increment;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_currency[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->underlying_security_issuer_lei[i]; }
  wire[at++] = record->x_rolling_closing_type;
  wire[at++] = record->x_rolling_reference_buyer_rate;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->x_rolling_buyer_markup[i]; }
  wire[at++] = record->x_rolling_reference_seller_rate;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->x_rolling_seller_markup[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->x_rolling_dividend_percentage[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->x_rolling_dividend_pay_date_diff[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_1[i]; }
  wire[at++] = record->leg_side_1;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_1[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_2[i]; }
  wire[at++] = record->leg_side_2;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_2[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_3[i]; }
  wire[at++] = record->leg_side_3;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_3[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_4[i]; }
  wire[at++] = record->leg_side_4;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_4[i]; }
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->leg_symbol_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leg_ratio_qty_5[i]; }
  wire[at++] = record->leg_side_5;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->leg_price_5[i]; }

  return at;
}

/* Security List Update Report Message off the wire: 713 bytes from at, returning where the next byte lies */
static size_t decode_security_list_update_report_message(SecurityListUpdateReportMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->symbol_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->fisn[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->issuer_lei[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->family_code[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->cfi_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->maturity_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->issue_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->contract_multiplier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->li_spre[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sst_ipre[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->li_spost[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sst_ipost[i] = wire[at++]; }
  record->liquid_instrument = wire[at++];
  record->admission_requested_by_issuer = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->min_trade_vol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->round_lot[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->modality_mask_b_4[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->security_description[i] = wire[at++]; }
  record->trading_obligation = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->sec_description[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->underlying_asset[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->security_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = wire[at++]; }
  record->opt_attribute = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->min_price_increment[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->unit_of_measure[i] = wire[at++]; }
  record->settl_method = wire[at++];
  record->exercise_style = wire[at++];
  record->put_or_call = wire[at++];
  record->flexible_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = wire[at++]; }
  record->number_of_decimals = wire[at++];
  record->order_number_of_decimals = wire[at++];
  record->adjustments_rule = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->maximum_order_size[i] = wire[at++]; }
  record->self_match_prevention = wire[at++];
  record->commodity_derivative_indicator = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->stock_when_underlying_is_dividend[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->base_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->quoted_currency[i] = wire[at++]; }
  record->maturity_month_year_increment_units = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->start_maturity_month_year[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_maturity_month_year[i] = wire[at++]; }
  record->maturity_month_year_increment = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->underlying_security_issuer_lei[i] = wire[at++]; }
  record->x_rolling_closing_type = wire[at++];
  record->x_rolling_reference_buyer_rate = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->x_rolling_buyer_markup[i] = wire[at++]; }
  record->x_rolling_reference_seller_rate = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->x_rolling_seller_markup[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->x_rolling_dividend_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->x_rolling_dividend_pay_date_diff[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_1[i] = wire[at++]; }
  record->leg_side_1 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_1[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_2[i] = wire[at++]; }
  record->leg_side_2 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_3[i] = wire[at++]; }
  record->leg_side_3 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_3[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_4[i] = wire[at++]; }
  record->leg_side_4 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_4[i] = wire[at++]; }
  for (size_t i = 0; i < 22; i++) { record->leg_symbol_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leg_ratio_qty_5[i] = wire[at++]; }
  record->leg_side_5 = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->leg_price_5[i] = wire[at++]; }

  return at;
}

/* what was read of Security List Update Report Message is what was written, byte for byte */
static void equal_security_list_update_report_message(const SecurityListUpdateReportMessage *read, const SecurityListUpdateReportMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_id[i] == written->market_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->symbol_isin[i] == written->symbol_isin[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->fisn[i] == written->fisn[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->issuer_lei[i] == written->issuer_lei[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group[i] == written->security_group[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->family_code[i] == written->family_code[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->cfi_code[i] == written->cfi_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_type[i] == written->security_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->maturity_date[i] == written->maturity_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->issue_date[i] == written->issue_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->contract_multiplier[i] == written->contract_multiplier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->li_spre[i] == written->li_spre[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sst_ipre[i] == written->sst_ipre[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->li_spost[i] == written->li_spost[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sst_ipost[i] == written->sst_ipost[i]); }
  assert(read->liquid_instrument == written->liquid_instrument);
  assert(read->admission_requested_by_issuer == written->admission_requested_by_issuer);
  for (size_t i = 0; i < 4; i++) { assert(read->min_trade_vol[i] == written->min_trade_vol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->round_lot[i] == written->round_lot[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->currency[i] == written->currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->modality_mask_b_4[i] == written->modality_mask_b_4[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->security_description[i] == written->security_description[i]); }
  assert(read->trading_obligation == written->trading_obligation);
  for (size_t i = 0; i < 20; i++) { assert(read->sec_description[i] == written->sec_description[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->underlying_asset[i] == written->underlying_asset[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->security_sub_type[i] == written->security_sub_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_value[i] == written->strike_value[i]); }
  assert(read->opt_attribute == written->opt_attribute);
  for (size_t i = 0; i < 8; i++) { assert(read->min_price_increment[i] == written->min_price_increment[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->unit_of_measure[i] == written->unit_of_measure[i]); }
  assert(read->settl_method == written->settl_method);
  assert(read->exercise_style == written->exercise_style);
  assert(read->put_or_call == written->put_or_call);
  assert(read->flexible_indicator == written->flexible_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_day[i] == written->last_trading_day[i]); }
  assert(read->number_of_decimals == written->number_of_decimals);
  assert(read->order_number_of_decimals == written->order_number_of_decimals);
  assert(read->adjustments_rule == written->adjustments_rule);
  for (size_t i = 0; i < 8; i++) { assert(read->maximum_order_size[i] == written->maximum_order_size[i]); }
  assert(read->self_match_prevention == written->self_match_prevention);
  assert(read->commodity_derivative_indicator == written->commodity_derivative_indicator);
  for (size_t i = 0; i < 22; i++) { assert(read->stock_when_underlying_is_dividend[i] == written->stock_when_underlying_is_dividend[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->base_product[i] == written->base_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sub_product[i] == written->sub_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->further_sub_product[i] == written->further_sub_product[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->base_currency[i] == written->base_currency[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->quoted_currency[i] == written->quoted_currency[i]); }
  assert(read->maturity_month_year_increment_units == written->maturity_month_year_increment_units);
  for (size_t i = 0; i < 8; i++) { assert(read->start_maturity_month_year[i] == written->start_maturity_month_year[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_maturity_month_year[i] == written->end_maturity_month_year[i]); }
  assert(read->maturity_month_year_increment == written->maturity_month_year_increment);
  for (size_t i = 0; i < 22; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_isin[i] == written->underlying_isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_currency[i] == written->underlying_currency[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->underlying_security_issuer_lei[i] == written->underlying_security_issuer_lei[i]); }
  assert(read->x_rolling_closing_type == written->x_rolling_closing_type);
  assert(read->x_rolling_reference_buyer_rate == written->x_rolling_reference_buyer_rate);
  for (size_t i = 0; i < 8; i++) { assert(read->x_rolling_buyer_markup[i] == written->x_rolling_buyer_markup[i]); }
  assert(read->x_rolling_reference_seller_rate == written->x_rolling_reference_seller_rate);
  for (size_t i = 0; i < 8; i++) { assert(read->x_rolling_seller_markup[i] == written->x_rolling_seller_markup[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->x_rolling_dividend_percentage[i] == written->x_rolling_dividend_percentage[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->x_rolling_dividend_pay_date_diff[i] == written->x_rolling_dividend_pay_date_diff[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_1[i] == written->leg_symbol_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_1[i] == written->leg_ratio_qty_1[i]); }
  assert(read->leg_side_1 == written->leg_side_1);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_1[i] == written->leg_price_1[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_2[i] == written->leg_symbol_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_2[i] == written->leg_ratio_qty_2[i]); }
  assert(read->leg_side_2 == written->leg_side_2);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_2[i] == written->leg_price_2[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_3[i] == written->leg_symbol_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_3[i] == written->leg_ratio_qty_3[i]); }
  assert(read->leg_side_3 == written->leg_side_3);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_3[i] == written->leg_price_3[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_4[i] == written->leg_symbol_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_4[i] == written->leg_ratio_qty_4[i]); }
  assert(read->leg_side_4 == written->leg_side_4);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_4[i] == written->leg_price_4[i]); }
  for (size_t i = 0; i < 22; i++) { assert(read->leg_symbol_5[i] == written->leg_symbol_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leg_ratio_qty_5[i] == written->leg_ratio_qty_5[i]); }
  assert(read->leg_side_5 == written->leg_side_5);
  for (size_t i = 0; i < 8; i++) { assert(read->leg_price_5[i] == written->leg_price_5[i]); }
}

/* Security List Update Report Message: written and read back, then read and written back */
static void check_security_list_update_report_message(void) {
  SecurityListUpdateReportMessage sent;
  SecurityListUpdateReportMessage got;
  uint8_t wire[713];
  uint8_t again[713];

  any_security_list_update_report_message(&sent);
  assert(encode_security_list_update_report_message(&sent, wire, 0) == 713);
  assert(decode_security_list_update_report_message(&got, wire, 0) == 713);
  equal_security_list_update_report_message(&got, &sent);

  for (size_t i = 0; i < 713; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_update_report_message(&got, wire, 0) == 713);
  assert(encode_security_list_update_report_message(&got, again, 0) == 713);
  for (size_t i = 0; i < 713; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 34 bytes --------------------------------------- */

/* Message sent by the server to inform on the status of one security */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t security_trading_status;       /* byte 16 */
  uint8_t non_availability_reason;       /* byte 17 */
  uint8_t high_limit_price[8];           /* bytes 18 to 25 */
  uint8_t low_limit_price[8];            /* bytes 26 to 33 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  record->security_trading_status = arbitrary();
  record->non_availability_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = arbitrary(); }
}

/* Security Status Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  wire[at++] = record->security_trading_status;
  wire[at++] = record->non_availability_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_limit_price[i]; }

  return at;
}

/* Security Status Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  record->security_trading_status = wire[at++];
  record->non_availability_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = wire[at++]; }

  return at;
}

/* what was read of Security Status Message is what was written, byte for byte */
static void equal_security_status_message(const SecurityStatusMessage *read, const SecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  assert(read->security_trading_status == written->security_trading_status);
  assert(read->non_availability_reason == written->non_availability_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->high_limit_price[i] == written->high_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_limit_price[i] == written->low_limit_price[i]); }
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 34);
  assert(decode_security_status_message(&got, wire, 0) == 34);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 34);
  assert(encode_security_status_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Family Status Message: 21 bytes ----------------------------------------- */

/* Message sent by the server in the Derivatives environment to inform about the status a Family of products */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_group[2];             /* bytes 4 to 5 */
  uint8_t family_code[5];                /* bytes 6 to 10 */
  uint8_t transaction_date_and_time[8];  /* bytes 11 to 18 */
  uint8_t security_trading_status;       /* byte 19 */
  uint8_t non_availability_reason;       /* byte 20 */
} FamilyStatusMessage;

/* any Family Status Message at all: every byte one the checker chooses */
static void any_family_status_message(FamilyStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->family_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  record->security_trading_status = arbitrary();
  record->non_availability_reason = arbitrary();
}

/* Family Status Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_family_status_message(const FamilyStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->family_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  wire[at++] = record->security_trading_status;
  wire[at++] = record->non_availability_reason;

  return at;
}

/* Family Status Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_family_status_message(FamilyStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->family_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  record->security_trading_status = wire[at++];
  record->non_availability_reason = wire[at++];

  return at;
}

/* what was read of Family Status Message is what was written, byte for byte */
static void equal_family_status_message(const FamilyStatusMessage *read, const FamilyStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group[i] == written->security_group[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->family_code[i] == written->family_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  assert(read->security_trading_status == written->security_trading_status);
  assert(read->non_availability_reason == written->non_availability_reason);
}

/* Family Status Message: written and read back, then read and written back */
static void check_family_status_message(void) {
  FamilyStatusMessage sent;
  FamilyStatusMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_family_status_message(&sent);
  assert(encode_family_status_message(&sent, wire, 0) == 21);
  assert(decode_family_status_message(&got, wire, 0) == 21);
  equal_family_status_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_family_status_message(&got, wire, 0) == 21);
  assert(encode_family_status_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Market Post Transparency Information Top Of Book Message: 54 bytes ---- */

/* Used by the server to communicate trade information related to trades resulting from order matching in channels C/D and E/F. It is also used in channels A/B when the trade is the result of order matching at the end of an auction period (where only top-of-book information is shown) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t market_segment_id[4];          /* bytes 16 to 19 */
  uint8_t trading_session_id;            /* byte 20 */
  uint8_t trd_match_id[4];               /* bytes 21 to 24 */
  uint8_t trade_type;                    /* byte 25 */
  uint8_t last_px[8];                    /* bytes 26 to 33 */
  uint8_t last_qty[4];                   /* bytes 34 to 37 */
  uint8_t gross_trade_amt[8];            /* bytes 38 to 45 */
  uint8_t designation;                   /* byte 46 */
  uint8_t market_mechanism;              /* byte 47 */
  uint8_t algo_flag;                     /* byte 48 */
  uint8_t transaction_category;          /* byte 49 */
  uint8_t strategy_trd_match_id[4];      /* bytes 50 to 53 */
} TradeMarketPostTransparencyInformationTopOfBookMessage;

/* any Trade Market Post Transparency Information Top Of Book Message at all: every byte one the checker chooses */
static void any_trade_market_post_transparency_information_top_of_book_message(TradeMarketPostTransparencyInformationTopOfBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = arbitrary(); }
  record->designation = arbitrary();
  record->market_mechanism = arbitrary();
  record->algo_flag = arbitrary();
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = arbitrary(); }
}

/* Trade Market Post Transparency Information Top Of Book Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_trade_market_post_transparency_information_top_of_book_message(const TradeMarketPostTransparencyInformationTopOfBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trd_match_id[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gross_trade_amt[i]; }
  wire[at++] = record->designation;
  wire[at++] = record->market_mechanism;
  wire[at++] = record->algo_flag;
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_trd_match_id[i]; }

  return at;
}

/* Trade Market Post Transparency Information Top Of Book Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_trade_market_post_transparency_information_top_of_book_message(TradeMarketPostTransparencyInformationTopOfBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = wire[at++]; }
  record->designation = wire[at++];
  record->market_mechanism = wire[at++];
  record->algo_flag = wire[at++];
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Market Post Transparency Information Top Of Book Message is what was written, byte for byte */
static void equal_trade_market_post_transparency_information_top_of_book_message(const TradeMarketPostTransparencyInformationTopOfBookMessage *read, const TradeMarketPostTransparencyInformationTopOfBookMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 4; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->gross_trade_amt[i] == written->gross_trade_amt[i]); }
  assert(read->designation == written->designation);
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->algo_flag == written->algo_flag);
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_trd_match_id[i] == written->strategy_trd_match_id[i]); }
}

/* Trade Market Post Transparency Information Top Of Book Message: written and read back, then read and written back */
static void check_trade_market_post_transparency_information_top_of_book_message(void) {
  TradeMarketPostTransparencyInformationTopOfBookMessage sent;
  TradeMarketPostTransparencyInformationTopOfBookMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_trade_market_post_transparency_information_top_of_book_message(&sent);
  assert(encode_trade_market_post_transparency_information_top_of_book_message(&sent, wire, 0) == 54);
  assert(decode_trade_market_post_transparency_information_top_of_book_message(&got, wire, 0) == 54);
  equal_trade_market_post_transparency_information_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_market_post_transparency_information_top_of_book_message(&got, wire, 0) == 54);
  assert(encode_trade_market_post_transparency_information_top_of_book_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation Message: 89 bytes ----------------- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. In this message, all fields with the suffix 2 refer to the sell order, and the ones without the suffix refer either to both legs or the buy order */
typedef struct {
  uint8_t sequence_number[4];              /* bytes 0 to 3 */
  uint8_t security_code[4];                /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];    /* bytes 8 to 15 */
  uint8_t market_segment_id[4];            /* bytes 16 to 19 */
  uint8_t trading_session_id;              /* byte 20 */
  uint8_t trd_match_id[4];                 /* bytes 21 to 24 */
  uint8_t trade_type;                      /* byte 25 */
  uint8_t last_px[8];                      /* bytes 26 to 33 */
  uint8_t last_qty[4];                     /* bytes 34 to 37 */
  uint8_t gross_trade_amt[8];              /* bytes 38 to 45 */
  uint8_t designation;                     /* byte 46 */
  uint8_t market_mechanism;                /* byte 47 */
  uint8_t algo_flag;                       /* byte 48 */
  uint8_t transaction_category;            /* byte 49 */
  uint8_t strategy_trd_match_id[4];        /* bytes 50 to 53 */
  uint8_t last_change_flag;                /* byte 54 */
  uint8_t benc_rfpt_flag;                  /* byte 55 */
  uint8_t trade_price_condition;           /* byte 56 */
  uint8_t pre_trade_transparency_waiver;   /* byte 57 */
  uint8_t deferral_waiver;                 /* byte 58 */
  uint8_t post_deferral_publication_type;  /* byte 59 */
  uint8_t publish_date_and_time[8];        /* bytes 60 to 67 */
  uint8_t trade_date[8];                   /* bytes 68 to 75 */
  uint8_t trade_session_date[4];           /* bytes 76 to 79 */
  uint8_t amended_trade_type;              /* byte 80 */
  uint8_t exec_ref_id[4];                  /* bytes 81 to 84 */
  uint8_t amended_trade_date[4];           /* bytes 85 to 88 */
} TradeTradeAmendmentOrCancellationMessage;

/* any Trade Trade Amendment Or Cancellation Message at all: every byte one the checker chooses */
static void any_trade_trade_amendment_or_cancellation_message(TradeTradeAmendmentOrCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = arbitrary(); }
  record->trade_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = arbitrary(); }
  record->designation = arbitrary();
  record->market_mechanism = arbitrary();
  record->algo_flag = arbitrary();
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = arbitrary(); }
  record->last_change_flag = arbitrary();
  record->benc_rfpt_flag = arbitrary();
  record->trade_price_condition = arbitrary();
  record->pre_trade_transparency_waiver = arbitrary();
  record->deferral_waiver = arbitrary();
  record->post_deferral_publication_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = arbitrary(); }
  record->amended_trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation Message to the wire: 89 bytes from at, returning where the next byte goes */
static size_t encode_trade_trade_amendment_or_cancellation_message(const TradeTradeAmendmentOrCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_segment_id[i]; }
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trd_match_id[i]; }
  wire[at++] = record->trade_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_px[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->gross_trade_amt[i]; }
  wire[at++] = record->designation;
  wire[at++] = record->market_mechanism;
  wire[at++] = record->algo_flag;
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_trd_match_id[i]; }
  wire[at++] = record->last_change_flag;
  wire[at++] = record->benc_rfpt_flag;
  wire[at++] = record->trade_price_condition;
  wire[at++] = record->pre_trade_transparency_waiver;
  wire[at++] = record->deferral_waiver;
  wire[at++] = record->post_deferral_publication_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->publish_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_session_date[i]; }
  wire[at++] = record->amended_trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amended_trade_date[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation Message off the wire: 89 bytes from at, returning where the next byte lies */
static size_t decode_trade_trade_amendment_or_cancellation_message(TradeTradeAmendmentOrCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_segment_id[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trd_match_id[i] = wire[at++]; }
  record->trade_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_px[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->gross_trade_amt[i] = wire[at++]; }
  record->designation = wire[at++];
  record->market_mechanism = wire[at++];
  record->algo_flag = wire[at++];
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = wire[at++]; }
  record->last_change_flag = wire[at++];
  record->benc_rfpt_flag = wire[at++];
  record->trade_price_condition = wire[at++];
  record->pre_trade_transparency_waiver = wire[at++];
  record->deferral_waiver = wire[at++];
  record->post_deferral_publication_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = wire[at++]; }
  record->amended_trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Trade Amendment Or Cancellation Message is what was written, byte for byte */
static void equal_trade_trade_amendment_or_cancellation_message(const TradeTradeAmendmentOrCancellationMessage *read, const TradeTradeAmendmentOrCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_segment_id[i] == written->market_segment_id[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 4; i++) { assert(read->trd_match_id[i] == written->trd_match_id[i]); }
  assert(read->trade_type == written->trade_type);
  for (size_t i = 0; i < 8; i++) { assert(read->last_px[i] == written->last_px[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_qty[i] == written->last_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->gross_trade_amt[i] == written->gross_trade_amt[i]); }
  assert(read->designation == written->designation);
  assert(read->market_mechanism == written->market_mechanism);
  assert(read->algo_flag == written->algo_flag);
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_trd_match_id[i] == written->strategy_trd_match_id[i]); }
  assert(read->last_change_flag == written->last_change_flag);
  assert(read->benc_rfpt_flag == written->benc_rfpt_flag);
  assert(read->trade_price_condition == written->trade_price_condition);
  assert(read->pre_trade_transparency_waiver == written->pre_trade_transparency_waiver);
  assert(read->deferral_waiver == written->deferral_waiver);
  assert(read->post_deferral_publication_type == written->post_deferral_publication_type);
  for (size_t i = 0; i < 8; i++) { assert(read->publish_date_and_time[i] == written->publish_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_session_date[i] == written->trade_session_date[i]); }
  assert(read->amended_trade_type == written->amended_trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amended_trade_date[i] == written->amended_trade_date[i]); }
}

/* Trade Trade Amendment Or Cancellation Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation_message(void) {
  TradeTradeAmendmentOrCancellationMessage sent;
  TradeTradeAmendmentOrCancellationMessage got;
  uint8_t wire[89];
  uint8_t again[89];

  any_trade_trade_amendment_or_cancellation_message(&sent);
  assert(encode_trade_trade_amendment_or_cancellation_message(&sent, wire, 0) == 89);
  assert(decode_trade_trade_amendment_or_cancellation_message(&got, wire, 0) == 89);
  equal_trade_trade_amendment_or_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 89; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation_message(&got, wire, 0) == 89);
  assert(encode_trade_trade_amendment_or_cancellation_message(&got, again, 0) == 89);
  for (size_t i = 0; i < 89; i++) { assert(again[i] == wire[i]); }
}

/* ---- Indication Of Interest Message: 36 bytes -------------------------------- */

/* Used by the Server to notify an indication of interest on a specific instrument. This functionality is available in Fixed Income and Derivatives */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t ioiid[4];                      /* bytes 16 to 19 */
  uint8_t ioi_trans_type;                /* byte 20 */
  uint8_t side;                          /* byte 21 */
  uint8_t ioi_qty[4];                    /* bytes 22 to 25 */
  uint8_t ioi_price[8];                  /* bytes 26 to 33 */
  uint8_t ioi_qlty_ind;                  /* byte 34 */
  uint8_t trading_session_id;            /* byte 35 */
} IndicationOfInterestMessage;

/* any Indication Of Interest Message at all: every byte one the checker chooses */
static void any_indication_of_interest_message(IndicationOfInterestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ioiid[i] = arbitrary(); }
  record->ioi_trans_type = arbitrary();
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->ioi_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ioi_price[i] = arbitrary(); }
  record->ioi_qlty_ind = arbitrary();
  record->trading_session_id = arbitrary();
}

/* Indication Of Interest Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_indication_of_interest_message(const IndicationOfInterestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ioiid[i]; }
  wire[at++] = record->ioi_trans_type;
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ioi_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ioi_price[i]; }
  wire[at++] = record->ioi_qlty_ind;
  wire[at++] = record->trading_session_id;

  return at;
}

/* Indication Of Interest Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_indication_of_interest_message(IndicationOfInterestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ioiid[i] = wire[at++]; }
  record->ioi_trans_type = wire[at++];
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->ioi_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ioi_price[i] = wire[at++]; }
  record->ioi_qlty_ind = wire[at++];
  record->trading_session_id = wire[at++];

  return at;
}

/* what was read of Indication Of Interest Message is what was written, byte for byte */
static void equal_indication_of_interest_message(const IndicationOfInterestMessage *read, const IndicationOfInterestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ioiid[i] == written->ioiid[i]); }
  assert(read->ioi_trans_type == written->ioi_trans_type);
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->ioi_qty[i] == written->ioi_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ioi_price[i] == written->ioi_price[i]); }
  assert(read->ioi_qlty_ind == written->ioi_qlty_ind);
  assert(read->trading_session_id == written->trading_session_id);
}

/* Indication Of Interest Message: written and read back, then read and written back */
static void check_indication_of_interest_message(void) {
  IndicationOfInterestMessage sent;
  IndicationOfInterestMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_indication_of_interest_message(&sent);
  assert(encode_indication_of_interest_message(&sent, wire, 0) == 36);
  assert(decode_indication_of_interest_message(&got, wire, 0) == 36);
  equal_indication_of_interest_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_indication_of_interest_message(&got, wire, 0) == 36);
  assert(encode_indication_of_interest_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Rfq Market Pre Transparency Information Message: 189 bytes -------------- */

/* Used by the server to communicate price information about RFQs. The contents of the RFQID field match those of the field IOIID in the corresponding Indication of Interest message */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t rfqid[4];                      /* bytes 4 to 7 */
  uint8_t trading_session_id;            /* byte 8 */
  uint8_t security_code[4];              /* bytes 9 to 12 */
  uint8_t transaction_date_and_time[8];  /* bytes 13 to 20 */
  uint8_t mid_buy_price[8];              /* bytes 21 to 28 */
  uint8_t mid_buy_volume[4];             /* bytes 29 to 32 */
  uint8_t buy_rf_qs_number[2];           /* bytes 33 to 34 */
  uint8_t mid_sell_price[8];             /* bytes 35 to 42 */
  uint8_t mid_sell_volume[4];            /* bytes 43 to 46 */
  uint8_t sell_rf_qs_number[2];          /* bytes 47 to 48 */
  uint8_t bid_orders_1[2];               /* bytes 49 to 50 */
  uint8_t bid_size_1[4];                 /* bytes 51 to 54 */
  uint8_t bid_px_1[8];                   /* bytes 55 to 62 */
  uint8_t ask_orders_1[2];               /* bytes 63 to 64 */
  uint8_t ask_size_1[4];                 /* bytes 65 to 68 */
  uint8_t ask_px_1[8];                   /* bytes 69 to 76 */
  uint8_t bid_orders_2[2];               /* bytes 77 to 78 */
  uint8_t bid_size_2[4];                 /* bytes 79 to 82 */
  uint8_t bid_px_2[8];                   /* bytes 83 to 90 */
  uint8_t ask_orders_2[2];               /* bytes 91 to 92 */
  uint8_t ask_size_2[4];                 /* bytes 93 to 96 */
  uint8_t ask_px_2[8];                   /* bytes 97 to 104 */
  uint8_t bid_orders_3[2];               /* bytes 105 to 106 */
  uint8_t bid_size_3[4];                 /* bytes 107 to 110 */
  uint8_t bid_px_3[8];                   /* bytes 111 to 118 */
  uint8_t ask_orders_3[2];               /* bytes 119 to 120 */
  uint8_t ask_size_3[4];                 /* bytes 121 to 124 */
  uint8_t ask_px_3[8];                   /* bytes 125 to 132 */
  uint8_t bid_orders_4[2];               /* bytes 133 to 134 */
  uint8_t bid_size_4[4];                 /* bytes 135 to 138 */
  uint8_t bid_px_4[8];                   /* bytes 139 to 146 */
  uint8_t ask_orders_4[2];               /* bytes 147 to 148 */
  uint8_t ask_size_4[4];                 /* bytes 149 to 152 */
  uint8_t ask_px_4[8];                   /* bytes 153 to 160 */
  uint8_t bid_orders_5[2];               /* bytes 161 to 162 */
  uint8_t bid_size_5[4];                 /* bytes 163 to 166 */
  uint8_t bid_px_5[8];                   /* bytes 167 to 174 */
  uint8_t ask_orders_5[2];               /* bytes 175 to 176 */
  uint8_t ask_size_5[4];                 /* bytes 177 to 180 */
  uint8_t ask_px_5[8];                   /* bytes 181 to 188 */
} RfqMarketPreTransparencyInformationMessage;

/* any Rfq Market Pre Transparency Information Message at all: every byte one the checker chooses */
static void any_rfq_market_pre_transparency_information_message(RfqMarketPreTransparencyInformationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rfqid[i] = arbitrary(); }
  record->trading_session_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_buy_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mid_buy_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->buy_rf_qs_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mid_sell_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mid_sell_volume[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->sell_rf_qs_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_3[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_3[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_4[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_4[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_5[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_5[i] = arbitrary(); }
}

/* Rfq Market Pre Transparency Information Message to the wire: 189 bytes from at, returning where the next byte goes */
static size_t encode_rfq_market_pre_transparency_information_message(const RfqMarketPreTransparencyInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rfqid[i]; }
  wire[at++] = record->trading_session_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_buy_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mid_buy_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->buy_rf_qs_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mid_sell_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mid_sell_volume[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sell_rf_qs_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_3[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_3[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_4[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_4[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_5[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_5[i]; }

  return at;
}

/* Rfq Market Pre Transparency Information Message off the wire: 189 bytes from at, returning where the next byte lies */
static size_t decode_rfq_market_pre_transparency_information_message(RfqMarketPreTransparencyInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rfqid[i] = wire[at++]; }
  record->trading_session_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mid_buy_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mid_buy_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->buy_rf_qs_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mid_sell_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mid_sell_volume[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->sell_rf_qs_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_3[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_3[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_4[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_4[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_5[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ask_orders_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_5[i] = wire[at++]; }

  return at;
}

/* what was read of Rfq Market Pre Transparency Information Message is what was written, byte for byte */
static void equal_rfq_market_pre_transparency_information_message(const RfqMarketPreTransparencyInformationMessage *read, const RfqMarketPreTransparencyInformationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rfqid[i] == written->rfqid[i]); }
  assert(read->trading_session_id == written->trading_session_id);
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_buy_price[i] == written->mid_buy_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mid_buy_volume[i] == written->mid_buy_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->buy_rf_qs_number[i] == written->buy_rf_qs_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mid_sell_price[i] == written->mid_sell_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mid_sell_volume[i] == written->mid_sell_volume[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->sell_rf_qs_number[i] == written->sell_rf_qs_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_1[i] == written->bid_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_1[i] == written->bid_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_1[i] == written->ask_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_1[i] == written->ask_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_2[i] == written->bid_orders_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_2[i] == written->bid_size_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_2[i] == written->bid_px_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_2[i] == written->ask_orders_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_2[i] == written->ask_size_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_2[i] == written->ask_px_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_3[i] == written->bid_orders_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_3[i] == written->bid_size_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_3[i] == written->bid_px_3[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_3[i] == written->ask_orders_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_3[i] == written->ask_size_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_3[i] == written->ask_px_3[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_4[i] == written->bid_orders_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_4[i] == written->bid_size_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_4[i] == written->bid_px_4[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_4[i] == written->ask_orders_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_4[i] == written->ask_size_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_4[i] == written->ask_px_4[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_5[i] == written->bid_orders_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_5[i] == written->bid_size_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_5[i] == written->bid_px_5[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_5[i] == written->ask_orders_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_5[i] == written->ask_size_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_5[i] == written->ask_px_5[i]); }
}

/* Rfq Market Pre Transparency Information Message: written and read back, then read and written back */
static void check_rfq_market_pre_transparency_information_message(void) {
  RfqMarketPreTransparencyInformationMessage sent;
  RfqMarketPreTransparencyInformationMessage got;
  uint8_t wire[189];
  uint8_t again[189];

  any_rfq_market_pre_transparency_information_message(&sent);
  assert(encode_rfq_market_pre_transparency_information_message(&sent, wire, 0) == 189);
  assert(decode_rfq_market_pre_transparency_information_message(&got, wire, 0) == 189);
  equal_rfq_market_pre_transparency_information_message(&got, &sent);

  for (size_t i = 0; i < 189; i++) { wire[i] = arbitrary(); }
  assert(decode_rfq_market_pre_transparency_information_message(&got, wire, 0) == 189);
  assert(encode_rfq_market_pre_transparency_information_message(&got, again, 0) == 189);
  for (size_t i = 0; i < 189; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Book Message: 46 bytes ------------------------------------------- */

/* Used by the UDP Servers to communicate Top-of-book price information during auctions. When there is an indicative match price, the fields BidPx1 and AskPx1 will have the same value */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t bid_orders_1[2];               /* bytes 16 to 17 */
  uint8_t bid_size_1[4];                 /* bytes 18 to 21 */
  uint8_t bid_px_1[8];                   /* bytes 22 to 29 */
  uint8_t retail_cl_bid_flag_1;          /* byte 30 */
  uint8_t ask_orders_1[2];               /* bytes 31 to 32 */
  uint8_t ask_size_1[4];                 /* bytes 33 to 36 */
  uint8_t ask_px_1[8];                   /* bytes 37 to 44 */
  uint8_t retail_cl_ask_flag_1;          /* byte 45 */
} TopOfBookMessage;

/* any Top Of Book Message at all: every byte one the checker chooses */
static void any_top_of_book_message(TopOfBookMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  record->retail_cl_bid_flag_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
  record->retail_cl_ask_flag_1 = arbitrary();
}

/* Top Of Book Message to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_top_of_book_message(const TopOfBookMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  wire[at++] = record->retail_cl_bid_flag_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }
  wire[at++] = record->retail_cl_ask_flag_1;

  return at;
}

/* Top Of Book Message off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_top_of_book_message(TopOfBookMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  record->retail_cl_bid_flag_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }
  record->retail_cl_ask_flag_1 = wire[at++];

  return at;
}

/* what was read of Top Of Book Message is what was written, byte for byte */
static void equal_top_of_book_message(const TopOfBookMessage *read, const TopOfBookMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_1[i] == written->bid_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_1[i] == written->bid_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  assert(read->retail_cl_bid_flag_1 == written->retail_cl_bid_flag_1);
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_1[i] == written->ask_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_1[i] == written->ask_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
  assert(read->retail_cl_ask_flag_1 == written->retail_cl_ask_flag_1);
}

/* Top Of Book Message: written and read back, then read and written back */
static void check_top_of_book_message(void) {
  TopOfBookMessage sent;
  TopOfBookMessage got;
  uint8_t wire[46];
  uint8_t again[46];

  any_top_of_book_message(&sent);
  assert(encode_top_of_book_message(&sent, wire, 0) == 46);
  assert(decode_top_of_book_message(&got, wire, 0) == 46);
  equal_top_of_book_message(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_book_message(&got, wire, 0) == 46);
  assert(encode_top_of_book_message(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Top Of Book 5 Levels Message: 166 bytes --------------------------------- */

/* Used by the UDP 5 level top-of-book Servers to communicate Top-of-book price information during open market. During auctions, only the first level is shown, and therefore this message is not published, and the message Top-of-book (Msg Type = 0x82) is used instead */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t bid_orders_1[2];               /* bytes 16 to 17 */
  uint8_t bid_size_1[4];                 /* bytes 18 to 21 */
  uint8_t bid_px_1[8];                   /* bytes 22 to 29 */
  uint8_t retail_cl_bid_flag_1;          /* byte 30 */
  uint8_t ask_orders_1[2];               /* bytes 31 to 32 */
  uint8_t ask_size_1[4];                 /* bytes 33 to 36 */
  uint8_t ask_px_1[8];                   /* bytes 37 to 44 */
  uint8_t retail_cl_ask_flag_1;          /* byte 45 */
  uint8_t bid_orders_2[2];               /* bytes 46 to 47 */
  uint8_t bid_size_2[4];                 /* bytes 48 to 51 */
  uint8_t bid_px_2[8];                   /* bytes 52 to 59 */
  uint8_t retail_cl_bid_flag_2;          /* byte 60 */
  uint8_t ask_orders_2[2];               /* bytes 61 to 62 */
  uint8_t ask_size_2[4];                 /* bytes 63 to 66 */
  uint8_t ask_px_2[8];                   /* bytes 67 to 74 */
  uint8_t retail_cl_ask_flag_2;          /* byte 75 */
  uint8_t bid_orders_3[2];               /* bytes 76 to 77 */
  uint8_t bid_size_3[4];                 /* bytes 78 to 81 */
  uint8_t bid_px_3[8];                   /* bytes 82 to 89 */
  uint8_t retail_cl_bid_flag_3;          /* byte 90 */
  uint8_t ask_orders_3[2];               /* bytes 91 to 92 */
  uint8_t ask_size_3[4];                 /* bytes 93 to 96 */
  uint8_t ask_px_3[8];                   /* bytes 97 to 104 */
  uint8_t retail_cl_ask_flag_3;          /* byte 105 */
  uint8_t bid_orders_4[2];               /* bytes 106 to 107 */
  uint8_t bid_size_4[4];                 /* bytes 108 to 111 */
  uint8_t bid_px_4[8];                   /* bytes 112 to 119 */
  uint8_t retail_cl_bid_flag_4;          /* byte 120 */
  uint8_t ask_orders_4[2];               /* bytes 121 to 122 */
  uint8_t ask_size_4[4];                 /* bytes 123 to 126 */
  uint8_t ask_px_4[8];                   /* bytes 127 to 134 */
  uint8_t retail_cl_ask_flag_4;          /* byte 135 */
  uint8_t bid_orders_5[2];               /* bytes 136 to 137 */
  uint8_t bid_size_5[4];                 /* bytes 138 to 141 */
  uint8_t bid_px_5[8];                   /* bytes 142 to 149 */
  uint8_t retail_cl_bid_flag_5;          /* byte 150 */
  uint8_t ask_orders_5[2];               /* bytes 151 to 152 */
  uint8_t ask_size_5[4];                 /* bytes 153 to 156 */
  uint8_t ask_px_5[8];                   /* bytes 157 to 164 */
  uint8_t retail_cl_ask_flag_5;          /* byte 165 */
} TopOfBook5LevelsMessage;

/* any Top Of Book 5 Levels Message at all: every byte one the checker chooses */
static void any_top_of_book5_levels_message(TopOfBook5LevelsMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  record->retail_cl_bid_flag_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
  record->retail_cl_ask_flag_1 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->bid_orders_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_2[i] = arbitrary(); }
  record->retail_cl_bid_flag_2 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ask_orders_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_2[i] = arbitrary(); }
  record->retail_cl_ask_flag_2 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->bid_orders_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_3[i] = arbitrary(); }
  record->retail_cl_bid_flag_3 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ask_orders_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_3[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_3[i] = arbitrary(); }
  record->retail_cl_ask_flag_3 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->bid_orders_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_4[i] = arbitrary(); }
  record->retail_cl_bid_flag_4 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ask_orders_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_4[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_4[i] = arbitrary(); }
  record->retail_cl_ask_flag_4 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->bid_orders_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_5[i] = arbitrary(); }
  record->retail_cl_bid_flag_5 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->ask_orders_5[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_5[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_5[i] = arbitrary(); }
  record->retail_cl_ask_flag_5 = arbitrary();
}

/* Top Of Book 5 Levels Message to the wire: 166 bytes from at, returning where the next byte goes */
static size_t encode_top_of_book5_levels_message(const TopOfBook5LevelsMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  wire[at++] = record->retail_cl_bid_flag_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }
  wire[at++] = record->retail_cl_ask_flag_1;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_2[i]; }
  wire[at++] = record->retail_cl_bid_flag_2;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_2[i]; }
  wire[at++] = record->retail_cl_ask_flag_2;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_3[i]; }
  wire[at++] = record->retail_cl_bid_flag_3;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_3[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_3[i]; }
  wire[at++] = record->retail_cl_ask_flag_3;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_4[i]; }
  wire[at++] = record->retail_cl_bid_flag_4;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_4[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_4[i]; }
  wire[at++] = record->retail_cl_ask_flag_4;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->bid_orders_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_5[i]; }
  wire[at++] = record->retail_cl_bid_flag_5;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ask_orders_5[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_5[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_5[i]; }
  wire[at++] = record->retail_cl_ask_flag_5;

  return at;
}

/* Top Of Book 5 Levels Message off the wire: 166 bytes from at, returning where the next byte lies */
static size_t decode_top_of_book5_levels_message(TopOfBook5LevelsMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->bid_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  record->retail_cl_bid_flag_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ask_orders_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }
  record->retail_cl_ask_flag_1 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->bid_orders_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_2[i] = wire[at++]; }
  record->retail_cl_bid_flag_2 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ask_orders_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_2[i] = wire[at++]; }
  record->retail_cl_ask_flag_2 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->bid_orders_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_3[i] = wire[at++]; }
  record->retail_cl_bid_flag_3 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ask_orders_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_3[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_3[i] = wire[at++]; }
  record->retail_cl_ask_flag_3 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->bid_orders_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_4[i] = wire[at++]; }
  record->retail_cl_bid_flag_4 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ask_orders_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_4[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_4[i] = wire[at++]; }
  record->retail_cl_ask_flag_4 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->bid_orders_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_5[i] = wire[at++]; }
  record->retail_cl_bid_flag_5 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->ask_orders_5[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_5[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_5[i] = wire[at++]; }
  record->retail_cl_ask_flag_5 = wire[at++];

  return at;
}

/* what was read of Top Of Book 5 Levels Message is what was written, byte for byte */
static void equal_top_of_book5_levels_message(const TopOfBook5LevelsMessage *read, const TopOfBook5LevelsMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_1[i] == written->bid_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_1[i] == written->bid_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  assert(read->retail_cl_bid_flag_1 == written->retail_cl_bid_flag_1);
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_1[i] == written->ask_orders_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_1[i] == written->ask_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
  assert(read->retail_cl_ask_flag_1 == written->retail_cl_ask_flag_1);
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_2[i] == written->bid_orders_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_2[i] == written->bid_size_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_2[i] == written->bid_px_2[i]); }
  assert(read->retail_cl_bid_flag_2 == written->retail_cl_bid_flag_2);
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_2[i] == written->ask_orders_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_2[i] == written->ask_size_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_2[i] == written->ask_px_2[i]); }
  assert(read->retail_cl_ask_flag_2 == written->retail_cl_ask_flag_2);
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_3[i] == written->bid_orders_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_3[i] == written->bid_size_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_3[i] == written->bid_px_3[i]); }
  assert(read->retail_cl_bid_flag_3 == written->retail_cl_bid_flag_3);
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_3[i] == written->ask_orders_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_3[i] == written->ask_size_3[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_3[i] == written->ask_px_3[i]); }
  assert(read->retail_cl_ask_flag_3 == written->retail_cl_ask_flag_3);
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_4[i] == written->bid_orders_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_4[i] == written->bid_size_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_4[i] == written->bid_px_4[i]); }
  assert(read->retail_cl_bid_flag_4 == written->retail_cl_bid_flag_4);
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_4[i] == written->ask_orders_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_4[i] == written->ask_size_4[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_4[i] == written->ask_px_4[i]); }
  assert(read->retail_cl_ask_flag_4 == written->retail_cl_ask_flag_4);
  for (size_t i = 0; i < 2; i++) { assert(read->bid_orders_5[i] == written->bid_orders_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_5[i] == written->bid_size_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_5[i] == written->bid_px_5[i]); }
  assert(read->retail_cl_bid_flag_5 == written->retail_cl_bid_flag_5);
  for (size_t i = 0; i < 2; i++) { assert(read->ask_orders_5[i] == written->ask_orders_5[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_5[i] == written->ask_size_5[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_5[i] == written->ask_px_5[i]); }
  assert(read->retail_cl_ask_flag_5 == written->retail_cl_ask_flag_5);
}

/* Top Of Book 5 Levels Message: written and read back, then read and written back */
static void check_top_of_book5_levels_message(void) {
  TopOfBook5LevelsMessage sent;
  TopOfBook5LevelsMessage got;
  uint8_t wire[166];
  uint8_t again[166];

  any_top_of_book5_levels_message(&sent);
  assert(encode_top_of_book5_levels_message(&sent, wire, 0) == 166);
  assert(decode_top_of_book5_levels_message(&got, wire, 0) == 166);
  equal_top_of_book5_levels_message(&got, &sent);

  for (size_t i = 0; i < 166; i++) { wire[i] = arbitrary(); }
  assert(decode_top_of_book5_levels_message(&got, wire, 0) == 166);
  assert(encode_top_of_book5_levels_message(&got, again, 0) == 166);
  for (size_t i = 0; i < 166; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_response_message();
  check_logout_response_message();
  check_heartbeat_message();
  check_network_status_message();
  check_trading_session_status_message();
  check_news_message();
  check_security_list_cancellation_report_message();
  check_security_list_message();
  check_security_list_update_report_message();
  check_security_status_message();
  check_family_status_message();
  check_trade_market_post_transparency_information_top_of_book_message();
  check_trade_trade_amendment_or_cancellation_message();
  check_indication_of_interest_message();
  check_rfq_market_pre_transparency_information_message();
  check_top_of_book_message();
  check_top_of_book5_levels_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
