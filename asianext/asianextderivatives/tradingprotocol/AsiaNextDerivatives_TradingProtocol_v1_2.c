// asianext/asianextderivatives/tradingprotocol/AsiaNextDerivatives_TradingProtocol_v1_2.c
/*
 * AsiaNext Aquis Trading Protocol
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

/* ---- Message Header: 11 bytes ------------------------------------------------ */

/* AsiaNext Atp message header */
typedef struct {
  uint8_t msg_length[2];  /* bytes 0 to 1 */
  uint8_t msg_type;       /* byte 2 */
  uint8_t msg_seq_no[8];  /* bytes 3 to 10 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  record->msg_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->msg_seq_no[i] = arbitrary(); }
}

/* Message Header to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  wire[at++] = record->msg_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->msg_seq_no[i]; }

  return at;
}

/* Message Header off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  record->msg_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->msg_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  assert(read->msg_type == written->msg_type);
  for (size_t i = 0; i < 8; i++) { assert(read->msg_seq_no[i] == written->msg_seq_no[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[11];
  uint8_t again[11];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 11);
  assert(decode_message_header(&got, wire, 0) == 11);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 11);
  assert(encode_message_header(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Message: 44 bytes ------------------------------------------------- */

/* The Login message is sent by the trading Member as the initial message used to establish a trading session. It is also used to re-establish a session after a break. */
typedef struct {
  uint8_t protocol_version[2];    /* bytes 0 to 1 */
  uint8_t sender_id[16];          /* bytes 2 to 17 */
  uint8_t password[16];           /* bytes 18 to 33 */
  uint8_t inactivity_timeout[2];  /* bytes 34 to 35 */
  uint8_t atp_seq_no[8];          /* bytes 36 to 43 */
} LoginMessage;

/* any Login Message at all: every byte one the checker chooses */
static void any_login_message(LoginMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->protocol_version[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inactivity_timeout[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->atp_seq_no[i] = arbitrary(); }
}

/* Login Message to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_login_message(const LoginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->protocol_version[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inactivity_timeout[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->atp_seq_no[i]; }

  return at;
}

/* Login Message off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_login_message(LoginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->protocol_version[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inactivity_timeout[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->atp_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Login Message is what was written, byte for byte */
static void equal_login_message(const LoginMessage *read, const LoginMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inactivity_timeout[i] == written->inactivity_timeout[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->atp_seq_no[i] == written->atp_seq_no[i]); }
}

/* Login Message: written and read back, then read and written back */
static void check_login_message(void) {
  LoginMessage sent;
  LoginMessage got;
  uint8_t wire[44];
  uint8_t again[44];

  any_login_message(&sent);
  assert(encode_login_message(&sent, wire, 0) == 44);
  assert(decode_login_message(&got, wire, 0) == 44);
  equal_login_message(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_login_message(&got, wire, 0) == 44);
  assert(encode_login_message(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response Message: 9 bytes ----------------------------------------- */

/* The Login Response message is sent by AsiaNext to acknowledge a Login request, and either accept or reject it. */
typedef struct {
  uint8_t result_code;       /* byte 0 */
  uint8_t client_seq_no[8];  /* bytes 1 to 8 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  record->result_code = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->client_seq_no[i] = arbitrary(); }
}

/* Login Response Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->result_code;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_seq_no[i]; }

  return at;
}

/* Login Response Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  record->result_code = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->client_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  assert(read->result_code == written->result_code);
  for (size_t i = 0; i < 8; i++) { assert(read->client_seq_no[i] == written->client_seq_no[i]); }
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 9);
  assert(decode_login_response_message(&got, wire, 0) == 9);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 9);
  assert(encode_login_response_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 33 bytes ------------------------------------------------ */

/* The Logout message is usually sent as a response to the Logout Request. However it may also be sent by AsiaNext in case of a low sequence number or other protocol violation, or for other reasons. */
typedef struct {
  uint8_t logout_reason_code;  /* byte 0 */
  uint8_t reason_text[32];     /* bytes 1 to 32 */
} LogoutMessage;

/* any Logout Message at all: every byte one the checker chooses */
static void any_logout_message(LogoutMessage *record) {
  record->logout_reason_code = arbitrary();
  for (size_t i = 0; i < 32; i++) { record->reason_text[i] = arbitrary(); }
}

/* Logout Message to the wire: 33 bytes from at, returning where the next byte goes */
static size_t encode_logout_message(const LogoutMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->logout_reason_code;
  for (size_t i = 0; i < 32; i++) { wire[at++] = record->reason_text[i]; }

  return at;
}

/* Logout Message off the wire: 33 bytes from at, returning where the next byte lies */
static size_t decode_logout_message(LogoutMessage *record, const uint8_t *wire, size_t at) {
  record->logout_reason_code = wire[at++];
  for (size_t i = 0; i < 32; i++) { record->reason_text[i] = wire[at++]; }

  return at;
}

/* what was read of Logout Message is what was written, byte for byte */
static void equal_logout_message(const LogoutMessage *read, const LogoutMessage *written) {
  assert(read->logout_reason_code == written->logout_reason_code);
  for (size_t i = 0; i < 32; i++) { assert(read->reason_text[i] == written->reason_text[i]); }
}

/* Logout Message: written and read back, then read and written back */
static void check_logout_message(void) {
  LogoutMessage sent;
  LogoutMessage got;
  uint8_t wire[33];
  uint8_t again[33];

  any_logout_message(&sent);
  assert(encode_logout_message(&sent, wire, 0) == 33);
  assert(decode_logout_message(&got, wire, 0) == 33);
  equal_logout_message(&got, &sent);

  for (size_t i = 0; i < 33; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_message(&got, wire, 0) == 33);
  assert(encode_logout_message(&got, again, 0) == 33);
  for (size_t i = 0; i < 33; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Request Message: 37 bytes ----------------------------------------- */

/* The Quote Request Message is sent to commence RFQ session. */
typedef struct {
  uint8_t security_id_long[4];     /* bytes 0 to 3 */
  uint8_t quantity[4];             /* bytes 4 to 7 */
  uint8_t side;                    /* byte 8 */
  uint8_t user_tag[8];             /* bytes 9 to 16 */
  uint8_t market_maker_code_1[4];  /* bytes 17 to 20 */
  uint8_t market_maker_code_2[4];  /* bytes 21 to 24 */
  uint8_t market_maker_code_3[4];  /* bytes 25 to 28 */
  uint8_t market_maker_code_4[4];  /* bytes 29 to 32 */
  uint8_t market_maker_code_5[4];  /* bytes 33 to 36 */
} QuoteRequestMessage;

/* any Quote Request Message at all: every byte one the checker chooses */
static void any_quote_request_message(QuoteRequestMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->security_id_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->user_tag[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_1[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_2[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_4[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_5[i] = arbitrary(); }
}

/* Quote Request Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_quote_request_message(const QuoteRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_tag[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_maker_code_1[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_maker_code_2[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_maker_code_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_maker_code_4[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_maker_code_5[i]; }

  return at;
}

/* Quote Request Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_quote_request_message(QuoteRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->security_id_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->user_tag[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_1[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_2[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_4[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_maker_code_5[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Request Message is what was written, byte for byte */
static void equal_quote_request_message(const QuoteRequestMessage *read, const QuoteRequestMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_long[i] == written->security_id_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->user_tag[i] == written->user_tag[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_maker_code_1[i] == written->market_maker_code_1[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_maker_code_2[i] == written->market_maker_code_2[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_maker_code_3[i] == written->market_maker_code_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_maker_code_4[i] == written->market_maker_code_4[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_maker_code_5[i] == written->market_maker_code_5[i]); }
}

/* Quote Request Message: written and read back, then read and written back */
static void check_quote_request_message(void) {
  QuoteRequestMessage sent;
  QuoteRequestMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_quote_request_message(&sent);
  assert(encode_quote_request_message(&sent, wire, 0) == 37);
  assert(decode_quote_request_message(&got, wire, 0) == 37);
  equal_quote_request_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_request_message(&got, wire, 0) == 37);
  assert(encode_quote_request_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Request Notification Message: 35 bytes ---------------------------- */

/* The Quote Request Notification is sent back to requestor to acknowledge the Quote Request. It is also sent to Market Maker to share the Quote Request. */
typedef struct {
  uint8_t rfq_session_id[8];     /* bytes 0 to 7 */
  uint8_t security_id_long[4];   /* bytes 8 to 11 */
  uint8_t quantity[4];           /* bytes 12 to 15 */
  uint8_t side;                  /* byte 16 */
  uint8_t quote_request_status;  /* byte 17 */
  uint8_t status_details;        /* byte 18 */
  uint8_t msg_ref[8];            /* bytes 19 to 26 */
  uint8_t user_tag[8];           /* bytes 27 to 34 */
} QuoteRequestNotificationMessage;

/* any Quote Request Notification Message at all: every byte one the checker chooses */
static void any_quote_request_notification_message(QuoteRequestNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->rfq_session_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->security_id_long[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  record->side = arbitrary();
  record->quote_request_status = arbitrary();
  record->status_details = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->msg_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_tag[i] = arbitrary(); }
}

/* Quote Request Notification Message to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_quote_request_notification_message(const QuoteRequestNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rfq_session_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_id_long[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->side;
  wire[at++] = record->quote_request_status;
  wire[at++] = record->status_details;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->msg_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_tag[i]; }

  return at;
}

/* Quote Request Notification Message off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_quote_request_notification_message(QuoteRequestNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->rfq_session_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->security_id_long[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  record->side = wire[at++];
  record->quote_request_status = wire[at++];
  record->status_details = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->msg_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_tag[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Request Notification Message is what was written, byte for byte */
static void equal_quote_request_notification_message(const QuoteRequestNotificationMessage *read, const QuoteRequestNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->rfq_session_id[i] == written->rfq_session_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->security_id_long[i] == written->security_id_long[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->side == written->side);
  assert(read->quote_request_status == written->quote_request_status);
  assert(read->status_details == written->status_details);
  for (size_t i = 0; i < 8; i++) { assert(read->msg_ref[i] == written->msg_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_tag[i] == written->user_tag[i]); }
}

/* Quote Request Notification Message: written and read back, then read and written back */
static void check_quote_request_notification_message(void) {
  QuoteRequestNotificationMessage sent;
  QuoteRequestNotificationMessage got;
  uint8_t wire[35];
  uint8_t again[35];

  any_quote_request_notification_message(&sent);
  assert(encode_quote_request_notification_message(&sent, wire, 0) == 35);
  assert(decode_quote_request_notification_message(&got, wire, 0) == 35);
  equal_quote_request_notification_message(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_request_notification_message(&got, wire, 0) == 35);
  assert(encode_quote_request_notification_message(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Add Message: 31 bytes --------------------------------------------- */

/* The Quote Add Message is used to disseminate quotes sent by Market Makers to the RFQ session requestor. */
typedef struct {
  uint8_t aqx_order_id[8];       /* bytes 0 to 7 */
  uint8_t security_id_short[2];  /* bytes 8 to 9 */
  uint8_t side;                  /* byte 10 */
  uint8_t quantity[4];           /* bytes 11 to 14 */
  uint8_t price[8];              /* bytes 15 to 22 */
  uint8_t rfq_session_id[8];     /* bytes 23 to 30 */
} QuoteAddMessage;

/* any Quote Add Message at all: every byte one the checker chooses */
static void any_quote_add_message(QuoteAddMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->aqx_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id_short[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->rfq_session_id[i] = arbitrary(); }
}

/* Quote Add Message to the wire: 31 bytes from at, returning where the next byte goes */
static size_t encode_quote_add_message(const QuoteAddMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aqx_order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id_short[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->rfq_session_id[i]; }

  return at;
}

/* Quote Add Message off the wire: 31 bytes from at, returning where the next byte lies */
static size_t decode_quote_add_message(QuoteAddMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->aqx_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id_short[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->rfq_session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Add Message is what was written, byte for byte */
static void equal_quote_add_message(const QuoteAddMessage *read, const QuoteAddMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->aqx_order_id[i] == written->aqx_order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id_short[i] == written->security_id_short[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->rfq_session_id[i] == written->rfq_session_id[i]); }
}

/* Quote Add Message: written and read back, then read and written back */
static void check_quote_add_message(void) {
  QuoteAddMessage sent;
  QuoteAddMessage got;
  uint8_t wire[31];
  uint8_t again[31];

  any_quote_add_message(&sent);
  assert(encode_quote_add_message(&sent, wire, 0) == 31);
  assert(decode_quote_add_message(&got, wire, 0) == 31);
  equal_quote_add_message(&got, &sent);

  for (size_t i = 0; i < 31; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_add_message(&got, wire, 0) == 31);
  assert(encode_quote_add_message(&got, again, 0) == 31);
  for (size_t i = 0; i < 31; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Modify Message: 22 bytes ------------------------------------------ */

/* Quote Modify Message is used to disseminate any quote modification submitted by the market makers to the RFQ session requestor. */
typedef struct {
  uint8_t aqx_order_id[8];       /* bytes 0 to 7 */
  uint8_t security_id_short[2];  /* bytes 8 to 9 */
  uint8_t quantity[4];           /* bytes 10 to 13 */
  uint8_t price[8];              /* bytes 14 to 21 */
} QuoteModifyMessage;

/* any Quote Modify Message at all: every byte one the checker chooses */
static void any_quote_modify_message(QuoteModifyMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->aqx_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id_short[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
}

/* Quote Modify Message to the wire: 22 bytes from at, returning where the next byte goes */
static size_t encode_quote_modify_message(const QuoteModifyMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aqx_order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id_short[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }

  return at;
}

/* Quote Modify Message off the wire: 22 bytes from at, returning where the next byte lies */
static size_t decode_quote_modify_message(QuoteModifyMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->aqx_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id_short[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Modify Message is what was written, byte for byte */
static void equal_quote_modify_message(const QuoteModifyMessage *read, const QuoteModifyMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->aqx_order_id[i] == written->aqx_order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id_short[i] == written->security_id_short[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
}

/* Quote Modify Message: written and read back, then read and written back */
static void check_quote_modify_message(void) {
  QuoteModifyMessage sent;
  QuoteModifyMessage got;
  uint8_t wire[22];
  uint8_t again[22];

  any_quote_modify_message(&sent);
  assert(encode_quote_modify_message(&sent, wire, 0) == 22);
  assert(decode_quote_modify_message(&got, wire, 0) == 22);
  equal_quote_modify_message(&got, &sent);

  for (size_t i = 0; i < 22; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_modify_message(&got, wire, 0) == 22);
  assert(encode_quote_modify_message(&got, again, 0) == 22);
  for (size_t i = 0; i < 22; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Cancel Message: 10 bytes ------------------------------------------ */

/* Quote Cancel Message is used to disseminate any quote cancelation messages submitted by the market makers to the RFQ session requestor. */
typedef struct {
  uint8_t aqx_order_id[8];       /* bytes 0 to 7 */
  uint8_t security_id_short[2];  /* bytes 8 to 9 */
} QuoteCancelMessage;

/* any Quote Cancel Message at all: every byte one the checker chooses */
static void any_quote_cancel_message(QuoteCancelMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->aqx_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->security_id_short[i] = arbitrary(); }
}

/* Quote Cancel Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_quote_cancel_message(const QuoteCancelMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->aqx_order_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->security_id_short[i]; }

  return at;
}

/* Quote Cancel Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_quote_cancel_message(QuoteCancelMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->aqx_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->security_id_short[i] = wire[at++]; }

  return at;
}

/* what was read of Quote Cancel Message is what was written, byte for byte */
static void equal_quote_cancel_message(const QuoteCancelMessage *read, const QuoteCancelMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->aqx_order_id[i] == written->aqx_order_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->security_id_short[i] == written->security_id_short[i]); }
}

/* Quote Cancel Message: written and read back, then read and written back */
static void check_quote_cancel_message(void) {
  QuoteCancelMessage sent;
  QuoteCancelMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_quote_cancel_message(&sent);
  assert(encode_quote_cancel_message(&sent, wire, 0) == 10);
  assert(decode_quote_cancel_message(&got, wire, 0) == 10);
  equal_quote_cancel_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_cancel_message(&got, wire, 0) == 10);
  assert(encode_quote_cancel_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust Message: 37 bytes -------------------------------------------- */

/* If a trade is invalidated, a Trade Bust message is sent to notify the trading Member. */
typedef struct {
  uint8_t order_ref[8];  /* bytes 0 to 7 */
  uint8_t quantity[4];   /* bytes 8 to 11 */
  uint8_t price[8];      /* bytes 12 to 19 */
  uint8_t side;          /* byte 20 */
  uint8_t trade_ref[8];  /* bytes 21 to 28 */
  uint8_t timestamp[8];  /* bytes 29 to 36 */
} TradeBustMessage;

/* any Trade Bust Message at all: every byte one the checker chooses */
static void any_trade_bust_message(TradeBustMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->order_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->trade_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = arbitrary(); }
}

/* Trade Bust Message to the wire: 37 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust_message(const TradeBustMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_ref[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->trade_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->timestamp[i]; }

  return at;
}

/* Trade Bust Message off the wire: 37 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust_message(TradeBustMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->order_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->trade_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Bust Message is what was written, byte for byte */
static void equal_trade_bust_message(const TradeBustMessage *read, const TradeBustMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 8; i++) { assert(read->trade_ref[i] == written->trade_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
}

/* Trade Bust Message: written and read back, then read and written back */
static void check_trade_bust_message(void) {
  TradeBustMessage sent;
  TradeBustMessage got;
  uint8_t wire[37];
  uint8_t again[37];

  any_trade_bust_message(&sent);
  assert(encode_trade_bust_message(&sent, wire, 0) == 37);
  assert(decode_trade_bust_message(&got, wire, 0) == 37);
  equal_trade_bust_message(&got, &sent);

  for (size_t i = 0; i < 37; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust_message(&got, wire, 0) == 37);
  assert(encode_trade_bust_message(&got, again, 0) == 37);
  for (size_t i = 0; i < 37; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_message();
  check_login_response_message();
  check_logout_message();
  check_quote_request_message();
  check_quote_request_notification_message();
  check_quote_add_message();
  check_quote_modify_message();
  check_quote_cancel_message();
  check_trade_bust_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
