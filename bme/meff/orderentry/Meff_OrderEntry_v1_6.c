// bme/meff/orderentry/Meff_OrderEntry_v1_6.c
/*
 * Bolsas y Mercados Españoles MEFF Order Entry
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

/* ---- Order Cancellation Market Member Message: 24 bytes ---------------------- */

/* Used by the Server to communicate information order cancellation. The same message is used in Full-Depth data feeds (for order cancellations of any user), in the Order Entry Server (for cancellations of user orders) and in the Market & Order Server (for order cancellations of any user) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t entry_date[4];                 /* bytes 20 to 23 */
} OrderCancellationMarketMemberMessage;

/* any Order Cancellation Market Member Message at all: every byte one the checker chooses */
static void any_order_cancellation_market_member_message(OrderCancellationMarketMemberMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = arbitrary(); }
}

/* Order Cancellation Market Member Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_order_cancellation_market_member_message(const OrderCancellationMarketMemberMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->entry_date[i]; }

  return at;
}

/* Order Cancellation Market Member Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_order_cancellation_market_member_message(OrderCancellationMarketMemberMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->entry_date[i] = wire[at++]; }

  return at;
}

/* what was read of Order Cancellation Market Member Message is what was written, byte for byte */
static void equal_order_cancellation_market_member_message(const OrderCancellationMarketMemberMessage *read, const OrderCancellationMarketMemberMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->entry_date[i] == written->entry_date[i]); }
}

/* Order Cancellation Market Member Message: written and read back, then read and written back */
static void check_order_cancellation_market_member_message(void) {
  OrderCancellationMarketMemberMessage sent;
  OrderCancellationMarketMemberMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_order_cancellation_market_member_message(&sent);
  assert(encode_order_cancellation_market_member_message(&sent, wire, 0) == 24);
  assert(decode_order_cancellation_market_member_message(&got, wire, 0) == 24);
  equal_order_cancellation_market_member_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_order_cancellation_market_member_message(&got, wire, 0) == 24);
  assert(encode_order_cancellation_market_member_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancellation Market Member Message: 24 bytes ---------------------- */

/* Used by the Server to communicate information about quote cancellation. The same message is used in Full-Depth data feeds (for quote cancellations of any user), in the Order Entry Server (for cancellations of user quotes) and in the Market & Order Server (for quote cancellations of any user) */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t transaction_date_and_time[8];  /* bytes 8 to 15 */
  uint8_t secondary_order_id[4];         /* bytes 16 to 19 */
  uint8_t secondary_order_id_2[4];       /* bytes 20 to 23 */
} QuoteCancellationMarketMemberMessage;

/* any Quote Cancellation Market Member Message at all: every byte one the checker chooses */
static void any_quote_cancellation_market_member_message(QuoteCancellationMarketMemberMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = arbitrary(); }
}

/* Quote Cancellation Market Member Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancellation_market_member_message(const QuoteCancellationMarketMemberMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transaction_date_and_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->secondary_order_id_2[i]; }

  return at;
}

/* Quote Cancellation Market Member Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancellation_market_member_message(QuoteCancellationMarketMemberMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->transaction_date_and_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->secondary_order_id_2[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Cancellation Market Member Message is what was written, byte for byte */
static void equal_quote_cancellation_market_member_message(const QuoteCancellationMarketMemberMessage *read, const QuoteCancellationMarketMemberMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->transaction_date_and_time[i] == written->transaction_date_and_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->secondary_order_id_2[i] == written->secondary_order_id_2[i]); }
}

/* Quote Cancellation Market Member Message: written and read back, then read and written back */
static void check_quote_cancellation_market_member_message(void) {
  QuoteCancellationMarketMemberMessage sent;
  QuoteCancellationMarketMemberMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_quote_cancellation_market_member_message(&sent);
  assert(encode_quote_cancellation_market_member_message(&sent, wire, 0) == 24);
  assert(decode_quote_cancellation_market_member_message(&got, wire, 0) == 24);
  equal_quote_cancellation_market_member_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancellation_market_member_message(&got, wire, 0) == 24);
  assert(encode_quote_cancellation_market_member_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
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

/* ---- Order And Quote Client Data Message: 78 bytes --------------------------- */

/* Sent by the client to set default attributes for subsequent orders and quotes. Please note that in Fixed Income it is possible to enter orders on behalf of other members (AccountMember), based on the corresponding brokerage permissions */
typedef struct {
  uint8_t request_id[4];                 /* bytes 0 to 3 */
  uint8_t client_data_id[2];             /* bytes 4 to 5 */
  uint8_t algorithmic_trade_indicator;   /* byte 6 */
  uint8_t client_id[4];                  /* bytes 7 to 10 */
  uint8_t account[5];                    /* bytes 11 to 15 */
  uint8_t dea_flag;                      /* byte 16 */
  uint8_t decisor_id[4];                 /* bytes 17 to 20 */
  uint8_t executor_id[4];                /* bytes 21 to 24 */
  uint8_t liquidity_provision_activity;  /* byte 25 */
  uint8_t give_in_member[4];             /* bytes 26 to 29 */
  uint8_t firm_mnemonic[10];             /* bytes 30 to 39 */
  uint8_t alloc_text[18];                /* bytes 40 to 57 */
  uint8_t last_capacity;                 /* byte 58 */
  uint8_t self_match_prevention_id[2];   /* bytes 59 to 60 */
  uint8_t persistence;                   /* byte 61 */
  uint8_t self_match_prevention_type;    /* byte 62 */
  uint8_t client_data_reference[15];     /* bytes 63 to 77 */
} OrderAndQuoteClientDataMessage;

/* any Order And Quote Client Data Message at all: every byte one the checker chooses */
static void any_order_and_quote_client_data_message(OrderAndQuoteClientDataMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
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
  record->persistence = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Order And Quote Client Data Message to the wire: 78 bytes from at, returning where the next byte goes */
static size_t encode_order_and_quote_client_data_message(const OrderAndQuoteClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
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
  wire[at++] = record->persistence;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Order And Quote Client Data Message off the wire: 78 bytes from at, returning where the next byte lies */
static size_t decode_order_and_quote_client_data_message(OrderAndQuoteClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
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
  record->persistence = wire[at++];
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
  assert(read->persistence == written->persistence);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Order And Quote Client Data Message: written and read back, then read and written back */
static void check_order_and_quote_client_data_message(void) {
  OrderAndQuoteClientDataMessage sent;
  OrderAndQuoteClientDataMessage got;
  uint8_t wire[78];
  uint8_t again[78];

  any_order_and_quote_client_data_message(&sent);
  assert(encode_order_and_quote_client_data_message(&sent, wire, 0) == 78);
  assert(decode_order_and_quote_client_data_message(&got, wire, 0) == 78);
  equal_order_and_quote_client_data_message(&got, &sent);

  for (size_t i = 0; i < 78; i++) { wire[i] = arbitrary(); }
  assert(decode_order_and_quote_client_data_message(&got, wire, 0) == 78);
  assert(encode_order_and_quote_client_data_message(&got, again, 0) == 78);
  for (size_t i = 0; i < 78; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delta Protection Parameters Message: 12 bytes --------------------------- */

/* Sent by the client in Derivatives to set attributes for delta protection */
typedef struct {
  uint8_t request_id[4];               /* bytes 0 to 3 */
  uint8_t security_group[2];           /* bytes 4 to 5 */
  uint8_t product_type;                /* byte 6 */
  uint8_t delta_protection_time;       /* byte 7 */
  uint8_t delta_protection_volume[4];  /* bytes 8 to 11 */
} DeltaProtectionParametersMessage;

/* any Delta Protection Parameters Message at all: every byte one the checker chooses */
static void any_delta_protection_parameters_message(DeltaProtectionParametersMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = arbitrary(); }
  record->product_type = arbitrary();
  record->delta_protection_time = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->delta_protection_volume[i] = arbitrary(); }
}

/* Delta Protection Parameters Message to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_delta_protection_parameters_message(const DeltaProtectionParametersMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group[i]; }
  wire[at++] = record->product_type;
  wire[at++] = record->delta_protection_time;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delta_protection_volume[i]; }

  return at;
}

/* Delta Protection Parameters Message off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_delta_protection_parameters_message(DeltaProtectionParametersMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = wire[at++]; }
  record->product_type = wire[at++];
  record->delta_protection_time = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->delta_protection_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Delta Protection Parameters Message is what was written, byte for byte */
static void equal_delta_protection_parameters_message(const DeltaProtectionParametersMessage *read, const DeltaProtectionParametersMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group[i] == written->security_group[i]); }
  assert(read->product_type == written->product_type);
  assert(read->delta_protection_time == written->delta_protection_time);
  for (size_t i = 0; i < 4; i++) { assert(read->delta_protection_volume[i] == written->delta_protection_volume[i]); }
}

/* Delta Protection Parameters Message: written and read back, then read and written back */
static void check_delta_protection_parameters_message(void) {
  DeltaProtectionParametersMessage sent;
  DeltaProtectionParametersMessage got;
  uint8_t wire[12];
  uint8_t again[12];

  any_delta_protection_parameters_message(&sent);
  assert(encode_delta_protection_parameters_message(&sent, wire, 0) == 12);
  assert(decode_delta_protection_parameters_message(&got, wire, 0) == 12);
  equal_delta_protection_parameters_message(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_delta_protection_parameters_message(&got, wire, 0) == 12);
  assert(encode_delta_protection_parameters_message(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple New Order Message: 28 bytes -------------------------------------- */

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
}

/* Simple New Order Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_simple_new_order_message(const SimpleNewOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->time_in_force;

  return at;
}

/* Simple New Order Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_simple_new_order_message(SimpleNewOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->time_in_force = wire[at++];

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
}

/* Simple New Order Message: written and read back, then read and written back */
static void check_simple_new_order_message(void) {
  SimpleNewOrderMessage sent;
  SimpleNewOrderMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_simple_new_order_message(&sent);
  assert(encode_simple_new_order_message(&sent, wire, 0) == 28);
  assert(decode_simple_new_order_message(&got, wire, 0) == 28);
  equal_simple_new_order_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_new_order_message(&got, wire, 0) == 28);
  assert(encode_simple_new_order_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Simple New Order With Client Data Message: 98 bytes --------------------- */

/* Message sent by the client to enter a new order and, at the same time, the values for the Client Data parmeters. Note that no ClientDataID may be assigned */
typedef struct {
  uint8_t request_id[4];                 /* bytes 0 to 3 */
  uint8_t security_code[4];              /* bytes 4 to 7 */
  uint8_t order_id[4];                   /* bytes 8 to 11 */
  uint8_t side;                          /* byte 12 */
  uint8_t price[8];                      /* bytes 13 to 20 */
  uint8_t order_qty[4];                  /* bytes 21 to 24 */
  uint8_t time_in_force;                 /* byte 25 */
  uint8_t algorithmic_trade_indicator;   /* byte 26 */
  uint8_t client_id[4];                  /* bytes 27 to 30 */
  uint8_t account[5];                    /* bytes 31 to 35 */
  uint8_t dea_flag;                      /* byte 36 */
  uint8_t decisor_id[4];                 /* bytes 37 to 40 */
  uint8_t executor_id[4];                /* bytes 41 to 44 */
  uint8_t liquidity_provision_activity;  /* byte 45 */
  uint8_t give_in_member[4];             /* bytes 46 to 49 */
  uint8_t firm_mnemonic[10];             /* bytes 50 to 59 */
  uint8_t alloc_text[18];                /* bytes 60 to 77 */
  uint8_t last_capacity;                 /* byte 78 */
  uint8_t self_match_prevention_id[2];   /* bytes 79 to 80 */
  uint8_t persistence;                   /* byte 81 */
  uint8_t self_match_prevention_type;    /* byte 82 */
  uint8_t client_data_reference[15];     /* bytes 83 to 97 */
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
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
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
  record->persistence = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Simple New Order With Client Data Message to the wire: 98 bytes from at, returning where the next byte goes */
static size_t encode_simple_new_order_with_client_data_message(const SimpleNewOrderWithClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->time_in_force;
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
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
  wire[at++] = record->persistence;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Simple New Order With Client Data Message off the wire: 98 bytes from at, returning where the next byte lies */
static size_t decode_simple_new_order_with_client_data_message(SimpleNewOrderWithClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->time_in_force = wire[at++];
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
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
  record->persistence = wire[at++];
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
  assert(read->algorithmic_trade_indicator == written->algorithmic_trade_indicator);
  for (size_t i = 0; i < 4; i++) { assert(read->client_id[i] == written->client_id[i]); }
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
  assert(read->persistence == written->persistence);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Simple New Order With Client Data Message: written and read back, then read and written back */
static void check_simple_new_order_with_client_data_message(void) {
  SimpleNewOrderWithClientDataMessage sent;
  SimpleNewOrderWithClientDataMessage got;
  uint8_t wire[98];
  uint8_t again[98];

  any_simple_new_order_with_client_data_message(&sent);
  assert(encode_simple_new_order_with_client_data_message(&sent, wire, 0) == 98);
  assert(decode_simple_new_order_with_client_data_message(&got, wire, 0) == 98);
  equal_simple_new_order_with_client_data_message(&got, &sent);

  for (size_t i = 0; i < 98; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_new_order_with_client_data_message(&got, wire, 0) == 98);
  assert(encode_simple_new_order_with_client_data_message(&got, again, 0) == 98);
  for (size_t i = 0; i < 98; i++) { assert(again[i] == wire[i]); }
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

/* ---- Simple Order Modification With Client Data Message: 97 bytes ------------ */

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
  uint8_t account[5];                    /* bytes 30 to 34 */
  uint8_t dea_flag;                      /* byte 35 */
  uint8_t decisor_id[4];                 /* bytes 36 to 39 */
  uint8_t executor_id[4];                /* bytes 40 to 43 */
  uint8_t liquidity_provision_activity;  /* byte 44 */
  uint8_t give_in_member[4];             /* bytes 45 to 48 */
  uint8_t firm_mnemonic[10];             /* bytes 49 to 58 */
  uint8_t alloc_text[18];                /* bytes 59 to 76 */
  uint8_t last_capacity;                 /* byte 77 */
  uint8_t self_match_prevention_id[2];   /* bytes 78 to 79 */
  uint8_t persistence;                   /* byte 80 */
  uint8_t self_match_prevention_type;    /* byte 81 */
  uint8_t client_data_reference[15];     /* bytes 82 to 96 */
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
  record->persistence = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Simple Order Modification With Client Data Message to the wire: 97 bytes from at, returning where the next byte goes */
static size_t encode_simple_order_modification_with_client_data_message(const SimpleOrderModificationWithClientDataMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_qty[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
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
  wire[at++] = record->persistence;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Simple Order Modification With Client Data Message off the wire: 97 bytes from at, returning where the next byte lies */
static size_t decode_simple_order_modification_with_client_data_message(SimpleOrderModificationWithClientDataMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_id[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_qty[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
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
  record->persistence = wire[at++];
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
  assert(read->persistence == written->persistence);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Simple Order Modification With Client Data Message: written and read back, then read and written back */
static void check_simple_order_modification_with_client_data_message(void) {
  SimpleOrderModificationWithClientDataMessage sent;
  SimpleOrderModificationWithClientDataMessage got;
  uint8_t wire[97];
  uint8_t again[97];

  any_simple_order_modification_with_client_data_message(&sent);
  assert(encode_simple_order_modification_with_client_data_message(&sent, wire, 0) == 97);
  assert(decode_simple_order_modification_with_client_data_message(&got, wire, 0) == 97);
  equal_simple_order_modification_with_client_data_message(&got, &sent);

  for (size_t i = 0; i < 97; i++) { wire[i] = arbitrary(); }
  assert(decode_simple_order_modification_with_client_data_message(&got, wire, 0) == 97);
  assert(encode_simple_order_modification_with_client_data_message(&got, again, 0) == 97);
  for (size_t i = 0; i < 97; i++) { assert(again[i] == wire[i]); }
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

/* ---- Mass Orderquote Cancellation Message: 18 bytes -------------------------- */

/* Message sent by the client to request the cancellation of multiple orders and or quotes, based on the specified selection criteria */
typedef struct {
  uint8_t request_id[4];          /* bytes 0 to 3 */
  uint8_t account[5];             /* bytes 4 to 8 */
  uint8_t security_group[2];      /* bytes 9 to 10 */
  uint8_t security_code[4];       /* bytes 11 to 14 */
  uint8_t product_type;           /* byte 15 */
  uint8_t side;                   /* byte 16 */
  uint8_t order_or_quote_cancel;  /* byte 17 */
} MassOrderquoteCancellationMessage;

/* any Mass Orderquote Cancellation Message at all: every byte one the checker chooses */
static void any_mass_orderquote_cancellation_message(MassOrderquoteCancellationMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->account[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = arbitrary(); }
  record->product_type = arbitrary();
  record->side = arbitrary();
  record->order_or_quote_cancel = arbitrary();
}

/* Mass Orderquote Cancellation Message to the wire: 18 bytes from at, returning where the next byte goes */
static size_t encode_mass_orderquote_cancellation_message(const MassOrderquoteCancellationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->account[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_code[i]; }
  wire[at++] = record->product_type;
  wire[at++] = record->side;
  wire[at++] = record->order_or_quote_cancel;

  return at;
}

/* Mass Orderquote Cancellation Message off the wire: 18 bytes from at, returning where the next byte lies */
static size_t decode_mass_orderquote_cancellation_message(MassOrderquoteCancellationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->account[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_code[i] = wire[at++]; }
  record->product_type = wire[at++];
  record->side = wire[at++];
  record->order_or_quote_cancel = wire[at++];

  return at;
}

/* what was read of Mass Orderquote Cancellation Message is what was written, byte for byte */
static void equal_mass_orderquote_cancellation_message(const MassOrderquoteCancellationMessage *read, const MassOrderquoteCancellationMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->account[i] == written->account[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_group[i] == written->security_group[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_code[i] == written->security_code[i]); }
  assert(read->product_type == written->product_type);
  assert(read->side == written->side);
  assert(read->order_or_quote_cancel == written->order_or_quote_cancel);
}

/* Mass Orderquote Cancellation Message: written and read back, then read and written back */
static void check_mass_orderquote_cancellation_message(void) {
  MassOrderquoteCancellationMessage sent;
  MassOrderquoteCancellationMessage got;
  uint8_t wire[18];
  uint8_t again[18];

  any_mass_orderquote_cancellation_message(&sent);
  assert(encode_mass_orderquote_cancellation_message(&sent, wire, 0) == 18);
  assert(decode_mass_orderquote_cancellation_message(&got, wire, 0) == 18);
  equal_mass_orderquote_cancellation_message(&got, &sent);

  for (size_t i = 0; i < 18; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_orderquote_cancellation_message(&got, wire, 0) == 18);
  assert(encode_mass_orderquote_cancellation_message(&got, again, 0) == 18);
  for (size_t i = 0; i < 18; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order And Quote Client Data Parameters Ack Nack Message: 83 bytes ------- */

/* Sent by the server to confirm an Order and Quote Client Data Parameters message */
typedef struct {
  uint8_t sequence_number[4];            /* bytes 0 to 3 */
  uint8_t request_id[4];                 /* bytes 4 to 7 */
  uint8_t status;                        /* byte 8 */
  uint8_t client_data_id[2];             /* bytes 9 to 10 */
  uint8_t algorithmic_trade_indicator;   /* byte 11 */
  uint8_t client_id[4];                  /* bytes 12 to 15 */
  uint8_t account[5];                    /* bytes 16 to 20 */
  uint8_t dea_flag;                      /* byte 21 */
  uint8_t decisor_id[4];                 /* bytes 22 to 25 */
  uint8_t executor_id[4];                /* bytes 26 to 29 */
  uint8_t liquidity_provision_activity;  /* byte 30 */
  uint8_t give_in_member[4];             /* bytes 31 to 34 */
  uint8_t firm_mnemonic[10];             /* bytes 35 to 44 */
  uint8_t alloc_text[18];                /* bytes 45 to 62 */
  uint8_t last_capacity;                 /* byte 63 */
  uint8_t self_match_prevention_id[2];   /* bytes 64 to 65 */
  uint8_t persistence;                   /* byte 66 */
  uint8_t self_match_prevention_type;    /* byte 67 */
  uint8_t client_data_reference[15];     /* bytes 68 to 82 */
} OrderAndQuoteClientDataParametersAckNackMessage;

/* any Order And Quote Client Data Parameters Ack Nack Message at all: every byte one the checker chooses */
static void any_order_and_quote_client_data_parameters_ack_nack_message(OrderAndQuoteClientDataParametersAckNackMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = arbitrary(); }
  record->algorithmic_trade_indicator = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = arbitrary(); }
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
  record->persistence = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 15; i++) { record->client_data_reference[i] = arbitrary(); }
}

/* Order And Quote Client Data Parameters Ack Nack Message to the wire: 83 bytes from at, returning where the next byte goes */
static size_t encode_order_and_quote_client_data_parameters_ack_nack_message(const OrderAndQuoteClientDataParametersAckNackMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->client_data_id[i]; }
  wire[at++] = record->algorithmic_trade_indicator;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_id[i]; }
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
  wire[at++] = record->persistence;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->client_data_reference[i]; }

  return at;
}

/* Order And Quote Client Data Parameters Ack Nack Message off the wire: 83 bytes from at, returning where the next byte lies */
static size_t decode_order_and_quote_client_data_parameters_ack_nack_message(OrderAndQuoteClientDataParametersAckNackMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->client_data_id[i] = wire[at++]; }
  record->algorithmic_trade_indicator = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_id[i] = wire[at++]; }
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
  record->persistence = wire[at++];
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
  assert(read->persistence == written->persistence);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 15; i++) { assert(read->client_data_reference[i] == written->client_data_reference[i]); }
}

/* Order And Quote Client Data Parameters Ack Nack Message: written and read back, then read and written back */
static void check_order_and_quote_client_data_parameters_ack_nack_message(void) {
  OrderAndQuoteClientDataParametersAckNackMessage sent;
  OrderAndQuoteClientDataParametersAckNackMessage got;
  uint8_t wire[83];
  uint8_t again[83];

  any_order_and_quote_client_data_parameters_ack_nack_message(&sent);
  assert(encode_order_and_quote_client_data_parameters_ack_nack_message(&sent, wire, 0) == 83);
  assert(decode_order_and_quote_client_data_parameters_ack_nack_message(&got, wire, 0) == 83);
  equal_order_and_quote_client_data_parameters_ack_nack_message(&got, &sent);

  for (size_t i = 0; i < 83; i++) { wire[i] = arbitrary(); }
  assert(decode_order_and_quote_client_data_parameters_ack_nack_message(&got, wire, 0) == 83);
  assert(encode_order_and_quote_client_data_parameters_ack_nack_message(&got, again, 0) == 83);
  for (size_t i = 0; i < 83; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delta Protection Parameters Ack Nack Message: 17 bytes ------------------ */

/* Sent by the server to confirm a Delta Protection Parameters message */
typedef struct {
  uint8_t sequence_number[4];          /* bytes 0 to 3 */
  uint8_t request_id[4];               /* bytes 4 to 7 */
  uint8_t status;                      /* byte 8 */
  uint8_t security_group[2];           /* bytes 9 to 10 */
  uint8_t product_type;                /* byte 11 */
  uint8_t delta_protection_time;       /* byte 12 */
  uint8_t delta_protection_volume[4];  /* bytes 13 to 16 */
} DeltaProtectionParametersAckNackMessage;

/* any Delta Protection Parameters Ack Nack Message at all: every byte one the checker chooses */
static void any_delta_protection_parameters_ack_nack_message(DeltaProtectionParametersAckNackMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = arbitrary(); }
  record->status = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = arbitrary(); }
  record->product_type = arbitrary();
  record->delta_protection_time = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->delta_protection_volume[i] = arbitrary(); }
}

/* Delta Protection Parameters Ack Nack Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_delta_protection_parameters_ack_nack_message(const DeltaProtectionParametersAckNackMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_id[i]; }
  wire[at++] = record->status;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_group[i]; }
  wire[at++] = record->product_type;
  wire[at++] = record->delta_protection_time;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->delta_protection_volume[i]; }

  return at;
}

/* Delta Protection Parameters Ack Nack Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_delta_protection_parameters_ack_nack_message(DeltaProtectionParametersAckNackMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->request_id[i] = wire[at++]; }
  record->status = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->security_group[i] = wire[at++]; }
  record->product_type = wire[at++];
  record->delta_protection_time = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->delta_protection_volume[i] = wire[at++]; }

  return at;
}

/* what was read of Delta Protection Parameters Ack Nack Message is what was written, byte for byte */
static void equal_delta_protection_parameters_ack_nack_message(const DeltaProtectionParametersAckNackMessage *read, const DeltaProtectionParametersAckNackMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->request_id[i] == written->request_id[i]); }
  assert(read->status == written->status);
  for (size_t i = 0; i < 2; i++) { assert(read->security_group[i] == written->security_group[i]); }
  assert(read->product_type == written->product_type);
  assert(read->delta_protection_time == written->delta_protection_time);
  for (size_t i = 0; i < 4; i++) { assert(read->delta_protection_volume[i] == written->delta_protection_volume[i]); }
}

/* Delta Protection Parameters Ack Nack Message: written and read back, then read and written back */
static void check_delta_protection_parameters_ack_nack_message(void) {
  DeltaProtectionParametersAckNackMessage sent;
  DeltaProtectionParametersAckNackMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_delta_protection_parameters_ack_nack_message(&sent);
  assert(encode_delta_protection_parameters_ack_nack_message(&sent, wire, 0) == 17);
  assert(decode_delta_protection_parameters_ack_nack_message(&got, wire, 0) == 17);
  equal_delta_protection_parameters_ack_nack_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_delta_protection_parameters_ack_nack_message(&got, wire, 0) == 17);
  assert(encode_delta_protection_parameters_ack_nack_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
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

/* ---- Execution Private Information 2 Legs Message: 144 bytes ----------------- */

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
  uint8_t transaction_category;          /* byte 49 */
  uint8_t strategy_trd_match_id[4];      /* bytes 50 to 53 */
  uint8_t secondary_order_id[4];         /* bytes 54 to 57 */
  uint8_t entry_date[4];                 /* bytes 58 to 61 */
  uint8_t priority[4];                   /* bytes 62 to 65 */
  uint8_t price[8];                      /* bytes 66 to 73 */
  uint8_t display_qty[4];                /* bytes 74 to 77 */
  uint8_t order_id[4];                   /* bytes 78 to 81 */
  uint8_t secondary_exec_id[4];          /* bytes 82 to 85 */
  uint8_t order_qty[4];                  /* bytes 86 to 89 */
  uint8_t ord_status;                    /* byte 90 */
  uint8_t ccp_code;                      /* byte 91 */
  uint8_t aggressor_indicator;           /* byte 92 */
  uint8_t request_id[4];                 /* bytes 93 to 96 */
  uint8_t client_data_id[2];             /* bytes 97 to 98 */
  uint8_t secondary_order_id_2[4];       /* bytes 99 to 102 */
  uint8_t entry_date_2[4];               /* bytes 103 to 106 */
  uint8_t priority_2[4];                 /* bytes 107 to 110 */
  uint8_t price_2[8];                    /* bytes 111 to 118 */
  uint8_t display_qty_2[4];              /* bytes 119 to 122 */
  uint8_t order_id_2[4];                 /* bytes 123 to 126 */
  uint8_t secondary_exec_id_2[4];        /* bytes 127 to 130 */
  uint8_t order_qty_2[4];                /* bytes 131 to 134 */
  uint8_t ord_status_2;                  /* byte 135 */
  uint8_t ccp_code_2;                    /* byte 136 */
  uint8_t aggressor_indicator_2;         /* byte 137 */
  uint8_t request_id_2[4];               /* bytes 138 to 141 */
  uint8_t client_data_id_2[2];           /* bytes 142 to 143 */
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
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = arbitrary(); }
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

/* Execution Private Information 2 Legs Message to the wire: 144 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_trd_match_id[i]; }
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

/* Execution Private Information 2 Legs Message off the wire: 144 bytes from at, returning where the next byte lies */
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
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = wire[at++]; }
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
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_trd_match_id[i] == written->strategy_trd_match_id[i]); }
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
  uint8_t wire[144];
  uint8_t again[144];

  any_execution_private_information2_legs_message(&sent);
  assert(encode_execution_private_information2_legs_message(&sent, wire, 0) == 144);
  assert(decode_execution_private_information2_legs_message(&got, wire, 0) == 144);
  equal_execution_private_information2_legs_message(&got, &sent);

  for (size_t i = 0; i < 144; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information2_legs_message(&got, wire, 0) == 144);
  assert(encode_execution_private_information2_legs_message(&got, again, 0) == 144);
  for (size_t i = 0; i < 144; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message: 255 bytes ---- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. The user is involved in the trade as Buyer. It is also sent to inform about the amendment or cancellation of whatever origin trade where the user is involved as Buyer. Shares the same layout as the next message */
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
  uint8_t broker[4];                       /* bytes 89 to 92 */
  uint8_t broker_trader[3];                /* bytes 93 to 95 */
  uint8_t broker_text[15];                 /* bytes 96 to 110 */
  uint8_t cancel_pre_amendment;            /* byte 111 */
  uint8_t secondary_order_id[4];           /* bytes 112 to 115 */
  uint8_t entry_date[4];                   /* bytes 116 to 119 */
  uint8_t priority[4];                     /* bytes 120 to 123 */
  uint8_t price[8];                        /* bytes 124 to 131 */
  uint8_t display_qty[4];                  /* bytes 132 to 135 */
  uint8_t order_id[4];                     /* bytes 136 to 139 */
  uint8_t secondary_exec_id[4];            /* bytes 140 to 143 */
  uint8_t order_qty[4];                    /* bytes 144 to 147 */
  uint8_t ord_status;                      /* byte 148 */
  uint8_t ccp_code;                        /* byte 149 */
  uint8_t aggressor_indicator;             /* byte 150 */
  uint8_t request_id[4];                   /* bytes 151 to 154 */
  uint8_t client_data_id[2];               /* bytes 155 to 156 */
  uint8_t algorithmic_trade_indicator;     /* byte 157 */
  uint8_t client_id[4];                    /* bytes 158 to 161 */
  uint8_t account[5];                      /* bytes 162 to 166 */
  uint8_t dea_flag;                        /* byte 167 */
  uint8_t decisor_id[4];                   /* bytes 168 to 171 */
  uint8_t executor_id[4];                  /* bytes 172 to 175 */
  uint8_t liquidity_provision_activity;    /* byte 176 */
  uint8_t give_in_member[4];               /* bytes 177 to 180 */
  uint8_t firm_mnemonic[10];               /* bytes 181 to 190 */
  uint8_t alloc_text[18];                  /* bytes 191 to 208 */
  uint8_t last_capacity;                   /* byte 209 */
  uint8_t self_match_prevention_id[2];     /* bytes 210 to 211 */
  uint8_t persistence;                     /* byte 212 */
  uint8_t self_match_prevention_type;      /* byte 213 */
  uint8_t member[4];                       /* bytes 214 to 217 */
  uint8_t trader[3];                       /* bytes 218 to 220 */
  uint8_t sub_member;                      /* byte 221 */
  uint8_t cross_id[4];                     /* bytes 222 to 225 */
  uint8_t ccv[20];                         /* bytes 226 to 245 */
  uint8_t order_security_code[4];          /* bytes 246 to 249 */
  uint8_t external_member[4];              /* bytes 250 to 253 */
  uint8_t risk_reduction;                  /* byte 254 */
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
  for (size_t i = 0; i < 4; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = arbitrary(); }
  record->cancel_pre_amendment = arbitrary();
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
  record->persistence = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = arbitrary(); }
  record->risk_reduction = arbitrary();
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message to the wire: 255 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker_trader[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->broker_text[i]; }
  wire[at++] = record->cancel_pre_amendment;
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
  wire[at++] = record->persistence;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ccv[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_member[i]; }
  wire[at++] = record->risk_reduction;

  return at;
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message off the wire: 255 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 4; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = wire[at++]; }
  record->cancel_pre_amendment = wire[at++];
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
  record->persistence = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = wire[at++]; }
  record->risk_reduction = wire[at++];

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
  for (size_t i = 0; i < 4; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker_trader[i] == written->broker_trader[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->broker_text[i] == written->broker_text[i]); }
  assert(read->cancel_pre_amendment == written->cancel_pre_amendment);
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
  assert(read->persistence == written->persistence);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ccv[i] == written->ccv[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->external_member[i] == written->external_member[i]); }
  assert(read->risk_reduction == written->risk_reduction);
}

/* Trade Trade Amendment Or Cancellation 1 Leg Buy Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(void) {
  TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 sent;
  TradeTradeAmendmentOrCancellation1LegBuyPrivateInformatio_lt8bv1 got;
  uint8_t wire[255];
  uint8_t again[255];

  any_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&sent);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&sent, wire, 0) == 255);
  assert(decode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, wire, 0) == 255);
  equal_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, &sent);

  for (size_t i = 0; i < 255; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, wire, 0) == 255);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_buy_private_informatio_lt8bv1(&got, again, 0) == 255);
  for (size_t i = 0; i < 255; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message: 255 bytes ---- */

/* Sent by the server to inform about a trade produced due to any reason other than order matching, also to inform about trades produced due to order matching in a Dark pool. The user is involved in the trade as Seller */
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
  uint8_t broker[4];                       /* bytes 89 to 92 */
  uint8_t broker_trader[3];                /* bytes 93 to 95 */
  uint8_t broker_text[15];                 /* bytes 96 to 110 */
  uint8_t cancel_pre_amendment;            /* byte 111 */
  uint8_t secondary_order_id[4];           /* bytes 112 to 115 */
  uint8_t entry_date[4];                   /* bytes 116 to 119 */
  uint8_t priority[4];                     /* bytes 120 to 123 */
  uint8_t price[8];                        /* bytes 124 to 131 */
  uint8_t display_qty[4];                  /* bytes 132 to 135 */
  uint8_t order_id[4];                     /* bytes 136 to 139 */
  uint8_t secondary_exec_id[4];            /* bytes 140 to 143 */
  uint8_t order_qty[4];                    /* bytes 144 to 147 */
  uint8_t ord_status;                      /* byte 148 */
  uint8_t ccp_code;                        /* byte 149 */
  uint8_t aggressor_indicator;             /* byte 150 */
  uint8_t request_id[4];                   /* bytes 151 to 154 */
  uint8_t client_data_id[2];               /* bytes 155 to 156 */
  uint8_t algorithmic_trade_indicator;     /* byte 157 */
  uint8_t client_id[4];                    /* bytes 158 to 161 */
  uint8_t account[5];                      /* bytes 162 to 166 */
  uint8_t dea_flag;                        /* byte 167 */
  uint8_t decisor_id[4];                   /* bytes 168 to 171 */
  uint8_t executor_id[4];                  /* bytes 172 to 175 */
  uint8_t liquidity_provision_activity;    /* byte 176 */
  uint8_t give_in_member[4];               /* bytes 177 to 180 */
  uint8_t firm_mnemonic[10];               /* bytes 181 to 190 */
  uint8_t alloc_text[18];                  /* bytes 191 to 208 */
  uint8_t last_capacity;                   /* byte 209 */
  uint8_t self_match_prevention_id[2];     /* bytes 210 to 211 */
  uint8_t persistence;                     /* byte 212 */
  uint8_t self_match_prevention_type;      /* byte 213 */
  uint8_t member[4];                       /* bytes 214 to 217 */
  uint8_t trader[3];                       /* bytes 218 to 220 */
  uint8_t sub_member;                      /* byte 221 */
  uint8_t cross_id[4];                     /* bytes 222 to 225 */
  uint8_t ccv[20];                         /* bytes 226 to 245 */
  uint8_t order_security_code[4];          /* bytes 246 to 249 */
  uint8_t external_member[4];              /* bytes 250 to 253 */
  uint8_t risk_reduction;                  /* byte 254 */
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
  for (size_t i = 0; i < 4; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = arbitrary(); }
  record->cancel_pre_amendment = arbitrary();
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
  record->persistence = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = arbitrary(); }
  record->risk_reduction = arbitrary();
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message to the wire: 255 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker_trader[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->broker_text[i]; }
  wire[at++] = record->cancel_pre_amendment;
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
  wire[at++] = record->persistence;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ccv[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_member[i]; }
  wire[at++] = record->risk_reduction;

  return at;
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message off the wire: 255 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 4; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = wire[at++]; }
  record->cancel_pre_amendment = wire[at++];
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
  record->persistence = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = wire[at++]; }
  record->risk_reduction = wire[at++];

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
  for (size_t i = 0; i < 4; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker_trader[i] == written->broker_trader[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->broker_text[i] == written->broker_text[i]); }
  assert(read->cancel_pre_amendment == written->cancel_pre_amendment);
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
  assert(read->persistence == written->persistence);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ccv[i] == written->ccv[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->external_member[i] == written->external_member[i]); }
  assert(read->risk_reduction == written->risk_reduction);
}

/* Trade Trade Amendment Or Cancellation 1 Leg Sell Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(void) {
  TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv sent;
  TradeTradeAmendmentOrCancellation1LegSellPrivateInformati_tynsxv got;
  uint8_t wire[255];
  uint8_t again[255];

  any_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&sent);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&sent, wire, 0) == 255);
  assert(decode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, wire, 0) == 255);
  equal_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, &sent);

  for (size_t i = 0; i < 255; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, wire, 0) == 255);
  assert(encode_trade_trade_amendment_or_cancellation1_leg_sell_private_informati_tynsxv(&got, again, 0) == 255);
  for (size_t i = 0; i < 255; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Trade Amendment Or Cancellation 2 Legs Private Information Message: 398 bytes ---- */

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
  uint8_t broker[4];                       /* bytes 89 to 92 */
  uint8_t broker_trader[3];                /* bytes 93 to 95 */
  uint8_t broker_text[15];                 /* bytes 96 to 110 */
  uint8_t cancel_pre_amendment;            /* byte 111 */
  uint8_t secondary_order_id[4];           /* bytes 112 to 115 */
  uint8_t entry_date[4];                   /* bytes 116 to 119 */
  uint8_t priority[4];                     /* bytes 120 to 123 */
  uint8_t price[8];                        /* bytes 124 to 131 */
  uint8_t display_qty[4];                  /* bytes 132 to 135 */
  uint8_t order_id[4];                     /* bytes 136 to 139 */
  uint8_t secondary_exec_id[4];            /* bytes 140 to 143 */
  uint8_t order_qty[4];                    /* bytes 144 to 147 */
  uint8_t ord_status;                      /* byte 148 */
  uint8_t ccp_code;                        /* byte 149 */
  uint8_t aggressor_indicator;             /* byte 150 */
  uint8_t request_id[4];                   /* bytes 151 to 154 */
  uint8_t client_data_id[2];               /* bytes 155 to 156 */
  uint8_t algorithmic_trade_indicator;     /* byte 157 */
  uint8_t client_id[4];                    /* bytes 158 to 161 */
  uint8_t account[5];                      /* bytes 162 to 166 */
  uint8_t dea_flag;                        /* byte 167 */
  uint8_t decisor_id[4];                   /* bytes 168 to 171 */
  uint8_t executor_id[4];                  /* bytes 172 to 175 */
  uint8_t liquidity_provision_activity;    /* byte 176 */
  uint8_t give_in_member[4];               /* bytes 177 to 180 */
  uint8_t firm_mnemonic[10];               /* bytes 181 to 190 */
  uint8_t alloc_text[18];                  /* bytes 191 to 208 */
  uint8_t last_capacity;                   /* byte 209 */
  uint8_t self_match_prevention_id[2];     /* bytes 210 to 211 */
  uint8_t persistence;                     /* byte 212 */
  uint8_t self_match_prevention_type;      /* byte 213 */
  uint8_t member[4];                       /* bytes 214 to 217 */
  uint8_t trader[3];                       /* bytes 218 to 220 */
  uint8_t sub_member;                      /* byte 221 */
  uint8_t cross_id[4];                     /* bytes 222 to 225 */
  uint8_t ccv[20];                         /* bytes 226 to 245 */
  uint8_t order_security_code[4];          /* bytes 246 to 249 */
  uint8_t external_member[4];              /* bytes 250 to 253 */
  uint8_t risk_reduction;                  /* byte 254 */
  uint8_t secondary_order_id_2[4];         /* bytes 255 to 258 */
  uint8_t entry_date_2[4];                 /* bytes 259 to 262 */
  uint8_t priority_2[4];                   /* bytes 263 to 266 */
  uint8_t price_2[8];                      /* bytes 267 to 274 */
  uint8_t display_qty_2[4];                /* bytes 275 to 278 */
  uint8_t order_id_2[4];                   /* bytes 279 to 282 */
  uint8_t secondary_exec_id_2[4];          /* bytes 283 to 286 */
  uint8_t order_qty_2[4];                  /* bytes 287 to 290 */
  uint8_t ord_status_2;                    /* byte 291 */
  uint8_t ccp_code_2;                      /* byte 292 */
  uint8_t aggressor_indicator_2;           /* byte 293 */
  uint8_t request_id_2[4];                 /* bytes 294 to 297 */
  uint8_t client_data_id_2[2];             /* bytes 298 to 299 */
  uint8_t algorithmic_trade_indicator_2;   /* byte 300 */
  uint8_t client_id_2[4];                  /* bytes 301 to 304 */
  uint8_t account_2[5];                    /* bytes 305 to 309 */
  uint8_t dea_flag_2;                      /* byte 310 */
  uint8_t decisor_id_2[4];                 /* bytes 311 to 314 */
  uint8_t executor_id_2[4];                /* bytes 315 to 318 */
  uint8_t liquidity_provision_activity_2;  /* byte 319 */
  uint8_t give_in_member_2[4];             /* bytes 320 to 323 */
  uint8_t firm_mnemonic_2[10];             /* bytes 324 to 333 */
  uint8_t alloc_text_2[18];                /* bytes 334 to 351 */
  uint8_t last_capacity_2;                 /* byte 352 */
  uint8_t self_match_prevention_id_2[2];   /* bytes 353 to 354 */
  uint8_t persistence_2;                   /* byte 355 */
  uint8_t self_match_prevention_type_2;    /* byte 356 */
  uint8_t member_2[4];                     /* bytes 357 to 360 */
  uint8_t trader_2[3];                     /* bytes 361 to 363 */
  uint8_t sub_member_2;                    /* byte 364 */
  uint8_t cross_id_2[4];                   /* bytes 365 to 368 */
  uint8_t ccv_2[20];                       /* bytes 369 to 388 */
  uint8_t order_security_code_2[4];        /* bytes 389 to 392 */
  uint8_t external_member_2[4];            /* bytes 393 to 396 */
  uint8_t risk_reduction_2;                /* byte 397 */
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
  for (size_t i = 0; i < 4; i++) { record->broker[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = arbitrary(); }
  record->cancel_pre_amendment = arbitrary();
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
  record->persistence = arbitrary();
  record->self_match_prevention_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = arbitrary(); }
  record->sub_member = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = arbitrary(); }
  record->risk_reduction = arbitrary();
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
  record->persistence_2 = arbitrary();
  record->self_match_prevention_type_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->member_2[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->trader_2[i] = arbitrary(); }
  record->sub_member_2 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->cross_id_2[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->ccv_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_security_code_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->external_member_2[i] = arbitrary(); }
  record->risk_reduction_2 = arbitrary();
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message to the wire: 398 bytes from at, returning where the next byte goes */
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
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->broker[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->broker_trader[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->broker_text[i]; }
  wire[at++] = record->cancel_pre_amendment;
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
  wire[at++] = record->persistence;
  wire[at++] = record->self_match_prevention_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader[i]; }
  wire[at++] = record->sub_member;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ccv[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_member[i]; }
  wire[at++] = record->risk_reduction;
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
  wire[at++] = record->persistence_2;
  wire[at++] = record->self_match_prevention_type_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_2[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->trader_2[i]; }
  wire[at++] = record->sub_member_2;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cross_id_2[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->ccv_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_security_code_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->external_member_2[i]; }
  wire[at++] = record->risk_reduction_2;

  return at;
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message off the wire: 398 bytes from at, returning where the next byte lies */
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
  for (size_t i = 0; i < 4; i++) { record->broker[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->broker_trader[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->broker_text[i] = wire[at++]; }
  record->cancel_pre_amendment = wire[at++];
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
  record->persistence = wire[at++];
  record->self_match_prevention_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader[i] = wire[at++]; }
  record->sub_member = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ccv[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->external_member[i] = wire[at++]; }
  record->risk_reduction = wire[at++];
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
  record->persistence_2 = wire[at++];
  record->self_match_prevention_type_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->member_2[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->trader_2[i] = wire[at++]; }
  record->sub_member_2 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->cross_id_2[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->ccv_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_security_code_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->external_member_2[i] = wire[at++]; }
  record->risk_reduction_2 = wire[at++];

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
  for (size_t i = 0; i < 4; i++) { assert(read->broker[i] == written->broker[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->broker_trader[i] == written->broker_trader[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->broker_text[i] == written->broker_text[i]); }
  assert(read->cancel_pre_amendment == written->cancel_pre_amendment);
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
  assert(read->persistence == written->persistence);
  assert(read->self_match_prevention_type == written->self_match_prevention_type);
  for (size_t i = 0; i < 4; i++) { assert(read->member[i] == written->member[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader[i] == written->trader[i]); }
  assert(read->sub_member == written->sub_member);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id[i] == written->cross_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ccv[i] == written->ccv[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code[i] == written->order_security_code[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->external_member[i] == written->external_member[i]); }
  assert(read->risk_reduction == written->risk_reduction);
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
  assert(read->persistence_2 == written->persistence_2);
  assert(read->self_match_prevention_type_2 == written->self_match_prevention_type_2);
  for (size_t i = 0; i < 4; i++) { assert(read->member_2[i] == written->member_2[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->trader_2[i] == written->trader_2[i]); }
  assert(read->sub_member_2 == written->sub_member_2);
  for (size_t i = 0; i < 4; i++) { assert(read->cross_id_2[i] == written->cross_id_2[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->ccv_2[i] == written->ccv_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_security_code_2[i] == written->order_security_code_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->external_member_2[i] == written->external_member_2[i]); }
  assert(read->risk_reduction_2 == written->risk_reduction_2);
}

/* Trade Trade Amendment Or Cancellation 2 Legs Private Information Message: written and read back, then read and written back */
static void check_trade_trade_amendment_or_cancellation2_legs_private_information_message(void) {
  TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage sent;
  TradeTradeAmendmentOrCancellation2LegsPrivateInformationMessage got;
  uint8_t wire[398];
  uint8_t again[398];

  any_trade_trade_amendment_or_cancellation2_legs_private_information_message(&sent);
  assert(encode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&sent, wire, 0) == 398);
  assert(decode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, wire, 0) == 398);
  equal_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, &sent);

  for (size_t i = 0; i < 398; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, wire, 0) == 398);
  assert(encode_trade_trade_amendment_or_cancellation2_legs_private_information_message(&got, again, 0) == 398);
  for (size_t i = 0; i < 398; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Private Information 1 Leg Buy Order Entry Message: 99 bytes ---- */

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
  uint8_t transaction_category;          /* byte 49 */
  uint8_t strategy_trd_match_id[4];      /* bytes 50 to 53 */
  uint8_t secondary_order_id[4];         /* bytes 54 to 57 */
  uint8_t entry_date[4];                 /* bytes 58 to 61 */
  uint8_t priority[4];                   /* bytes 62 to 65 */
  uint8_t price[8];                      /* bytes 66 to 73 */
  uint8_t display_qty[4];                /* bytes 74 to 77 */
  uint8_t order_id[4];                   /* bytes 78 to 81 */
  uint8_t secondary_exec_id[4];          /* bytes 82 to 85 */
  uint8_t order_qty[4];                  /* bytes 86 to 89 */
  uint8_t ord_status;                    /* byte 90 */
  uint8_t ccp_code;                      /* byte 91 */
  uint8_t aggressor_indicator;           /* byte 92 */
  uint8_t request_id[4];                 /* bytes 93 to 96 */
  uint8_t client_data_id[2];             /* bytes 97 to 98 */
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
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = arbitrary(); }
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

/* Execution Private Information 1 Leg Buy Order Entry Message to the wire: 99 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_trd_match_id[i]; }
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

/* Execution Private Information 1 Leg Buy Order Entry Message off the wire: 99 bytes from at, returning where the next byte lies */
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
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = wire[at++]; }
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
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_trd_match_id[i] == written->strategy_trd_match_id[i]); }
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
  uint8_t wire[99];
  uint8_t again[99];

  any_execution_private_information1_leg_buy_order_entry_message(&sent);
  assert(encode_execution_private_information1_leg_buy_order_entry_message(&sent, wire, 0) == 99);
  assert(decode_execution_private_information1_leg_buy_order_entry_message(&got, wire, 0) == 99);
  equal_execution_private_information1_leg_buy_order_entry_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information1_leg_buy_order_entry_message(&got, wire, 0) == 99);
  assert(encode_execution_private_information1_leg_buy_order_entry_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Execution Private Information 1 Leg Sell Order Entry Message: 99 bytes ---- */

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
  uint8_t transaction_category;          /* byte 49 */
  uint8_t strategy_trd_match_id[4];      /* bytes 50 to 53 */
  uint8_t secondary_order_id[4];         /* bytes 54 to 57 */
  uint8_t entry_date[4];                 /* bytes 58 to 61 */
  uint8_t priority[4];                   /* bytes 62 to 65 */
  uint8_t price[8];                      /* bytes 66 to 73 */
  uint8_t display_qty[4];                /* bytes 74 to 77 */
  uint8_t order_id[4];                   /* bytes 78 to 81 */
  uint8_t secondary_exec_id[4];          /* bytes 82 to 85 */
  uint8_t order_qty[4];                  /* bytes 86 to 89 */
  uint8_t ord_status;                    /* byte 90 */
  uint8_t ccp_code;                      /* byte 91 */
  uint8_t aggressor_indicator;           /* byte 92 */
  uint8_t request_id[4];                 /* bytes 93 to 96 */
  uint8_t client_data_id[2];             /* bytes 97 to 98 */
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
  record->transaction_category = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = arbitrary(); }
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

/* Execution Private Information 1 Leg Sell Order Entry Message to the wire: 99 bytes from at, returning where the next byte goes */
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
  wire[at++] = record->transaction_category;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strategy_trd_match_id[i]; }
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

/* Execution Private Information 1 Leg Sell Order Entry Message off the wire: 99 bytes from at, returning where the next byte lies */
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
  record->transaction_category = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->strategy_trd_match_id[i] = wire[at++]; }
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
  assert(read->transaction_category == written->transaction_category);
  for (size_t i = 0; i < 4; i++) { assert(read->strategy_trd_match_id[i] == written->strategy_trd_match_id[i]); }
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
  uint8_t wire[99];
  uint8_t again[99];

  any_execution_private_information1_leg_sell_order_entry_message(&sent);
  assert(encode_execution_private_information1_leg_sell_order_entry_message(&sent, wire, 0) == 99);
  assert(decode_execution_private_information1_leg_sell_order_entry_message(&got, wire, 0) == 99);
  equal_execution_private_information1_leg_sell_order_entry_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_execution_private_information1_leg_sell_order_entry_message(&got, wire, 0) == 99);
  assert(encode_execution_private_information1_leg_sell_order_entry_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
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
  check_family_status_message();
  check_order_cancellation_market_member_message();
  check_quote_cancellation_market_member_message();
  check_indication_of_interest_message();
  check_order_and_quote_client_data_message();
  check_delta_protection_parameters_message();
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
  check_delta_protection_parameters_ack_nack_message();
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
