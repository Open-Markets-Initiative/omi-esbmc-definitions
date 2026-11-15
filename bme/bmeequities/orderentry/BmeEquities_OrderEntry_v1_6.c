// bme/bmeequities/orderentry/BmeEquities_OrderEntry_v1_6.c
/*
 * Bolsas y Mercados Españoles BME Equities Order Entry
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

/* ---- Logon Message: 53 bytes ------------------------------------------------- */

/* The Logon message is used to start a session by the client application */
typedef struct {
  uint8_t username[7];                  /* bytes 0 to 6 */
  uint8_t password[10];                 /* bytes 7 to 16 */
  uint8_t software_name[25];            /* bytes 17 to 41 */
  uint8_t expected_sequence_number[4];  /* bytes 42 to 45 */
  uint8_t subscriptions;                /* byte 46 */
  uint8_t protocol_version[6];          /* bytes 47 to 52 */
} LogonMessage;

/* any Logon Message at all: every byte one the checker chooses */
static void any_logon_message(LogonMessage *record) {
  for (size_t i = 0; i < 7; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 25; i++) { record->software_name[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->expected_sequence_number[i] = arbitrary(); }
  record->subscriptions = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->protocol_version[i] = arbitrary(); }
}

/* Logon Message to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_logon_message(const LogonMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 25; i++) { wire[at++] = record->software_name[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->expected_sequence_number[i]; }
  wire[at++] = record->subscriptions;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->protocol_version[i]; }

  return at;
}

/* Logon Message off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_logon_message(LogonMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 25; i++) { record->software_name[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->expected_sequence_number[i] = wire[at++]; }
  record->subscriptions = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->protocol_version[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Message is what was written, byte for byte */
static void equal_logon_message(const LogonMessage *read, const LogonMessage *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 25; i++) { assert(read->software_name[i] == written->software_name[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->expected_sequence_number[i] == written->expected_sequence_number[i]); }
  assert(read->subscriptions == written->subscriptions);
  for (size_t i = 0; i < 6; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
}

/* Logon Message: written and read back, then read and written back */
static void check_logon_message(void) {
  LogonMessage sent;
  LogonMessage got;
  uint8_t wire[53];
  uint8_t again[53];

  any_logon_message(&sent);
  assert(encode_logon_message(&sent, wire, 0) == 53);
  assert(decode_logon_message(&got, wire, 0) == 53);
  equal_logon_message(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_message(&got, wire, 0) == 53);
  assert(encode_logon_message(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reject Message: 70 bytes ------------------------------------------------ */

/* It may be sent by the server to inform about the rejection of an unsupported or syntactically incorrect message. In the Reject message, the SequenceNumber of the previously received message will be repeated */
typedef struct {
  uint8_t sequence_number[4];         /* bytes 0 to 3 */
  uint8_t session_reject_reason;      /* byte 4 */
  uint8_t text_c_58[58];              /* bytes 5 to 62 */
  uint8_t msg_rejected_reference[7];  /* bytes 63 to 69 */
} RejectMessage;

/* any Reject Message at all: every byte one the checker chooses */
static void any_reject_message(RejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  record->session_reject_reason = arbitrary();
  for (size_t i = 0; i < 58; i++) { record->text_c_58[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->msg_rejected_reference[i] = arbitrary(); }
}

/* Reject Message to the wire: 70 bytes from at, returning where the next byte goes */
static size_t encode_reject_message(const RejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  wire[at++] = record->session_reject_reason;
  for (size_t i = 0; i < 58; i++) { wire[at++] = record->text_c_58[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->msg_rejected_reference[i]; }

  return at;
}

/* Reject Message off the wire: 70 bytes from at, returning where the next byte lies */
static size_t decode_reject_message(RejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  record->session_reject_reason = wire[at++];
  for (size_t i = 0; i < 58; i++) { record->text_c_58[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->msg_rejected_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Reject Message is what was written, byte for byte */
static void equal_reject_message(const RejectMessage *read, const RejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  assert(read->session_reject_reason == written->session_reject_reason);
  for (size_t i = 0; i < 58; i++) { assert(read->text_c_58[i] == written->text_c_58[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->msg_rejected_reference[i] == written->msg_rejected_reference[i]); }
}

/* Reject Message: written and read back, then read and written back */
static void check_reject_message(void) {
  RejectMessage sent;
  RejectMessage got;
  uint8_t wire[70];
  uint8_t again[70];

  any_reject_message(&sent);
  assert(encode_reject_message(&sent, wire, 0) == 70);
  assert(decode_reject_message(&got, wire, 0) == 70);
  equal_reject_message(&got, &sent);

  for (size_t i = 0; i < 70; i++) { wire[i] = arbitrary(); }
  assert(decode_reject_message(&got, wire, 0) == 70);
  assert(encode_reject_message(&got, again, 0) == 70);
  for (size_t i = 0; i < 70; i++) { assert(again[i] == wire[i]); }
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

/* ---- Security List Message: 976 bytes ---------------------------------------- */

/* Message sent by the server to provide the definition of one security. It shares the same layout as the Security List Update Report message, but with a different Message Type */
typedef struct {
  uint8_t sequence_number[4];                              /* bytes 0 to 3 */
  uint8_t market_id[4];                                    /* bytes 4 to 7 */
  uint8_t market_segment_id[4];                            /* bytes 8 to 11 */
  uint8_t security_code[4];                                /* bytes 12 to 15 */
  uint8_t symbol[22];                                      /* bytes 16 to 37 */
  uint8_t symbol_isin[12];                                 /* bytes 38 to 49 */
  uint8_t fisn[35];                                        /* bytes 50 to 84 */
  uint8_t issuer_lei[20];                                  /* bytes 85 to 104 */
  uint8_t security_group[2];                               /* bytes 105 to 106 */
  uint8_t cfi_code[6];                                     /* bytes 107 to 112 */
  uint8_t security_type[2];                                /* bytes 113 to 114 */
  uint8_t maturity_date[4];                                /* bytes 115 to 118 */
  uint8_t issue_date[4];                                   /* bytes 119 to 122 */
  uint8_t contract_multiplier[8];                          /* bytes 123 to 130 */
  uint8_t li_spre[8];                                      /* bytes 131 to 138 */
  uint8_t sst_ipre[8];                                     /* bytes 139 to 146 */
  uint8_t li_spost[8];                                     /* bytes 147 to 154 */
  uint8_t sst_ipost[8];                                    /* bytes 155 to 162 */
  uint8_t liquid_instrument;                               /* byte 163 */
  uint8_t admission_requested_by_issuer;                   /* byte 164 */
  uint8_t min_trade_vol[4];                                /* bytes 165 to 168 */
  uint8_t round_lot[4];                                    /* bytes 169 to 172 */
  uint8_t currency[3];                                     /* bytes 173 to 175 */
  uint8_t modality_mask_b_4[4];                            /* bytes 176 to 179 */
  uint8_t security_description[80];                        /* bytes 180 to 259 */
  uint8_t trading_obligation;                              /* byte 260 */
  uint8_t security_name[40];                               /* bytes 261 to 300 */
  uint8_t net_asset_value_identifier[7];                   /* bytes 301 to 307 */
  uint8_t security_sub_type[2];                            /* bytes 308 to 309 */
  uint8_t maturity_month_year[8];                          /* bytes 310 to 317 */
  uint8_t security_status;                                 /* byte 318 */
  uint8_t strike_price[8];                                 /* bytes 319 to 326 */
  uint8_t strike_value[8];                                 /* bytes 327 to 334 */
  uint8_t exercise_style;                                  /* byte 335 */
  uint8_t put_or_call;                                     /* byte 336 */
  uint8_t position_limit[8];                               /* bytes 337 to 344 */
  uint8_t nt_position_limit[8];                            /* bytes 345 to 352 */
  uint8_t issuer[12];                                      /* bytes 353 to 364 */
  uint8_t cp_reg_type;                                     /* byte 365 */
  uint8_t barrier[8];                                      /* bytes 366 to 373 */
  uint8_t last_trading_day[4];                             /* bytes 374 to 377 */
  uint8_t automatic_expiration;                            /* byte 378 */
  uint8_t fee_type[2];                                     /* bytes 379 to 380 */
  uint8_t barrier_2[8];                                    /* bytes 381 to 388 */
  uint8_t trigger_barrier[8];                              /* bytes 389 to 396 */
  uint8_t trigger_upper_barrier[8];                        /* bytes 397 to 404 */
  uint8_t average_quarterly_turnover[8];                   /* bytes 405 to 412 */
  uint8_t trading_scope;                                   /* byte 413 */
  uint8_t sicav_counterparty_member[4];                    /* bytes 414 to 417 */
  uint8_t net_asset_value_indicator;                       /* byte 418 */
  uint8_t reference_trading_venue;                         /* byte 419 */
  uint8_t outstanding_capital[8];                          /* bytes 420 to 427 */
  uint8_t first_trading_date[4];                           /* bytes 428 to 431 */
  uint8_t settlement_system;                               /* byte 432 */
  uint8_t number_of_decimals;                              /* byte 433 */
  uint8_t number_of_holders[4];                            /* bytes 434 to 437 */
  uint8_t outstanding_shares[4];                           /* bytes 438 to 441 */
  uint8_t minimum_authorized_shares[4];                    /* bytes 442 to 445 */
  uint8_t minimum_capital[8];                              /* bytes 446 to 453 */
  uint8_t last_admission_date[4];                          /* bytes 454 to 457 */
  uint8_t barrier_return[8];                               /* bytes 458 to 465 */
  uint8_t investment_fund_manager[80];                     /* bytes 466 to 545 */
  uint8_t effective_amount_filters_routed_orders[8];       /* bytes 546 to 553 */
  uint8_t order_number_of_decimals;                        /* byte 554 */
  uint8_t investment_fund_class;                           /* byte 555 */
  uint8_t master_fund_name[80];                            /* bytes 556 to 635 */
  uint8_t investment_fund_management_company[80];          /* bytes 636 to 715 */
  uint8_t investment_fund_depository[80];                  /* bytes 716 to 795 */
  uint8_t investment_fund_category[80];                    /* bytes 796 to 875 */
  uint8_t investment_fund_minimum_subscription_amount[8];  /* bytes 876 to 883 */
  uint8_t investment_fund_minimum_maintenance_amount[8];   /* bytes 884 to 891 */
  uint8_t investment_fund_cut_off_time[8];                 /* bytes 892 to 899 */
  uint8_t nav_communication_term;                          /* byte 900 */
  uint8_t investment_fund_number_of_decimals;              /* byte 901 */
  uint8_t commodity_derivative_indicator;                  /* byte 902 */
  uint8_t double_volume_cap_reached;                       /* byte 903 */
  uint8_t adt[8];                                          /* bytes 904 to 911 */
  uint8_t base_product[4];                                 /* bytes 912 to 915 */
  uint8_t sub_product[4];                                  /* bytes 916 to 919 */
  uint8_t further_sub_product[4];                          /* bytes 920 to 923 */
  uint8_t adnt[8];                                         /* bytes 924 to 931 */
  uint8_t price_tick_rule;                                 /* byte 932 */
  uint8_t underlying_symbol[22];                           /* bytes 933 to 954 */
  uint8_t underlying_isin[12];                             /* bytes 955 to 966 */
  uint8_t underlying_currency[3];                          /* bytes 967 to 969 */
  uint8_t minimum_display_qty[4];                          /* bytes 970 to 973 */
  uint8_t retail_service_flag;                             /* byte 974 */
  uint8_t self_match_prevention;                           /* byte 975 */
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
  for (size_t i = 0; i < 40; i++) { record->security_name[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->net_asset_value_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = arbitrary(); }
  record->security_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = arbitrary(); }
  record->exercise_style = arbitrary();
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nt_position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = arbitrary(); }
  record->cp_reg_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = arbitrary(); }
  record->automatic_expiration = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->barrier_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trigger_barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trigger_upper_barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average_quarterly_turnover[i] = arbitrary(); }
  record->trading_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sicav_counterparty_member[i] = arbitrary(); }
  record->net_asset_value_indicator = arbitrary();
  record->reference_trading_venue = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->outstanding_capital[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = arbitrary(); }
  record->settlement_system = arbitrary();
  record->number_of_decimals = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number_of_holders[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->outstanding_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_authorized_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_capital[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_admission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->barrier_return[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_manager[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->effective_amount_filters_routed_orders[i] = arbitrary(); }
  record->order_number_of_decimals = arbitrary();
  record->investment_fund_class = arbitrary();
  for (size_t i = 0; i < 80; i++) { record->master_fund_name[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_management_company[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_depository[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_category[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_subscription_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_maintenance_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_cut_off_time[i] = arbitrary(); }
  record->nav_communication_term = arbitrary();
  record->investment_fund_number_of_decimals = arbitrary();
  record->commodity_derivative_indicator = arbitrary();
  record->double_volume_cap_reached = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->adnt[i] = arbitrary(); }
  record->price_tick_rule = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_display_qty[i] = arbitrary(); }
  record->retail_service_flag = arbitrary();
  record->self_match_prevention = arbitrary();
}

/* Security List Message to the wire: 976 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->security_name[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->net_asset_value_identifier[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_sub_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_month_year[i]; }
  wire[at++] = record->security_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_value[i]; }
  wire[at++] = record->exercise_style;
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->position_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nt_position_limit[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issuer[i]; }
  wire[at++] = record->cp_reg_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_day[i]; }
  wire[at++] = record->automatic_expiration;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trigger_barrier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trigger_upper_barrier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average_quarterly_turnover[i]; }
  wire[at++] = record->trading_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sicav_counterparty_member[i]; }
  wire[at++] = record->net_asset_value_indicator;
  wire[at++] = record->reference_trading_venue;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding_capital[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_trading_date[i]; }
  wire[at++] = record->settlement_system;
  wire[at++] = record->number_of_decimals;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_holders[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->outstanding_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_authorized_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_capital[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_admission_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier_return[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_manager[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_amount_filters_routed_orders[i]; }
  wire[at++] = record->order_number_of_decimals;
  wire[at++] = record->investment_fund_class;
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->master_fund_name[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_management_company[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_depository[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_category[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_minimum_subscription_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_minimum_maintenance_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_cut_off_time[i]; }
  wire[at++] = record->nav_communication_term;
  wire[at++] = record->investment_fund_number_of_decimals;
  wire[at++] = record->commodity_derivative_indicator;
  wire[at++] = record->double_volume_cap_reached;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->base_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sub_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->further_sub_product[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adnt[i]; }
  wire[at++] = record->price_tick_rule;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_display_qty[i]; }
  wire[at++] = record->retail_service_flag;
  wire[at++] = record->self_match_prevention;

  return at;
}

/* Security List Message off the wire: 976 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 40; i++) { record->security_name[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->net_asset_value_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = wire[at++]; }
  record->security_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = wire[at++]; }
  record->exercise_style = wire[at++];
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nt_position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = wire[at++]; }
  record->cp_reg_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = wire[at++]; }
  record->automatic_expiration = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->barrier_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trigger_barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trigger_upper_barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average_quarterly_turnover[i] = wire[at++]; }
  record->trading_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sicav_counterparty_member[i] = wire[at++]; }
  record->net_asset_value_indicator = wire[at++];
  record->reference_trading_venue = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->outstanding_capital[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = wire[at++]; }
  record->settlement_system = wire[at++];
  record->number_of_decimals = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number_of_holders[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->outstanding_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_authorized_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_capital[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_admission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->barrier_return[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_manager[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->effective_amount_filters_routed_orders[i] = wire[at++]; }
  record->order_number_of_decimals = wire[at++];
  record->investment_fund_class = wire[at++];
  for (size_t i = 0; i < 80; i++) { record->master_fund_name[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_management_company[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_depository[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_category[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_subscription_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_maintenance_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_cut_off_time[i] = wire[at++]; }
  record->nav_communication_term = wire[at++];
  record->investment_fund_number_of_decimals = wire[at++];
  record->commodity_derivative_indicator = wire[at++];
  record->double_volume_cap_reached = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->adnt[i] = wire[at++]; }
  record->price_tick_rule = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_display_qty[i] = wire[at++]; }
  record->retail_service_flag = wire[at++];
  record->self_match_prevention = wire[at++];

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
  for (size_t i = 0; i < 40; i++) { assert(read->security_name[i] == written->security_name[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->net_asset_value_identifier[i] == written->net_asset_value_identifier[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_sub_type[i] == written->security_sub_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
  assert(read->security_status == written->security_status);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_value[i] == written->strike_value[i]); }
  assert(read->exercise_style == written->exercise_style);
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 8; i++) { assert(read->position_limit[i] == written->position_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nt_position_limit[i] == written->nt_position_limit[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->issuer[i] == written->issuer[i]); }
  assert(read->cp_reg_type == written->cp_reg_type);
  for (size_t i = 0; i < 8; i++) { assert(read->barrier[i] == written->barrier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_day[i] == written->last_trading_day[i]); }
  assert(read->automatic_expiration == written->automatic_expiration);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_type[i] == written->fee_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->barrier_2[i] == written->barrier_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trigger_barrier[i] == written->trigger_barrier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trigger_upper_barrier[i] == written->trigger_upper_barrier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average_quarterly_turnover[i] == written->average_quarterly_turnover[i]); }
  assert(read->trading_scope == written->trading_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->sicav_counterparty_member[i] == written->sicav_counterparty_member[i]); }
  assert(read->net_asset_value_indicator == written->net_asset_value_indicator);
  assert(read->reference_trading_venue == written->reference_trading_venue);
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding_capital[i] == written->outstanding_capital[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_trading_date[i] == written->first_trading_date[i]); }
  assert(read->settlement_system == written->settlement_system);
  assert(read->number_of_decimals == written->number_of_decimals);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_holders[i] == written->number_of_holders[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->outstanding_shares[i] == written->outstanding_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_authorized_shares[i] == written->minimum_authorized_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_capital[i] == written->minimum_capital[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_admission_date[i] == written->last_admission_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->barrier_return[i] == written->barrier_return[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_manager[i] == written->investment_fund_manager[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->effective_amount_filters_routed_orders[i] == written->effective_amount_filters_routed_orders[i]); }
  assert(read->order_number_of_decimals == written->order_number_of_decimals);
  assert(read->investment_fund_class == written->investment_fund_class);
  for (size_t i = 0; i < 80; i++) { assert(read->master_fund_name[i] == written->master_fund_name[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_management_company[i] == written->investment_fund_management_company[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_depository[i] == written->investment_fund_depository[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_category[i] == written->investment_fund_category[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_minimum_subscription_amount[i] == written->investment_fund_minimum_subscription_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_minimum_maintenance_amount[i] == written->investment_fund_minimum_maintenance_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_cut_off_time[i] == written->investment_fund_cut_off_time[i]); }
  assert(read->nav_communication_term == written->nav_communication_term);
  assert(read->investment_fund_number_of_decimals == written->investment_fund_number_of_decimals);
  assert(read->commodity_derivative_indicator == written->commodity_derivative_indicator);
  assert(read->double_volume_cap_reached == written->double_volume_cap_reached);
  for (size_t i = 0; i < 8; i++) { assert(read->adt[i] == written->adt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->base_product[i] == written->base_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sub_product[i] == written->sub_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->further_sub_product[i] == written->further_sub_product[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->adnt[i] == written->adnt[i]); }
  assert(read->price_tick_rule == written->price_tick_rule);
  for (size_t i = 0; i < 22; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_isin[i] == written->underlying_isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_currency[i] == written->underlying_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_display_qty[i] == written->minimum_display_qty[i]); }
  assert(read->retail_service_flag == written->retail_service_flag);
  assert(read->self_match_prevention == written->self_match_prevention);
}

/* Security List Message: written and read back, then read and written back */
static void check_security_list_message(void) {
  SecurityListMessage sent;
  SecurityListMessage got;
  uint8_t wire[976];
  uint8_t again[976];

  any_security_list_message(&sent);
  assert(encode_security_list_message(&sent, wire, 0) == 976);
  assert(decode_security_list_message(&got, wire, 0) == 976);
  equal_security_list_message(&got, &sent);

  for (size_t i = 0; i < 976; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_message(&got, wire, 0) == 976);
  assert(encode_security_list_message(&got, again, 0) == 976);
  for (size_t i = 0; i < 976; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security List Update Report Message: 976 bytes -------------------------- */

/* Message sent by the server for reporting updates, during the session, to the security definition */
typedef struct {
  uint8_t sequence_number[4];                              /* bytes 0 to 3 */
  uint8_t market_id[4];                                    /* bytes 4 to 7 */
  uint8_t market_segment_id[4];                            /* bytes 8 to 11 */
  uint8_t security_code[4];                                /* bytes 12 to 15 */
  uint8_t symbol[22];                                      /* bytes 16 to 37 */
  uint8_t symbol_isin[12];                                 /* bytes 38 to 49 */
  uint8_t fisn[35];                                        /* bytes 50 to 84 */
  uint8_t issuer_lei[20];                                  /* bytes 85 to 104 */
  uint8_t security_group[2];                               /* bytes 105 to 106 */
  uint8_t cfi_code[6];                                     /* bytes 107 to 112 */
  uint8_t security_type[2];                                /* bytes 113 to 114 */
  uint8_t maturity_date[4];                                /* bytes 115 to 118 */
  uint8_t issue_date[4];                                   /* bytes 119 to 122 */
  uint8_t contract_multiplier[8];                          /* bytes 123 to 130 */
  uint8_t li_spre[8];                                      /* bytes 131 to 138 */
  uint8_t sst_ipre[8];                                     /* bytes 139 to 146 */
  uint8_t li_spost[8];                                     /* bytes 147 to 154 */
  uint8_t sst_ipost[8];                                    /* bytes 155 to 162 */
  uint8_t liquid_instrument;                               /* byte 163 */
  uint8_t admission_requested_by_issuer;                   /* byte 164 */
  uint8_t min_trade_vol[4];                                /* bytes 165 to 168 */
  uint8_t round_lot[4];                                    /* bytes 169 to 172 */
  uint8_t currency[3];                                     /* bytes 173 to 175 */
  uint8_t modality_mask_b_4[4];                            /* bytes 176 to 179 */
  uint8_t security_description[80];                        /* bytes 180 to 259 */
  uint8_t trading_obligation;                              /* byte 260 */
  uint8_t security_name[40];                               /* bytes 261 to 300 */
  uint8_t net_asset_value_identifier[7];                   /* bytes 301 to 307 */
  uint8_t security_sub_type[2];                            /* bytes 308 to 309 */
  uint8_t maturity_month_year[8];                          /* bytes 310 to 317 */
  uint8_t security_status;                                 /* byte 318 */
  uint8_t strike_price[8];                                 /* bytes 319 to 326 */
  uint8_t strike_value[8];                                 /* bytes 327 to 334 */
  uint8_t exercise_style;                                  /* byte 335 */
  uint8_t put_or_call;                                     /* byte 336 */
  uint8_t position_limit[8];                               /* bytes 337 to 344 */
  uint8_t nt_position_limit[8];                            /* bytes 345 to 352 */
  uint8_t issuer[12];                                      /* bytes 353 to 364 */
  uint8_t cp_reg_type;                                     /* byte 365 */
  uint8_t barrier[8];                                      /* bytes 366 to 373 */
  uint8_t last_trading_day[4];                             /* bytes 374 to 377 */
  uint8_t automatic_expiration;                            /* byte 378 */
  uint8_t fee_type[2];                                     /* bytes 379 to 380 */
  uint8_t barrier_2[8];                                    /* bytes 381 to 388 */
  uint8_t trigger_barrier[8];                              /* bytes 389 to 396 */
  uint8_t trigger_upper_barrier[8];                        /* bytes 397 to 404 */
  uint8_t average_quarterly_turnover[8];                   /* bytes 405 to 412 */
  uint8_t trading_scope;                                   /* byte 413 */
  uint8_t sicav_counterparty_member[4];                    /* bytes 414 to 417 */
  uint8_t net_asset_value_indicator;                       /* byte 418 */
  uint8_t reference_trading_venue;                         /* byte 419 */
  uint8_t outstanding_capital[8];                          /* bytes 420 to 427 */
  uint8_t first_trading_date[4];                           /* bytes 428 to 431 */
  uint8_t settlement_system;                               /* byte 432 */
  uint8_t number_of_decimals;                              /* byte 433 */
  uint8_t number_of_holders[4];                            /* bytes 434 to 437 */
  uint8_t outstanding_shares[4];                           /* bytes 438 to 441 */
  uint8_t minimum_authorized_shares[4];                    /* bytes 442 to 445 */
  uint8_t minimum_capital[8];                              /* bytes 446 to 453 */
  uint8_t last_admission_date[4];                          /* bytes 454 to 457 */
  uint8_t barrier_return[8];                               /* bytes 458 to 465 */
  uint8_t investment_fund_manager[80];                     /* bytes 466 to 545 */
  uint8_t effective_amount_filters_routed_orders[8];       /* bytes 546 to 553 */
  uint8_t order_number_of_decimals;                        /* byte 554 */
  uint8_t investment_fund_class;                           /* byte 555 */
  uint8_t master_fund_name[80];                            /* bytes 556 to 635 */
  uint8_t investment_fund_management_company[80];          /* bytes 636 to 715 */
  uint8_t investment_fund_depository[80];                  /* bytes 716 to 795 */
  uint8_t investment_fund_category[80];                    /* bytes 796 to 875 */
  uint8_t investment_fund_minimum_subscription_amount[8];  /* bytes 876 to 883 */
  uint8_t investment_fund_minimum_maintenance_amount[8];   /* bytes 884 to 891 */
  uint8_t investment_fund_cut_off_time[8];                 /* bytes 892 to 899 */
  uint8_t nav_communication_term;                          /* byte 900 */
  uint8_t investment_fund_number_of_decimals;              /* byte 901 */
  uint8_t commodity_derivative_indicator;                  /* byte 902 */
  uint8_t double_volume_cap_reached;                       /* byte 903 */
  uint8_t adt[8];                                          /* bytes 904 to 911 */
  uint8_t base_product[4];                                 /* bytes 912 to 915 */
  uint8_t sub_product[4];                                  /* bytes 916 to 919 */
  uint8_t further_sub_product[4];                          /* bytes 920 to 923 */
  uint8_t adnt[8];                                         /* bytes 924 to 931 */
  uint8_t price_tick_rule;                                 /* byte 932 */
  uint8_t underlying_symbol[22];                           /* bytes 933 to 954 */
  uint8_t underlying_isin[12];                             /* bytes 955 to 966 */
  uint8_t underlying_currency[3];                          /* bytes 967 to 969 */
  uint8_t minimum_display_qty[4];                          /* bytes 970 to 973 */
  uint8_t retail_service_flag;                             /* byte 974 */
  uint8_t self_match_prevention;                           /* byte 975 */
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
  for (size_t i = 0; i < 40; i++) { record->security_name[i] = arbitrary(); }
  for (size_t i = 0; i < 7; i++) { record->net_asset_value_identifier[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_sub_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = arbitrary(); }
  record->security_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = arbitrary(); }
  record->exercise_style = arbitrary();
  record->put_or_call = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->nt_position_limit[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = arbitrary(); }
  record->cp_reg_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = arbitrary(); }
  record->automatic_expiration = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fee_type[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->barrier_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trigger_barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trigger_upper_barrier[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->average_quarterly_turnover[i] = arbitrary(); }
  record->trading_scope = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->sicav_counterparty_member[i] = arbitrary(); }
  record->net_asset_value_indicator = arbitrary();
  record->reference_trading_venue = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->outstanding_capital[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = arbitrary(); }
  record->settlement_system = arbitrary();
  record->number_of_decimals = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->number_of_holders[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->outstanding_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_authorized_shares[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->minimum_capital[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_admission_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->barrier_return[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_manager[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->effective_amount_filters_routed_orders[i] = arbitrary(); }
  record->order_number_of_decimals = arbitrary();
  record->investment_fund_class = arbitrary();
  for (size_t i = 0; i < 80; i++) { record->master_fund_name[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_management_company[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_depository[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_category[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_subscription_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_maintenance_amount[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_cut_off_time[i] = arbitrary(); }
  record->nav_communication_term = arbitrary();
  record->investment_fund_number_of_decimals = arbitrary();
  record->commodity_derivative_indicator = arbitrary();
  record->double_volume_cap_reached = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->adt[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->adnt[i] = arbitrary(); }
  record->price_tick_rule = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_display_qty[i] = arbitrary(); }
  record->retail_service_flag = arbitrary();
  record->self_match_prevention = arbitrary();
}

/* Security List Update Report Message to the wire: 976 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->security_name[i]; }
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->net_asset_value_identifier[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_sub_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->maturity_month_year[i]; }
  wire[at++] = record->security_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_value[i]; }
  wire[at++] = record->exercise_style;
  wire[at++] = record->put_or_call;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->position_limit[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->nt_position_limit[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issuer[i]; }
  wire[at++] = record->cp_reg_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_trading_day[i]; }
  wire[at++] = record->automatic_expiration;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fee_type[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trigger_barrier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trigger_upper_barrier[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->average_quarterly_turnover[i]; }
  wire[at++] = record->trading_scope;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sicav_counterparty_member[i]; }
  wire[at++] = record->net_asset_value_indicator;
  wire[at++] = record->reference_trading_venue;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->outstanding_capital[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->first_trading_date[i]; }
  wire[at++] = record->settlement_system;
  wire[at++] = record->number_of_decimals;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->number_of_holders[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->outstanding_shares[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_authorized_shares[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->minimum_capital[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_admission_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->barrier_return[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_manager[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->effective_amount_filters_routed_orders[i]; }
  wire[at++] = record->order_number_of_decimals;
  wire[at++] = record->investment_fund_class;
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->master_fund_name[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_management_company[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_depository[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->investment_fund_category[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_minimum_subscription_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_minimum_maintenance_amount[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->investment_fund_cut_off_time[i]; }
  wire[at++] = record->nav_communication_term;
  wire[at++] = record->investment_fund_number_of_decimals;
  wire[at++] = record->commodity_derivative_indicator;
  wire[at++] = record->double_volume_cap_reached;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adt[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->base_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sub_product[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->further_sub_product[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->adnt[i]; }
  wire[at++] = record->price_tick_rule;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->underlying_symbol[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->underlying_isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->underlying_currency[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_display_qty[i]; }
  wire[at++] = record->retail_service_flag;
  wire[at++] = record->self_match_prevention;

  return at;
}

/* Security List Update Report Message off the wire: 976 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 40; i++) { record->security_name[i] = wire[at++]; }
  for (size_t i = 0; i < 7; i++) { record->net_asset_value_identifier[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_sub_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->maturity_month_year[i] = wire[at++]; }
  record->security_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_value[i] = wire[at++]; }
  record->exercise_style = wire[at++];
  record->put_or_call = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->nt_position_limit[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = wire[at++]; }
  record->cp_reg_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_trading_day[i] = wire[at++]; }
  record->automatic_expiration = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fee_type[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->barrier_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trigger_barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trigger_upper_barrier[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->average_quarterly_turnover[i] = wire[at++]; }
  record->trading_scope = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->sicav_counterparty_member[i] = wire[at++]; }
  record->net_asset_value_indicator = wire[at++];
  record->reference_trading_venue = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->outstanding_capital[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->first_trading_date[i] = wire[at++]; }
  record->settlement_system = wire[at++];
  record->number_of_decimals = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->number_of_holders[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->outstanding_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_authorized_shares[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->minimum_capital[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_admission_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->barrier_return[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_manager[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->effective_amount_filters_routed_orders[i] = wire[at++]; }
  record->order_number_of_decimals = wire[at++];
  record->investment_fund_class = wire[at++];
  for (size_t i = 0; i < 80; i++) { record->master_fund_name[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_management_company[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_depository[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->investment_fund_category[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_subscription_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_minimum_maintenance_amount[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->investment_fund_cut_off_time[i] = wire[at++]; }
  record->nav_communication_term = wire[at++];
  record->investment_fund_number_of_decimals = wire[at++];
  record->commodity_derivative_indicator = wire[at++];
  record->double_volume_cap_reached = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->adt[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->base_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->further_sub_product[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->adnt[i] = wire[at++]; }
  record->price_tick_rule = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->underlying_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->underlying_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->underlying_currency[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_display_qty[i] = wire[at++]; }
  record->retail_service_flag = wire[at++];
  record->self_match_prevention = wire[at++];

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
  for (size_t i = 0; i < 40; i++) { assert(read->security_name[i] == written->security_name[i]); }
  for (size_t i = 0; i < 7; i++) { assert(read->net_asset_value_identifier[i] == written->net_asset_value_identifier[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_sub_type[i] == written->security_sub_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->maturity_month_year[i] == written->maturity_month_year[i]); }
  assert(read->security_status == written->security_status);
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_value[i] == written->strike_value[i]); }
  assert(read->exercise_style == written->exercise_style);
  assert(read->put_or_call == written->put_or_call);
  for (size_t i = 0; i < 8; i++) { assert(read->position_limit[i] == written->position_limit[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->nt_position_limit[i] == written->nt_position_limit[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->issuer[i] == written->issuer[i]); }
  assert(read->cp_reg_type == written->cp_reg_type);
  for (size_t i = 0; i < 8; i++) { assert(read->barrier[i] == written->barrier[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_trading_day[i] == written->last_trading_day[i]); }
  assert(read->automatic_expiration == written->automatic_expiration);
  for (size_t i = 0; i < 2; i++) { assert(read->fee_type[i] == written->fee_type[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->barrier_2[i] == written->barrier_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trigger_barrier[i] == written->trigger_barrier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trigger_upper_barrier[i] == written->trigger_upper_barrier[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->average_quarterly_turnover[i] == written->average_quarterly_turnover[i]); }
  assert(read->trading_scope == written->trading_scope);
  for (size_t i = 0; i < 4; i++) { assert(read->sicav_counterparty_member[i] == written->sicav_counterparty_member[i]); }
  assert(read->net_asset_value_indicator == written->net_asset_value_indicator);
  assert(read->reference_trading_venue == written->reference_trading_venue);
  for (size_t i = 0; i < 8; i++) { assert(read->outstanding_capital[i] == written->outstanding_capital[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->first_trading_date[i] == written->first_trading_date[i]); }
  assert(read->settlement_system == written->settlement_system);
  assert(read->number_of_decimals == written->number_of_decimals);
  for (size_t i = 0; i < 4; i++) { assert(read->number_of_holders[i] == written->number_of_holders[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->outstanding_shares[i] == written->outstanding_shares[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_authorized_shares[i] == written->minimum_authorized_shares[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->minimum_capital[i] == written->minimum_capital[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_admission_date[i] == written->last_admission_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->barrier_return[i] == written->barrier_return[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_manager[i] == written->investment_fund_manager[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->effective_amount_filters_routed_orders[i] == written->effective_amount_filters_routed_orders[i]); }
  assert(read->order_number_of_decimals == written->order_number_of_decimals);
  assert(read->investment_fund_class == written->investment_fund_class);
  for (size_t i = 0; i < 80; i++) { assert(read->master_fund_name[i] == written->master_fund_name[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_management_company[i] == written->investment_fund_management_company[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_depository[i] == written->investment_fund_depository[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->investment_fund_category[i] == written->investment_fund_category[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_minimum_subscription_amount[i] == written->investment_fund_minimum_subscription_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_minimum_maintenance_amount[i] == written->investment_fund_minimum_maintenance_amount[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->investment_fund_cut_off_time[i] == written->investment_fund_cut_off_time[i]); }
  assert(read->nav_communication_term == written->nav_communication_term);
  assert(read->investment_fund_number_of_decimals == written->investment_fund_number_of_decimals);
  assert(read->commodity_derivative_indicator == written->commodity_derivative_indicator);
  assert(read->double_volume_cap_reached == written->double_volume_cap_reached);
  for (size_t i = 0; i < 8; i++) { assert(read->adt[i] == written->adt[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->base_product[i] == written->base_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sub_product[i] == written->sub_product[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->further_sub_product[i] == written->further_sub_product[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->adnt[i] == written->adnt[i]); }
  assert(read->price_tick_rule == written->price_tick_rule);
  for (size_t i = 0; i < 22; i++) { assert(read->underlying_symbol[i] == written->underlying_symbol[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->underlying_isin[i] == written->underlying_isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->underlying_currency[i] == written->underlying_currency[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_display_qty[i] == written->minimum_display_qty[i]); }
  assert(read->retail_service_flag == written->retail_service_flag);
  assert(read->self_match_prevention == written->self_match_prevention);
}

/* Security List Update Report Message: written and read back, then read and written back */
static void check_security_list_update_report_message(void) {
  SecurityListUpdateReportMessage sent;
  SecurityListUpdateReportMessage got;
  uint8_t wire[976];
  uint8_t again[976];

  any_security_list_update_report_message(&sent);
  assert(encode_security_list_update_report_message(&sent, wire, 0) == 976);
  assert(decode_security_list_update_report_message(&got, wire, 0) == 976);
  equal_security_list_update_report_message(&got, &sent);

  for (size_t i = 0; i < 976; i++) { wire[i] = arbitrary(); }
  assert(decode_security_list_update_report_message(&got, wire, 0) == 976);
  assert(encode_security_list_update_report_message(&got, again, 0) == 976);
  for (size_t i = 0; i < 976; i++) { assert(again[i] == wire[i]); }
}

/* ---- Security Status Message: 115 bytes -------------------------------------- */

/* Message sent by the server to inform on the status of one security */
typedef struct {
  uint8_t sequence_number[4];                      /* bytes 0 to 3 */
  uint8_t security_code[4];                        /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];            /* bytes 8 to 15 */
  uint8_t reference_price[8];                      /* bytes 16 to 23 */
  uint8_t static_price[8];                         /* bytes 24 to 31 */
  uint8_t dynamic_price_oscilation_percentage[8];  /* bytes 32 to 39 */
  uint8_t dynamic_range_multiplier;                /* byte 40 */
  uint8_t auction_trigger_price[8];                /* bytes 41 to 48 */
  uint8_t auction_end_time[8];                     /* bytes 49 to 56 */
  uint8_t liquidative_value_date[4];               /* bytes 57 to 60 */
  uint8_t bonus_warrants_with_active_bonus;        /* byte 61 */
  uint8_t security_trading_status;                 /* byte 62 */
  uint8_t auction_origin;                          /* byte 63 */
  uint8_t non_availability_reason;                 /* byte 64 */
  uint8_t exemption_situation;                     /* byte 65 */
  uint8_t block_oscilation_percentage[8];          /* bytes 66 to 73 */
  uint8_t high_limit_price[8];                     /* bytes 74 to 81 */
  uint8_t low_limit_price[8];                      /* bytes 82 to 89 */
  uint8_t liquidative_value[8];                    /* bytes 90 to 97 */
  uint8_t static_range_type;                       /* byte 98 */
  uint8_t order_static_range[8];                   /* bytes 99 to 106 */
  uint8_t block_static_range[8];                   /* bytes 107 to 114 */
} SecurityStatusMessage;

/* any Security Status Message at all: every byte one the checker chooses */
static void any_security_status_message(SecurityStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->static_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->dynamic_price_oscilation_percentage[i] = arbitrary(); }
  record->dynamic_range_multiplier = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->auction_trigger_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->auction_end_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->liquidative_value_date[i] = arbitrary(); }
  record->bonus_warrants_with_active_bonus = arbitrary();
  record->security_trading_status = arbitrary();
  record->auction_origin = arbitrary();
  record->non_availability_reason = arbitrary();
  record->exemption_situation = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->block_oscilation_percentage[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->liquidative_value[i] = arbitrary(); }
  record->static_range_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->order_static_range[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->block_static_range[i] = arbitrary(); }
}

/* Security Status Message to the wire: 115 bytes from at, returning where the next byte goes */
static size_t encode_security_status_message(const SecurityStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reference_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->static_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->dynamic_price_oscilation_percentage[i]; }
  wire[at++] = record->dynamic_range_multiplier;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_trigger_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->auction_end_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->liquidative_value_date[i]; }
  wire[at++] = record->bonus_warrants_with_active_bonus;
  wire[at++] = record->security_trading_status;
  wire[at++] = record->auction_origin;
  wire[at++] = record->non_availability_reason;
  wire[at++] = record->exemption_situation;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->block_oscilation_percentage[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->high_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->low_limit_price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->liquidative_value[i]; }
  wire[at++] = record->static_range_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_static_range[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->block_static_range[i]; }

  return at;
}

/* Security Status Message off the wire: 115 bytes from at, returning where the next byte lies */
static size_t decode_security_status_message(SecurityStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reference_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->static_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->dynamic_price_oscilation_percentage[i] = wire[at++]; }
  record->dynamic_range_multiplier = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->auction_trigger_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->auction_end_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->liquidative_value_date[i] = wire[at++]; }
  record->bonus_warrants_with_active_bonus = wire[at++];
  record->security_trading_status = wire[at++];
  record->auction_origin = wire[at++];
  record->non_availability_reason = wire[at++];
  record->exemption_situation = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->block_oscilation_percentage[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->high_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->low_limit_price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->liquidative_value[i] = wire[at++]; }
  record->static_range_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->order_static_range[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->block_static_range[i] = wire[at++]; }

  return at;
}

/* what was read of Security Status Message is what was written, byte for byte */
static void equal_security_status_message(const SecurityStatusMessage *read, const SecurityStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reference_price[i] == written->reference_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->static_price[i] == written->static_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->dynamic_price_oscilation_percentage[i] == written->dynamic_price_oscilation_percentage[i]); }
  assert(read->dynamic_range_multiplier == written->dynamic_range_multiplier);
  for (size_t i = 0; i < 8; i++) { assert(read->auction_trigger_price[i] == written->auction_trigger_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->auction_end_time[i] == written->auction_end_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->liquidative_value_date[i] == written->liquidative_value_date[i]); }
  assert(read->bonus_warrants_with_active_bonus == written->bonus_warrants_with_active_bonus);
  assert(read->security_trading_status == written->security_trading_status);
  assert(read->auction_origin == written->auction_origin);
  assert(read->non_availability_reason == written->non_availability_reason);
  assert(read->exemption_situation == written->exemption_situation);
  for (size_t i = 0; i < 8; i++) { assert(read->block_oscilation_percentage[i] == written->block_oscilation_percentage[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->high_limit_price[i] == written->high_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->low_limit_price[i] == written->low_limit_price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->liquidative_value[i] == written->liquidative_value[i]); }
  assert(read->static_range_type == written->static_range_type);
  for (size_t i = 0; i < 8; i++) { assert(read->order_static_range[i] == written->order_static_range[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->block_static_range[i] == written->block_static_range[i]); }
}

/* Security Status Message: written and read back, then read and written back */
static void check_security_status_message(void) {
  SecurityStatusMessage sent;
  SecurityStatusMessage got;
  uint8_t wire[115];
  uint8_t again[115];

  any_security_status_message(&sent);
  assert(encode_security_status_message(&sent, wire, 0) == 115);
  assert(decode_security_status_message(&got, wire, 0) == 115);
  equal_security_status_message(&got, &sent);

  for (size_t i = 0; i < 115; i++) { wire[i] = arbitrary(); }
  assert(decode_security_status_message(&got, wire, 0) == 115);
  assert(encode_security_status_message(&got, again, 0) == 115);
  for (size_t i = 0; i < 115; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Market Member Message: 25 bytes ---------------------- */

/* Used by the Server to communicate information order cancellation. The same message is used in Full-Depth data feeds (for order cancellations of any user), in the Order Entry Server (for cancellations of user orders) and in the Market & Order Server (for order cancellations of any user) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t entry_date[4];                 /* bytes 20 to 23 */
  uint8_t retail_flag;                   /* byte 24 */
} OrderCancellationMarketMemberMessage;

/* any Order Cancellation Market Member Message at all: every byte one the checker chooses */
static void any_order_cancellation_market_member_message(OrderCancellationMarketMemberMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  record->retail_flag = arbitrary();
}

/* Order Cancellation Market Member Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_market_member_message(const OrderCancellationMarketMemberMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  wire[at++] = record->retail_flag;

  return at;
}

/* Order Cancellation Market Member Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_market_member_message(OrderCancellationMarketMemberMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  record->retail_flag = wire[at++];

  return at;
}

/* what was read of Order Cancellation Market Member Message is what was written, byte for byte */
static void equal_order_cancellation_market_member_message(const OrderCancellationMarketMemberMessage *read, const OrderCancellationMarketMemberMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  assert(read->retail_flag == written->retail_flag);
}

/* Order Cancellation Market Member Message: written and read back, then read and written back */
static void check_order_cancellation_market_member_message(void) {
  OrderCancellationMarketMemberMessage sent;
  OrderCancellationMarketMemberMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_order_cancellation_market_member_message(&sent);
  assert(encode_order_cancellation_market_member_message(&sent, wire, 0) == 25);
  assert(decode_order_cancellation_market_member_message(&got, wire, 0) == 25);
  equal_order_cancellation_market_member_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_market_member_message(&got, wire, 0) == 25);
  assert(encode_order_cancellation_market_member_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancellation Market Member Message: 25 bytes ---------------------- */

/* Used by the Server to communicate information about quote cancellation. The same message is used in Full-Depth data feeds (for quote cancellations of any user), in the Order Entry Server (for cancellations of user quotes) and in the Market & Order Server (for quote cancellations of any user) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t secondary_order_id_2[4];       /* bytes 20 to 23 */
  uint8_t retail_flag;                   /* byte 24 */
} QuoteCancellationMarketMemberMessage;

/* any Quote Cancellation Market Member Message at all: every byte one the checker chooses */
static void any_quote_cancellation_market_member_message(QuoteCancellationMarketMemberMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  record->retail_flag = arbitrary();
}

/* Quote Cancellation Market Member Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancellation_market_member_message(const QuoteCancellationMarketMemberMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  wire[at++] = record->retail_flag;

  return at;
}

/* Quote Cancellation Market Member Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancellation_market_member_message(QuoteCancellationMarketMemberMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  record->retail_flag = wire[at++];

  return at;
}

/* what was read of Quote Cancellation Market Member Message is what was written, byte for byte */
static void equal_quote_cancellation_market_member_message(const QuoteCancellationMarketMemberMessage *read, const QuoteCancellationMarketMemberMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  assert(read->retail_flag == written->retail_flag);
}

/* Quote Cancellation Market Member Message: written and read back, then read and written back */
static void check_quote_cancellation_market_member_message(void) {
  QuoteCancellationMarketMemberMessage sent;
  QuoteCancellationMarketMemberMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_quote_cancellation_market_member_message(&sent);
  assert(encode_quote_cancellation_market_member_message(&sent, wire, 0) == 25);
  assert(decode_quote_cancellation_market_member_message(&got, wire, 0) == 25);
  equal_quote_cancellation_market_member_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancellation_market_member_message(&got, wire, 0) == 25);
  assert(encode_quote_cancellation_market_member_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order And Quote Client Data Message: 97 bytes --------------------------- */

/* Sent by the client to set default attributes for subsequent orders and quotes. Please note that in Fixed Income it is possible to enter orders on behalf of other members (AccountMember), based on the corresponding brokerage permissions */
typedef struct {
  uint8_t request_id[4];                 /* bytes 0 to 3 */
  uint8_t client_data_id[2];             /* bytes 4 to 5 */
  uint8_t algorithmic_trade_indicator;   /* byte 6 */
  uint8_t client_id[4];                  /* bytes 7 to 10 */
  uint8_t account_bolsa[16];             /* bytes 11 to 26 */
  uint8_t account[5];                    /* bytes 27 to 31 */
  uint8_t dea_flag;                      /* byte 32 */
  uint8_t decisor_id[4];                 /* bytes 33 to 36 */
  uint8_t executor_id[4];                /* bytes 37 to 40 */
  uint8_t liquidity_provision_activity;  /* byte 41 */
  uint8_t give_in_member[4];             /* bytes 42 to 45 */
  uint8_t firm_mnemonic[10];             /* bytes 46 to 55 */
  uint8_t alloc_text[18];                /* bytes 56 to 73 */
  uint8_t last_capacity;                 /* byte 74 */
  uint8_t self_match_prevention_id[2];   /* bytes 75 to 76 */
  uint8_t automatic_order_filter_flag;   /* byte 77 */
  uint8_t received_dept_id;              /* byte 78 */
  uint8_t persistence;                   /* byte 79 */
  uint8_t account_type;                  /* byte 80 */
  uint8_t self_match_prevention_type;    /* byte 81 */
  uint8_t client_data_reference[15];     /* bytes 82 to 96 */
} OrderAndQuoteClientDataMessage;

/* any Order And Quote Client Data Message at all: every byte one the checker chooses */
static void any_order_and_quote_client_data_message(OrderAndQuoteClientDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  record->automatic_order_filter_flag = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  record->account_type = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Order And Quote Client Data Message to the wire: 97 bytes from at, returning where the next byte goes */
static size_t encode_order_and_quote_client_data_message(const OrderAndQuoteClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_in_member[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->firm_mnemonic[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->alloc_text[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  wire[at++] = record->automatic_order_filter_flag;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  wire[at++] = record->account_type;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Order And Quote Client Data Message off the wire: 97 bytes from at, returning where the next byte lies */
static size_t decode_order_and_quote_client_data_message(OrderAndQuoteClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  record->automatic_order_filter_flag = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  record->account_type = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Order And Quote Client Data Message is what was written, byte for byte */
static void equal_order_and_quote_client_data_message(const OrderAndQuoteClientDataMessage *read, const OrderAndQuoteClientDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->give_in_member[i] == written->give_in_member[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->firm_mnemonic[i] == written->firm_mnemonic[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->alloc_text[i] == written->alloc_text[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  assert(read->automatic_order_filter_flag == written->automatic_order_filter_flag);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  assert(read->account_type == written->account_type);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Order And Quote Client Data Message: written and read back, then read and written back */
static void check_order_and_quote_client_data_message(void) {
  OrderAndQuoteClientDataMessage sent;
  OrderAndQuoteClientDataMessage got;
  uint8_t wire[97];
  uint8_t again[97];

  any_order_and_quote_client_data_message(&sent);
  assert(encode_order_and_quote_client_data_message(&sent, wire, 0) == 97);
  assert(decode_order_and_quote_client_data_message(&got, wire, 0) == 97);
  equal_order_and_quote_client_data_message(&got, &sent);

  for (size_t i = 0; i < 97; i++) { wire[i] = arbitrary(); }
  assert(decode_order_and_quote_client_data_message(&got, wire, 0) == 97);
  assert(encode_order_and_quote_client_data_message(&got, again, 0) == 97);
  for (size_t i = 0; i < 97; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple New Order Message: 29 bytes -------------------------------------- */

/* Message sent by the client to enter a new order */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t client_data_id[2];  /* bytes 8 to 9 */
  uint8_t order_id[4];        /* bytes 10 to 13 */
  uint8_t side;               /* byte 14 */
  uint8_t price[8];           /* bytes 15 to 22 */
  uint8_t order_qty[4];       /* bytes 23 to 26 */
  uint8_t time_in_force;      /* byte 27 */
  uint8_t order_placement;    /* byte 28 */
} SimpleNewOrderMessage;

/* any Simple New Order Message at all: every byte one the checker chooses */
static void any_simple_new_order_message(SimpleNewOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->order_placement = arbitrary();
}

/* Simple New Order Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_simple_new_order_message(const SimpleNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->order_placement;

  return at;
}

/* Simple New Order Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_simple_new_order_message(SimpleNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->order_placement = wire[at++];

  return at;
}

/* what was read of Simple New Order Message is what was written, byte for byte */
static void equal_simple_new_order_message(const SimpleNewOrderMessage *read, const SimpleNewOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->order_placement == written->order_placement);
}

/* Simple New Order Message: written and read back, then read and written back */
static void check_simple_new_order_message(void) {
  SimpleNewOrderMessage sent;
  SimpleNewOrderMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_simple_new_order_message(&sent);
  assert(encode_simple_new_order_message(&sent, wire, 0) == 29);
  assert(decode_simple_new_order_message(&got, wire, 0) == 29);
  equal_simple_new_order_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_new_order_message(&got, wire, 0) == 29);
  assert(encode_simple_new_order_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple New Order With Client Data Message: 118 bytes -------------------- */

/* Message sent by the client to enter a new order and, at the same time, the values for the Client Data parmeters. Note that no ClientDataID may be assigned */
typedef struct {
  uint8_t request_id[4];                 /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t order_id[4];                   /* bytes 8 to 11 */
  uint8_t side;                          /* byte 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t order_qty[4];                  /* bytes 21 to 24 */
  uint8_t time_in_force;                 /* byte 25 */
  uint8_t order_placement;               /* byte 26 */
  uint8_t algorithmic_trade_indicator;   /* byte 27 */
  uint8_t client_id[4];                  /* bytes 28 to 31 */
  uint8_t account_bolsa[16];             /* bytes 32 to 47 */
  uint8_t account[5];                    /* bytes 48 to 52 */
  uint8_t dea_flag;                      /* byte 53 */
  uint8_t decisor_id[4];                 /* bytes 54 to 57 */
  uint8_t executor_id[4];                /* bytes 58 to 61 */
  uint8_t liquidity_provision_activity;  /* byte 62 */
  uint8_t give_in_member[4];             /* bytes 63 to 66 */
  uint8_t firm_mnemonic[10];             /* bytes 67 to 76 */
  uint8_t alloc_text[18];                /* bytes 77 to 94 */
  uint8_t last_capacity;                 /* byte 95 */
  uint8_t self_match_prevention_id[2];   /* bytes 96 to 97 */
  uint8_t automatic_order_filter_flag;   /* byte 98 */
  uint8_t received_dept_id;              /* byte 99 */
  uint8_t persistence;                   /* byte 100 */
  uint8_t account_type;                  /* byte 101 */
  uint8_t self_match_prevention_type;    /* byte 102 */
  uint8_t client_data_reference[15];     /* bytes 103 to 117 */
} SimpleNewOrderWithClientDataMessage;

/* any Simple New Order With Client Data Message at all: every byte one the checker chooses */
static void any_simple_new_order_with_client_data_message(SimpleNewOrderWithClientDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->time_in_force = arbitrary();
  record->order_placement = arbitrary();
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  record->automatic_order_filter_flag = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  record->account_type = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Simple New Order With Client Data Message to the wire: 118 bytes from at, returning where the next byte goes */
static size_t encode_simple_new_order_with_client_data_message(const SimpleNewOrderWithClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->order_placement;
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_in_member[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->firm_mnemonic[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->alloc_text[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  wire[at++] = record->automatic_order_filter_flag;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  wire[at++] = record->account_type;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Simple New Order With Client Data Message off the wire: 118 bytes from at, returning where the next byte lies */
static size_t decode_simple_new_order_with_client_data_message(SimpleNewOrderWithClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->order_placement = wire[at++];
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  record->automatic_order_filter_flag = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  record->account_type = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Simple New Order With Client Data Message is what was written, byte for byte */
static void equal_simple_new_order_with_client_data_message(const SimpleNewOrderWithClientDataMessage *read, const SimpleNewOrderWithClientDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->time_in_force == written->time_in_force);
  assert(read->order_placement == written->order_placement);
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->give_in_member[i] == written->give_in_member[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->firm_mnemonic[i] == written->firm_mnemonic[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->alloc_text[i] == written->alloc_text[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  assert(read->automatic_order_filter_flag == written->automatic_order_filter_flag);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  assert(read->account_type == written->account_type);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Simple New Order With Client Data Message: written and read back, then read and written back */
static void check_simple_new_order_with_client_data_message(void) {
  SimpleNewOrderWithClientDataMessage sent;
  SimpleNewOrderWithClientDataMessage got;
  uint8_t wire[118];
  uint8_t again[118];

  any_simple_new_order_with_client_data_message(&sent);
  assert(encode_simple_new_order_with_client_data_message(&sent, wire, 0) == 118);
  assert(decode_simple_new_order_with_client_data_message(&got, wire, 0) == 118);
  equal_simple_new_order_with_client_data_message(&got, &sent);

  for (size_t i = 0; i < 118; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_new_order_with_client_data_message(&got, wire, 0) == 118);
  assert(encode_simple_new_order_with_client_data_message(&got, again, 0) == 118);
  for (size_t i = 0; i < 118; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Order Modification Message: 27 bytes ----------------------------- */

/* Message sent by the client to modify an order. The field OrderID must contain the client reference of the order that is to be modified */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t order_id[4];        /* bytes 8 to 11 */
  uint8_t side;               /* byte 12 */
  uint8_t price[8];           /* bytes 13 to 20 */
  uint8_t order_qty[4];       /* bytes 21 to 24 */
  uint8_t client_data_id[2];  /* bytes 25 to 26 */
} SimpleOrderModificationMessage;

/* any Simple Order Modification Message at all: every byte one the checker chooses */
static void any_simple_order_modification_message(SimpleOrderModificationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Simple Order Modification Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_simple_order_modification_message(const SimpleOrderModificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Simple Order Modification Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_simple_order_modification_message(SimpleOrderModificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Order Modification Message is what was written, byte for byte */
static void equal_simple_order_modification_message(const SimpleOrderModificationMessage *read, const SimpleOrderModificationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Simple Order Modification Message: written and read back, then read and written back */
static void check_simple_order_modification_message(void) {
  SimpleOrderModificationMessage sent;
  SimpleOrderModificationMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_simple_order_modification_message(&sent);
  assert(encode_simple_order_modification_message(&sent, wire, 0) == 27);
  assert(decode_simple_order_modification_message(&got, wire, 0) == 27);
  equal_simple_order_modification_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_order_modification_message(&got, wire, 0) == 27);
  assert(encode_simple_order_modification_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Order Modification With Client Data Message: 116 bytes ----------- */

/* Message sent by the client to modify an order. The field OrderID must contain the client reference of the order that is to be modified */
typedef struct {
  uint8_t request_id[4];                 /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t order_id[4];                   /* bytes 8 to 11 */
  uint8_t side;                          /* byte 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t order_qty[4];                  /* bytes 21 to 24 */
  uint8_t algorithmic_trade_indicator;   /* byte 25 */
  uint8_t client_id[4];                  /* bytes 26 to 29 */
  uint8_t account_bolsa[16];             /* bytes 30 to 45 */
  uint8_t account[5];                    /* bytes 46 to 50 */
  uint8_t dea_flag;                      /* byte 51 */
  uint8_t decisor_id[4];                 /* bytes 52 to 55 */
  uint8_t executor_id[4];                /* bytes 56 to 59 */
  uint8_t liquidity_provision_activity;  /* byte 60 */
  uint8_t give_in_member[4];             /* bytes 61 to 64 */
  uint8_t firm_mnemonic[10];             /* bytes 65 to 74 */
  uint8_t alloc_text[18];                /* bytes 75 to 92 */
  uint8_t last_capacity;                 /* byte 93 */
  uint8_t self_match_prevention_id[2];   /* bytes 94 to 95 */
  uint8_t automatic_order_filter_flag;   /* byte 96 */
  uint8_t received_dept_id;              /* byte 97 */
  uint8_t persistence;                   /* byte 98 */
  uint8_t account_type;                  /* byte 99 */
  uint8_t self_match_prevention_type;    /* byte 100 */
  uint8_t client_data_reference[15];     /* bytes 101 to 115 */
} SimpleOrderModificationWithClientDataMessage;

/* any Simple Order Modification With Client Data Message at all: every byte one the checker chooses */
static void any_simple_order_modification_with_client_data_message(SimpleOrderModificationWithClientDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  record->automatic_order_filter_flag = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  record->account_type = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Simple Order Modification With Client Data Message to the wire: 116 bytes from at, returning where the next byte goes */
static size_t encode_simple_order_modification_with_client_data_message(const SimpleOrderModificationWithClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_in_member[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->firm_mnemonic[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->alloc_text[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  wire[at++] = record->automatic_order_filter_flag;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  wire[at++] = record->account_type;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Simple Order Modification With Client Data Message off the wire: 116 bytes from at, returning where the next byte lies */
static size_t decode_simple_order_modification_with_client_data_message(SimpleOrderModificationWithClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  record->automatic_order_filter_flag = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  record->account_type = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Order Modification With Client Data Message is what was written, byte for byte */
static void equal_simple_order_modification_with_client_data_message(const SimpleOrderModificationWithClientDataMessage *read, const SimpleOrderModificationWithClientDataMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->give_in_member[i] == written->give_in_member[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->firm_mnemonic[i] == written->firm_mnemonic[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->alloc_text[i] == written->alloc_text[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  assert(read->automatic_order_filter_flag == written->automatic_order_filter_flag);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  assert(read->account_type == written->account_type);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Simple Order Modification With Client Data Message: written and read back, then read and written back */
static void check_simple_order_modification_with_client_data_message(void) {
  SimpleOrderModificationWithClientDataMessage sent;
  SimpleOrderModificationWithClientDataMessage got;
  uint8_t wire[116];
  uint8_t again[116];

  any_simple_order_modification_with_client_data_message(&sent);
  assert(encode_simple_order_modification_with_client_data_message(&sent, wire, 0) == 116);
  assert(decode_simple_order_modification_with_client_data_message(&got, wire, 0) == 116);
  equal_simple_order_modification_with_client_data_message(&got, &sent);

  for (size_t i = 0; i < 116; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_order_modification_with_client_data_message(&got, wire, 0) == 116);
  assert(encode_simple_order_modification_with_client_data_message(&got, again, 0) == 116);
  for (size_t i = 0; i < 116; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancellation Request Message: 12 bytes ---------------------------- */

/* Message sent by the client to cancel an order. The field OrderID must contain a reference to the order that is to be cancelled */
typedef struct {
  uint8_t request_id[4];     /* bytes 0 to 3 */
  uint8_t security_code[4];  /* bytes 4 to 7 */
  uint8_t order_id[4];       /* bytes 8 to 11 */
} OrderCancellationRequestMessage;

/* any Order Cancellation Request Message at all: every byte one the checker chooses */
static void any_order_cancellation_request_message(OrderCancellationRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
}

/* Order Cancellation Request Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_request_message(const OrderCancellationRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }

  return at;
}

/* Order Cancellation Request Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_request_message(OrderCancellationRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Request Message is what was written, byte for byte */
static void equal_order_cancellation_request_message(const OrderCancellationRequestMessage *read, const OrderCancellationRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
}

/* Order Cancellation Request Message: written and read back, then read and written back */
static void check_order_cancellation_request_message(void) {
  OrderCancellationRequestMessage sent;
  OrderCancellationRequestMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_order_cancellation_request_message(&sent);
  assert(encode_order_cancellation_request_message(&sent, wire, 0) == 12);
  assert(decode_order_cancellation_request_message(&got, wire, 0) == 12);
  equal_order_cancellation_request_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_request_message(&got, wire, 0) == 12);
  assert(encode_order_cancellation_request_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Quote Message: 34 bytes --------------------------------------------- */

/* Message sent by the client application to create a new quote. A new quote by the same user on the same SecurityCode and with the same ClientDataID cancels the previous one */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t client_data_id[2];  /* bytes 8 to 9 */
  uint8_t bid_size_1[4];      /* bytes 10 to 13 */
  uint8_t bid_px_1[8];        /* bytes 14 to 21 */
  uint8_t ask_size_1[4];      /* bytes 22 to 25 */
  uint8_t ask_px_1[8];        /* bytes 26 to 33 */
} NewQuoteMessage;

/* any New Quote Message at all: every byte one the checker chooses */
static void any_new_quote_message(NewQuoteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
}

/* New Quote Message to the wire: 34 bytes from at, returning where the next byte goes */
static size_t encode_new_quote_message(const NewQuoteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->bid_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ask_size_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }

  return at;
}

/* New Quote Message off the wire: 34 bytes from at, returning where the next byte lies */
static size_t decode_new_quote_message(NewQuoteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->bid_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ask_size_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }

  return at;
}

/* what was read of New Quote Message is what was written, byte for byte */
static void equal_new_quote_message(const NewQuoteMessage *read, const NewQuoteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->bid_size_1[i] == written->bid_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ask_size_1[i] == written->ask_size_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
}

/* New Quote Message: written and read back, then read and written back */
static void check_new_quote_message(void) {
  NewQuoteMessage sent;
  NewQuoteMessage got;
  uint8_t wire[34];
  uint8_t again[34];

  any_new_quote_message(&sent);
  assert(encode_new_quote_message(&sent, wire, 0) == 34);
  assert(decode_new_quote_message(&got, wire, 0) == 34);
  equal_new_quote_message(&got, &sent);

  for (size_t i = 0; i < 34; i++) { wire[i] = arbitrary(); }
  assert(decode_new_quote_message(&got, wire, 0) == 34);
  assert(encode_new_quote_message(&got, again, 0) == 34);
  for (size_t i = 0; i < 34; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Modification Request Message: 26 bytes ---------------------------- */

/* Message sent by the client to modify a quote. Field ClientDataID is required in RF to identify a quote */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t client_data_id[2];  /* bytes 8 to 9 */
  uint8_t bid_px_1[8];        /* bytes 10 to 17 */
  uint8_t ask_px_1[8];        /* bytes 18 to 25 */
} QuoteModificationRequestMessage;

/* any Quote Modification Request Message at all: every byte one the checker chooses */
static void any_quote_modification_request_message(QuoteModificationRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = arbitrary(); }
}

/* Quote Modification Request Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_quote_modification_request_message(const QuoteModificationRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bid_px_1[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->ask_px_1[i]; }

  return at;
}

/* Quote Modification Request Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_quote_modification_request_message(QuoteModificationRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bid_px_1[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->ask_px_1[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Modification Request Message is what was written, byte for byte */
static void equal_quote_modification_request_message(const QuoteModificationRequestMessage *read, const QuoteModificationRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bid_px_1[i] == written->bid_px_1[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->ask_px_1[i] == written->ask_px_1[i]); }
}

/* Quote Modification Request Message: written and read back, then read and written back */
static void check_quote_modification_request_message(void) {
  QuoteModificationRequestMessage sent;
  QuoteModificationRequestMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_quote_modification_request_message(&sent);
  assert(encode_quote_modification_request_message(&sent, wire, 0) == 26);
  assert(decode_quote_modification_request_message(&got, wire, 0) == 26);
  equal_quote_modification_request_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_modification_request_message(&got, wire, 0) == 26);
  assert(encode_quote_modification_request_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancellation Request Message: 10 bytes ---------------------------- */

/* Message sent by the client to cancel a quote */
typedef struct {
  uint8_t request_id[4];      /* bytes 0 to 3 */
  uint8_t security_code[4];   /* bytes 4 to 7 */
  uint8_t client_data_id[2];  /* bytes 8 to 9 */
} QuoteCancellationRequestMessage;

/* any Quote Cancellation Request Message at all: every byte one the checker chooses */
static void any_quote_cancellation_request_message(QuoteCancellationRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Quote Cancellation Request Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancellation_request_message(const QuoteCancellationRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Quote Cancellation Request Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancellation_request_message(QuoteCancellationRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Cancellation Request Message is what was written, byte for byte */
static void equal_quote_cancellation_request_message(const QuoteCancellationRequestMessage *read, const QuoteCancellationRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Quote Cancellation Request Message: written and read back, then read and written back */
static void check_quote_cancellation_request_message(void) {
  QuoteCancellationRequestMessage sent;
  QuoteCancellationRequestMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_quote_cancellation_request_message(&sent);
  assert(encode_quote_cancellation_request_message(&sent, wire, 0) == 10);
  assert(decode_quote_cancellation_request_message(&got, wire, 0) == 10);
  equal_quote_cancellation_request_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancellation_request_message(&got, wire, 0) == 10);
  assert(encode_quote_cancellation_request_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Orderquote Cancellation Message: 38 bytes -------------------------- */

/* Message sent by the client to request the cancellation of multiple orders and or quotes, based on the specified selection criteria */
typedef struct {
  uint8_t request_id[4];          /* bytes 0 to 3 */
  uint8_t security_code[4];       /* bytes 4 to 7 */
  uint8_t side;                   /* byte 8 */
  uint8_t issuer[12];             /* bytes 9 to 20 */
  uint8_t account_bolsa[16];      /* bytes 21 to 36 */
  uint8_t order_or_quote_cancel;  /* byte 37 */
} MassOrderquoteCancellationMessage;

/* any Mass Orderquote Cancellation Message at all: every byte one the checker chooses */
static void any_mass_orderquote_cancellation_message(MassOrderquoteCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  record->order_or_quote_cancel = arbitrary();
}

/* Mass Orderquote Cancellation Message to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_mass_orderquote_cancellation_message(const MassOrderquoteCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->issuer[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  wire[at++] = record->order_or_quote_cancel;

  return at;
}

/* Mass Orderquote Cancellation Message off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_mass_orderquote_cancellation_message(MassOrderquoteCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->issuer[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  record->order_or_quote_cancel = wire[at++];

  return at;
}

/* what was read of Mass Orderquote Cancellation Message is what was written, byte for byte */
static void equal_mass_orderquote_cancellation_message(const MassOrderquoteCancellationMessage *read, const MassOrderquoteCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 12; i++) { assert(read->issuer[i] == written->issuer[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  assert(read->order_or_quote_cancel == written->order_or_quote_cancel);
}

/* Mass Orderquote Cancellation Message: written and read back, then read and written back */
static void check_mass_orderquote_cancellation_message(void) {
  MassOrderquoteCancellationMessage sent;
  MassOrderquoteCancellationMessage got;
  uint8_t wire[38];
  uint8_t again[38];

  any_mass_orderquote_cancellation_message(&sent);
  assert(encode_mass_orderquote_cancellation_message(&sent, wire, 0) == 38);
  assert(decode_mass_orderquote_cancellation_message(&got, wire, 0) == 38);
  equal_mass_orderquote_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_orderquote_cancellation_message(&got, wire, 0) == 38);
  assert(encode_mass_orderquote_cancellation_message(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order And Quote Client Data Parameters Ack Nack Message: 102 bytes ------ */

/* Sent by the server to confirm an Order and Quote Client Data Parameters message */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t request_id[4];                 /* bytes 4 to 7 */
  uint8_t status;                        /* byte 8 */
  uint8_t client_data_id[2];             /* bytes 9 to 10 */
  uint8_t algorithmic_trade_indicator;   /* byte 11 */
  uint8_t client_id[4];                  /* bytes 12 to 15 */
  uint8_t account_bolsa[16];             /* bytes 16 to 31 */
  uint8_t account[5];                    /* bytes 32 to 36 */
  uint8_t dea_flag;                      /* byte 37 */
  uint8_t decisor_id[4];                 /* bytes 38 to 41 */
  uint8_t executor_id[4];                /* bytes 42 to 45 */
  uint8_t liquidity_provision_activity;  /* byte 46 */
  uint8_t give_in_member[4];             /* bytes 47 to 50 */
  uint8_t firm_mnemonic[10];             /* bytes 51 to 60 */
  uint8_t alloc_text[18];                /* bytes 61 to 78 */
  uint8_t last_capacity;                 /* byte 79 */
  uint8_t self_match_prevention_id[2];   /* bytes 80 to 81 */
  uint8_t automatic_order_filter_flag;   /* byte 82 */
  uint8_t received_dept_id;              /* byte 83 */
  uint8_t persistence;                   /* byte 84 */
  uint8_t account_type;                  /* byte 85 */
  uint8_t self_match_prevention_type;    /* byte 86 */
  uint8_t client_data_reference[15];     /* bytes 87 to 101 */
} OrderAndQuoteClientDataParametersAckNackMessage;

/* any Order And Quote Client Data Parameters Ack Nack Message at all: every byte one the checker chooses */
static void any_order_and_quote_client_data_parameters_ack_nack_message(OrderAndQuoteClientDataParametersAckNackMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  record->automatic_order_filter_flag = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  record->account_type = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Order And Quote Client Data Parameters Ack Nack Message to the wire: 102 bytes from at, returning where the next byte goes */
static size_t encode_order_and_quote_client_data_parameters_ack_nack_message(const OrderAndQuoteClientDataParametersAckNackMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_in_member[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->firm_mnemonic[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->alloc_text[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  wire[at++] = record->automatic_order_filter_flag;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  wire[at++] = record->account_type;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Order And Quote Client Data Parameters Ack Nack Message off the wire: 102 bytes from at, returning where the next byte lies */
static size_t decode_order_and_quote_client_data_parameters_ack_nack_message(OrderAndQuoteClientDataParametersAckNackMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  record->automatic_order_filter_flag = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  record->account_type = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = wire[at++]; }

  return at;
}

/* what was read of Order And Quote Client Data Parameters Ack Nack Message is what was written, byte for byte */
static void equal_order_and_quote_client_data_parameters_ack_nack_message(const OrderAndQuoteClientDataParametersAckNackMessage *read, const OrderAndQuoteClientDataParametersAckNackMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->give_in_member[i] == written->give_in_member[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->firm_mnemonic[i] == written->firm_mnemonic[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->alloc_text[i] == written->alloc_text[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  assert(read->automatic_order_filter_flag == written->automatic_order_filter_flag);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  assert(read->account_type == written->account_type);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Order And Quote Client Data Parameters Ack Nack Message: written and read back, then read and written back */
static void check_order_and_quote_client_data_parameters_ack_nack_message(void) {
  OrderAndQuoteClientDataParametersAckNackMessage sent;
  OrderAndQuoteClientDataParametersAckNackMessage got;
  uint8_t wire[102];
  uint8_t again[102];

  any_order_and_quote_client_data_parameters_ack_nack_message(&sent);
  assert(encode_order_and_quote_client_data_parameters_ack_nack_message(&sent, wire, 0) == 102);
  assert(decode_order_and_quote_client_data_parameters_ack_nack_message(&got, wire, 0) == 102);
  equal_order_and_quote_client_data_parameters_ack_nack_message(&got, &sent);

  for (size_t i = 0; i < 102; i++) { wire[i] = arbitrary(); }
  assert(decode_order_and_quote_client_data_parameters_ack_nack_message(&got, wire, 0) == 102);
  assert(encode_order_and_quote_client_data_parameters_ack_nack_message(&got, again, 0) == 102);
  for (size_t i = 0; i < 102; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple Order Status Message: 62 bytes ----------------------------------- */

/* Sent by the server to inform about the order status. Please note that the first fields of this message are the same as the ones for Order Market Pre- Transparency Information (Msg Type = 0x03) (see section 5.4.12) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t entry_date[4];                 /* bytes 20 to 23 */
  uint8_t side;                          /* byte 24 */
  uint8_t priority[4];                   /* bytes 25 to 28 */
  uint8_t price[8];                      /* bytes 29 to 36 */
  uint8_t display_qty[4];                /* bytes 37 to 40 */
  uint8_t order_id[4];                   /* bytes 41 to 44 */
  uint8_t secondary_exec_id[4];          /* bytes 45 to 48 */
  uint8_t order_qty[4];                  /* bytes 49 to 52 */
  uint8_t ord_status;                    /* byte 53 */
  uint8_t ord_rej_reason;                /* byte 54 */
  uint8_t exec_type;                     /* byte 55 */
  uint8_t request_id[4];                 /* bytes 56 to 59 */
  uint8_t client_data_id[2];             /* bytes 60 to 61 */
} SimpleOrderStatusMessage;

/* any Simple Order Status Message at all: every byte one the checker chooses */
static void any_simple_order_status_message(SimpleOrderStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ord_rej_reason = arbitrary();
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Simple Order Status Message to the wire: 62 bytes from at, returning where the next byte goes */
static size_t encode_simple_order_status_message(const SimpleOrderStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ord_rej_reason;
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Simple Order Status Message off the wire: 62 bytes from at, returning where the next byte lies */
static size_t decode_simple_order_status_message(SimpleOrderStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ord_rej_reason = wire[at++];
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Simple Order Status Message is what was written, byte for byte */
static void equal_simple_order_status_message(const SimpleOrderStatusMessage *read, const SimpleOrderStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ord_rej_reason == written->ord_rej_reason);
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Simple Order Status Message: written and read back, then read and written back */
static void check_simple_order_status_message(void) {
  SimpleOrderStatusMessage sent;
  SimpleOrderStatusMessage got;
  uint8_t wire[62];
  uint8_t again[62];

  any_simple_order_status_message(&sent);
  assert(encode_simple_order_status_message(&sent, wire, 0) == 62);
  assert(decode_simple_order_status_message(&got, wire, 0) == 62);
  equal_simple_order_status_message(&got, &sent);

  for (size_t i = 0; i < 62; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_order_status_message(&got, wire, 0) == 62);
  assert(encode_simple_order_status_message(&got, again, 0) == 62);
  for (size_t i = 0; i < 62; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Status Message: 92 bytes ------------------------------------------ */

/* Sent by the server to inform about the status of a Quote */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t secondary_order_id_2[4];       /* bytes 20 to 23 */
  uint8_t priority[4];                   /* bytes 24 to 27 */
  uint8_t price[8];                      /* bytes 28 to 35 */
  uint8_t display_qty[4];                /* bytes 36 to 39 */
  uint8_t priority_2[4];                 /* bytes 40 to 43 */
  uint8_t price_2[8];                    /* bytes 44 to 51 */
  uint8_t display_qty_2[4];              /* bytes 52 to 55 */
  uint8_t order_id[4];                   /* bytes 56 to 59 */
  uint8_t secondary_exec_id[4];          /* bytes 60 to 63 */
  uint8_t order_qty[4];                  /* bytes 64 to 67 */
  uint8_t ord_status;                    /* byte 68 */
  uint8_t ord_rej_reason;                /* byte 69 */
  uint8_t exec_type;                     /* byte 70 */
  uint8_t order_id_2[4];                 /* bytes 71 to 74 */
  uint8_t secondary_exec_id_2[4];        /* bytes 75 to 78 */
  uint8_t order_qty_2[4];                /* bytes 79 to 82 */
  uint8_t ord_status_2;                  /* byte 83 */
  uint8_t ord_rej_reason_2;              /* byte 84 */
  uint8_t exec_type_2;                   /* byte 85 */
  uint8_t request_id[4];                 /* bytes 86 to 89 */
  uint8_t client_data_id[2];             /* bytes 90 to 91 */
} QuoteStatusMessage;

/* any Quote Status Message at all: every byte one the checker chooses */
static void any_quote_status_message(QuoteStatusMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ord_rej_reason = arbitrary();
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = arbitrary(); }
  record->ord_status_2 = arbitrary();
  record->ord_rej_reason_2 = arbitrary();
  record->exec_type_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Quote Status Message to the wire: 92 bytes from at, returning where the next byte goes */
static size_t encode_quote_status_message(const QuoteStatusMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ord_rej_reason;
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty_2[i]; }
  wire[at++] = record->ord_status_2;
  wire[at++] = record->ord_rej_reason_2;
  wire[at++] = record->exec_type_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Quote Status Message off the wire: 92 bytes from at, returning where the next byte lies */
static size_t decode_quote_status_message(QuoteStatusMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ord_rej_reason = wire[at++];
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = wire[at++]; }
  record->ord_status_2 = wire[at++];
  record->ord_rej_reason_2 = wire[at++];
  record->exec_type_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Status Message is what was written, byte for byte */
static void equal_quote_status_message(const QuoteStatusMessage *read, const QuoteStatusMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ord_rej_reason == written->ord_rej_reason);
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 4; i++) { assert(read->order_id_2[i] == written->order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id_2[i] == written->secondary_exec_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty_2[i] == written->order_qty_2[i]); }
  assert(read->ord_status_2 == written->ord_status_2);
  assert(read->ord_rej_reason_2 == written->ord_rej_reason_2);
  assert(read->exec_type_2 == written->exec_type_2);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Quote Status Message: written and read back, then read and written back */
static void check_quote_status_message(void) {
  QuoteStatusMessage sent;
  QuoteStatusMessage got;
  uint8_t wire[92];
  uint8_t again[92];

  any_quote_status_message(&sent);
  assert(encode_quote_status_message(&sent, wire, 0) == 92);
  assert(decode_quote_status_message(&got, wire, 0) == 92);
  equal_quote_status_message(&got, &sent);

  for (size_t i = 0; i < 92; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_status_message(&got, wire, 0) == 92);
  assert(encode_quote_status_message(&got, again, 0) == 92);
  for (size_t i = 0; i < 92; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Cancel Reject Message: 23 bytes ----------------------------------- */

/* Sent by the server to inform about the rejection of a Simple order modification (MsgType = 0x47) or an Order cancellation request (MsgType = 0x46) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t transaction_date_and_time[8];  /* bytes 4 to 11 */
  uint8_t order_id[4];                   /* bytes 12 to 15 */
  uint8_t ord_status;                    /* byte 16 */
  uint8_t cxl_rej_response_to;           /* byte 17 */
  uint8_t cxl_rej_reason;                /* byte 18 */
  uint8_t request_id[4];                 /* bytes 19 to 22 */
} OrderCancelRejectMessage;

/* any Order Cancel Reject Message at all: every byte one the checker chooses */
static void any_order_cancel_reject_message(OrderCancelRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->cxl_rej_response_to = arbitrary();
  record->cxl_rej_reason = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Order Cancel Reject Message to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_order_cancel_reject_message(const OrderCancelRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->cxl_rej_response_to;
  wire[at++] = record->cxl_rej_reason;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Order Cancel Reject Message off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_order_cancel_reject_message(OrderCancelRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->cxl_rej_response_to = wire[at++];
  record->cxl_rej_reason = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancel Reject Message is what was written, byte for byte */
static void equal_order_cancel_reject_message(const OrderCancelRejectMessage *read, const OrderCancelRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->cxl_rej_response_to == written->cxl_rej_response_to);
  assert(read->cxl_rej_reason == written->cxl_rej_reason);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Order Cancel Reject Message: written and read back, then read and written back */
static void check_order_cancel_reject_message(void) {
  OrderCancelRejectMessage sent;
  OrderCancelRejectMessage got;
  uint8_t wire[23];
  uint8_t again[23];

  any_order_cancel_reject_message(&sent);
  assert(encode_order_cancel_reject_message(&sent, wire, 0) == 23);
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 23);
  equal_order_cancel_reject_message(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancel_reject_message(&got, wire, 0) == 23);
  assert(encode_order_cancel_reject_message(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Orderquote Cancellation Completion Message: 18 bytes --------------- */

/* Message reporting the completion of a valid mass order cancellation request. More than one message may be sent for a single RequestID */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t transaction_date_and_time[8];  /* bytes 4 to 11 */
  uint8_t trading_unit;                  /* byte 12 */
  uint8_t order_or_quote_cancel;         /* byte 13 */
  uint8_t request_id[4];                 /* bytes 14 to 17 */
} MassOrderquoteCancellationCompletionMessage;

/* any Mass Orderquote Cancellation Completion Message at all: every byte one the checker chooses */
static void any_mass_orderquote_cancellation_completion_message(MassOrderquoteCancellationCompletionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  record->trading_unit = arbitrary();
  record->order_or_quote_cancel = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Mass Orderquote Cancellation Completion Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_mass_orderquote_cancellation_completion_message(const MassOrderquoteCancellationCompletionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  wire[at++] = record->trading_unit;
  wire[at++] = record->order_or_quote_cancel;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Mass Orderquote Cancellation Completion Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_mass_orderquote_cancellation_completion_message(MassOrderquoteCancellationCompletionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  record->trading_unit = wire[at++];
  record->order_or_quote_cancel = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Orderquote Cancellation Completion Message is what was written, byte for byte */
static void equal_mass_orderquote_cancellation_completion_message(const MassOrderquoteCancellationCompletionMessage *read, const MassOrderquoteCancellationCompletionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  assert(read->trading_unit == written->trading_unit);
  assert(read->order_or_quote_cancel == written->order_or_quote_cancel);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Mass Orderquote Cancellation Completion Message: written and read back, then read and written back */
static void check_mass_orderquote_cancellation_completion_message(void) {
  MassOrderquoteCancellationCompletionMessage sent;
  MassOrderquoteCancellationCompletionMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_mass_orderquote_cancellation_completion_message(&sent);
  assert(encode_mass_orderquote_cancellation_completion_message(&sent, wire, 0) == 18);
  assert(decode_mass_orderquote_cancellation_completion_message(&got, wire, 0) == 18);
  equal_mass_orderquote_cancellation_completion_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_orderquote_cancellation_completion_message(&got, wire, 0) == 18);
  assert(encode_mass_orderquote_cancellation_completion_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Orderquote Cancellation Reject Message: 14 bytes ------------------- */

/* Message reporting the rejection of a mass order cancellation request. More than one message may be sent for a single RequestID */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t transaction_date_and_time[8];  /* bytes 4 to 11 */
  uint8_t trading_unit;                  /* byte 12 */
  uint8_t mass_cancel_reject_reason;     /* byte 13 */
} MassOrderquoteCancellationRejectMessage;

/* any Mass Orderquote Cancellation Reject Message at all: every byte one the checker chooses */
static void any_mass_orderquote_cancellation_reject_message(MassOrderquoteCancellationRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  record->trading_unit = arbitrary();
  record->mass_cancel_reject_reason = arbitrary();
}

/* Mass Orderquote Cancellation Reject Message to the wire: 14 bytes from at, returning where the next byte goes */
static size_t encode_mass_orderquote_cancellation_reject_message(const MassOrderquoteCancellationRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  wire[at++] = record->trading_unit;
  wire[at++] = record->mass_cancel_reject_reason;

  return at;
}

/* Mass Orderquote Cancellation Reject Message off the wire: 14 bytes from at, returning where the next byte lies */
static size_t decode_mass_orderquote_cancellation_reject_message(MassOrderquoteCancellationRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  record->trading_unit = wire[at++];
  record->mass_cancel_reject_reason = wire[at++];

  return at;
}

/* what was read of Mass Orderquote Cancellation Reject Message is what was written, byte for byte */
static void equal_mass_orderquote_cancellation_reject_message(const MassOrderquoteCancellationRejectMessage *read, const MassOrderquoteCancellationRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  assert(read->trading_unit == written->trading_unit);
  assert(read->mass_cancel_reject_reason == written->mass_cancel_reject_reason);
}

/* Mass Orderquote Cancellation Reject Message: written and read back, then read and written back */
static void check_mass_orderquote_cancellation_reject_message(void) {
  MassOrderquoteCancellationRejectMessage sent;
  MassOrderquoteCancellationRejectMessage got;
  uint8_t wire[14];
  uint8_t again[14];

  any_mass_orderquote_cancellation_reject_message(&sent);
  assert(encode_mass_orderquote_cancellation_reject_message(&sent, wire, 0) == 14);
  assert(decode_mass_orderquote_cancellation_reject_message(&got, wire, 0) == 14);
  equal_mass_orderquote_cancellation_reject_message(&got, &sent);

  for (size_t i = 0; i < 14; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_orderquote_cancellation_reject_message(&got, wire, 0) == 14);
  assert(encode_mass_orderquote_cancellation_reject_message(&got, again, 0) == 14);
  for (size_t i = 0; i < 14; i++) { assert(again[i] == wire[i]); }
}

/* ---- Business Message Reject Message: 83 bytes ------------------------------- */

/* It may be sent by the server to inform about the rejection of a supported message that is syntactically correct in an unsupported situation */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t transaction_date_and_time[8];  /* bytes 4 to 11 */
  uint8_t ref_msg_type;                  /* byte 12 */
  uint8_t business_reject_reason;        /* byte 13 */
  uint8_t text_c_65[65];                 /* bytes 14 to 78 */
  uint8_t request_id[4];                 /* bytes 79 to 82 */
} BusinessMessageRejectMessage;

/* any Business Message Reject Message at all: every byte one the checker chooses */
static void any_business_message_reject_message(BusinessMessageRejectMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  record->ref_msg_type = arbitrary();
  record->business_reject_reason = arbitrary();
  for (size_t i = 0; i < 65; i++) { record->text_c_65[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
}

/* Business Message Reject Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_business_message_reject_message(const BusinessMessageRejectMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  wire[at++] = record->ref_msg_type;
  wire[at++] = record->business_reject_reason;
  for (size_t i = 0; i < 65; i++) { wire[at++] = record->text_c_65[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }

  return at;
}

/* Business Message Reject Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_business_message_reject_message(BusinessMessageRejectMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  record->ref_msg_type = wire[at++];
  record->business_reject_reason = wire[at++];
  for (size_t i = 0; i < 65; i++) { record->text_c_65[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }

  return at;
}

/* what was read of Business Message Reject Message is what was written, byte for byte */
static void equal_business_message_reject_message(const BusinessMessageRejectMessage *read, const BusinessMessageRejectMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  assert(read->ref_msg_type == written->ref_msg_type);
  assert(read->business_reject_reason == written->business_reject_reason);
  for (size_t i = 0; i < 65; i++) { assert(read->text_c_65[i] == written->text_c_65[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
}

/* Business Message Reject Message: written and read back, then read and written back */
static void check_business_message_reject_message(void) {
  BusinessMessageRejectMessage sent;
  BusinessMessageRejectMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_business_message_reject_message(&sent);
  assert(encode_business_message_reject_message(&sent, wire, 0) == 83);
  assert(decode_business_message_reject_message(&got, wire, 0) == 83);
  equal_business_message_reject_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_business_message_reject_message(&got, wire, 0) == 83);
  assert(encode_business_message_reject_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Private Information 2 Legs Message: 145 bytes ----------------- */

/* Sent by the server to inform about a trade where two orders of the user are involved both as Buyer and Seller */
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
  uint8_t buyer_bolsa_code;              /* byte 49 */
  uint8_t settl_date[4];                 /* bytes 50 to 53 */
  uint8_t transaction_category;          /* byte 54 */
  uint8_t secondary_order_id[4];         /* bytes 55 to 58 */
  uint8_t entry_date[4];                 /* bytes 59 to 62 */
  uint8_t priority[4];                   /* bytes 63 to 66 */
  uint8_t price[8];                      /* bytes 67 to 74 */
  uint8_t display_qty[4];                /* bytes 75 to 78 */
  uint8_t order_id[4];                   /* bytes 79 to 82 */
  uint8_t secondary_exec_id[4];          /* bytes 83 to 86 */
  uint8_t order_qty[4];                  /* bytes 87 to 90 */
  uint8_t ord_status;                    /* byte 91 */
  uint8_t ccp_code;                      /* byte 92 */
  uint8_t aggressor_indicator;           /* byte 93 */
  uint8_t request_id[4];                 /* bytes 94 to 97 */
  uint8_t client_data_id[2];             /* bytes 98 to 99 */
  uint8_t secondary_order_id_2[4];       /* bytes 100 to 103 */
  uint8_t entry_date_2[4];               /* bytes 104 to 107 */
  uint8_t priority_2[4];                 /* bytes 108 to 111 */
  uint8_t price_2[8];                    /* bytes 112 to 119 */
  uint8_t display_qty_2[4];              /* bytes 120 to 123 */
  uint8_t order_id_2[4];                 /* bytes 124 to 127 */
  uint8_t secondary_exec_id_2[4];        /* bytes 128 to 131 */
  uint8_t order_qty_2[4];                /* bytes 132 to 135 */
  uint8_t ord_status_2;                  /* byte 136 */
  uint8_t ccp_code_2;                    /* byte 137 */
  uint8_t aggressor_indicator_2;         /* byte 138 */
  uint8_t request_id_2[4];               /* bytes 139 to 142 */
  uint8_t client_data_id_2[2];           /* bytes 143 to 144 */
} ExecutionPrivateInformation2LegsMessage;

/* any Execution Private Information 2 Legs Message at all: every byte one the checker chooses */
static void any_execution_private_information2_legs_message(ExecutionPrivateInformation2LegsMessage *record) {
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = arbitrary(); }
  record->ord_status_2 = arbitrary();
  record->ccp_code_2 = arbitrary();
  record->aggressor_indicator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id_2[i] = arbitrary(); }
}

/* Execution Private Information 2 Legs Message to the wire: 145 bytes from at, returning where the next byte goes */
static size_t encode_execution_private_information2_legs_message(const ExecutionPrivateInformation2LegsMessage *record, uint8_t *wire, size_t at) {
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty_2[i]; }
  wire[at++] = record->ord_status_2;
  wire[at++] = record->ccp_code_2;
  wire[at++] = record->aggressor_indicator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id_2[i]; }

  return at;
}

/* Execution Private Information 2 Legs Message off the wire: 145 bytes from at, returning where the next byte lies */
static size_t decode_execution_private_information2_legs_message(ExecutionPrivateInformation2LegsMessage *record, const uint8_t *wire, size_t at) {
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
  record->buyer_bolsa_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = wire[at++]; }
  record->ord_status_2 = wire[at++];
  record->ccp_code_2 = wire[at++];
  record->aggressor_indicator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id_2[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Private Information 2 Legs Message is what was written, byte for byte */
static void equal_execution_private_information2_legs_message(const ExecutionPrivateInformation2LegsMessage *read, const ExecutionPrivateInformation2LegsMessage *written) {
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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date_2[i] == written->entry_date_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id_2[i] == written->order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id_2[i] == written->secondary_exec_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty_2[i] == written->order_qty_2[i]); }
  assert(read->ord_status_2 == written->ord_status_2);
  assert(read->ccp_code_2 == written->ccp_code_2);
  assert(read->aggressor_indicator_2 == written->aggressor_indicator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id_2[i] == written->request_id_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id_2[i] == written->client_data_id_2[i]); }
}

/* Execution Private Information 2 Legs Message: written and read back, then read and written back */
static void check_execution_private_information2_legs_message(void) {
  ExecutionPrivateInformation2LegsMessage sent;
  ExecutionPrivateInformation2LegsMessage got;
  uint8_t wire[145];
  uint8_t again[145];

  any_execution_private_information2_legs_message(&sent);
  assert(encode_execution_private_information2_legs_message(&sent, wire, 0) == 145);
  assert(decode_execution_private_information2_legs_message(&got, wire, 0) == 145);
  equal_execution_private_information2_legs_message(&got, &sent);

  for (size_t i = 0; i < 145; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information2_legs_message(&got, wire, 0) == 145);
  assert(encode_execution_private_information2_legs_message(&got, again, 0) == 145);
  for (size_t i = 0; i < 145; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message: 317 bytes ---- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. The user is involved in the trade as Buyer. It is also sent to inform about the amendment or cancellation of whatever origin trade where the user is involved as Buyer. Shares the same layout as the next message */
typedef struct {
  uint8_t sequence_number[4];             /* bytes 0 to 3 */
  uint8_t security_code[4];               /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];   /* bytes 8 to 15 */
  uint8_t market_segment_id[4];           /* bytes 16 to 19 */
  uint8_t trading_session_id;             /* byte 20 */
  uint8_t trd_match_id[4];                /* bytes 21 to 24 */
  uint8_t trade_type;                     /* byte 25 */
  uint8_t last_px[8];                     /* bytes 26 to 33 */
  uint8_t last_qty[4];                    /* bytes 34 to 37 */
  uint8_t gross_trade_amt[8];             /* bytes 38 to 45 */
  uint8_t designation;                    /* byte 46 */
  uint8_t market_mechanism;               /* byte 47 */
  uint8_t algo_flag;                      /* byte 48 */
  uint8_t buyer_bolsa_code;               /* byte 49 */
  uint8_t settl_date[4];                  /* bytes 50 to 53 */
  uint8_t transaction_category;           /* byte 54 */
  uint8_t last_change_flag;               /* byte 55 */
  uint8_t benc_rfpt_flag;                 /* byte 56 */
  uint8_t trade_price_condition;          /* byte 57 */
  uint8_t pre_trade_transparency_waiver;  /* byte 58 */
  uint8_t deferral_waiver;                /* byte 59 */
  uint8_t publish_date_and_time[8];       /* bytes 60 to 67 */
  uint8_t trade_date[8];                  /* bytes 68 to 75 */
  uint8_t trade_session_date[4];          /* bytes 76 to 79 */
  uint8_t volume_float[8];                /* bytes 80 to 87 */
  uint8_t sicav_fund_counterparty_side;   /* byte 88 */
  uint8_t amended_trade_type;             /* byte 89 */
  uint8_t exec_ref_id[4];                 /* bytes 90 to 93 */
  uint8_t amended_trade_date[4];          /* bytes 94 to 97 */
  uint8_t secondary_order_id[4];          /* bytes 98 to 101 */
  uint8_t entry_date[4];                  /* bytes 102 to 105 */
  uint8_t priority[4];                    /* bytes 106 to 109 */
  uint8_t price[8];                       /* bytes 110 to 117 */
  uint8_t display_qty[4];                 /* bytes 118 to 121 */
  uint8_t order_id[4];                    /* bytes 122 to 125 */
  uint8_t secondary_exec_id[4];           /* bytes 126 to 129 */
  uint8_t order_qty[4];                   /* bytes 130 to 133 */
  uint8_t ord_status;                     /* byte 134 */
  uint8_t ccp_code;                       /* byte 135 */
  uint8_t aggressor_indicator;            /* byte 136 */
  uint8_t request_id[4];                  /* bytes 137 to 140 */
  uint8_t client_data_id[2];              /* bytes 141 to 142 */
  uint8_t algorithmic_trade_indicator;    /* byte 143 */
  uint8_t client_id[4];                   /* bytes 144 to 147 */
  uint8_t account_bolsa[16];              /* bytes 148 to 163 */
  uint8_t account[5];                     /* bytes 164 to 168 */
  uint8_t dea_flag;                       /* byte 169 */
  uint8_t decisor_id[4];                  /* bytes 170 to 173 */
  uint8_t executor_id[4];                 /* bytes 174 to 177 */
  uint8_t liquidity_provision_activity;   /* byte 178 */
  uint8_t give_in_member[4];              /* bytes 179 to 182 */
  uint8_t firm_mnemonic[10];              /* bytes 183 to 192 */
  uint8_t alloc_text[18];                 /* bytes 193 to 210 */
  uint8_t last_capacity;                  /* byte 211 */
  uint8_t self_match_prevention_id[2];    /* bytes 212 to 213 */
  uint8_t automatic_order_filter_flag;    /* byte 214 */
  uint8_t received_dept_id;               /* byte 215 */
  uint8_t persistence;                    /* byte 216 */
  uint8_t account_type;                   /* byte 217 */
  uint8_t self_match_prevention_type;     /* byte 218 */
  uint8_t member[4];                      /* bytes 219 to 222 */
  uint8_t trader[3];                      /* bytes 223 to 225 */
  uint8_t sub_member;                     /* byte 226 */
  uint8_t cross_id[4];                    /* bytes 227 to 230 */
  uint8_t bolsa_code;                     /* byte 231 */
  uint8_t csdbic[11];                     /* bytes 232 to 242 */
  uint8_t participant[11];                /* bytes 243 to 253 */
  uint8_t cta_liq[35];                    /* bytes 254 to 288 */
  uint8_t ccv[20];                        /* bytes 289 to 308 */
  uint8_t order_security_code[4];         /* bytes 309 to 312 */
  uint8_t external_member[4];             /* bytes 313 to 316 */
} TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1;

/* any Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message at all: every byte one the checker chooses */
static void any_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *record) {
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  record->last_change_flag = arbitrary();
  record->benc_rfpt_flag = arbitrary();
  record->trade_price_condition = arbitrary();
  record->pre_trade_transparency_waiver = arbitrary();
  record->deferral_waiver = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_float[i] = arbitrary(); }
  record->sicav_fund_counterparty_side = arbitrary();
  record->amended_trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  record->automatic_order_filter_flag = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  record->account_type = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  record->bolsa_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->csdbic[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->participant[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->cta_liq[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message to the wire: 317 bytes from at, returning where the next byte goes */
static size_t encode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(const TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *record, uint8_t *wire, size_t at) {
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  wire[at++] = record->last_change_flag;
  wire[at++] = record->benc_rfpt_flag;
  wire[at++] = record->trade_price_condition;
  wire[at++] = record->pre_trade_transparency_waiver;
  wire[at++] = record->deferral_waiver;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->publish_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_session_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_float[i]; }
  wire[at++] = record->sicav_fund_counterparty_side;
  wire[at++] = record->amended_trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amended_trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_in_member[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->firm_mnemonic[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->alloc_text[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  wire[at++] = record->automatic_order_filter_flag;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  wire[at++] = record->account_type;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  wire[at++] = record->bolsa_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->csdbic[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->participant[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->cta_liq[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ccv[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_member[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message off the wire: 317 bytes from at, returning where the next byte lies */
static size_t decode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *record, const uint8_t *wire, size_t at) {
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
  record->buyer_bolsa_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  record->last_change_flag = wire[at++];
  record->benc_rfpt_flag = wire[at++];
  record->trade_price_condition = wire[at++];
  record->pre_trade_transparency_waiver = wire[at++];
  record->deferral_waiver = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_float[i] = wire[at++]; }
  record->sicav_fund_counterparty_side = wire[at++];
  record->amended_trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  record->automatic_order_filter_flag = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  record->account_type = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  record->bolsa_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->csdbic[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->participant[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->cta_liq[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message is what was written, byte for byte */
static void equal_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(const TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *read, const TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 *written) {
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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  assert(read->last_change_flag == written->last_change_flag);
  assert(read->benc_rfpt_flag == written->benc_rfpt_flag);
  assert(read->trade_price_condition == written->trade_price_condition);
  assert(read->pre_trade_transparency_waiver == written->pre_trade_transparency_waiver);
  assert(read->deferral_waiver == written->deferral_waiver);
  for (size_t i = 0; i < 8; i++) { assert(read->publish_date_and_time[i] == written->publish_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_session_date[i] == written->trade_session_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_float[i] == written->volume_float[i]); }
  assert(read->sicav_fund_counterparty_side == written->sicav_fund_counterparty_side);
  assert(read->amended_trade_type == written->amended_trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amended_trade_date[i] == written->amended_trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->give_in_member[i] == written->give_in_member[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->firm_mnemonic[i] == written->firm_mnemonic[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->alloc_text[i] == written->alloc_text[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  assert(read->automatic_order_filter_flag == written->automatic_order_filter_flag);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  assert(read->account_type == written->account_type);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  assert(read->bolsa_code == written->bolsa_code);
  for (size_t i = 0; i < 11; i++) { assert(read->csdbic[i] == written->csdbic[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->participant[i] == written->participant[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->cta_liq[i] == written->cta_liq[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ccv[i] == written->ccv[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->external_member[i] == written->external_member[i]); }
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(void) {
  TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 sent;
  TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 got;
  uint8_t wire[317];
  uint8_t again[317];

  any_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&sent);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&sent, wire, 0) == 317);
  assert(decode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, wire, 0) == 317);
  equal_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, &sent);

  for (size_t i = 0; i < 317; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, wire, 0) == 317);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, again, 0) == 317);
  for (size_t i = 0; i < 317; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message: 317 bytes ---- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. The user is involved in the trade as Seller */
typedef struct {
  uint8_t sequence_number[4];             /* bytes 0 to 3 */
  uint8_t security_code[4];               /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];   /* bytes 8 to 15 */
  uint8_t market_segment_id[4];           /* bytes 16 to 19 */
  uint8_t trading_session_id;             /* byte 20 */
  uint8_t trd_match_id[4];                /* bytes 21 to 24 */
  uint8_t trade_type;                     /* byte 25 */
  uint8_t last_px[8];                     /* bytes 26 to 33 */
  uint8_t last_qty[4];                    /* bytes 34 to 37 */
  uint8_t gross_trade_amt[8];             /* bytes 38 to 45 */
  uint8_t designation;                    /* byte 46 */
  uint8_t market_mechanism;               /* byte 47 */
  uint8_t algo_flag;                      /* byte 48 */
  uint8_t buyer_bolsa_code;               /* byte 49 */
  uint8_t settl_date[4];                  /* bytes 50 to 53 */
  uint8_t transaction_category;           /* byte 54 */
  uint8_t last_change_flag;               /* byte 55 */
  uint8_t benc_rfpt_flag;                 /* byte 56 */
  uint8_t trade_price_condition;          /* byte 57 */
  uint8_t pre_trade_transparency_waiver;  /* byte 58 */
  uint8_t deferral_waiver;                /* byte 59 */
  uint8_t publish_date_and_time[8];       /* bytes 60 to 67 */
  uint8_t trade_date[8];                  /* bytes 68 to 75 */
  uint8_t trade_session_date[4];          /* bytes 76 to 79 */
  uint8_t volume_float[8];                /* bytes 80 to 87 */
  uint8_t sicav_fund_counterparty_side;   /* byte 88 */
  uint8_t amended_trade_type;             /* byte 89 */
  uint8_t exec_ref_id[4];                 /* bytes 90 to 93 */
  uint8_t amended_trade_date[4];          /* bytes 94 to 97 */
  uint8_t secondary_order_id[4];          /* bytes 98 to 101 */
  uint8_t entry_date[4];                  /* bytes 102 to 105 */
  uint8_t priority[4];                    /* bytes 106 to 109 */
  uint8_t price[8];                       /* bytes 110 to 117 */
  uint8_t display_qty[4];                 /* bytes 118 to 121 */
  uint8_t order_id[4];                    /* bytes 122 to 125 */
  uint8_t secondary_exec_id[4];           /* bytes 126 to 129 */
  uint8_t order_qty[4];                   /* bytes 130 to 133 */
  uint8_t ord_status;                     /* byte 134 */
  uint8_t ccp_code;                       /* byte 135 */
  uint8_t aggressor_indicator;            /* byte 136 */
  uint8_t request_id[4];                  /* bytes 137 to 140 */
  uint8_t client_data_id[2];              /* bytes 141 to 142 */
  uint8_t algorithmic_trade_indicator;    /* byte 143 */
  uint8_t client_id[4];                   /* bytes 144 to 147 */
  uint8_t account_bolsa[16];              /* bytes 148 to 163 */
  uint8_t account[5];                     /* bytes 164 to 168 */
  uint8_t dea_flag;                       /* byte 169 */
  uint8_t decisor_id[4];                  /* bytes 170 to 173 */
  uint8_t executor_id[4];                 /* bytes 174 to 177 */
  uint8_t liquidity_provision_activity;   /* byte 178 */
  uint8_t give_in_member[4];              /* bytes 179 to 182 */
  uint8_t firm_mnemonic[10];              /* bytes 183 to 192 */
  uint8_t alloc_text[18];                 /* bytes 193 to 210 */
  uint8_t last_capacity;                  /* byte 211 */
  uint8_t self_match_prevention_id[2];    /* bytes 212 to 213 */
  uint8_t automatic_order_filter_flag;    /* byte 214 */
  uint8_t received_dept_id;               /* byte 215 */
  uint8_t persistence;                    /* byte 216 */
  uint8_t account_type;                   /* byte 217 */
  uint8_t self_match_prevention_type;     /* byte 218 */
  uint8_t member[4];                      /* bytes 219 to 222 */
  uint8_t trader[3];                      /* bytes 223 to 225 */
  uint8_t sub_member;                     /* byte 226 */
  uint8_t cross_id[4];                    /* bytes 227 to 230 */
  uint8_t bolsa_code;                     /* byte 231 */
  uint8_t csdbic[11];                     /* bytes 232 to 242 */
  uint8_t participant[11];                /* bytes 243 to 253 */
  uint8_t cta_liq[35];                    /* bytes 254 to 288 */
  uint8_t ccv[20];                        /* bytes 289 to 308 */
  uint8_t order_security_code[4];         /* bytes 309 to 312 */
  uint8_t external_member[4];             /* bytes 313 to 316 */
} TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv;

/* any Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message at all: every byte one the checker chooses */
static void any_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *record) {
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  record->last_change_flag = arbitrary();
  record->benc_rfpt_flag = arbitrary();
  record->trade_price_condition = arbitrary();
  record->pre_trade_transparency_waiver = arbitrary();
  record->deferral_waiver = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_float[i] = arbitrary(); }
  record->sicav_fund_counterparty_side = arbitrary();
  record->amended_trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  record->automatic_order_filter_flag = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  record->account_type = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  record->bolsa_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->csdbic[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->participant[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->cta_liq[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message to the wire: 317 bytes from at, returning where the next byte goes */
static size_t encode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(const TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *record, uint8_t *wire, size_t at) {
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  wire[at++] = record->last_change_flag;
  wire[at++] = record->benc_rfpt_flag;
  wire[at++] = record->trade_price_condition;
  wire[at++] = record->pre_trade_transparency_waiver;
  wire[at++] = record->deferral_waiver;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->publish_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_session_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_float[i]; }
  wire[at++] = record->sicav_fund_counterparty_side;
  wire[at++] = record->amended_trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amended_trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_in_member[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->firm_mnemonic[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->alloc_text[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  wire[at++] = record->automatic_order_filter_flag;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  wire[at++] = record->account_type;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  wire[at++] = record->bolsa_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->csdbic[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->participant[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->cta_liq[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ccv[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_member[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message off the wire: 317 bytes from at, returning where the next byte lies */
static size_t decode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *record, const uint8_t *wire, size_t at) {
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
  record->buyer_bolsa_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  record->last_change_flag = wire[at++];
  record->benc_rfpt_flag = wire[at++];
  record->trade_price_condition = wire[at++];
  record->pre_trade_transparency_waiver = wire[at++];
  record->deferral_waiver = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_float[i] = wire[at++]; }
  record->sicav_fund_counterparty_side = wire[at++];
  record->amended_trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  record->automatic_order_filter_flag = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  record->account_type = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  record->bolsa_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->csdbic[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->participant[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->cta_liq[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message is what was written, byte for byte */
static void equal_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(const TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *read, const TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv *written) {
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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  assert(read->last_change_flag == written->last_change_flag);
  assert(read->benc_rfpt_flag == written->benc_rfpt_flag);
  assert(read->trade_price_condition == written->trade_price_condition);
  assert(read->pre_trade_transparency_waiver == written->pre_trade_transparency_waiver);
  assert(read->deferral_waiver == written->deferral_waiver);
  for (size_t i = 0; i < 8; i++) { assert(read->publish_date_and_time[i] == written->publish_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_session_date[i] == written->trade_session_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_float[i] == written->volume_float[i]); }
  assert(read->sicav_fund_counterparty_side == written->sicav_fund_counterparty_side);
  assert(read->amended_trade_type == written->amended_trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amended_trade_date[i] == written->amended_trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->give_in_member[i] == written->give_in_member[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->firm_mnemonic[i] == written->firm_mnemonic[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->alloc_text[i] == written->alloc_text[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  assert(read->automatic_order_filter_flag == written->automatic_order_filter_flag);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  assert(read->account_type == written->account_type);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  assert(read->bolsa_code == written->bolsa_code);
  for (size_t i = 0; i < 11; i++) { assert(read->csdbic[i] == written->csdbic[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->participant[i] == written->participant[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->cta_liq[i] == written->cta_liq[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ccv[i] == written->ccv[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->external_member[i] == written->external_member[i]); }
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(void) {
  TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv sent;
  TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv got;
  uint8_t wire[317];
  uint8_t again[317];

  any_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&sent);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&sent, wire, 0) == 317);
  assert(decode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, wire, 0) == 317);
  equal_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, &sent);

  for (size_t i = 0; i < 317; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, wire, 0) == 317);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, again, 0) == 317);
  for (size_t i = 0; i < 317; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 2 Legs Private Information Message: 536 bytes ---- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. The user is involved in the trade both as Buyer and Seller */
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
  uint8_t buyer_bolsa_code;                /* byte 49 */
  uint8_t settl_date[4];                   /* bytes 50 to 53 */
  uint8_t transaction_category;            /* byte 54 */
  uint8_t last_change_flag;                /* byte 55 */
  uint8_t benc_rfpt_flag;                  /* byte 56 */
  uint8_t trade_price_condition;           /* byte 57 */
  uint8_t pre_trade_transparency_waiver;   /* byte 58 */
  uint8_t deferral_waiver;                 /* byte 59 */
  uint8_t publish_date_and_time[8];        /* bytes 60 to 67 */
  uint8_t trade_date[8];                   /* bytes 68 to 75 */
  uint8_t trade_session_date[4];           /* bytes 76 to 79 */
  uint8_t volume_float[8];                 /* bytes 80 to 87 */
  uint8_t sicav_fund_counterparty_side;    /* byte 88 */
  uint8_t amended_trade_type;              /* byte 89 */
  uint8_t exec_ref_id[4];                  /* bytes 90 to 93 */
  uint8_t amended_trade_date[4];           /* bytes 94 to 97 */
  uint8_t secondary_order_id[4];           /* bytes 98 to 101 */
  uint8_t entry_date[4];                   /* bytes 102 to 105 */
  uint8_t priority[4];                     /* bytes 106 to 109 */
  uint8_t price[8];                        /* bytes 110 to 117 */
  uint8_t display_qty[4];                  /* bytes 118 to 121 */
  uint8_t order_id[4];                     /* bytes 122 to 125 */
  uint8_t secondary_exec_id[4];            /* bytes 126 to 129 */
  uint8_t order_qty[4];                    /* bytes 130 to 133 */
  uint8_t ord_status;                      /* byte 134 */
  uint8_t ccp_code;                        /* byte 135 */
  uint8_t aggressor_indicator;             /* byte 136 */
  uint8_t request_id[4];                   /* bytes 137 to 140 */
  uint8_t client_data_id[2];               /* bytes 141 to 142 */
  uint8_t algorithmic_trade_indicator;     /* byte 143 */
  uint8_t client_id[4];                    /* bytes 144 to 147 */
  uint8_t account_bolsa[16];               /* bytes 148 to 163 */
  uint8_t account[5];                      /* bytes 164 to 168 */
  uint8_t dea_flag;                        /* byte 169 */
  uint8_t decisor_id[4];                   /* bytes 170 to 173 */
  uint8_t executor_id[4];                  /* bytes 174 to 177 */
  uint8_t liquidity_provision_activity;    /* byte 178 */
  uint8_t give_in_member[4];               /* bytes 179 to 182 */
  uint8_t firm_mnemonic[10];               /* bytes 183 to 192 */
  uint8_t alloc_text[18];                  /* bytes 193 to 210 */
  uint8_t last_capacity;                   /* byte 211 */
  uint8_t self_match_prevention_id[2];     /* bytes 212 to 213 */
  uint8_t automatic_order_filter_flag;     /* byte 214 */
  uint8_t received_dept_id;                /* byte 215 */
  uint8_t persistence;                     /* byte 216 */
  uint8_t account_type;                    /* byte 217 */
  uint8_t self_match_prevention_type;      /* byte 218 */
  uint8_t member[4];                       /* bytes 219 to 222 */
  uint8_t trader[3];                       /* bytes 223 to 225 */
  uint8_t sub_member;                      /* byte 226 */
  uint8_t cross_id[4];                     /* bytes 227 to 230 */
  uint8_t bolsa_code;                      /* byte 231 */
  uint8_t csdbic[11];                      /* bytes 232 to 242 */
  uint8_t participant[11];                 /* bytes 243 to 253 */
  uint8_t cta_liq[35];                     /* bytes 254 to 288 */
  uint8_t ccv[20];                         /* bytes 289 to 308 */
  uint8_t order_security_code[4];          /* bytes 309 to 312 */
  uint8_t external_member[4];              /* bytes 313 to 316 */
  uint8_t secondary_order_id_2[4];         /* bytes 317 to 320 */
  uint8_t entry_date_2[4];                 /* bytes 321 to 324 */
  uint8_t priority_2[4];                   /* bytes 325 to 328 */
  uint8_t price_2[8];                      /* bytes 329 to 336 */
  uint8_t display_qty_2[4];                /* bytes 337 to 340 */
  uint8_t order_id_2[4];                   /* bytes 341 to 344 */
  uint8_t secondary_exec_id_2[4];          /* bytes 345 to 348 */
  uint8_t order_qty_2[4];                  /* bytes 349 to 352 */
  uint8_t ord_status_2;                    /* byte 353 */
  uint8_t ccp_code_2;                      /* byte 354 */
  uint8_t aggressor_indicator_2;           /* byte 355 */
  uint8_t request_id_2[4];                 /* bytes 356 to 359 */
  uint8_t client_data_id_2[2];             /* bytes 360 to 361 */
  uint8_t algorithmic_trade_indicator_2;   /* byte 362 */
  uint8_t client_id_2[4];                  /* bytes 363 to 366 */
  uint8_t account_bolsa_2[16];             /* bytes 367 to 382 */
  uint8_t account_2[5];                    /* bytes 383 to 387 */
  uint8_t dea_flag_2;                      /* byte 388 */
  uint8_t decisor_id_2[4];                 /* bytes 389 to 392 */
  uint8_t executor_id_2[4];                /* bytes 393 to 396 */
  uint8_t liquidity_provision_activity_2;  /* byte 397 */
  uint8_t give_in_member_2[4];             /* bytes 398 to 401 */
  uint8_t firm_mnemonic_2[10];             /* bytes 402 to 411 */
  uint8_t alloc_text_2[18];                /* bytes 412 to 429 */
  uint8_t last_capacity_2;                 /* byte 430 */
  uint8_t self_match_prevention_id_2[2];   /* bytes 431 to 432 */
  uint8_t automatic_order_filter_flag_2;   /* byte 433 */
  uint8_t received_dept_id_2;              /* byte 434 */
  uint8_t persistence_2;                   /* byte 435 */
  uint8_t account_type_2;                  /* byte 436 */
  uint8_t self_match_prevention_type_2;    /* byte 437 */
  uint8_t member_2[4];                     /* bytes 438 to 441 */
  uint8_t trader_2[3];                     /* bytes 442 to 444 */
  uint8_t sub_member_2;                    /* byte 445 */
  uint8_t cross_id_2[4];                   /* bytes 446 to 449 */
  uint8_t bolsa_code_2;                    /* byte 450 */
  uint8_t csdbic_2[11];                    /* bytes 451 to 461 */
  uint8_t participant_2[11];               /* bytes 462 to 472 */
  uint8_t cta_liq_2[35];                   /* bytes 473 to 507 */
  uint8_t ccv_2[20];                       /* bytes 508 to 527 */
  uint8_t order_security_code_2[4];        /* bytes 528 to 531 */
  uint8_t external_member_2[4];            /* bytes 532 to 535 */
} TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage;

/* any Trade Trade Amendment Or Cancellation 2 Legs Private Information Message at all: every byte one the checker chooses */
static void any_trade_trade_amendment_or_cancellation2_legs_private_information_message(TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *record) {
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  record->last_change_flag = arbitrary();
  record->benc_rfpt_flag = arbitrary();
  record->trade_price_condition = arbitrary();
  record->pre_trade_transparency_waiver = arbitrary();
  record->deferral_waiver = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume_float[i] = arbitrary(); }
  record->sicav_fund_counterparty_side = arbitrary();
  record->amended_trade_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  record->dea_flag = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = arbitrary(); }
  record->liquidity_provision_activity = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = arbitrary(); }
  record->last_capacity = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = arbitrary(); }
  record->automatic_order_filter_flag = arbitrary();
  record->received_dept_id = arbitrary();
  record->persistence = arbitrary();
  record->account_type = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  record->bolsa_code = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->csdbic[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->participant[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->cta_liq[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = arbitrary(); }
  record->ord_status_2 = arbitrary();
  record->ccp_code_2 = arbitrary();
  record->aggressor_indicator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id_2[i] = arbitrary(); }
  record->algorithmic_trade_indicator_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa_2[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account_2[i] = arbitrary(); }
  record->dea_flag_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->decisor_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->executor_id_2[i] = arbitrary(); }
  record->liquidity_provision_activity_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_in_member_2[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic_2[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->alloc_text_2[i] = arbitrary(); }
  record->last_capacity_2 = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id_2[i] = arbitrary(); }
  record->automatic_order_filter_flag_2 = arbitrary();
  record->received_dept_id_2 = arbitrary();
  record->persistence_2 = arbitrary();
  record->account_type_2 = arbitrary();
  record->self_match_prevention_type_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member_2[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader_2[i] = arbitrary(); }
  record->sub_member_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id_2[i] = arbitrary(); }
  record->bolsa_code_2 = arbitrary();
  for (size_t i = 0; i < 11; i++) { record->csdbic_2[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->participant_2[i] = arbitrary(); }
  for (size_t i = 0; i < 35; i++) { record->cta_liq_2[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ccv_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->external_member_2[i] = arbitrary(); }
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message to the wire: 536 bytes from at, returning where the next byte goes */
static size_t encode_trade_trade_amendment_or_cancellation2_legs_private_information_message(const TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *record, uint8_t *wire, size_t at) {
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  wire[at++] = record->last_change_flag;
  wire[at++] = record->benc_rfpt_flag;
  wire[at++] = record->trade_price_condition;
  wire[at++] = record->pre_trade_transparency_waiver;
  wire[at++] = record->deferral_waiver;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->publish_date_and_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_session_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume_float[i]; }
  wire[at++] = record->sicav_fund_counterparty_side;
  wire[at++] = record->amended_trade_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->exec_ref_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->amended_trade_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  wire[at++] = record->dea_flag;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id[i]; }
  wire[at++] = record->liquidity_provision_activity;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_in_member[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->firm_mnemonic[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->alloc_text[i]; }
  wire[at++] = record->last_capacity;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->self_match_prevention_id[i]; }
  wire[at++] = record->automatic_order_filter_flag;
  wire[at++] = record->received_dept_id;
  wire[at++] = record->persistence;
  wire[at++] = record->account_type;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  wire[at++] = record->bolsa_code;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->csdbic[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->participant[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->cta_liq[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ccv[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_member[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority_2[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty_2[i]; }
  wire[at++] = record->ord_status_2;
  wire[at++] = record->ccp_code_2;
  wire[at++] = record->aggressor_indicator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id_2[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id_2[i]; }
  wire[at++] = record->algorithmic_trade_indicator_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id_2[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->account_bolsa_2[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account_2[i]; }
  wire[at++] = record->dea_flag_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->decisor_id_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executor_id_2[i]; }
  wire[at++] = record->liquidity_provision_activity_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_in_member_2[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->firm_mnemonic_2[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->alloc_text_2[i]; }
  wire[at++] = record->last_capacity_2;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->self_match_prevention_id_2[i]; }
  wire[at++] = record->automatic_order_filter_flag_2;
  wire[at++] = record->received_dept_id_2;
  wire[at++] = record->persistence_2;
  wire[at++] = record->account_type_2;
  wire[at++] = record->self_match_prevention_type_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_2[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader_2[i]; }
  wire[at++] = record->sub_member_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id_2[i]; }
  wire[at++] = record->bolsa_code_2;
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->csdbic_2[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->participant_2[i]; }
  for (size_t i = 0; i < 35; i++) { wire[at++] = record->cta_liq_2[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ccv_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_member_2[i]; }

  return at;
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message off the wire: 536 bytes from at, returning where the next byte lies */
static size_t decode_trade_trade_amendment_or_cancellation2_legs_private_information_message(TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *record, const uint8_t *wire, size_t at) {
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
  record->buyer_bolsa_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  record->last_change_flag = wire[at++];
  record->benc_rfpt_flag = wire[at++];
  record->trade_price_condition = wire[at++];
  record->pre_trade_transparency_waiver = wire[at++];
  record->deferral_waiver = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->publish_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_session_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume_float[i] = wire[at++]; }
  record->sicav_fund_counterparty_side = wire[at++];
  record->amended_trade_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->exec_ref_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->amended_trade_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  record->dea_flag = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id[i] = wire[at++]; }
  record->liquidity_provision_activity = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_in_member[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->alloc_text[i] = wire[at++]; }
  record->last_capacity = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id[i] = wire[at++]; }
  record->automatic_order_filter_flag = wire[at++];
  record->received_dept_id = wire[at++];
  record->persistence = wire[at++];
  record->account_type = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  record->bolsa_code = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->csdbic[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->participant[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->cta_liq[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority_2[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty_2[i] = wire[at++]; }
  record->ord_status_2 = wire[at++];
  record->ccp_code_2 = wire[at++];
  record->aggressor_indicator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id_2[i] = wire[at++]; }
  record->algorithmic_trade_indicator_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->account_bolsa_2[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account_2[i] = wire[at++]; }
  record->dea_flag_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->decisor_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->executor_id_2[i] = wire[at++]; }
  record->liquidity_provision_activity_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_in_member_2[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->firm_mnemonic_2[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->alloc_text_2[i] = wire[at++]; }
  record->last_capacity_2 = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->self_match_prevention_id_2[i] = wire[at++]; }
  record->automatic_order_filter_flag_2 = wire[at++];
  record->received_dept_id_2 = wire[at++];
  record->persistence_2 = wire[at++];
  record->account_type_2 = wire[at++];
  record->self_match_prevention_type_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member_2[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader_2[i] = wire[at++]; }
  record->sub_member_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id_2[i] = wire[at++]; }
  record->bolsa_code_2 = wire[at++];
  for (size_t i = 0; i < 11; i++) { record->csdbic_2[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->participant_2[i] = wire[at++]; }
  for (size_t i = 0; i < 35; i++) { record->cta_liq_2[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ccv_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->external_member_2[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Trade Amendment Or Cancellation 2 Legs Private Information Message is what was written, byte for byte */
static void equal_trade_trade_amendment_or_cancellation2_legs_private_information_message(const TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *read, const TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage *written) {
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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  assert(read->last_change_flag == written->last_change_flag);
  assert(read->benc_rfpt_flag == written->benc_rfpt_flag);
  assert(read->trade_price_condition == written->trade_price_condition);
  assert(read->pre_trade_transparency_waiver == written->pre_trade_transparency_waiver);
  assert(read->deferral_waiver == written->deferral_waiver);
  for (size_t i = 0; i < 8; i++) { assert(read->publish_date_and_time[i] == written->publish_date_and_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->trade_date[i] == written->trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_session_date[i] == written->trade_session_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume_float[i] == written->volume_float[i]); }
  assert(read->sicav_fund_counterparty_side == written->sicav_fund_counterparty_side);
  assert(read->amended_trade_type == written->amended_trade_type);
  for (size_t i = 0; i < 4; i++) { assert(read->exec_ref_id[i] == written->exec_ref_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->amended_trade_date[i] == written->amended_trade_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa[i] == written->account_bolsa[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  assert(read->dea_flag == written->dea_flag);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id[i] == written->decisor_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id[i] == written->executor_id[i]); }
  assert(read->liquidity_provision_activity == written->liquidity_provision_activity);
  for (size_t i = 0; i < 4; i++) { assert(read->give_in_member[i] == written->give_in_member[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->firm_mnemonic[i] == written->firm_mnemonic[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->alloc_text[i] == written->alloc_text[i]); }
  assert(read->last_capacity == written->last_capacity);
  for (size_t i = 0; i < 2; i++) { assert(read->self_match_prevention_id[i] == written->self_match_prevention_id[i]); }
  assert(read->automatic_order_filter_flag == written->automatic_order_filter_flag);
  assert(read->received_dept_id == written->received_dept_id);
  assert(read->persistence == written->persistence);
  assert(read->account_type == written->account_type);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  assert(read->bolsa_code == written->bolsa_code);
  for (size_t i = 0; i < 11; i++) { assert(read->csdbic[i] == written->csdbic[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->participant[i] == written->participant[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->cta_liq[i] == written->cta_liq[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ccv[i] == written->ccv[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->external_member[i] == written->external_member[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date_2[i] == written->entry_date_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority_2[i] == written->priority_2[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price_2[i] == written->price_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty_2[i] == written->display_qty_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id_2[i] == written->order_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id_2[i] == written->secondary_exec_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty_2[i] == written->order_qty_2[i]); }
  assert(read->ord_status_2 == written->ord_status_2);
  assert(read->ccp_code_2 == written->ccp_code_2);
  assert(read->aggressor_indicator_2 == written->aggressor_indicator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id_2[i] == written->request_id_2[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id_2[i] == written->client_data_id_2[i]); }
  assert(read->algorithmic_trade_indicator_2 == written->algorithmic_trade_indicator_2);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id_2[i] == written->client_id_2[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->account_bolsa_2[i] == written->account_bolsa_2[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account_2[i] == written->account_2[i]); }
  assert(read->dea_flag_2 == written->dea_flag_2);
  for (size_t i = 0; i < 4; i++) { assert(read->decisor_id_2[i] == written->decisor_id_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->executor_id_2[i] == written->executor_id_2[i]); }
  assert(read->liquidity_provision_activity_2 == written->liquidity_provision_activity_2);
  for (size_t i = 0; i < 4; i++) { assert(read->give_in_member_2[i] == written->give_in_member_2[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->firm_mnemonic_2[i] == written->firm_mnemonic_2[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->alloc_text_2[i] == written->alloc_text_2[i]); }
  assert(read->last_capacity_2 == written->last_capacity_2);
  for (size_t i = 0; i < 2; i++) { assert(read->self_match_prevention_id_2[i] == written->self_match_prevention_id_2[i]); }
  assert(read->automatic_order_filter_flag_2 == written->automatic_order_filter_flag_2);
  assert(read->received_dept_id_2 == written->received_dept_id_2);
  assert(read->persistence_2 == written->persistence_2);
  assert(read->account_type_2 == written->account_type_2);
  assert(read->self_match_prevention_type_2 == written->self_match_prevention_type_2);
  for (size_t i = 0; i < 4; i++) { assert(read->member_2[i] == written->member_2[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader_2[i] == written->trader_2[i]); }
  assert(read->sub_member_2 == written->sub_member_2);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id_2[i] == written->cross_id_2[i]); }
  assert(read->bolsa_code_2 == written->bolsa_code_2);
  for (size_t i = 0; i < 11; i++) { assert(read->csdbic_2[i] == written->csdbic_2[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->participant_2[i] == written->participant_2[i]); }
  for (size_t i = 0; i < 35; i++) { assert(read->cta_liq_2[i] == written->cta_liq_2[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ccv_2[i] == written->ccv_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code_2[i] == written->order_security_code_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->external_member_2[i] == written->external_member_2[i]); }
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation2_legs_private_information_message(void) {
  TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage sent;
  TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage got;
  uint8_t wire[536];
  uint8_t again[536];

  any_trade_trade_amendment_or_cancellation2_legs_private_information_message(&sent);
  assert(encode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&sent, wire, 0) == 536);
  assert(decode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, wire, 0) == 536);
  equal_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, &sent);

  for (size_t i = 0; i < 536; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, wire, 0) == 536);
  assert(encode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, again, 0) == 536);
  for (size_t i = 0; i < 536; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Private Information 1 Leg Buy Order Entry Message: 100 bytes ---- */

/* Sent by the server to inform about a trade where the user is involved as Buyer. Shares the same layout as the next message */
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
  uint8_t buyer_bolsa_code;              /* byte 49 */
  uint8_t settl_date[4];                 /* bytes 50 to 53 */
  uint8_t transaction_category;          /* byte 54 */
  uint8_t secondary_order_id[4];         /* bytes 55 to 58 */
  uint8_t entry_date[4];                 /* bytes 59 to 62 */
  uint8_t priority[4];                   /* bytes 63 to 66 */
  uint8_t price[8];                      /* bytes 67 to 74 */
  uint8_t display_qty[4];                /* bytes 75 to 78 */
  uint8_t order_id[4];                   /* bytes 79 to 82 */
  uint8_t secondary_exec_id[4];          /* bytes 83 to 86 */
  uint8_t order_qty[4];                  /* bytes 87 to 90 */
  uint8_t ord_status;                    /* byte 91 */
  uint8_t ccp_code;                      /* byte 92 */
  uint8_t aggressor_indicator;           /* byte 93 */
  uint8_t request_id[4];                 /* bytes 94 to 97 */
  uint8_t client_data_id[2];             /* bytes 98 to 99 */
} ExecutionPrivateInformation1LegBuyOrderEntryMessage;

/* any Execution Private Information 1 Leg Buy Order Entry Message at all: every byte one the checker chooses */
static void any_execution_private_information1_leg_buy_order_entry_message(ExecutionPrivateInformation1LegBuyOrderEntryMessage *record) {
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Execution Private Information 1 Leg Buy Order Entry Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_execution_private_information1_leg_buy_order_entry_message(const ExecutionPrivateInformation1LegBuyOrderEntryMessage *record, uint8_t *wire, size_t at) {
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Execution Private Information 1 Leg Buy Order Entry Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_execution_private_information1_leg_buy_order_entry_message(ExecutionPrivateInformation1LegBuyOrderEntryMessage *record, const uint8_t *wire, size_t at) {
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
  record->buyer_bolsa_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Private Information 1 Leg Buy Order Entry Message is what was written, byte for byte */
static void equal_execution_private_information1_leg_buy_order_entry_message(const ExecutionPrivateInformation1LegBuyOrderEntryMessage *read, const ExecutionPrivateInformation1LegBuyOrderEntryMessage *written) {
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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Execution Private Information 1 Leg Buy Order Entry Message: written and read back, then read and written back */
static void check_execution_private_information1_leg_buy_order_entry_message(void) {
  ExecutionPrivateInformation1LegBuyOrderEntryMessage sent;
  ExecutionPrivateInformation1LegBuyOrderEntryMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_execution_private_information1_leg_buy_order_entry_message(&sent);
  assert(encode_execution_private_information1_leg_buy_order_entry_message(&sent, wire, 0) == 100);
  assert(decode_execution_private_information1_leg_buy_order_entry_message(&got, wire, 0) == 100);
  equal_execution_private_information1_leg_buy_order_entry_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information1_leg_buy_order_entry_message(&got, wire, 0) == 100);
  assert(encode_execution_private_information1_leg_buy_order_entry_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Private Information 1 Leg Sell Order Entry Message: 100 bytes ---- */

/* Sent by the server to inform about a trade where the user is involved as Seller */
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
  uint8_t buyer_bolsa_code;              /* byte 49 */
  uint8_t settl_date[4];                 /* bytes 50 to 53 */
  uint8_t transaction_category;          /* byte 54 */
  uint8_t secondary_order_id[4];         /* bytes 55 to 58 */
  uint8_t entry_date[4];                 /* bytes 59 to 62 */
  uint8_t priority[4];                   /* bytes 63 to 66 */
  uint8_t price[8];                      /* bytes 67 to 74 */
  uint8_t display_qty[4];                /* bytes 75 to 78 */
  uint8_t order_id[4];                   /* bytes 79 to 82 */
  uint8_t secondary_exec_id[4];          /* bytes 83 to 86 */
  uint8_t order_qty[4];                  /* bytes 87 to 90 */
  uint8_t ord_status;                    /* byte 91 */
  uint8_t ccp_code;                      /* byte 92 */
  uint8_t aggressor_indicator;           /* byte 93 */
  uint8_t request_id[4];                 /* bytes 94 to 97 */
  uint8_t client_data_id[2];             /* bytes 98 to 99 */
} ExecutionPrivateInformation1LegSellOrderEntryMessage;

/* any Execution Private Information 1 Leg Sell Order Entry Message at all: every byte one the checker chooses */
static void any_execution_private_information1_leg_sell_order_entry_message(ExecutionPrivateInformation1LegSellOrderEntryMessage *record) {
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
  record->buyer_bolsa_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = arbitrary(); }
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = arbitrary(); }
  record->ord_status = arbitrary();
  record->ccp_code = arbitrary();
  record->aggressor_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
}

/* Execution Private Information 1 Leg Sell Order Entry Message to the wire: 100 bytes from at, returning where the next byte goes */
static size_t encode_execution_private_information1_leg_sell_order_entry_message(const ExecutionPrivateInformation1LegSellOrderEntryMessage *record, uint8_t *wire, size_t at) {
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
  wire[at++] = record->buyer_bolsa_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->settl_date[i]; }
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->priority[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_exec_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->ord_status;
  wire[at++] = record->ccp_code;
  wire[at++] = record->aggressor_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }

  return at;
}

/* Execution Private Information 1 Leg Sell Order Entry Message off the wire: 100 bytes from at, returning where the next byte lies */
static size_t decode_execution_private_information1_leg_sell_order_entry_message(ExecutionPrivateInformation1LegSellOrderEntryMessage *record, const uint8_t *wire, size_t at) {
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
  record->buyer_bolsa_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->settl_date[i] = wire[at++]; }
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->priority[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_exec_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->ord_status = wire[at++];
  record->ccp_code = wire[at++];
  record->aggressor_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }

  return at;
}

/* what was read of Execution Private Information 1 Leg Sell Order Entry Message is what was written, byte for byte */
static void equal_execution_private_information1_leg_sell_order_entry_message(const ExecutionPrivateInformation1LegSellOrderEntryMessage *read, const ExecutionPrivateInformation1LegSellOrderEntryMessage *written) {
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
  assert(read->buyer_bolsa_code == written->buyer_bolsa_code);
  for (size_t i = 0; i < 4; i++) { assert(read->settl_date[i] == written->settl_date[i]); }
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->priority[i] == written->priority[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_exec_id[i] == written->secondary_exec_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_qty[i] == written->order_qty[i]); }
  assert(read->ord_status == written->ord_status);
  assert(read->ccp_code == written->ccp_code);
  assert(read->aggressor_indicator == written->aggressor_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->client_data_id[i] == written->client_data_id[i]); }
}

/* Execution Private Information 1 Leg Sell Order Entry Message: written and read back, then read and written back */
static void check_execution_private_information1_leg_sell_order_entry_message(void) {
  ExecutionPrivateInformation1LegSellOrderEntryMessage sent;
  ExecutionPrivateInformation1LegSellOrderEntryMessage got;
  uint8_t wire[100];
  uint8_t again[100];

  any_execution_private_information1_leg_sell_order_entry_message(&sent);
  assert(encode_execution_private_information1_leg_sell_order_entry_message(&sent, wire, 0) == 100);
  assert(decode_execution_private_information1_leg_sell_order_entry_message(&got, wire, 0) == 100);
  equal_execution_private_information1_leg_sell_order_entry_message(&got, &sent);

  for (size_t i = 0; i < 100; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information1_leg_sell_order_entry_message(&got, wire, 0) == 100);
  assert(encode_execution_private_information1_leg_sell_order_entry_message(&got, again, 0) == 100);
  for (size_t i = 0; i < 100; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_logon_response_message();
  check_logout_response_message();
  check_heartbeat_message();
  check_network_status_message();
  check_logon_message();
  check_reject_message();
  check_trading_session_status_message();
  check_news_message();
  check_security_list_cancellation_report_message();
  check_security_list_message();
  check_security_list_update_report_message();
  check_security_status_message();
  check_order_cancellation_market_member_message();
  check_quote_cancellation_market_member_message();
  check_order_and_quote_client_data_message();
  check_simple_new_order_message();
  check_simple_new_order_with_client_data_message();
  check_simple_order_modification_message();
  check_simple_order_modification_with_client_data_message();
  check_order_cancellation_request_message();
  check_new_quote_message();
  check_quote_modification_request_message();
  check_quote_cancellation_request_message();
  check_mass_orderquote_cancellation_message();
  check_order_and_quote_client_data_parameters_ack_nack_message();
  check_simple_order_status_message();
  check_quote_status_message();
  check_order_cancel_reject_message();
  check_mass_orderquote_cancellation_completion_message();
  check_mass_orderquote_cancellation_reject_message();
  check_business_message_reject_message();
  check_execution_private_information2_legs_message();
  check_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1();
  check_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv();
  check_trade_trade_amendment_or_cancellation2_legs_private_information_message();
  check_execution_private_information1_leg_buy_order_entry_message();
  check_execution_private_information1_leg_sell_order_entry_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
