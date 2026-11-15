// box/boxoptions/solatradereporting/BoxOptions_SolaTradeReporting_v4_5_Client.c
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

/* ---- Restart Request: 8 bytes ------------------------------------------------ */

typedef struct {
  uint8_t sequence_number[8];  /* bytes 0 to 7 */
} RestartRequest;

/* any Restart Request at all: every byte one the checker chooses */
static void any_restart_request(RestartRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Restart Request to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_restart_request(const RestartRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Restart Request off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_restart_request(RestartRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Restart Request is what was written, byte for byte */
static void equal_restart_request(const RestartRequest *read, const RestartRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Restart Request: written and read back, then read and written back */
static void check_restart_request(void) {
  RestartRequest sent;
  RestartRequest got;
  uint8_t wire[8];
  uint8_t again[8];

  any_restart_request(&sent);
  assert(encode_restart_request(&sent, wire, 0) == 8);
  assert(decode_restart_request(&got, wire, 0) == 8);
  equal_restart_request(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_restart_request(&got, wire, 0) == 8);
  assert(encode_restart_request(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Client Signon: 36 bytes ------------------------------------------------- */

typedef struct {
  uint8_t member_number[4];             /* bytes 0 to 3 */
  uint8_t initial_sequence_number[8];   /* bytes 4 to 11 */
  uint8_t protocol_version[2];          /* bytes 12 to 13 */
  uint8_t time[6];                      /* bytes 14 to 19 */
  uint8_t username[8];                  /* bytes 20 to 27 */
  uint8_t password_md_5_encryption[8];  /* bytes 28 to 35 */
} ClientSignon;

/* any Client Signon at all: every byte one the checker chooses */
static void any_client_signon(ClientSignon *record) {
  for (size_t i = 0; i < 4; i++) { record->member_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->initial_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->protocol_version[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->password_md_5_encryption[i] = arbitrary(); }
}

/* Client Signon to the wire: 36 bytes from at, returning where the next byte goes */
static size_t encode_client_signon(const ClientSignon *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->member_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->initial_sequence_number[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->protocol_version[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->password_md_5_encryption[i]; }

  return at;
}

/* Client Signon off the wire: 36 bytes from at, returning where the next byte lies */
static size_t decode_client_signon(ClientSignon *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->member_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->initial_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->protocol_version[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->password_md_5_encryption[i] = wire[at++]; }

  return at;
}

/* what was read of Client Signon is what was written, byte for byte */
static void equal_client_signon(const ClientSignon *read, const ClientSignon *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->member_number[i] == written->member_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->initial_sequence_number[i] == written->initial_sequence_number[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->protocol_version[i] == written->protocol_version[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time[i] == written->time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->password_md_5_encryption[i] == written->password_md_5_encryption[i]); }
}

/* Client Signon: written and read back, then read and written back */
static void check_client_signon(void) {
  ClientSignon sent;
  ClientSignon got;
  uint8_t wire[36];
  uint8_t again[36];

  any_client_signon(&sent);
  assert(encode_client_signon(&sent, wire, 0) == 36);
  assert(decode_client_signon(&got, wire, 0) == 36);
  equal_client_signon(&got, &sent);

  for (size_t i = 0; i < 36; i++) { wire[i] = arbitrary(); }
  assert(decode_client_signon(&got, wire, 0) == 36);
  assert(encode_client_signon(&got, again, 0) == 36);
  for (size_t i = 0; i < 36; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Allocation: 94 bytes ------------------------------------------------ */

/* The guide heads this message 106 bytes, while the fields it states measure 122 including the 28 byte header. */
typedef struct {
  uint8_t reference_transaction_id[10];  /* bytes 0 to 9 */
  uint8_t reference_trade_number[15];    /* bytes 10 to 24 */
  uint8_t give_up_firm[4];               /* bytes 25 to 28 */
  uint8_t volume[8];                     /* bytes 29 to 36 */
  uint8_t account_type;                  /* byte 37 */
  uint8_t open_close;                    /* byte 38 */
  uint8_t client_account_number[12];     /* bytes 39 to 50 */
  uint8_t sub_trader_id[3];              /* bytes 51 to 53 */
  uint8_t cmta_broker[4];                /* bytes 54 to 57 */
  uint8_t client_memo[16];               /* bytes 58 to 73 */
  uint8_t additional_firm[4];            /* bytes 74 to 77 */
  uint8_t additional_client_memo[16];    /* bytes 78 to 93 */
} NewAllocation;

/* any New Allocation at all: every byte one the checker chooses */
static void any_new_allocation(NewAllocation *record) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->additional_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* New Allocation to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_new_allocation(const NewAllocation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reference_transaction_id[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->reference_trade_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->additional_firm[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* New Allocation off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_new_allocation(NewAllocation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->additional_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of New Allocation is what was written, byte for byte */
static void equal_new_allocation(const NewAllocation *read, const NewAllocation *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->reference_transaction_id[i] == written->reference_transaction_id[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->reference_trade_number[i] == written->reference_trade_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_firm[i] == written->give_up_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->additional_firm[i] == written->additional_firm[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* New Allocation: written and read back, then read and written back */
static void check_new_allocation(void) {
  NewAllocation sent;
  NewAllocation got;
  uint8_t wire[94];
  uint8_t again[94];

  any_new_allocation(&sent);
  assert(encode_new_allocation(&sent, wire, 0) == 94);
  assert(decode_new_allocation(&got, wire, 0) == 94);
  equal_new_allocation(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_new_allocation(&got, wire, 0) == 94);
  assert(encode_new_allocation(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Allocation: 94 bytes --------------------------------------------- */

/* The guide states this message as having the same structure as message type 42, whose fields are written out here. The guide heads this message 106 bytes, while the fields it states measure 122 including the 28 byte header. */
typedef struct {
  uint8_t reference_transaction_id[10];  /* bytes 0 to 9 */
  uint8_t reference_trade_number[15];    /* bytes 10 to 24 */
  uint8_t give_up_firm[4];               /* bytes 25 to 28 */
  uint8_t volume[8];                     /* bytes 29 to 36 */
  uint8_t account_type;                  /* byte 37 */
  uint8_t open_close;                    /* byte 38 */
  uint8_t client_account_number[12];     /* bytes 39 to 50 */
  uint8_t sub_trader_id[3];              /* bytes 51 to 53 */
  uint8_t cmta_broker[4];                /* bytes 54 to 57 */
  uint8_t client_memo[16];               /* bytes 58 to 73 */
  uint8_t additional_firm[4];            /* bytes 74 to 77 */
  uint8_t additional_client_memo[16];    /* bytes 78 to 93 */
} ModifyAllocation;

/* any Modify Allocation at all: every byte one the checker chooses */
static void any_modify_allocation(ModifyAllocation *record) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->additional_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Modify Allocation to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_modify_allocation(const ModifyAllocation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reference_transaction_id[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->reference_trade_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->additional_firm[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Modify Allocation off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_modify_allocation(ModifyAllocation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->additional_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Allocation is what was written, byte for byte */
static void equal_modify_allocation(const ModifyAllocation *read, const ModifyAllocation *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->reference_transaction_id[i] == written->reference_transaction_id[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->reference_trade_number[i] == written->reference_trade_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_firm[i] == written->give_up_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->additional_firm[i] == written->additional_firm[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Modify Allocation: written and read back, then read and written back */
static void check_modify_allocation(void) {
  ModifyAllocation sent;
  ModifyAllocation got;
  uint8_t wire[94];
  uint8_t again[94];

  any_modify_allocation(&sent);
  assert(encode_modify_allocation(&sent, wire, 0) == 94);
  assert(decode_modify_allocation(&got, wire, 0) == 94);
  equal_modify_allocation(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_allocation(&got, wire, 0) == 94);
  assert(encode_modify_allocation(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Allocation: 25 bytes --------------------------------------------- */

typedef struct {
  uint8_t reference_transaction_id[10];  /* bytes 0 to 9 */
  uint8_t reference_trade_number[15];    /* bytes 10 to 24 */
} DeleteAllocation;

/* any Delete Allocation at all: every byte one the checker chooses */
static void any_delete_allocation(DeleteAllocation *record) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = arbitrary(); }
}

/* Delete Allocation to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_delete_allocation(const DeleteAllocation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reference_transaction_id[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->reference_trade_number[i]; }

  return at;
}

/* Delete Allocation off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_delete_allocation(DeleteAllocation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Allocation is what was written, byte for byte */
static void equal_delete_allocation(const DeleteAllocation *read, const DeleteAllocation *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->reference_transaction_id[i] == written->reference_transaction_id[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->reference_trade_number[i] == written->reference_trade_number[i]); }
}

/* Delete Allocation: written and read back, then read and written back */
static void check_delete_allocation(void) {
  DeleteAllocation sent;
  DeleteAllocation got;
  uint8_t wire[25];
  uint8_t again[25];

  any_delete_allocation(&sent);
  assert(encode_delete_allocation(&sent, wire, 0) == 25);
  assert(decode_delete_allocation(&got, wire, 0) == 25);
  equal_delete_allocation(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_allocation(&got, wire, 0) == 25);
  assert(encode_delete_allocation(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Give Up: 94 bytes --------------------------------------------------- */

/* The guide states this message as having the same structure as message type 42, whose fields are written out here. The guide heads this message 106 bytes, while the fields it states measure 122 including the 28 byte header. */
typedef struct {
  uint8_t reference_transaction_id[10];  /* bytes 0 to 9 */
  uint8_t reference_trade_number[15];    /* bytes 10 to 24 */
  uint8_t give_up_firm[4];               /* bytes 25 to 28 */
  uint8_t volume[8];                     /* bytes 29 to 36 */
  uint8_t account_type;                  /* byte 37 */
  uint8_t open_close;                    /* byte 38 */
  uint8_t client_account_number[12];     /* bytes 39 to 50 */
  uint8_t sub_trader_id[3];              /* bytes 51 to 53 */
  uint8_t cmta_broker[4];                /* bytes 54 to 57 */
  uint8_t client_memo[16];               /* bytes 58 to 73 */
  uint8_t additional_firm[4];            /* bytes 74 to 77 */
  uint8_t additional_client_memo[16];    /* bytes 78 to 93 */
} NewGiveUp;

/* any New Give Up at all: every byte one the checker chooses */
static void any_new_give_up(NewGiveUp *record) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->additional_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* New Give Up to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_new_give_up(const NewGiveUp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reference_transaction_id[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->reference_trade_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->additional_firm[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* New Give Up off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_new_give_up(NewGiveUp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->additional_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of New Give Up is what was written, byte for byte */
static void equal_new_give_up(const NewGiveUp *read, const NewGiveUp *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->reference_transaction_id[i] == written->reference_transaction_id[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->reference_trade_number[i] == written->reference_trade_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_firm[i] == written->give_up_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->additional_firm[i] == written->additional_firm[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* New Give Up: written and read back, then read and written back */
static void check_new_give_up(void) {
  NewGiveUp sent;
  NewGiveUp got;
  uint8_t wire[94];
  uint8_t again[94];

  any_new_give_up(&sent);
  assert(encode_new_give_up(&sent, wire, 0) == 94);
  assert(decode_new_give_up(&got, wire, 0) == 94);
  equal_new_give_up(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_new_give_up(&got, wire, 0) == 94);
  assert(encode_new_give_up(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Give Up: 94 bytes ------------------------------------------------ */

/* The guide states this message as having the same structure as message type 42, whose fields are written out here. The guide heads this message 106 bytes, while the fields it states measure 122 including the 28 byte header. */
typedef struct {
  uint8_t reference_transaction_id[10];  /* bytes 0 to 9 */
  uint8_t reference_trade_number[15];    /* bytes 10 to 24 */
  uint8_t give_up_firm[4];               /* bytes 25 to 28 */
  uint8_t volume[8];                     /* bytes 29 to 36 */
  uint8_t account_type;                  /* byte 37 */
  uint8_t open_close;                    /* byte 38 */
  uint8_t client_account_number[12];     /* bytes 39 to 50 */
  uint8_t sub_trader_id[3];              /* bytes 51 to 53 */
  uint8_t cmta_broker[4];                /* bytes 54 to 57 */
  uint8_t client_memo[16];               /* bytes 58 to 73 */
  uint8_t additional_firm[4];            /* bytes 74 to 77 */
  uint8_t additional_client_memo[16];    /* bytes 78 to 93 */
} ModifyGiveUp;

/* any Modify Give Up at all: every byte one the checker chooses */
static void any_modify_give_up(ModifyGiveUp *record) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->give_up_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = arbitrary(); }
  record->account_type = arbitrary();
  record->open_close = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = arbitrary(); }
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->additional_firm[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = arbitrary(); }
}

/* Modify Give Up to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_modify_give_up(const ModifyGiveUp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reference_transaction_id[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->reference_trade_number[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->give_up_firm[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->volume[i]; }
  wire[at++] = record->account_type;
  wire[at++] = record->open_close;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->client_account_number[i]; }
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->sub_trader_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->cmta_broker[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->client_memo[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->additional_firm[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->additional_client_memo[i]; }

  return at;
}

/* Modify Give Up off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_modify_give_up(ModifyGiveUp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->give_up_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->volume[i] = wire[at++]; }
  record->account_type = wire[at++];
  record->open_close = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->client_account_number[i] = wire[at++]; }
  for (size_t i = 0; i < 3; i++) { record->sub_trader_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->cmta_broker[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->client_memo[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->additional_firm[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->additional_client_memo[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Give Up is what was written, byte for byte */
static void equal_modify_give_up(const ModifyGiveUp *read, const ModifyGiveUp *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->reference_transaction_id[i] == written->reference_transaction_id[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->reference_trade_number[i] == written->reference_trade_number[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->give_up_firm[i] == written->give_up_firm[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->volume[i] == written->volume[i]); }
  assert(read->account_type == written->account_type);
  assert(read->open_close == written->open_close);
  for (size_t i = 0; i < 12; i++) { assert(read->client_account_number[i] == written->client_account_number[i]); }
  for (size_t i = 0; i < 3; i++) { assert(read->sub_trader_id[i] == written->sub_trader_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->cmta_broker[i] == written->cmta_broker[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->client_memo[i] == written->client_memo[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->additional_firm[i] == written->additional_firm[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->additional_client_memo[i] == written->additional_client_memo[i]); }
}

/* Modify Give Up: written and read back, then read and written back */
static void check_modify_give_up(void) {
  ModifyGiveUp sent;
  ModifyGiveUp got;
  uint8_t wire[94];
  uint8_t again[94];

  any_modify_give_up(&sent);
  assert(encode_modify_give_up(&sent, wire, 0) == 94);
  assert(decode_modify_give_up(&got, wire, 0) == 94);
  equal_modify_give_up(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_give_up(&got, wire, 0) == 94);
  assert(encode_modify_give_up(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Delete Give Up: 25 bytes ------------------------------------------------ */

/* The guide states this message as having the same structure as message type 44, whose fields are written out here. */
typedef struct {
  uint8_t reference_transaction_id[10];  /* bytes 0 to 9 */
  uint8_t reference_trade_number[15];    /* bytes 10 to 24 */
} DeleteGiveUp;

/* any Delete Give Up at all: every byte one the checker chooses */
static void any_delete_give_up(DeleteGiveUp *record) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = arbitrary(); }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = arbitrary(); }
}

/* Delete Give Up to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_delete_give_up(const DeleteGiveUp *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reference_transaction_id[i]; }
  for (size_t i = 0; i < 15; i++) { wire[at++] = record->reference_trade_number[i]; }

  return at;
}

/* Delete Give Up off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_delete_give_up(DeleteGiveUp *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 10; i++) { record->reference_transaction_id[i] = wire[at++]; }
  for (size_t i = 0; i < 15; i++) { record->reference_trade_number[i] = wire[at++]; }

  return at;
}

/* what was read of Delete Give Up is what was written, byte for byte */
static void equal_delete_give_up(const DeleteGiveUp *read, const DeleteGiveUp *written) {
  for (size_t i = 0; i < 10; i++) { assert(read->reference_transaction_id[i] == written->reference_transaction_id[i]); }
  for (size_t i = 0; i < 15; i++) { assert(read->reference_trade_number[i] == written->reference_trade_number[i]); }
}

/* Delete Give Up: written and read back, then read and written back */
static void check_delete_give_up(void) {
  DeleteGiveUp sent;
  DeleteGiveUp got;
  uint8_t wire[25];
  uint8_t again[25];

  any_delete_give_up(&sent);
  assert(encode_delete_give_up(&sent, wire, 0) == 25);
  assert(decode_delete_give_up(&got, wire, 0) == 25);
  equal_delete_give_up(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_delete_give_up(&got, wire, 0) == 25);
  assert(encode_delete_give_up(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_header();
  check_restart_request();
  check_client_signon();
  check_new_allocation();
  check_modify_allocation();
  check_delete_allocation();
  check_new_give_up();
  check_modify_give_up();
  check_delete_give_up();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
