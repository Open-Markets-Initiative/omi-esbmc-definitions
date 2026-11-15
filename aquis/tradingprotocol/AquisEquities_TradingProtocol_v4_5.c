// aquis/tradingprotocol/AquisEquities_TradingProtocol_v4_5.c
/*
 * Aquis Exchange Aquis Trading Protocol
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

/* ---- Message Header: 7 bytes ------------------------------------------------- */

/* Aquis Atp message header */
typedef struct {
  uint8_t msg_length[2];  /* bytes 0 to 1 */
  uint8_t msg_type;       /* byte 2 */
  uint8_t msg_seq_no[4];  /* bytes 3 to 6 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  record->msg_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->msg_seq_no[i] = arbitrary(); }
}

/* Message Header to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  wire[at++] = record->msg_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_no[i]; }

  return at;
}

/* Message Header off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  record->msg_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->msg_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  assert(read->msg_type == written->msg_type);
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_no[i] == written->msg_seq_no[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[7];
  uint8_t again[7];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 7);
  assert(decode_message_header(&got, wire, 0) == 7);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 7);
  assert(encode_message_header(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Message: 40 bytes ------------------------------------------------- */

/* The Login message is sent by the trading Member as the initial message used to establish a trading session. It is also used to re-establish a session after a break. */
typedef struct {
  uint8_t protocol_version[2];    /* bytes 0 to 1 */
  uint8_t sender_id[16];          /* bytes 2 to 17 */
  uint8_t password[16];           /* bytes 18 to 33 */
  uint8_t inactivity_timeout[2];  /* bytes 34 to 35 */
  uint8_t atp_seq_no[4];          /* bytes 36 to 39 */
} LoginMessage;

/* any Login Message at all: every byte one the checker chooses */
static void any_login_message(LoginMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->protocol_version[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->sender_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->password[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->inactivity_timeout[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->atp_seq_no[i] = arbitrary(); }
}

/* Login Message to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_login_message(const LoginMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->protocol_version[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->sender_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->password[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->inactivity_timeout[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->atp_seq_no[i]; }

  return at;
}

/* Login Message off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_login_message(LoginMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->protocol_version[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->sender_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->password[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->inactivity_timeout[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->atp_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Login Message is what was written, byte for byte */
static void equal_login_message(const LoginMessage *read, const LoginMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->sender_id[i] == written->sender_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->password[i] == written->password[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->inactivity_timeout[i] == written->inactivity_timeout[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->atp_seq_no[i] == written->atp_seq_no[i]); }
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

/* ---- Login Response Message: 5 bytes ----------------------------------------- */

/* The Login Response message is sent by Aquis to acknowledge a Login request, and either accept or reject it. */
typedef struct {
  uint8_t result_code;       /* byte 0 */
  uint8_t client_seq_no[4];  /* bytes 1 to 4 */
} LoginResponseMessage;

/* any Login Response Message at all: every byte one the checker chooses */
static void any_login_response_message(LoginResponseMessage *record) {
  record->result_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->client_seq_no[i] = arbitrary(); }
}

/* Login Response Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_login_response_message(const LoginResponseMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->result_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->client_seq_no[i]; }

  return at;
}

/* Login Response Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_login_response_message(LoginResponseMessage *record, const uint8_t *wire, size_t at) {
  record->result_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->client_seq_no[i] = wire[at++]; }

  return at;
}

/* what was read of Login Response Message is what was written, byte for byte */
static void equal_login_response_message(const LoginResponseMessage *read, const LoginResponseMessage *written) {
  assert(read->result_code == written->result_code);
  for (size_t i = 0; i < 4; i++) { assert(read->client_seq_no[i] == written->client_seq_no[i]); }
}

/* Login Response Message: written and read back, then read and written back */
static void check_login_response_message(void) {
  LoginResponseMessage sent;
  LoginResponseMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_login_response_message(&sent);
  assert(encode_login_response_message(&sent, wire, 0) == 5);
  assert(decode_login_response_message(&got, wire, 0) == 5);
  equal_login_response_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response_message(&got, wire, 0) == 5);
  assert(encode_login_response_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Message: 33 bytes ------------------------------------------------ */

/* The Logout message is usually sent as a response to the Logout Request. However it may also be sent by Aquis in case of a low sequence number or other protocol violation, or for other reasons. The TCP/IP connection is closed immediately after this message has been sent. */
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

/* ---- Iceberg Order Refresh Message: 16 bytes --------------------------------- */

/* Aquis sends an Iceberg Order Refresh message to notify the Member when an iceberg order is refreshed from the non-displayed reserve quantity. */
typedef struct {
  uint8_t order_ref[4];        /* bytes 0 to 3 */
  uint8_t orig_aqx_ord_id[4];  /* bytes 4 to 7 */
  uint8_t new_aqx_ord_id[4];   /* bytes 8 to 11 */
  uint8_t quantity[4];         /* bytes 12 to 15 */
} IcebergOrderRefreshMessage;

/* any Iceberg Order Refresh Message at all: every byte one the checker chooses */
static void any_iceberg_order_refresh_message(IcebergOrderRefreshMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->orig_aqx_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->new_aqx_ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
}

/* Iceberg Order Refresh Message to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_iceberg_order_refresh_message(const IcebergOrderRefreshMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_ref[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->orig_aqx_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->new_aqx_ord_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }

  return at;
}

/* Iceberg Order Refresh Message off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_iceberg_order_refresh_message(IcebergOrderRefreshMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->orig_aqx_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->new_aqx_ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Iceberg Order Refresh Message is what was written, byte for byte */
static void equal_iceberg_order_refresh_message(const IcebergOrderRefreshMessage *read, const IcebergOrderRefreshMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->orig_aqx_ord_id[i] == written->orig_aqx_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->new_aqx_ord_id[i] == written->new_aqx_ord_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
}

/* Iceberg Order Refresh Message: written and read back, then read and written back */
static void check_iceberg_order_refresh_message(void) {
  IcebergOrderRefreshMessage sent;
  IcebergOrderRefreshMessage got;
  uint8_t wire[16];
  uint8_t again[16];

  any_iceberg_order_refresh_message(&sent);
  assert(encode_iceberg_order_refresh_message(&sent, wire, 0) == 16);
  assert(decode_iceberg_order_refresh_message(&got, wire, 0) == 16);
  equal_iceberg_order_refresh_message(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_iceberg_order_refresh_message(&got, wire, 0) == 16);
  assert(encode_iceberg_order_refresh_message(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust Message: 29 bytes -------------------------------------------- */

/* If a trade is invalidated, a Trade Bust message is sent to notify the trading Member. */
typedef struct {
  uint8_t order_ref[4];       /* bytes 0 to 3 */
  uint8_t quantity[4];        /* bytes 4 to 7 */
  uint8_t price[8];           /* bytes 8 to 15 */
  uint8_t side;               /* byte 16 */
  uint8_t trade_ref[4];       /* bytes 17 to 20 */
  uint8_t bust_timestamp[8];  /* bytes 21 to 28 */
} TradeBustMessage;

/* any Trade Bust Message at all: every byte one the checker chooses */
static void any_trade_bust_message(TradeBustMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->trade_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->bust_timestamp[i] = arbitrary(); }
}

/* Trade Bust Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust_message(const TradeBustMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_ref[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->bust_timestamp[i]; }

  return at;
}

/* Trade Bust Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust_message(TradeBustMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->trade_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->bust_timestamp[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Bust Message is what was written, byte for byte */
static void equal_trade_bust_message(const TradeBustMessage *read, const TradeBustMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 4; i++) { assert(read->trade_ref[i] == written->trade_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->bust_timestamp[i] == written->bust_timestamp[i]); }
}

/* Trade Bust Message: written and read back, then read and written back */
static void check_trade_bust_message(void) {
  TradeBustMessage sent;
  TradeBustMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_trade_bust_message(&sent);
  assert(encode_trade_bust_message(&sent, wire, 0) == 29);
  assert(decode_trade_bust_message(&got, wire, 0) == 29);
  equal_trade_bust_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust_message(&got, wire, 0) == 29);
  assert(encode_trade_bust_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ioi Invite Message: 36 bytes -------------------------------------------- */

/* Message from Aquis to the member indicating a firm up invite. The invite will expire 300ms after the value in the timestamp field. */
typedef struct {
  uint8_t order_ref[4];         /* bytes 0 to 3 */
  uint8_t price[8];             /* bytes 4 to 11 */
  uint8_t quantity[4];          /* bytes 12 to 15 */
  uint8_t min_qty[4];           /* bytes 16 to 19 */
  uint8_t invite_timestamp[8];  /* bytes 20 to 27 */
  uint8_t user_tag[8];          /* bytes 28 to 35 */
} IoiInviteMessage;

/* any Ioi Invite Message at all: every byte one the checker chooses */
static void any_ioi_invite_message(IoiInviteMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->invite_timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_tag[i] = arbitrary(); }
}

/* Ioi Invite Message to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_ioi_invite_message(const IoiInviteMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->invite_timestamp[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_tag[i]; }

  return at;
}

/* Ioi Invite Message off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_ioi_invite_message(IoiInviteMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->invite_timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_tag[i] = wire[at++]; }

  return at;
}

/* what was read of Ioi Invite Message is what was written, byte for byte */
static void equal_ioi_invite_message(const IoiInviteMessage *read, const IoiInviteMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->invite_timestamp[i] == written->invite_timestamp[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_tag[i] == written->user_tag[i]); }
}

/* Ioi Invite Message: written and read back, then read and written back */
static void check_ioi_invite_message(void) {
  IoiInviteMessage sent;
  IoiInviteMessage got;
  uint8_t wire[36];
  uint8_t again[36];

  any_ioi_invite_message(&sent);
  assert(encode_ioi_invite_message(&sent, wire, 0) == 36);
  assert(decode_ioi_invite_message(&got, wire, 0) == 36);
  equal_ioi_invite_message(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_ioi_invite_message(&got, wire, 0) == 36);
  assert(encode_ioi_invite_message(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ioi Firmup Message: 29 bytes -------------------------------------------- */

/* Firm up message to be used as a response to an invite. */
typedef struct {
  uint8_t order_ref[4];   /* bytes 0 to 3 */
  uint8_t price[8];       /* bytes 4 to 11 */
  uint8_t quantity[4];    /* bytes 12 to 15 */
  uint8_t min_qty[4];     /* bytes 16 to 19 */
  uint8_t user_tag[8];    /* bytes 20 to 27 */
  uint8_t time_in_force;  /* byte 28 */
} IoiFirmupMessage;

/* any Ioi Firmup Message at all: every byte one the checker chooses */
static void any_ioi_firmup_message(IoiFirmupMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_tag[i] = arbitrary(); }
  record->time_in_force = arbitrary();
}

/* Ioi Firmup Message to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_ioi_firmup_message(const IoiFirmupMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_ref[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->min_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_tag[i]; }
  wire[at++] = record->time_in_force;

  return at;
}

/* Ioi Firmup Message off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_ioi_firmup_message(IoiFirmupMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->order_ref[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->min_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_tag[i] = wire[at++]; }
  record->time_in_force = wire[at++];

  return at;
}

/* what was read of Ioi Firmup Message is what was written, byte for byte */
static void equal_ioi_firmup_message(const IoiFirmupMessage *read, const IoiFirmupMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->order_ref[i] == written->order_ref[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->min_qty[i] == written->min_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_tag[i] == written->user_tag[i]); }
  assert(read->time_in_force == written->time_in_force);
}

/* Ioi Firmup Message: written and read back, then read and written back */
static void check_ioi_firmup_message(void) {
  IoiFirmupMessage sent;
  IoiFirmupMessage got;
  uint8_t wire[29];
  uint8_t again[29];

  any_ioi_firmup_message(&sent);
  assert(encode_ioi_firmup_message(&sent, wire, 0) == 29);
  assert(decode_ioi_firmup_message(&got, wire, 0) == 29);
  equal_ioi_firmup_message(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_ioi_firmup_message(&got, wire, 0) == 29);
  assert(encode_ioi_firmup_message(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_message();
  check_login_response_message();
  check_logout_message();
  check_iceberg_order_refresh_message();
  check_trade_bust_message();
  check_ioi_invite_message();
  check_ioi_firmup_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
