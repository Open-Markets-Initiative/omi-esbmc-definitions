// nyse/nysebonds/depthofbook/NyseBonds_DepthOfBook_v4_01_b_Server.c
/*
 * New York Stock Exchange DepthOfBook
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

/* Sent to indicate a successful login. Carries the current version of the Nyse ArcaBook protocol. */
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

/* Sent when login fails authentication, the client does not log in within 5 seconds, no order data feed was subscribed to, the sequence number was invalid, no connections are available, or a timeout occurred. The socket is closed afterwards. */
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

/* ---- Add Order Message: 76 bytes --------------------------------------------- */

/* Sent for a new open order. The Order Reference Number is unique per order book, while the Sequence Number is unique across all order books. */
typedef struct {
  uint8_t time[4];                    /* bytes 0 to 3 */
  uint8_t sequence_number[4];         /* bytes 4 to 7 */
  uint8_t order_reference_number[4];  /* bytes 8 to 11 */
  uint8_t quantity[4];                /* bytes 12 to 15 */
  uint8_t price[4];                   /* bytes 16 to 19 */
  uint8_t price_scale_code;           /* byte 20 */
  uint8_t exchange_code;              /* byte 21 */
  uint8_t system_code;                /* byte 22 */
  uint8_t buy_sell_indicator;         /* byte 23 */
  uint8_t flat_pricing;               /* byte 24 */
  uint8_t trading_action;             /* byte 25 */
  uint8_t security_type;              /* byte 26 */
  uint8_t order_type;                 /* byte 27 */
  uint8_t nyse_bond_symbol[22];       /* bytes 28 to 49 */
  uint8_t cusip_isin[14];             /* bytes 50 to 63 */
  uint8_t quote_id[5];                /* bytes 64 to 68 */
  uint8_t padding_ascii_3[3];         /* bytes 69 to 71 */
  uint8_t minimum_quantity[4];        /* bytes 72 to 75 */
} AddOrderMessage;

/* any Add Order Message at all: every byte one the checker chooses */
static void any_add_order_message(AddOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->exchange_code = arbitrary();
  record->system_code = arbitrary();
  record->buy_sell_indicator = arbitrary();
  record->flat_pricing = arbitrary();
  record->trading_action = arbitrary();
  record->security_type = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->quote_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->padding_ascii_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Add Order Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_add_order_message(const AddOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->exchange_code;
  wire[at++] = record->system_code;
  wire[at++] = record->buy_sell_indicator;
  wire[at++] = record->flat_pricing;
  wire[at++] = record->trading_action;
  wire[at++] = record->security_type;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->nyse_bond_symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip_isin[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->quote_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->padding_ascii_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Add Order Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_add_order_message(AddOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->exchange_code = wire[at++];
  record->system_code = wire[at++];
  record->buy_sell_indicator = wire[at++];
  record->flat_pricing = wire[at++];
  record->trading_action = wire[at++];
  record->security_type = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->quote_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->padding_ascii_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Add Order Message is what was written, byte for byte */
static void equal_add_order_message(const AddOrderMessage *read, const AddOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->exchange_code == written->exchange_code);
  assert(read->system_code == written->system_code);
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  assert(read->flat_pricing == written->flat_pricing);
  assert(read->trading_action == written->trading_action);
  assert(read->security_type == written->security_type);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 22; i++) { assert(read->nyse_bond_symbol[i] == written->nyse_bond_symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip_isin[i] == written->cusip_isin[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->quote_id[i] == written->quote_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->padding_ascii_3[i] == written->padding_ascii_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Add Order Message: written and read back, then read and written back */
static void check_add_order_message(void) {
  AddOrderMessage sent;
  AddOrderMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_add_order_message(&sent);
  assert(encode_add_order_message(&sent, wire, 0) == 76);
  assert(decode_add_order_message(&got, wire, 0) == 76);
  equal_add_order_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_add_order_message(&got, wire, 0) == 76);
  assert(encode_add_order_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Message: 76 bytes ------------------------------------------ */

/* Sent when an order in a Nyse Bonds book is modified: its price or size changes, it is partially filled, or it is routed away with shares remaining. The Order Reference Number refers to the original Add Order. */
typedef struct {
  uint8_t time[4];                    /* bytes 0 to 3 */
  uint8_t sequence_number[4];         /* bytes 4 to 7 */
  uint8_t order_reference_number[4];  /* bytes 8 to 11 */
  uint8_t quantity[4];                /* bytes 12 to 15 */
  uint8_t price[4];                   /* bytes 16 to 19 */
  uint8_t price_scale_code;           /* byte 20 */
  uint8_t exchange_code;              /* byte 21 */
  uint8_t system_code;                /* byte 22 */
  uint8_t buy_sell_indicator;         /* byte 23 */
  uint8_t flat_pricing;               /* byte 24 */
  uint8_t trading_action;             /* byte 25 */
  uint8_t security_type;              /* byte 26 */
  uint8_t order_type;                 /* byte 27 */
  uint8_t nyse_bond_symbol[22];       /* bytes 28 to 49 */
  uint8_t cusip_isin[14];             /* bytes 50 to 63 */
  uint8_t quote_id[5];                /* bytes 64 to 68 */
  uint8_t padding_ascii_3[3];         /* bytes 69 to 71 */
  uint8_t minimum_quantity[4];        /* bytes 72 to 75 */
} ModifyOrderMessage;

/* any Modify Order Message at all: every byte one the checker chooses */
static void any_modify_order_message(ModifyOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->exchange_code = arbitrary();
  record->system_code = arbitrary();
  record->buy_sell_indicator = arbitrary();
  record->flat_pricing = arbitrary();
  record->trading_action = arbitrary();
  record->security_type = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->quote_id[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->padding_ascii_3[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = arbitrary(); }
}

/* Modify Order Message to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_message(const ModifyOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->exchange_code;
  wire[at++] = record->system_code;
  wire[at++] = record->buy_sell_indicator;
  wire[at++] = record->flat_pricing;
  wire[at++] = record->trading_action;
  wire[at++] = record->security_type;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->nyse_bond_symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip_isin[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->quote_id[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->padding_ascii_3[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->minimum_quantity[i]; }

  return at;
}

/* Modify Order Message off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_message(ModifyOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->exchange_code = wire[at++];
  record->system_code = wire[at++];
  record->buy_sell_indicator = wire[at++];
  record->flat_pricing = wire[at++];
  record->trading_action = wire[at++];
  record->security_type = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->quote_id[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->padding_ascii_3[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->minimum_quantity[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Message is what was written, byte for byte */
static void equal_modify_order_message(const ModifyOrderMessage *read, const ModifyOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->quantity[i] == written->quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->exchange_code == written->exchange_code);
  assert(read->system_code == written->system_code);
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  assert(read->flat_pricing == written->flat_pricing);
  assert(read->trading_action == written->trading_action);
  assert(read->security_type == written->security_type);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 22; i++) { assert(read->nyse_bond_symbol[i] == written->nyse_bond_symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip_isin[i] == written->cusip_isin[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->quote_id[i] == written->quote_id[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->padding_ascii_3[i] == written->padding_ascii_3[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->minimum_quantity[i] == written->minimum_quantity[i]); }
}

/* Modify Order Message: written and read back, then read and written back */
static void check_modify_order_message(void) {
  ModifyOrderMessage sent;
  ModifyOrderMessage got;
  uint8_t wire[76];
  uint8_t again[76];

  any_modify_order_message(&sent);
  assert(encode_modify_order_message(&sent, wire, 0) == 76);
  assert(decode_modify_order_message(&got, wire, 0) == 76);
  equal_modify_order_message(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_message(&got, wire, 0) == 76);
  assert(encode_modify_order_message(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Order Message: 60 bytes ------------------------------------------ */

/* Sent when an order is taken off the open order book because it was cancelled, expired, routed to an away market, or filled. */
typedef struct {
  uint8_t time[4];                    /* bytes 0 to 3 */
  uint8_t sequence_number[4];         /* bytes 4 to 7 */
  uint8_t order_reference_number[4];  /* bytes 8 to 11 */
  uint8_t exchange_code;              /* byte 12 */
  uint8_t system_code;                /* byte 13 */
  uint8_t buy_sell_indicator;         /* byte 14 */
  uint8_t flat_pricing;               /* byte 15 */
  uint8_t trading_action;             /* byte 16 */
  uint8_t security_type;              /* byte 17 */
  uint8_t order_type;                 /* byte 18 */
  uint8_t nyse_bond_symbol[22];       /* bytes 19 to 40 */
  uint8_t cusip_isin[14];             /* bytes 41 to 54 */
  uint8_t quote_id[5];                /* bytes 55 to 59 */
} DeleteOrderMessage;

/* any Delete Order Message at all: every byte one the checker chooses */
static void any_delete_order_message(DeleteOrderMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = arbitrary(); }
  record->exchange_code = arbitrary();
  record->system_code = arbitrary();
  record->buy_sell_indicator = arbitrary();
  record->flat_pricing = arbitrary();
  record->trading_action = arbitrary();
  record->security_type = arbitrary();
  record->order_type = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->quote_id[i] = arbitrary(); }
}

/* Delete Order Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_delete_order_message(const DeleteOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->order_reference_number[i]; }
  wire[at++] = record->exchange_code;
  wire[at++] = record->system_code;
  wire[at++] = record->buy_sell_indicator;
  wire[at++] = record->flat_pricing;
  wire[at++] = record->trading_action;
  wire[at++] = record->security_type;
  wire[at++] = record->order_type;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->nyse_bond_symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip_isin[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->quote_id[i]; }

  return at;
}

/* Delete Order Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_delete_order_message(DeleteOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->order_reference_number[i] = wire[at++]; }
  record->exchange_code = wire[at++];
  record->system_code = wire[at++];
  record->buy_sell_indicator = wire[at++];
  record->flat_pricing = wire[at++];
  record->trading_action = wire[at++];
  record->security_type = wire[at++];
  record->order_type = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->quote_id[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Order Message is what was written, byte for byte */
static void equal_delete_order_message(const DeleteOrderMessage *read, const DeleteOrderMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->order_reference_number[i] == written->order_reference_number[i]); }
  assert(read->exchange_code == written->exchange_code);
  assert(read->system_code == written->system_code);
  assert(read->buy_sell_indicator == written->buy_sell_indicator);
  assert(read->flat_pricing == written->flat_pricing);
  assert(read->trading_action == written->trading_action);
  assert(read->security_type == written->security_type);
  assert(read->order_type == written->order_type);
  for (size_t i = 0; i < 22; i++) { assert(read->nyse_bond_symbol[i] == written->nyse_bond_symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip_isin[i] == written->cusip_isin[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->quote_id[i] == written->quote_id[i]); }
}

/* Delete Order Message: written and read back, then read and written back */
static void check_delete_order_message(void) {
  DeleteOrderMessage sent;
  DeleteOrderMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_delete_order_message(&sent);
  assert(encode_delete_order_message(&sent, wire, 0) == 60);
  assert(decode_delete_order_message(&got, wire, 0) == 60);
  equal_delete_order_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_order_message(&got, wire, 0) == 60);
  assert(encode_delete_order_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Imbalance Message: 72 bytes --------------------------------------------- */

/* Sent in response to orders submitted during pending auctions, at the conclusion of the Opening, Market Order and Closing Auctions, and for Halt Auctions. Total and market imbalance volumes are negative for a sell imbalance. */
typedef struct {
  uint8_t time[4];               /* bytes 0 to 3 */
  uint8_t sequence_number[4];    /* bytes 4 to 7 */
  uint8_t match_quantity[4];     /* bytes 8 to 11 */
  uint8_t total_imbalance[4];    /* bytes 12 to 15 */
  uint8_t market_imbalance[4];   /* bytes 16 to 19 */
  uint8_t price[4];              /* bytes 20 to 23 */
  uint8_t price_scale_code;      /* byte 24 */
  uint8_t exchange_code;         /* byte 25 */
  uint8_t system_code;           /* byte 26 */
  uint8_t auction_type;          /* byte 27 */
  uint8_t flat_pricing;          /* byte 28 */
  uint8_t trading_action;        /* byte 29 */
  uint8_t security_type;         /* byte 30 */
  uint8_t quote_condition;       /* byte 31 */
  uint8_t nyse_bond_symbol[22];  /* bytes 32 to 53 */
  uint8_t cusip_isin[14];        /* bytes 54 to 67 */
  uint8_t auction_time[4];       /* bytes 68 to 71 */
} ImbalanceMessage;

/* any Imbalance Message at all: every byte one the checker chooses */
static void any_imbalance_message(ImbalanceMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->match_quantity[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->price[i] = arbitrary(); }
  record->price_scale_code = arbitrary();
  record->exchange_code = arbitrary();
  record->system_code = arbitrary();
  record->auction_type = arbitrary();
  record->flat_pricing = arbitrary();
  record->trading_action = arbitrary();
  record->security_type = arbitrary();
  record->quote_condition = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->auction_time[i] = arbitrary(); }
}

/* Imbalance Message to the wire: 72 bytes from at, returning where the next byte goes */
static size_t encode_imbalance_message(const ImbalanceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->match_quantity[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->total_imbalance[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->market_imbalance[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->price_scale_code;
  wire[at++] = record->exchange_code;
  wire[at++] = record->system_code;
  wire[at++] = record->auction_type;
  wire[at++] = record->flat_pricing;
  wire[at++] = record->trading_action;
  wire[at++] = record->security_type;
  wire[at++] = record->quote_condition;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->nyse_bond_symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip_isin[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->auction_time[i]; }

  return at;
}

/* Imbalance Message off the wire: 72 bytes from at, returning where the next byte lies */
static size_t decode_imbalance_message(ImbalanceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->match_quantity[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->total_imbalance[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->market_imbalance[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->price[i] = wire[at++]; }
  record->price_scale_code = wire[at++];
  record->exchange_code = wire[at++];
  record->system_code = wire[at++];
  record->auction_type = wire[at++];
  record->flat_pricing = wire[at++];
  record->trading_action = wire[at++];
  record->security_type = wire[at++];
  record->quote_condition = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->auction_time[i] = wire[at++]; }

  return at;
}

/* what was read of Imbalance Message is what was written, byte for byte */
static void equal_imbalance_message(const ImbalanceMessage *read, const ImbalanceMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->match_quantity[i] == written->match_quantity[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->total_imbalance[i] == written->total_imbalance[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->market_imbalance[i] == written->market_imbalance[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->price_scale_code == written->price_scale_code);
  assert(read->exchange_code == written->exchange_code);
  assert(read->system_code == written->system_code);
  assert(read->auction_type == written->auction_type);
  assert(read->flat_pricing == written->flat_pricing);
  assert(read->trading_action == written->trading_action);
  assert(read->security_type == written->security_type);
  assert(read->quote_condition == written->quote_condition);
  for (size_t i = 0; i < 22; i++) { assert(read->nyse_bond_symbol[i] == written->nyse_bond_symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip_isin[i] == written->cusip_isin[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->auction_time[i] == written->auction_time[i]); }
}

/* Imbalance Message: written and read back, then read and written back */
static void check_imbalance_message(void) {
  ImbalanceMessage sent;
  ImbalanceMessage got;
  uint8_t wire[72];
  uint8_t again[72];

  any_imbalance_message(&sent);
  assert(encode_imbalance_message(&sent, wire, 0) == 72);
  assert(decode_imbalance_message(&got, wire, 0) == 72);
  equal_imbalance_message(&got, &sent);

  for (size_t i = 0; i < 72; i++) { wire[i] = arbitrary(); }
  assert(decode_imbalance_message(&got, wire, 0) == 72);
  assert(encode_imbalance_message(&got, again, 0) == 72);
  for (size_t i = 0; i < 72; i++) { assert(again[i] == wire[i]); }
}

/* ---- System Event Message: 52 bytes ------------------------------------------ */

/* Sent to indicate a special system event to an order book. The Event Code says what happened and the System Code which book is affected. Also carries the next sequence number subscribers should expect, which is generally the current one plus one but may restart at 1. */
typedef struct {
  uint8_t time[4];                           /* bytes 0 to 3 */
  uint8_t sequence_number[4];                /* bytes 4 to 7 */
  uint8_t next_expected_sequence_number[4];  /* bytes 8 to 11 */
  uint8_t event_code;                        /* byte 12 */
  uint8_t system_code;                       /* byte 13 */
  uint8_t nyse_bond_symbol[22];              /* bytes 14 to 35 */
  uint8_t cusip_isin[14];                    /* bytes 36 to 49 */
  uint8_t padding_ascii_2[2];                /* bytes 50 to 51 */
} SystemEventMessage;

/* any System Event Message at all: every byte one the checker chooses */
static void any_system_event_message(SystemEventMessage *record) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->next_expected_sequence_number[i] = arbitrary(); }
  record->event_code = arbitrary();
  record->system_code = arbitrary();
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->padding_ascii_2[i] = arbitrary(); }
}

/* System Event Message to the wire: 52 bytes from at, returning where the next byte goes */
static size_t encode_system_event_message(const SystemEventMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->next_expected_sequence_number[i]; }
  wire[at++] = record->event_code;
  wire[at++] = record->system_code;
  for (size_t i = 0; i < 22; i++) { wire[at++] = record->nyse_bond_symbol[i]; }
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->cusip_isin[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->padding_ascii_2[i]; }

  return at;
}

/* System Event Message off the wire: 52 bytes from at, returning where the next byte lies */
static size_t decode_system_event_message(SystemEventMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->next_expected_sequence_number[i] = wire[at++]; }
  record->event_code = wire[at++];
  record->system_code = wire[at++];
  for (size_t i = 0; i < 22; i++) { record->nyse_bond_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 14; i++) { record->cusip_isin[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->padding_ascii_2[i] = wire[at++]; }

  return at;
}

/* what was read of System Event Message is what was written, byte for byte */
static void equal_system_event_message(const SystemEventMessage *read, const SystemEventMessage *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->next_expected_sequence_number[i] == written->next_expected_sequence_number[i]); }
  assert(read->event_code == written->event_code);
  assert(read->system_code == written->system_code);
  for (size_t i = 0; i < 22; i++) { assert(read->nyse_bond_symbol[i] == written->nyse_bond_symbol[i]); }
  for (size_t i = 0; i < 14; i++) { assert(read->cusip_isin[i] == written->cusip_isin[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->padding_ascii_2[i] == written->padding_ascii_2[i]); }
}

/* System Event Message: written and read back, then read and written back */
static void check_system_event_message(void) {
  SystemEventMessage sent;
  SystemEventMessage got;
  uint8_t wire[52];
  uint8_t again[52];

  any_system_event_message(&sent);
  assert(encode_system_event_message(&sent, wire, 0) == 52);
  assert(decode_system_event_message(&got, wire, 0) == 52);
  equal_system_event_message(&got, &sent);

  for (size_t i = 0; i < 52; i++) { wire[i] = arbitrary(); }
  assert(decode_system_event_message(&got, wire, 0) == 52);
  assert(encode_system_event_message(&got, again, 0) == 52);
  for (size_t i = 0; i < 52; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_login_accepted_message();
  check_login_rejected_message();
  check_test_response_message();
  check_add_order_message();
  check_modify_order_message();
  check_delete_order_message();
  check_imbalance_message();
  check_system_event_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
