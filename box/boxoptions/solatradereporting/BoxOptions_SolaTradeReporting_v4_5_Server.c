// box/boxoptions/solatradereporting/BoxOptions_SolaTradeReporting_v4_5_Server.c
/*
 * Box Options Market Sola Trade Reporting
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

/* ---- Message Header: 28 bytes ------------------------------------------------ */

/* Atr message header, twenty eight bytes opening every message either way */
typedef struct {
  uint8_t source[4];                           /* bytes 0 to 3 */
  uint8_t destination[4];                      /* bytes 4 to 7 */
  uint8_t message_type[2];                     /* bytes 8 to 9 */
  uint8_t message_flag;                        /* byte 10 */
  uint8_t control_byte;                        /* byte 11 */
  uint8_t sequence_number[8];                  /* bytes 12 to 19 */
  uint8_t acknowledgement_sequence_number[8];  /* bytes 20 to 27 */
} MessageHeader;

/* any Message Header at all: every byte one the checker chooses */
static void any_message_header(MessageHeader *record) {
  for (size_t i = 0; i < 4; i++) { record->source[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->destination[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = arbitrary(); }
  record->message_flag = arbitrary();
  record->control_byte = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->acknowledgement_sequence_number[i] = arbitrary(); }
}

/* Message Header to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_message_header(const MessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->source[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->destination[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_type[i]; }
  wire[at++] = record->message_flag;
  wire[at++] = record->control_byte;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->acknowledgement_sequence_number[i]; }

  return at;
}

/* Message Header off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_message_header(MessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->source[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->destination[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->message_type[i] = wire[at++]; }
  record->message_flag = wire[at++];
  record->control_byte = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->acknowledgement_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Message Header is what was written, byte for byte */
static void equal_message_header(const MessageHeader *read, const MessageHeader *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->source[i] == written->source[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->destination[i] == written->destination[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->message_type[i] == written->message_type[i]); }
  assert(read->message_flag == written->message_flag);
  assert(read->control_byte == written->control_byte);
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->acknowledgement_sequence_number[i] == written->acknowledgement_sequence_number[i]); }
}

/* Message Header: written and read back, then read and written back */
static void check_message_header(void) {
  MessageHeader sent;
  MessageHeader got;
  uint8_t wire[28];
  uint8_t again[28];

  any_message_header(&sent);
  assert(encode_message_header(&sent, wire, 0) == 28);
  assert(decode_message_header(&got, wire, 0) == 28);
  equal_message_header(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_message_header(&got, wire, 0) == 28);
  assert(encode_message_header(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- Client Signon Acknowledgment: 8 bytes ----------------------------------- */

typedef struct {
  uint8_t last_user_sequence_number[8];  /* bytes 0 to 7 */
} ClientSignonAcknowledgment;

/* any Client Signon Acknowledgment at all: every byte one the checker chooses */
static void any_client_signon_acknowledgment(ClientSignonAcknowledgment *record) {
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_number[i] = arbitrary(); }
}

/* Client Signon Acknowledgment to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_client_signon_acknowledgment(const ClientSignonAcknowledgment *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_user_sequence_number[i]; }

  return at;
}

/* Client Signon Acknowledgment off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_client_signon_acknowledgment(ClientSignonAcknowledgment *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->last_user_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Client Signon Acknowledgment is what was written, byte for byte */
static void equal_client_signon_acknowledgment(const ClientSignonAcknowledgment *read, const ClientSignonAcknowledgment *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->last_user_sequence_number[i] == written->last_user_sequence_number[i]); }
}

/* Client Signon Acknowledgment: written and read back, then read and written back */
static void check_client_signon_acknowledgment(void) {
  ClientSignonAcknowledgment sent;
  ClientSignonAcknowledgment got;
  uint8_t wire[8];
  uint8_t again[8];

  any_client_signon_acknowledgment(&sent);
  assert(encode_client_signon_acknowledgment(&sent, wire, 0) == 8);
  assert(decode_client_signon_acknowledgment(&got, wire, 0) == 8);
  equal_client_signon_acknowledgment(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_client_signon_acknowledgment(&got, wire, 0) == 8);
  assert(encode_client_signon_acknowledgment(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade: 200 bytes -------------------------------------------------------- */

/* The guide heads this message 212 bytes, while the fields it states measure 228 including the 28 byte header. */
typedef struct {
  uint8_t trade_number[15];                 /* bytes 0 to 14 */
  uint8_t transaction_type;                 /* byte 15 */
  uint8_t timestamp[6];                     /* bytes 16 to 21 */
  uint8_t symbol[30];                       /* bytes 22 to 51 */
  uint8_t expiration_date[6];               /* bytes 52 to 57 */
  uint8_t strike_price[8];                  /* bytes 58 to 65 */
  uint8_t strike_price_fraction_indicator;  /* byte 66 */
  uint8_t option_type;                      /* byte 67 */
  uint8_t volume[8];                        /* bytes 68 to 75 */
  uint8_t price[8];                         /* bytes 76 to 83 */
  uint8_t cmta_broker[4];                   /* bytes 84 to 87 */
  uint8_t account_type;                     /* byte 88 */
  uint8_t sub_trader_id[3];                 /* bytes 89 to 91 */
  uint8_t open_close;                       /* byte 92 */
  uint8_t executing_broker[4];              /* bytes 93 to 96 */
  uint8_t client_account_number[12];        /* bytes 97 to 108 */
  uint8_t client_order_id[20];              /* bytes 109 to 128 */
  uint8_t client_memo[16];                  /* bytes 129 to 144 */
  uint8_t liquidity_status;                 /* byte 145 */
  uint8_t trade_type;                       /* byte 146 */
  uint8_t opposite_account_type;            /* byte 147 */
  uint8_t participant_session_name[12];     /* bytes 148 to 159 */
  uint8_t unique_transaction_id[10];        /* bytes 160 to 169 */
  uint8_t parent_transaction_id[10];        /* bytes 170 to 179 */
  uint8_t opposite_executing_broker[4];     /* bytes 180 to 183 */
  uint8_t additional_client_memo[16];       /* bytes 184 to 199 */
} Trade;

/* any Trade at all: every byte one the checker chooses */
static void any_trade(Trade *record) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = arbitrary(); }
  record->transaction_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  record->trade_type = arbitrary();
  record->opposite_account_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Trade to the wire: 200 bytes from at, returning where the next byte goes */
static size_t encode_trade(const Trade *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->transaction_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_broker[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  wire[at++] = record->liquidity_status;
  wire[at++] = record->trade_type;
  wire[at++] = record->opposite_account_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_session_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->unique_transaction_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->parent_transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opposite_executing_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Trade off the wire: 200 bytes from at, returning where the next byte lies */
static size_t decode_trade(Trade *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = wire[at++]; }
  record->transaction_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  record->trade_type = wire[at++];
  record->opposite_account_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Trade is what was written, byte for byte */
static void equal_trade(const Trade *read, const Trade *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->transaction_type == written->transaction_type);
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->executing_broker[i] == written->executing_broker[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  assert(read->trade_type == written->trade_type);
  assert(read->opposite_account_type == written->opposite_account_type);
  for (size_t i = 0; i < 12; i++) { assert(read->participant_session_name[i] == written->participant_session_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->unique_transaction_id[i] == written->unique_transaction_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->parent_transaction_id[i] == written->parent_transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opposite_executing_broker[i] == written->opposite_executing_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Trade: written and read back, then read and written back */
static void check_trade(void) {
  Trade sent;
  Trade got;
  uint8_t wire[200];
  uint8_t again[200];

  any_trade(&sent);
  assert(encode_trade(&sent, wire, 0) == 200);
  assert(decode_trade(&got, wire, 0) == 200);
  equal_trade(&got, &sent);

  for (size_t i = 0; i < 200; i++) { wire[i] = arbitrary(); }
  assert(decode_trade(&got, wire, 0) == 200);
  assert(encode_trade(&got, again, 0) == 200);
  for (size_t i = 0; i < 200; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Cancel: 200 bytes ------------------------------------------------- */

/* The guide states this message as having the same structure as message type 30, whose fields are written out here. The guide heads this message 212 bytes, while the fields it states measure 228 including the 28 byte header. */
typedef struct {
  uint8_t trade_number[15];                 /* bytes 0 to 14 */
  uint8_t transaction_type;                 /* byte 15 */
  uint8_t timestamp[6];                     /* bytes 16 to 21 */
  uint8_t symbol[30];                       /* bytes 22 to 51 */
  uint8_t expiration_date[6];               /* bytes 52 to 57 */
  uint8_t strike_price[8];                  /* bytes 58 to 65 */
  uint8_t strike_price_fraction_indicator;  /* byte 66 */
  uint8_t option_type;                      /* byte 67 */
  uint8_t volume[8];                        /* bytes 68 to 75 */
  uint8_t price[8];                         /* bytes 76 to 83 */
  uint8_t cmta_broker[4];                   /* bytes 84 to 87 */
  uint8_t account_type;                     /* byte 88 */
  uint8_t sub_trader_id[3];                 /* bytes 89 to 91 */
  uint8_t open_close;                       /* byte 92 */
  uint8_t executing_broker[4];              /* bytes 93 to 96 */
  uint8_t client_account_number[12];        /* bytes 97 to 108 */
  uint8_t client_order_id[20];              /* bytes 109 to 128 */
  uint8_t client_memo[16];                  /* bytes 129 to 144 */
  uint8_t liquidity_status;                 /* byte 145 */
  uint8_t trade_type;                       /* byte 146 */
  uint8_t opposite_account_type;            /* byte 147 */
  uint8_t participant_session_name[12];     /* bytes 148 to 159 */
  uint8_t unique_transaction_id[10];        /* bytes 160 to 169 */
  uint8_t parent_transaction_id[10];        /* bytes 170 to 179 */
  uint8_t opposite_executing_broker[4];     /* bytes 180 to 183 */
  uint8_t additional_client_memo[16];       /* bytes 184 to 199 */
} TradeCancel;

/* any Trade Cancel at all: every byte one the checker chooses */
static void any_trade_cancel(TradeCancel *record) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = arbitrary(); }
  record->transaction_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  record->trade_type = arbitrary();
  record->opposite_account_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Trade Cancel to the wire: 200 bytes from at, returning where the next byte goes */
static size_t encode_trade_cancel(const TradeCancel *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->transaction_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_broker[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  wire[at++] = record->liquidity_status;
  wire[at++] = record->trade_type;
  wire[at++] = record->opposite_account_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_session_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->unique_transaction_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->parent_transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opposite_executing_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Trade Cancel off the wire: 200 bytes from at, returning where the next byte lies */
static size_t decode_trade_cancel(TradeCancel *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = wire[at++]; }
  record->transaction_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  record->trade_type = wire[at++];
  record->opposite_account_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Trade Cancel is what was written, byte for byte */
static void equal_trade_cancel(const TradeCancel *read, const TradeCancel *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->transaction_type == written->transaction_type);
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->executing_broker[i] == written->executing_broker[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  assert(read->trade_type == written->trade_type);
  assert(read->opposite_account_type == written->opposite_account_type);
  for (size_t i = 0; i < 12; i++) { assert(read->participant_session_name[i] == written->participant_session_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->unique_transaction_id[i] == written->unique_transaction_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->parent_transaction_id[i] == written->parent_transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opposite_executing_broker[i] == written->opposite_executing_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Trade Cancel: written and read back, then read and written back */
static void check_trade_cancel(void) {
  TradeCancel sent;
  TradeCancel got;
  uint8_t wire[200];
  uint8_t again[200];

  any_trade_cancel(&sent);
  assert(encode_trade_cancel(&sent, wire, 0) == 200);
  assert(decode_trade_cancel(&got, wire, 0) == 200);
  equal_trade_cancel(&got, &sent);

  for (size_t i = 0; i < 200; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_cancel(&got, wire, 0) == 200);
  assert(encode_trade_cancel(&got, again, 0) == 200);
  for (size_t i = 0; i < 200; i++) { assert(again[i] == wire[i]); }
}

/* ---- Allocation: 200 bytes --------------------------------------------------- */

/* The guide states this message as having the same structure as message type 30, whose fields are written out here. The guide heads this message 212 bytes, while the fields it states measure 228 including the 28 byte header. */
typedef struct {
  uint8_t trade_number[15];                 /* bytes 0 to 14 */
  uint8_t transaction_type;                 /* byte 15 */
  uint8_t timestamp[6];                     /* bytes 16 to 21 */
  uint8_t symbol[30];                       /* bytes 22 to 51 */
  uint8_t expiration_date[6];               /* bytes 52 to 57 */
  uint8_t strike_price[8];                  /* bytes 58 to 65 */
  uint8_t strike_price_fraction_indicator;  /* byte 66 */
  uint8_t option_type;                      /* byte 67 */
  uint8_t volume[8];                        /* bytes 68 to 75 */
  uint8_t price[8];                         /* bytes 76 to 83 */
  uint8_t cmta_broker[4];                   /* bytes 84 to 87 */
  uint8_t account_type;                     /* byte 88 */
  uint8_t sub_trader_id[3];                 /* bytes 89 to 91 */
  uint8_t open_close;                       /* byte 92 */
  uint8_t executing_broker[4];              /* bytes 93 to 96 */
  uint8_t client_account_number[12];        /* bytes 97 to 108 */
  uint8_t client_order_id[20];              /* bytes 109 to 128 */
  uint8_t client_memo[16];                  /* bytes 129 to 144 */
  uint8_t liquidity_status;                 /* byte 145 */
  uint8_t trade_type;                       /* byte 146 */
  uint8_t opposite_account_type;            /* byte 147 */
  uint8_t participant_session_name[12];     /* bytes 148 to 159 */
  uint8_t unique_transaction_id[10];        /* bytes 160 to 169 */
  uint8_t parent_transaction_id[10];        /* bytes 170 to 179 */
  uint8_t opposite_executing_broker[4];     /* bytes 180 to 183 */
  uint8_t additional_client_memo[16];       /* bytes 184 to 199 */
} Allocation;

/* any Allocation at all: every byte one the checker chooses */
static void any_allocation(Allocation *record) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = arbitrary(); }
  record->transaction_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  record->trade_type = arbitrary();
  record->opposite_account_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Allocation to the wire: 200 bytes from at, returning where the next byte goes */
static size_t encode_allocation(const Allocation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->transaction_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_broker[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  wire[at++] = record->liquidity_status;
  wire[at++] = record->trade_type;
  wire[at++] = record->opposite_account_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_session_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->unique_transaction_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->parent_transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opposite_executing_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Allocation off the wire: 200 bytes from at, returning where the next byte lies */
static size_t decode_allocation(Allocation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = wire[at++]; }
  record->transaction_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  record->trade_type = wire[at++];
  record->opposite_account_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Allocation is what was written, byte for byte */
static void equal_allocation(const Allocation *read, const Allocation *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->transaction_type == written->transaction_type);
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->executing_broker[i] == written->executing_broker[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  assert(read->trade_type == written->trade_type);
  assert(read->opposite_account_type == written->opposite_account_type);
  for (size_t i = 0; i < 12; i++) { assert(read->participant_session_name[i] == written->participant_session_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->unique_transaction_id[i] == written->unique_transaction_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->parent_transaction_id[i] == written->parent_transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opposite_executing_broker[i] == written->opposite_executing_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Allocation: written and read back, then read and written back */
static void check_allocation(void) {
  Allocation sent;
  Allocation got;
  uint8_t wire[200];
  uint8_t again[200];

  any_allocation(&sent);
  assert(encode_allocation(&sent, wire, 0) == 200);
  assert(decode_allocation(&got, wire, 0) == 200);
  equal_allocation(&got, &sent);

  for (size_t i = 0; i < 200; i++) { wire[i] = arbitrary(); }
  assert(decode_allocation(&got, wire, 0) == 200);
  assert(encode_allocation(&got, again, 0) == 200);
  for (size_t i = 0; i < 200; i++) { assert(again[i] == wire[i]); }
}

/* ---- Allocation Cancel: 200 bytes -------------------------------------------- */

/* The guide states this message as having the same structure as message type 30, whose fields are written out here. The guide heads this message 212 bytes, while the fields it states measure 228 including the 28 byte header. */
typedef struct {
  uint8_t trade_number[15];                 /* bytes 0 to 14 */
  uint8_t transaction_type;                 /* byte 15 */
  uint8_t timestamp[6];                     /* bytes 16 to 21 */
  uint8_t symbol[30];                       /* bytes 22 to 51 */
  uint8_t expiration_date[6];               /* bytes 52 to 57 */
  uint8_t strike_price[8];                  /* bytes 58 to 65 */
  uint8_t strike_price_fraction_indicator;  /* byte 66 */
  uint8_t option_type;                      /* byte 67 */
  uint8_t volume[8];                        /* bytes 68 to 75 */
  uint8_t price[8];                         /* bytes 76 to 83 */
  uint8_t cmta_broker[4];                   /* bytes 84 to 87 */
  uint8_t account_type;                     /* byte 88 */
  uint8_t sub_trader_id[3];                 /* bytes 89 to 91 */
  uint8_t open_close;                       /* byte 92 */
  uint8_t executing_broker[4];              /* bytes 93 to 96 */
  uint8_t client_account_number[12];        /* bytes 97 to 108 */
  uint8_t client_order_id[20];              /* bytes 109 to 128 */
  uint8_t client_memo[16];                  /* bytes 129 to 144 */
  uint8_t liquidity_status;                 /* byte 145 */
  uint8_t trade_type;                       /* byte 146 */
  uint8_t opposite_account_type;            /* byte 147 */
  uint8_t participant_session_name[12];     /* bytes 148 to 159 */
  uint8_t unique_transaction_id[10];        /* bytes 160 to 169 */
  uint8_t parent_transaction_id[10];        /* bytes 170 to 179 */
  uint8_t opposite_executing_broker[4];     /* bytes 180 to 183 */
  uint8_t additional_client_memo[16];       /* bytes 184 to 199 */
} AllocationCancel;

/* any Allocation Cancel at all: every byte one the checker chooses */
static void any_allocation_cancel(AllocationCancel *record) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = arbitrary(); }
  record->transaction_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  record->trade_type = arbitrary();
  record->opposite_account_type = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Allocation Cancel to the wire: 200 bytes from at, returning where the next byte goes */
static size_t encode_allocation_cancel(const AllocationCancel *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->transaction_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_broker[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  wire[at++] = record->liquidity_status;
  wire[at++] = record->trade_type;
  wire[at++] = record->opposite_account_type;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_session_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->unique_transaction_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->parent_transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opposite_executing_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Allocation Cancel off the wire: 200 bytes from at, returning where the next byte lies */
static size_t decode_allocation_cancel(AllocationCancel *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = wire[at++]; }
  record->transaction_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  record->trade_type = wire[at++];
  record->opposite_account_type = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Allocation Cancel is what was written, byte for byte */
static void equal_allocation_cancel(const AllocationCancel *read, const AllocationCancel *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->transaction_type == written->transaction_type);
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->executing_broker[i] == written->executing_broker[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  assert(read->trade_type == written->trade_type);
  assert(read->opposite_account_type == written->opposite_account_type);
  for (size_t i = 0; i < 12; i++) { assert(read->participant_session_name[i] == written->participant_session_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->unique_transaction_id[i] == written->unique_transaction_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->parent_transaction_id[i] == written->parent_transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opposite_executing_broker[i] == written->opposite_executing_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Allocation Cancel: written and read back, then read and written back */
static void check_allocation_cancel(void) {
  AllocationCancel sent;
  AllocationCancel got;
  uint8_t wire[200];
  uint8_t again[200];

  any_allocation_cancel(&sent);
  assert(encode_allocation_cancel(&sent, wire, 0) == 200);
  assert(decode_allocation_cancel(&got, wire, 0) == 200);
  equal_allocation_cancel(&got, &sent);

  for (size_t i = 0; i < 200; i++) { wire[i] = arbitrary(); }
  assert(decode_allocation_cancel(&got, wire, 0) == 200);
  assert(encode_allocation_cancel(&got, again, 0) == 200);
  for (size_t i = 0; i < 200; i++) { assert(again[i] == wire[i]); }
}

/* ---- Give Up: 208 bytes ------------------------------------------------------ */

/* The guide heads this message 220 bytes, while the fields it states measure 236 including the 28 byte header. */
typedef struct {
  uint8_t trade_number[15];                 /* bytes 0 to 14 */
  uint8_t transaction_type;                 /* byte 15 */
  uint8_t timestamp[6];                     /* bytes 16 to 21 */
  uint8_t symbol[30];                       /* bytes 22 to 51 */
  uint8_t expiration_date[6];               /* bytes 52 to 57 */
  uint8_t strike_price[8];                  /* bytes 58 to 65 */
  uint8_t strike_price_fraction_indicator;  /* byte 66 */
  uint8_t option_type;                      /* byte 67 */
  uint8_t volume[8];                        /* bytes 68 to 75 */
  uint8_t price[8];                         /* bytes 76 to 83 */
  uint8_t cmta_broker[4];                   /* bytes 84 to 87 */
  uint8_t account_type;                     /* byte 88 */
  uint8_t sub_trader_id[3];                 /* bytes 89 to 91 */
  uint8_t open_close;                       /* byte 92 */
  uint8_t executing_broker[4];              /* bytes 93 to 96 */
  uint8_t client_account_number[12];        /* bytes 97 to 108 */
  uint8_t client_order_id[20];              /* bytes 109 to 128 */
  uint8_t client_memo[16];                  /* bytes 129 to 144 */
  uint8_t liquidity_status;                 /* byte 145 */
  uint8_t trade_type;                       /* byte 146 */
  uint8_t opposite_account_type;            /* byte 147 */
  uint8_t give_up_source[4];                /* bytes 148 to 151 */
  uint8_t give_up_destination[4];           /* bytes 152 to 155 */
  uint8_t participant_session_name[12];     /* bytes 156 to 167 */
  uint8_t unique_transaction_id[10];        /* bytes 168 to 177 */
  uint8_t parent_transaction_id[10];        /* bytes 178 to 187 */
  uint8_t opposite_executing_broker[4];     /* bytes 188 to 191 */
  uint8_t additional_client_memo[16];       /* bytes 192 to 207 */
} GiveUp;

/* any Give Up at all: every byte one the checker chooses */
static void any_give_up(GiveUp *record) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = arbitrary(); }
  record->transaction_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  record->trade_type = arbitrary();
  record->opposite_account_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_up_source[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_destination[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Give Up to the wire: 208 bytes from at, returning where the next byte goes */
static size_t encode_give_up(const GiveUp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->transaction_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_broker[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  wire[at++] = record->liquidity_status;
  wire[at++] = record->trade_type;
  wire[at++] = record->opposite_account_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_source[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_destination[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_session_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->unique_transaction_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->parent_transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opposite_executing_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Give Up off the wire: 208 bytes from at, returning where the next byte lies */
static size_t decode_give_up(GiveUp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = wire[at++]; }
  record->transaction_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  record->trade_type = wire[at++];
  record->opposite_account_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_up_source[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_destination[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Give Up is what was written, byte for byte */
static void equal_give_up(const GiveUp *read, const GiveUp *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->transaction_type == written->transaction_type);
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->executing_broker[i] == written->executing_broker[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  assert(read->trade_type == written->trade_type);
  assert(read->opposite_account_type == written->opposite_account_type);
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_source[i] == written->give_up_source[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_destination[i] == written->give_up_destination[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->participant_session_name[i] == written->participant_session_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->unique_transaction_id[i] == written->unique_transaction_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->parent_transaction_id[i] == written->parent_transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opposite_executing_broker[i] == written->opposite_executing_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Give Up: written and read back, then read and written back */
static void check_give_up(void) {
  GiveUp sent;
  GiveUp got;
  uint8_t wire[208];
  uint8_t again[208];

  any_give_up(&sent);
  assert(encode_give_up(&sent, wire, 0) == 208);
  assert(decode_give_up(&got, wire, 0) == 208);
  equal_give_up(&got, &sent);

  for (size_t i = 0; i < 208; i++) { wire[i] = arbitrary(); }
  assert(decode_give_up(&got, wire, 0) == 208);
  assert(encode_give_up(&got, again, 0) == 208);
  for (size_t i = 0; i < 208; i++) { assert(again[i] == wire[i]); }
}

/* ---- Give Up Cancel: 208 bytes ----------------------------------------------- */

/* The guide states this message as having the same structure as message type 50, whose fields are written out here. The guide heads this message 216 bytes, while the fields it states measure 236 including the 28 byte header. */
typedef struct {
  uint8_t trade_number[15];                 /* bytes 0 to 14 */
  uint8_t transaction_type;                 /* byte 15 */
  uint8_t timestamp[6];                     /* bytes 16 to 21 */
  uint8_t symbol[30];                       /* bytes 22 to 51 */
  uint8_t expiration_date[6];               /* bytes 52 to 57 */
  uint8_t strike_price[8];                  /* bytes 58 to 65 */
  uint8_t strike_price_fraction_indicator;  /* byte 66 */
  uint8_t option_type;                      /* byte 67 */
  uint8_t volume[8];                        /* bytes 68 to 75 */
  uint8_t price[8];                         /* bytes 76 to 83 */
  uint8_t cmta_broker[4];                   /* bytes 84 to 87 */
  uint8_t account_type;                     /* byte 88 */
  uint8_t sub_trader_id[3];                 /* bytes 89 to 91 */
  uint8_t open_close;                       /* byte 92 */
  uint8_t executing_broker[4];              /* bytes 93 to 96 */
  uint8_t client_account_number[12];        /* bytes 97 to 108 */
  uint8_t client_order_id[20];              /* bytes 109 to 128 */
  uint8_t client_memo[16];                  /* bytes 129 to 144 */
  uint8_t liquidity_status;                 /* byte 145 */
  uint8_t trade_type;                       /* byte 146 */
  uint8_t opposite_account_type;            /* byte 147 */
  uint8_t give_up_source[4];                /* bytes 148 to 151 */
  uint8_t give_up_destination[4];           /* bytes 152 to 155 */
  uint8_t participant_session_name[12];     /* bytes 156 to 167 */
  uint8_t unique_transaction_id[10];        /* bytes 168 to 177 */
  uint8_t parent_transaction_id[10];        /* bytes 178 to 187 */
  uint8_t opposite_executing_broker[4];     /* bytes 188 to 191 */
  uint8_t additional_client_memo[16];       /* bytes 192 to 207 */
} GiveUpCancel;

/* any Give Up Cancel at all: every byte one the checker chooses */
static void any_give_up_cancel(GiveUpCancel *record) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = arbitrary(); }
  record->transaction_type = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = arbitrary(); }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = arbitrary(); }
  record->strike_price_fraction_indicator = arbitrary();
  record->option_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  record->account_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  record->open_close = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  record->liquidity_status = arbitrary();
  record->trade_type = arbitrary();
  record->opposite_account_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->give_up_source[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_destination[i] = arbitrary(); }
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Give Up Cancel to the wire: 208 bytes from at, returning where the next byte goes */
static size_t encode_give_up_cancel(const GiveUpCancel *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->trade_number[i]; }
  wire[at++] = record->transaction_type;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->timestamp[i]; }
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->symbol[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->expiration_date[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->strike_price_fraction_indicator;
  wire[at++] = record->option_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  wire[at++] = record->account_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->executing_broker[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  wire[at++] = record->liquidity_status;
  wire[at++] = record->trade_type;
  wire[at++] = record->opposite_account_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_source[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_destination[i]; }
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->participant_session_name[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->unique_transaction_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->parent_transaction_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->opposite_executing_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Give Up Cancel off the wire: 208 bytes from at, returning where the next byte lies */
static size_t decode_give_up_cancel(GiveUpCancel *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 15; i++) { record->trade_number[i] = wire[at++]; }
  record->transaction_type = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->timestamp[i] = wire[at++]; }
  for (size_t i = 0; i < 30; i++) { record->symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->expiration_date[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->strike_price[i] = wire[at++]; }
  record->strike_price_fraction_indicator = wire[at++];
  record->option_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  record->account_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  record->open_close = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  record->liquidity_status = wire[at++];
  record->trade_type = wire[at++];
  record->opposite_account_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->give_up_source[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_destination[i] = wire[at++]; }
  for (size_t i = 0; i < 12; i++) { record->participant_session_name[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->unique_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->parent_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->opposite_executing_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Give Up Cancel is what was written, byte for byte */
static void equal_give_up_cancel(const GiveUpCancel *read, const GiveUpCancel *written) {
  for (size_t i = 0; i < 15; i++) { assert(read->trade_number[i] == written->trade_number[i]); }
  assert(read->transaction_type == written->transaction_type);
  for (size_t i = 0; i < 6; i++) { assert(read->timestamp[i] == written->timestamp[i]); }
  for (size_t i = 0; i < 30; i++) { assert(read->symbol[i] == written->symbol[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->expiration_date[i] == written->expiration_date[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->strike_price_fraction_indicator == written->strike_price_fraction_indicator);
  assert(read->option_type == written->option_type);
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  assert(read->account_type == written->account_type);
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 4; i++) { assert(read->executing_broker[i] == written->executing_broker[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  assert(read->liquidity_status == written->liquidity_status);
  assert(read->trade_type == written->trade_type);
  assert(read->opposite_account_type == written->opposite_account_type);
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_source[i] == written->give_up_source[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_destination[i] == written->give_up_destination[i]); }
  for (size_t i = 0; i < 12; i++) { assert(read->participant_session_name[i] == written->participant_session_name[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->unique_transaction_id[i] == written->unique_transaction_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->parent_transaction_id[i] == written->parent_transaction_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->opposite_executing_broker[i] == written->opposite_executing_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Give Up Cancel: written and read back, then read and written back */
static void check_give_up_cancel(void) {
  GiveUpCancel sent;
  GiveUpCancel got;
  uint8_t wire[208];
  uint8_t again[208];

  any_give_up_cancel(&sent);
  assert(encode_give_up_cancel(&sent, wire, 0) == 208);
  assert(decode_give_up_cancel(&got, wire, 0) == 208);
  equal_give_up_cancel(&got, &sent);

  for (size_t i = 0; i < 208; i++) { wire[i] = arbitrary(); }
  assert(decode_give_up_cancel(&got, wire, 0) == 208);
  assert(encode_give_up_cancel(&got, again, 0) == 208);
  for (size_t i = 0; i < 208; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Message: 86 bytes ------------------------------------------------- */

/* The guide heads this message up to 112 bytes, while the fields it states measure 114 including the 28 byte header. */
typedef struct {
  uint8_t reference_message_type[2];  /* bytes 0 to 1 */
  uint8_t error_code[4];              /* bytes 2 to 5 */
  uint8_t error_text[80];             /* bytes 6 to 85 */
} ErrorMessage;

/* any Error Message at all: every byte one the checker chooses */
static void any_error_message(ErrorMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reference_message_type[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = arbitrary(); }
  for (size_t i = 0; i < 80; i++) { record->error_text[i] = arbitrary(); }
}

/* Error Message to the wire: 86 bytes from at, returning where the next byte goes */
static size_t encode_error_message(const ErrorMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reference_message_type[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->error_code[i]; }
  for (size_t i = 0; i < 80; i++) { wire[at++] = record->error_text[i]; }

  return at;
}

/* Error Message off the wire: 86 bytes from at, returning where the next byte lies */
static size_t decode_error_message(ErrorMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reference_message_type[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->error_code[i] = wire[at++]; }
  for (size_t i = 0; i < 80; i++) { record->error_text[i] = wire[at++]; }

  return at;
}

/* what was read of Error Message is what was written, byte for byte */
static void equal_error_message(const ErrorMessage *read, const ErrorMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reference_message_type[i] == written->reference_message_type[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->error_code[i] == written->error_code[i]); }
  for (size_t i = 0; i < 80; i++) { assert(read->error_text[i] == written->error_text[i]); }
}

/* Error Message: written and read back, then read and written back */
static void check_error_message(void) {
  ErrorMessage sent;
  ErrorMessage got;
  uint8_t wire[86];
  uint8_t again[86];

  any_error_message(&sent);
  assert(encode_error_message(&sent, wire, 0) == 86);
  assert(decode_error_message(&got, wire, 0) == 86);
  equal_error_message(&got, &sent);

  for (size_t i = 0; i < 86; i++) { wire[i] = arbitrary(); }
  assert(decode_error_message(&got, wire, 0) == 86);
  assert(encode_error_message(&got, again, 0) == 86);
  for (size_t i = 0; i < 86; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_client_signon_acknowledgment();
  check_trade();
  check_trade_cancel();
  check_allocation();
  check_allocation_cancel();
  check_give_up();
  check_give_up_cancel();
  check_error_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
