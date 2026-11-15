// nyse/nysebonds/trades/NyseBonds_Trades_v1_07_a_Server.c
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
 *   - a run filling what frames it
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

/* ---- Message Header: 4 bytes ------------------------------------------------- */

/* Nyse Arca Binary Protocol message header */
typedef struct {
  uint8_t message_body_length[2];  /* bytes 0 to 1 */
  uint8_t message_type;            /* byte 2 */
  uint8_t padding;                 /* byte 3 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_body_length[i] = arbitrary(); }
  record->message_type = arbitrary();
  record->padding = arbitrary();
}

/* Message Header to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_body_length[i]; }
  wire[at++] = record->message_type;
  wire[at++] = record->padding;

  return at;
}

/* Message Header off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_body_length[i] = wire[at++]; }
  record->message_type = wire[at++];
  record->padding = wire[at++];

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_body_length[i] == written->message_body_length[i]); }
  assert(read->message_type == written->message_type);
  assert(read->padding == written->padding);
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[4];
  uint8_t again[4];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 4);
  assert(decode_message_header(&got, wire, 0) == 4);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 4);
  assert(encode_message_header(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Accepted Message: 6 bytes ----------------------------------------- */

/* Sent to indicate a successful login. Carries the current version of ArcaTrade. */
typedef struct {
  uint8_t version_id[5];    /* bytes 0 to 4 */
  uint8_t padding_ascii_1;  /* byte 5 */
} LoginAcceptedMessage;

/* any Login Accepted Message at all: every byte one the checker chooses */
static void any_login_accepted_message(LoginAcceptedMessage *record) {
  for (size_t i = 0; i < 5; i++) { record->version_id[i] = arbitrary(); }
  record->padding_ascii_1 = arbitrary();
}

/* Login Accepted Message to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_login_accepted_message(const LoginAcceptedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->version_id[i]; }
  wire[at++] = record->padding_ascii_1;

  return at;
}

/* Login Accepted Message off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_login_accepted_message(LoginAcceptedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->version_id[i] = wire[at++]; }
  record->padding_ascii_1 = wire[at++];

  return at;
}

/* what was read of Login Accepted Message is what was written, byte for byte */
static void equal_login_accepted_message(const LoginAcceptedMessage *read, const LoginAcceptedMessage *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->version_id[i] == written->version_id[i]); }
  assert(read->padding_ascii_1 == written->padding_ascii_1);
}

/* Login Accepted Message: written and read back, then read and written back */
static void check_login_accepted_message(void) {
  LoginAcceptedMessage sent;
  LoginAcceptedMessage got;
  uint8_t wire[6];
  uint8_t again[6];

  any_login_accepted_message(&sent);
  assert(encode_login_accepted_message(&sent, wire, 0) == 6);
  assert(decode_login_accepted_message(&got, wire, 0) == 6);
  equal_login_accepted_message(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_login_accepted_message(&got, wire, 0) == 6);
  assert(encode_login_accepted_message(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Rejected Message: 2 bytes ----------------------------------------- */

/* Sent when login fails authentication, the client does not log in within 30 seconds, no trade data feed was subscribed to, the sequence number was invalid, or no connections are available. The socket is closed afterwards. */
typedef struct {
  uint8_t reject_code;      /* byte 0 */
  uint8_t padding_ascii_1;  /* byte 1 */
} LoginRejectedMessage;

/* any Login Rejected Message at all: every byte one the checker chooses */
static void any_login_rejected_message(LoginRejectedMessage *record) {
  record->reject_code = arbitrary();
  record->padding_ascii_1 = arbitrary();
}

/* Login Rejected Message to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_login_rejected_message(const LoginRejectedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reject_code;
  wire[at++] = record->padding_ascii_1;

  return at;
}

/* Login Rejected Message off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_login_rejected_message(LoginRejectedMessage *record, const uint8_t *wire, size_t at) {
  record->reject_code = wire[at++];
  record->padding_ascii_1 = wire[at++];

  return at;
}

/* what was read of Login Rejected Message is what was written, byte for byte */
static void equal_login_rejected_message(const LoginRejectedMessage *read, const LoginRejectedMessage *written) {
  assert(read->reject_code == written->reject_code);
  assert(read->padding_ascii_1 == written->padding_ascii_1);
}

/* Login Rejected Message: written and read back, then read and written back */
static void check_login_rejected_message(void) {
  LoginRejectedMessage sent;
  LoginRejectedMessage got;
  uint8_t wire[2];
  uint8_t again[2];

  any_login_rejected_message(&sent);
  assert(encode_login_rejected_message(&sent, wire, 0) == 2);
  assert(decode_login_rejected_message(&got, wire, 0) == 2);
  equal_login_rejected_message(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_login_rejected_message(&got, wire, 0) == 2);
  assert(encode_login_rejected_message(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- Test Response Message: 20 bytes ----------------------------------------- */

/* Sent in response to a Test Request, echoing back any text the request carried. */
typedef struct {
  uint8_t test_message[20];  /* bytes 0 to 19 */
} TestResponseMessage;

/* any Test Response Message at all: every byte one the checker chooses */
static void any_test_response_message(TestResponseMessage *record) {
  for (size_t i = 0; i < 20; i++) { record->test_message[i] = arbitrary(); }
}

/* Test Response Message to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_test_response_message(const TestResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->test_message[i]; }

  return at;
}

/* Test Response Message off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_test_response_message(TestResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->test_message[i] = wire[at++]; }

  return at;
}

/* what was read of Test Response Message is what was written, byte for byte */
static void equal_test_response_message(const TestResponseMessage *read, const TestResponseMessage *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->test_message[i] == written->test_message[i]); }
}

/* Test Response Message: written and read back, then read and written back */
static void check_test_response_message(void) {
  TestResponseMessage sent;
  TestResponseMessage got;
  uint8_t wire[20];
  uint8_t again[20];

  any_test_response_message(&sent);
  assert(encode_test_response_message(&sent, wire, 0) == 20);
  assert(decode_test_response_message(&got, wire, 0) == 20);
  equal_test_response_message(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_test_response_message(&got, wire, 0) == 20);
  assert(encode_test_response_message(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Last Sale Message: 64 bytes --------------------------------------------- */

/* Sent when an order partially trades or completely trades. */
typedef struct {
  uint8_t last_sale_time[4];          /* bytes 0 to 3 */
  uint8_t sequence_number[4];         /* bytes 4 to 7 */
  uint8_t trade_reference_number[4];  /* bytes 8 to 11 */
  uint8_t quantity[4];                /* bytes 12 to 15 */
  uint8_t price[4];                   /* bytes 16 to 19 */
  uint8_t price_scale_code;           /* byte 20 */
  uint8_t system_code;                /* byte 21 */
  uint8_t exchange_code;              /* byte 22 */
  uint8_t trade_condition;            /* byte 23 */
  uint8_t security_type;              /* byte 24 */
  uint8_t nyse_bond_symbol[22];       /* bytes 25 to 46 */
  uint8_t cusip_isin[14];             /* bytes 47 to 60 */
  uint8_t padding_ascii_3[3];         /* bytes 61 to 63 */
} LastSaleMessage;

/* any Last Sale Message at all: every byte one the checker chooses */
static void any_last_sale_message(LastSaleMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_sale_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->system_code = arbitrary();
  record->exchange_code = arbitrary();
  record->trade_condition = arbitrary();
  record->security_type = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->padding_ascii_3[i] = arbitrary(); }
}

/* Last Sale Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_last_sale_message(const LastSaleMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_sale_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->system_code;
  wire[at++] = record->exchange_code;
  wire[at++] = record->trade_condition;
  wire[at++] = record->security_type;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->nyse_bond_symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip_isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->padding_ascii_3[i]; }

  return at;
}

/* Last Sale Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_last_sale_message(LastSaleMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_sale_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->system_code = wire[at++];
  record->exchange_code = wire[at++];
  record->trade_condition = wire[at++];
  record->security_type = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->padding_ascii_3[i] = wire[at++]; }

  return at;
}

/* what was read of Last Sale Message is what was written, byte for byte */
static void equal_last_sale_message(const LastSaleMessage *read, const LastSaleMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_sale_time[i] == written->last_sale_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_reference_number[i] == written->trade_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->system_code == written->system_code);
  assert(read->exchange_code == written->exchange_code);
  assert(read->trade_condition == written->trade_condition);
  assert(read->security_type == written->security_type);
  for (size_t i = 0; i < 22; i++) { assert(read->nyse_bond_symbol[i] == written->nyse_bond_symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip_isin[i] == written->cusip_isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->padding_ascii_3[i] == written->padding_ascii_3[i]); }
}

/* Last Sale Message: written and read back, then read and written back */
static void check_last_sale_message(void) {
  LastSaleMessage sent;
  LastSaleMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_last_sale_message(&sent);
  assert(encode_last_sale_message(&sent, wire, 0) == 64);
  assert(decode_last_sale_message(&got, wire, 0) == 64);
  equal_last_sale_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_last_sale_message(&got, wire, 0) == 64);
  assert(encode_last_sale_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Bust Or Correction Message: 64 bytes ------------------------------ */

/* Sent when trades are busted or corrected. The Event Code field says which. */
typedef struct {
  uint8_t last_sale_time[4];          /* bytes 0 to 3 */
  uint8_t sequence_number[4];         /* bytes 4 to 7 */
  uint8_t trade_reference_number[4];  /* bytes 8 to 11 */
  uint8_t quantity[4];                /* bytes 12 to 15 */
  uint8_t price[4];                   /* bytes 16 to 19 */
  uint8_t price_scale_code;           /* byte 20 */
  uint8_t system_code;                /* byte 21 */
  uint8_t event_code;                 /* byte 22 */
  uint8_t exchange_code;              /* byte 23 */
  uint8_t trade_condition;            /* byte 24 */
  uint8_t security_type;              /* byte 25 */
  uint8_t nyse_bond_symbol[22];       /* bytes 26 to 47 */
  uint8_t cusip_isin[14];             /* bytes 48 to 61 */
  uint8_t padding_ascii_2[2];         /* bytes 62 to 63 */
} TradeBustOrCorrectionMessage;

/* any Trade Bust Or Correction Message at all: every byte one the checker chooses */
static void any_trade_bust_or_correction_message(TradeBustOrCorrectionMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->last_sale_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->system_code = arbitrary();
  record->event_code = arbitrary();
  record->exchange_code = arbitrary();
  record->trade_condition = arbitrary();
  record->security_type = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->padding_ascii_2[i] = arbitrary(); }
}

/* Trade Bust Or Correction Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_trade_bust_or_correction_message(const TradeBustOrCorrectionMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_sale_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->system_code;
  wire[at++] = record->event_code;
  wire[at++] = record->exchange_code;
  wire[at++] = record->trade_condition;
  wire[at++] = record->security_type;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->nyse_bond_symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip_isin[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->padding_ascii_2[i]; }

  return at;
}

/* Trade Bust Or Correction Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_trade_bust_or_correction_message(TradeBustOrCorrectionMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->last_sale_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->system_code = wire[at++];
  record->event_code = wire[at++];
  record->exchange_code = wire[at++];
  record->trade_condition = wire[at++];
  record->security_type = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->padding_ascii_2[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Bust Or Correction Message is what was written, byte for byte */
static void equal_trade_bust_or_correction_message(const TradeBustOrCorrectionMessage *read, const TradeBustOrCorrectionMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->last_sale_time[i] == written->last_sale_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_reference_number[i] == written->trade_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->system_code == written->system_code);
  assert(read->event_code == written->event_code);
  assert(read->exchange_code == written->exchange_code);
  assert(read->trade_condition == written->trade_condition);
  assert(read->security_type == written->security_type);
  for (size_t i = 0; i < 22; i++) { assert(read->nyse_bond_symbol[i] == written->nyse_bond_symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip_isin[i] == written->cusip_isin[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->padding_ascii_2[i] == written->padding_ascii_2[i]); }
}

/* Trade Bust Or Correction Message: written and read back, then read and written back */
static void check_trade_bust_or_correction_message(void) {
  TradeBustOrCorrectionMessage sent;
  TradeBustOrCorrectionMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_trade_bust_or_correction_message(&sent);
  assert(encode_trade_bust_or_correction_message(&sent, wire, 0) == 64);
  assert(decode_trade_bust_or_correction_message(&got, wire, 0) == 64);
  equal_trade_bust_or_correction_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_bust_or_correction_message(&got, wire, 0) == 64);
  assert(encode_trade_bust_or_correction_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- Nyse Bond Closing Price Message: 64 bytes ------------------------------- */

/* Sent during day end processing with the final closing price and volume for a bond. The specification notes this message is not supported at the time of writing and will be implemented in a future release. */
typedef struct {
  uint8_t closing_time[4];            /* bytes 0 to 3 */
  uint8_t sequence_number[4];         /* bytes 4 to 7 */
  uint8_t trade_reference_number[4];  /* bytes 8 to 11 */
  uint8_t quantity[4];                /* bytes 12 to 15 */
  uint8_t closing_price[4];           /* bytes 16 to 19 */
  uint8_t price_scale_code;           /* byte 20 */
  uint8_t system_code;                /* byte 21 */
  uint8_t exchange_code;              /* byte 22 */
  uint8_t trade_condition;            /* byte 23 */
  uint8_t security_type;              /* byte 24 */
  uint8_t nyse_bond_symbol[22];       /* bytes 25 to 46 */
  uint8_t cusip_isin[14];             /* bytes 47 to 60 */
  uint8_t padding_ascii_3[3];         /* bytes 61 to 63 */
} NyseBondClosingPriceMessage;

/* any Nyse Bond Closing Price Message at all: every byte one the checker chooses */
static void any_nyse_bond_closing_price_message(NyseBondClosingPriceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->closing_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->trade_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->system_code = arbitrary();
  record->exchange_code = arbitrary();
  record->trade_condition = arbitrary();
  record->security_type = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->padding_ascii_3[i] = arbitrary(); }
}

/* Nyse Bond Closing Price Message to the wire: 64 bytes from at, returning where the next byte goes */
static size_t encode_nyse_bond_closing_price_message(const NyseBondClosingPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->trade_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->closing_price[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->system_code;
  wire[at++] = record->exchange_code;
  wire[at++] = record->trade_condition;
  wire[at++] = record->security_type;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->nyse_bond_symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip_isin[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->padding_ascii_3[i]; }

  return at;
}

/* Nyse Bond Closing Price Message off the wire: 64 bytes from at, returning where the next byte lies */
static size_t decode_nyse_bond_closing_price_message(NyseBondClosingPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->closing_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->trade_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->closing_price[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->system_code = wire[at++];
  record->exchange_code = wire[at++];
  record->trade_condition = wire[at++];
  record->security_type = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->padding_ascii_3[i] = wire[at++]; }

  return at;
}

/* what was read of Nyse Bond Closing Price Message is what was written, byte for byte */
static void equal_nyse_bond_closing_price_message(const NyseBondClosingPriceMessage *read, const NyseBondClosingPriceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->closing_time[i] == written->closing_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->trade_reference_number[i] == written->trade_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->closing_price[i] == written->closing_price[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->system_code == written->system_code);
  assert(read->exchange_code == written->exchange_code);
  assert(read->trade_condition == written->trade_condition);
  assert(read->security_type == written->security_type);
  for (size_t i = 0; i < 22; i++) { assert(read->nyse_bond_symbol[i] == written->nyse_bond_symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip_isin[i] == written->cusip_isin[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->padding_ascii_3[i] == written->padding_ascii_3[i]); }
}

/* Nyse Bond Closing Price Message: written and read back, then read and written back */
static void check_nyse_bond_closing_price_message(void) {
  NyseBondClosingPriceMessage sent;
  NyseBondClosingPriceMessage got;
  uint8_t wire[64];
  uint8_t again[64];

  any_nyse_bond_closing_price_message(&sent);
  assert(encode_nyse_bond_closing_price_message(&sent, wire, 0) == 64);
  assert(decode_nyse_bond_closing_price_message(&got, wire, 0) == 64);
  equal_nyse_bond_closing_price_message(&got, &sent);

  for (size_t i = 0; i < 64; i++) { wire[i] = arbitrary(); }
  assert(decode_nyse_bond_closing_price_message(&got, wire, 0) == 64);
  assert(encode_nyse_bond_closing_price_message(&got, again, 0) == 64);
  for (size_t i = 0; i < 64; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_accepted_message();
  check_login_rejected_message();
  check_test_response_message();
  check_last_sale_message();
  check_trade_bust_or_correction_message();
  check_nyse_bond_closing_price_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
