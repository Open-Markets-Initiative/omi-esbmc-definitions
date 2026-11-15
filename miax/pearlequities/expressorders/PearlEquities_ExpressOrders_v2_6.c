// miax/pearlequities/expressorders/PearlEquities_ExpressOrders_v2_6.c
/*
 * Miami International Holdings Express Orders
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
 *   - a length prefix framing what follows
 *   - a field read in bits
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

/* ---- Esesm Packet Header: 3 bytes -------------------------------------------- */

/* ESesM packet header */
typedef struct {
  uint8_t esesm_packet_length[2];  /* bytes 0 to 1 */
  uint8_t esesm_packet_type;       /* byte 2 */
} EsesmPacketHeader;

/* any Esesm Packet Header at all: every byte one the checker chooses */
static void any_esesm_packet_header(EsesmPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->esesm_packet_length[i] = arbitrary(); }
  record->esesm_packet_type = arbitrary();
}

/* Esesm Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_esesm_packet_header(const EsesmPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->esesm_packet_length[i]; }
  wire[at++] = record->esesm_packet_type;

  return at;
}

/* Esesm Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_esesm_packet_header(EsesmPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->esesm_packet_length[i] = wire[at++]; }
  record->esesm_packet_type = wire[at++];

  return at;
}

/* what was read of Esesm Packet Header is what was written, byte for byte */
static void equal_esesm_packet_header(const EsesmPacketHeader *read, const EsesmPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->esesm_packet_length[i] == written->esesm_packet_length[i]); }
  assert(read->esesm_packet_type == written->esesm_packet_type);
}

/* Esesm Packet Header: written and read back, then read and written back */
static void check_esesm_packet_header(void) {
  EsesmPacketHeader sent;
  EsesmPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_esesm_packet_header(&sent);
  assert(encode_esesm_packet_header(&sent, wire, 0) == 3);
  assert(decode_esesm_packet_header(&got, wire, 0) == 3);
  equal_esesm_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_esesm_packet_header(&got, wire, 0) == 3);
  assert(encode_esesm_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Update Message: 59 bytes ----------------------------------------- */

/* used to disseminate all security symbols traded on MIAX Pearl Equities for the current session */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[4];             /* bytes 8 to 11 */
  uint8_t ticker_symbol[11];        /* bytes 12 to 22 */
  uint8_t reserved_1;               /* byte 23 */
  uint8_t test_security_indicator;  /* byte 24 */
  uint8_t second_reserved_1;        /* byte 25 */
  uint8_t lot_size[4];              /* bytes 26 to 29 */
  uint8_t opening_time[8];          /* bytes 30 to 37 */
  uint8_t closing_time[8];          /* bytes 38 to 45 */
  uint8_t primary_market_code;      /* byte 46 */
  uint8_t reserved_12[12];          /* bytes 47 to 58 */
} SymbolUpdateMessage;

/* any Symbol Update Message at all: every byte one the checker chooses */
static void any_symbol_update_message(SymbolUpdateMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 11; i++) { record->ticker_symbol[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
  record->test_security_indicator = arbitrary();
  record->second_reserved_1 = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->opening_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->closing_time[i] = arbitrary(); }
  record->primary_market_code = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = arbitrary(); }
}

/* Symbol Update Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_symbol_update_message(const SymbolUpdateMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 11; i++) { wire[at++] = record->ticker_symbol[i]; }
  wire[at++] = record->reserved_1;
  wire[at++] = record->test_security_indicator;
  wire[at++] = record->second_reserved_1;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->lot_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->opening_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->closing_time[i]; }
  wire[at++] = record->primary_market_code;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reserved_12[i]; }

  return at;
}

/* Symbol Update Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_symbol_update_message(SymbolUpdateMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 11; i++) { record->ticker_symbol[i] = wire[at++]; }
  record->reserved_1 = wire[at++];
  record->test_security_indicator = wire[at++];
  record->second_reserved_1 = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->lot_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->opening_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->closing_time[i] = wire[at++]; }
  record->primary_market_code = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Update Message is what was written, byte for byte */
static void equal_symbol_update_message(const SymbolUpdateMessage *read, const SymbolUpdateMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 11; i++) { assert(read->ticker_symbol[i] == written->ticker_symbol[i]); }
  assert(read->reserved_1 == written->reserved_1);
  assert(read->test_security_indicator == written->test_security_indicator);
  assert(read->second_reserved_1 == written->second_reserved_1);
  for (size_t i = 0; i < 4; i++) { assert(read->lot_size[i] == written->lot_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->opening_time[i] == written->opening_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->closing_time[i] == written->closing_time[i]); }
  assert(read->primary_market_code == written->primary_market_code);
  for (size_t i = 0; i < 12; i++) { assert(read->reserved_12[i] == written->reserved_12[i]); }
}

/* Symbol Update Message: written and read back, then read and written back */
static void check_symbol_update_message(void) {
  SymbolUpdateMessage sent;
  SymbolUpdateMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_symbol_update_message(&sent);
  assert(encode_symbol_update_message(&sent, wire, 0) == 59);
  assert(decode_symbol_update_message(&got, wire, 0) == 59);
  equal_symbol_update_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_update_message(&got, wire, 0) == 59);
  assert(encode_symbol_update_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Response Message: 67 bytes ------------------------------------ */

/* provides an acknowledgement for a New Order Request accepted by MIAX Pearl Equities */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t mpid[4];                  /* bytes 8 to 11 */
  uint8_t client_order_id[20];      /* bytes 12 to 31 */
  uint8_t symbol_id[4];             /* bytes 32 to 35 */
  uint8_t order_id[8];              /* bytes 36 to 43 */
  uint8_t price[8];                 /* bytes 44 to 51 */
  uint8_t size[4];                  /* bytes 52 to 55 */
  uint8_t order_status;             /* byte 56 */
  uint8_t reserved_10[10];          /* bytes 57 to 66 */
} NewOrderResponseMessage;

/* any New Order Response Message at all: every byte one the checker chooses */
static void any_new_order_response_message(NewOrderResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->size[i] = arbitrary(); }
  record->order_status = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* New Order Response Message to the wire: 67 bytes from at, returning where the next byte goes */
static size_t encode_new_order_response_message(const NewOrderResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->size[i]; }
  wire[at++] = record->order_status;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* New Order Response Message off the wire: 67 bytes from at, returning where the next byte lies */
static size_t decode_new_order_response_message(NewOrderResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->size[i] = wire[at++]; }
  record->order_status = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Response Message is what was written, byte for byte */
static void equal_new_order_response_message(const NewOrderResponseMessage *read, const NewOrderResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->size[i] == written->size[i]); }
  assert(read->order_status == written->order_status);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* New Order Response Message: written and read back, then read and written back */
static void check_new_order_response_message(void) {
  NewOrderResponseMessage sent;
  NewOrderResponseMessage got;
  uint8_t wire[67];
  uint8_t again[67];

  any_new_order_response_message(&sent);
  assert(encode_new_order_response_message(&sent, wire, 0) == 67);
  assert(decode_new_order_response_message(&got, wire, 0) == 67);
  equal_new_order_response_message(&got, &sent);

  for (size_t i = 0; i < 67; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_response_message(&got, wire, 0) == 67);
  assert(encode_new_order_response_message(&got, again, 0) == 67);
  for (size_t i = 0; i < 67; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Response: 87 bytes ----------------------------------------- */

/* This message format provides acknowledgement for a Modify Order Request accepted by MIAX Pearl Equities */
typedef struct {
  uint8_t matching_engine_time[8];       /* bytes 0 to 7 */
  uint8_t mpid[4];                       /* bytes 8 to 11 */
  uint8_t client_order_id[20];           /* bytes 12 to 31 */
  uint8_t original_client_order_id[20];  /* bytes 32 to 51 */
  uint8_t symbol_id[4];                  /* bytes 52 to 55 */
  uint8_t order_id[8];                   /* bytes 56 to 63 */
  uint8_t leaves_qty[4];                 /* bytes 64 to 67 */
  uint8_t price[8];                      /* bytes 68 to 75 */
  uint8_t modify_status;                 /* byte 76 */
  uint8_t reserved_10[10];               /* bytes 77 to 86 */
} ModifyOrderResponse;

/* any Modify Order Response at all: every byte one the checker chooses */
static void any_modify_order_response(ModifyOrderResponse *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->price[i] = arbitrary(); }
  record->modify_status = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Modify Order Response to the wire: 87 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_response(const ModifyOrderResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->original_client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->price[i]; }
  wire[at++] = record->modify_status;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Modify Order Response off the wire: 87 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_response(ModifyOrderResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->price[i] = wire[at++]; }
  record->modify_status = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Response is what was written, byte for byte */
static void equal_modify_order_response(const ModifyOrderResponse *read, const ModifyOrderResponse *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->original_client_order_id[i] == written->original_client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->price[i] == written->price[i]); }
  assert(read->modify_status == written->modify_status);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Modify Order Response: written and read back, then read and written back */
static void check_modify_order_response(void) {
  ModifyOrderResponse sent;
  ModifyOrderResponse got;
  uint8_t wire[87];
  uint8_t again[87];

  any_modify_order_response(&sent);
  assert(encode_modify_order_response(&sent, wire, 0) == 87);
  assert(decode_modify_order_response(&got, wire, 0) == 87);
  equal_modify_order_response(&got, &sent);

  for (size_t i = 0; i < 87; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_response(&got, wire, 0) == 87);
  assert(encode_modify_order_response(&got, again, 0) == 87);
  for (size_t i = 0; i < 87; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Response: 79 bytes ----------------------------------------- */

/* This message format provides response to an Order Cancel Request */
typedef struct {
  uint8_t matching_engine_time[8];       /* bytes 0 to 7 */
  uint8_t mpid[4];                       /* bytes 8 to 11 */
  uint8_t client_order_id[20];           /* bytes 12 to 31 */
  uint8_t original_client_order_id[20];  /* bytes 32 to 51 */
  uint8_t symbol_id[4];                  /* bytes 52 to 55 */
  uint8_t order_id[8];                   /* bytes 56 to 63 */
  uint8_t leaves_qty[4];                 /* bytes 64 to 67 */
  uint8_t cancel_status;                 /* byte 68 */
  uint8_t reserved_10[10];               /* bytes 69 to 78 */
} CancelOrderResponse;

/* any Cancel Order Response at all: every byte one the checker chooses */
static void any_cancel_order_response(CancelOrderResponse *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->cancel_status = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Cancel Order Response to the wire: 79 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_response(const CancelOrderResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->original_client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->cancel_status;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Cancel Order Response off the wire: 79 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_response(CancelOrderResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->cancel_status = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Response is what was written, byte for byte */
static void equal_cancel_order_response(const CancelOrderResponse *read, const CancelOrderResponse *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->original_client_order_id[i] == written->original_client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->cancel_status == written->cancel_status);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Cancel Order Response: written and read back, then read and written back */
static void check_cancel_order_response(void) {
  CancelOrderResponse sent;
  CancelOrderResponse got;
  uint8_t wire[79];
  uint8_t again[79];

  any_cancel_order_response(&sent);
  assert(encode_cancel_order_response(&sent, wire, 0) == 79);
  assert(decode_cancel_order_response(&got, wire, 0) == 79);
  equal_cancel_order_response(&got, &sent);

  for (size_t i = 0; i < 79; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_response(&got, wire, 0) == 79);
  assert(encode_cancel_order_response(&got, again, 0) == 79);
  for (size_t i = 0; i < 79; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order By Exchange Order Id Response Message: 59 bytes ------------ */

/* Cancel Order by Exchange Order ID Response */
typedef struct {
  uint8_t matching_engine_time[8];             /* bytes 0 to 7 */
  uint8_t mpid[4];                             /* bytes 8 to 11 */
  uint8_t client_order_id[20];                 /* bytes 12 to 31 */
  uint8_t symbol_id[4];                        /* bytes 32 to 35 */
  uint8_t order_id[8];                         /* bytes 36 to 43 */
  uint8_t leaves_qty[4];                       /* bytes 44 to 47 */
  uint8_t cancel_by_exchange_order_id_status;  /* byte 48 */
  uint8_t reserved_10[10];                     /* bytes 49 to 58 */
} CancelOrderByExchangeOrderIdResponseMessage;

/* any Cancel Order By Exchange Order Id Response Message at all: every byte one the checker chooses */
static void any_cancel_order_by_exchange_order_id_response_message(CancelOrderByExchangeOrderIdResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->cancel_by_exchange_order_id_status = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Cancel Order By Exchange Order Id Response Message to the wire: 59 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_by_exchange_order_id_response_message(const CancelOrderByExchangeOrderIdResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->cancel_by_exchange_order_id_status;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Cancel Order By Exchange Order Id Response Message off the wire: 59 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_by_exchange_order_id_response_message(CancelOrderByExchangeOrderIdResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->cancel_by_exchange_order_id_status = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order By Exchange Order Id Response Message is what was written, byte for byte */
static void equal_cancel_order_by_exchange_order_id_response_message(const CancelOrderByExchangeOrderIdResponseMessage *read, const CancelOrderByExchangeOrderIdResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->cancel_by_exchange_order_id_status == written->cancel_by_exchange_order_id_status);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Cancel Order By Exchange Order Id Response Message: written and read back, then read and written back */
static void check_cancel_order_by_exchange_order_id_response_message(void) {
  CancelOrderByExchangeOrderIdResponseMessage sent;
  CancelOrderByExchangeOrderIdResponseMessage got;
  uint8_t wire[59];
  uint8_t again[59];

  any_cancel_order_by_exchange_order_id_response_message(&sent);
  assert(encode_cancel_order_by_exchange_order_id_response_message(&sent, wire, 0) == 59);
  assert(decode_cancel_order_by_exchange_order_id_response_message(&got, wire, 0) == 59);
  equal_cancel_order_by_exchange_order_id_response_message(&got, &sent);

  for (size_t i = 0; i < 59; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_by_exchange_order_id_response_message(&got, wire, 0) == 59);
  assert(encode_cancel_order_by_exchange_order_id_response_message(&got, again, 0) == 59);
  for (size_t i = 0; i < 59; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Notification: 26 bytes ------------------------------------- */

/* This message is published whenever system state events take place */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t meo_version[8];           /* bytes 8 to 15 */
  uint8_t session_id;               /* byte 16 */
  uint8_t system_status;            /* byte 17 */
  uint8_t reserved_8[8];            /* bytes 18 to 25 */
} SystemStateNotification;

/* any System State Notification at all: every byte one the checker chooses */
static void any_system_state_notification(SystemStateNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->meo_version[i] = arbitrary(); }
  record->session_id = arbitrary();
  record->system_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* System State Notification to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_system_state_notification(const SystemStateNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->meo_version[i]; }
  wire[at++] = record->session_id;
  wire[at++] = record->system_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* System State Notification off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_system_state_notification(SystemStateNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->meo_version[i] = wire[at++]; }
  record->session_id = wire[at++];
  record->system_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of System State Notification is what was written, byte for byte */
static void equal_system_state_notification(const SystemStateNotification *read, const SystemStateNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->meo_version[i] == written->meo_version[i]); }
  assert(read->session_id == written->session_id);
  assert(read->system_status == written->system_status);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* System State Notification: written and read back, then read and written back */
static void check_system_state_notification(void) {
  SystemStateNotification sent;
  SystemStateNotification got;
  uint8_t wire[26];
  uint8_t again[26];

  any_system_state_notification(&sent);
  assert(encode_system_state_notification(&sent, wire, 0) == 26);
  assert(decode_system_state_notification(&got, wire, 0) == 26);
  equal_system_state_notification(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_system_state_notification(&got, wire, 0) == 26);
  assert(encode_system_state_notification(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Reduce Size Order Notification: 71 bytes ------------------------- */

/* This is the message format that will be used when Cancel Order Request is accepted by MIAX Pearl Equities or when unsolicited order cancels or order size reductions are to be notified to firms */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t mpid[4];                  /* bytes 8 to 11 */
  uint8_t client_order_id[20];      /* bytes 12 to 31 */
  uint8_t symbol_id[4];             /* bytes 32 to 35 */
  uint8_t order_id[8];              /* bytes 36 to 43 */
  uint8_t leaves_qty[4];            /* bytes 44 to 47 */
  uint8_t cancel_reason;            /* byte 48 */
  uint8_t last_price[8];            /* bytes 49 to 56 */
  uint8_t last_size[4];             /* bytes 57 to 60 */
  uint8_t pending_cancel_status;    /* byte 61 */
  uint8_t pending_reject_reason;    /* byte 62 */
  uint8_t reserved_8[8];            /* bytes 63 to 70 */
} CancelReduceSizeOrderNotification;

/* any Cancel Reduce Size Order Notification at all: every byte one the checker chooses */
static void any_cancel_reduce_size_order_notification(CancelReduceSizeOrderNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = arbitrary(); }
  record->pending_cancel_status = arbitrary();
  record->pending_reject_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Cancel Reduce Size Order Notification to the wire: 71 bytes from at, returning where the next byte goes */
static size_t encode_cancel_reduce_size_order_notification(const CancelReduceSizeOrderNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->cancel_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_size[i]; }
  wire[at++] = record->pending_cancel_status;
  wire[at++] = record->pending_reject_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Cancel Reduce Size Order Notification off the wire: 71 bytes from at, returning where the next byte lies */
static size_t decode_cancel_reduce_size_order_notification(CancelReduceSizeOrderNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->cancel_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = wire[at++]; }
  record->pending_cancel_status = wire[at++];
  record->pending_reject_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Reduce Size Order Notification is what was written, byte for byte */
static void equal_cancel_reduce_size_order_notification(const CancelReduceSizeOrderNotification *read, const CancelReduceSizeOrderNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->cancel_reason == written->cancel_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_size[i] == written->last_size[i]); }
  assert(read->pending_cancel_status == written->pending_cancel_status);
  assert(read->pending_reject_reason == written->pending_reject_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Cancel Reduce Size Order Notification: written and read back, then read and written back */
static void check_cancel_reduce_size_order_notification(void) {
  CancelReduceSizeOrderNotification sent;
  CancelReduceSizeOrderNotification got;
  uint8_t wire[71];
  uint8_t again[71];

  any_cancel_reduce_size_order_notification(&sent);
  assert(encode_cancel_reduce_size_order_notification(&sent, wire, 0) == 71);
  assert(decode_cancel_reduce_size_order_notification(&got, wire, 0) == 71);
  equal_cancel_reduce_size_order_notification(&got, &sent);

  for (size_t i = 0; i < 71; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_reduce_size_order_notification(&got, wire, 0) == 71);
  assert(encode_cancel_reduce_size_order_notification(&got, again, 0) == 71);
  for (size_t i = 0; i < 71; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Price Update Notification: 38 bytes ------------------------------- */

/* This is the message format that will be used to notify firms about order reprices */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[4];             /* bytes 8 to 11 */
  uint8_t order_id[8];              /* bytes 12 to 19 */
  uint8_t working_price[8];         /* bytes 20 to 27 */
  uint8_t nbbo_indicator;           /* byte 28 */
  uint8_t reserved_9[9];            /* bytes 29 to 37 */
} OrderPriceUpdateNotification;

/* any Order Price Update Notification at all: every byte one the checker chooses */
static void any_order_price_update_notification(OrderPriceUpdateNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = arbitrary(); }
  record->nbbo_indicator = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
}

/* Order Price Update Notification to the wire: 38 bytes from at, returning where the next byte goes */
static size_t encode_order_price_update_notification(const OrderPriceUpdateNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->working_price[i]; }
  wire[at++] = record->nbbo_indicator;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }

  return at;
}

/* Order Price Update Notification off the wire: 38 bytes from at, returning where the next byte lies */
static size_t decode_order_price_update_notification(OrderPriceUpdateNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->working_price[i] = wire[at++]; }
  record->nbbo_indicator = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }

  return at;
}

/* what was read of Order Price Update Notification is what was written, byte for byte */
static void equal_order_price_update_notification(const OrderPriceUpdateNotification *read, const OrderPriceUpdateNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->working_price[i] == written->working_price[i]); }
  assert(read->nbbo_indicator == written->nbbo_indicator);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
}

/* Order Price Update Notification: written and read back, then read and written back */
static void check_order_price_update_notification(void) {
  OrderPriceUpdateNotification sent;
  OrderPriceUpdateNotification got;
  uint8_t wire[38];
  uint8_t again[38];

  any_order_price_update_notification(&sent);
  assert(encode_order_price_update_notification(&sent, wire, 0) == 38);
  assert(decode_order_price_update_notification(&got, wire, 0) == 38);
  equal_order_price_update_notification(&got, &sent);

  for (size_t i = 0; i < 38; i++) { wire[i] = arbitrary(); }
  assert(decode_order_price_update_notification(&got, wire, 0) == 38);
  assert(encode_order_price_update_notification(&got, again, 0) == 38);
  for (size_t i = 0; i < 38; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reserve Order Replenishment Notification: 42 bytes ---------------------- */

/* This is the message format that will be used to notify firms of their Reserve order replenishment events */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t symbol_id[4];             /* bytes 8 to 11 */
  uint8_t order_id[8];              /* bytes 12 to 19 */
  uint8_t secondary_order_id[8];    /* bytes 20 to 27 */
  uint8_t display_qty[4];           /* bytes 28 to 31 */
  uint8_t reserved_10[10];          /* bytes 32 to 41 */
} ReserveOrderReplenishmentNotification;

/* any Reserve Order Replenishment Notification at all: every byte one the checker chooses */
static void any_reserve_order_replenishment_notification(ReserveOrderReplenishmentNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Reserve Order Replenishment Notification to the wire: 42 bytes from at, returning where the next byte goes */
static size_t encode_reserve_order_replenishment_notification(const ReserveOrderReplenishmentNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Reserve Order Replenishment Notification off the wire: 42 bytes from at, returning where the next byte lies */
static size_t decode_reserve_order_replenishment_notification(ReserveOrderReplenishmentNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Reserve Order Replenishment Notification is what was written, byte for byte */
static void equal_reserve_order_replenishment_notification(const ReserveOrderReplenishmentNotification *read, const ReserveOrderReplenishmentNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Reserve Order Replenishment Notification: written and read back, then read and written back */
static void check_reserve_order_replenishment_notification(void) {
  ReserveOrderReplenishmentNotification sent;
  ReserveOrderReplenishmentNotification got;
  uint8_t wire[42];
  uint8_t again[42];

  any_reserve_order_replenishment_notification(&sent);
  assert(encode_reserve_order_replenishment_notification(&sent, wire, 0) == 42);
  assert(decode_reserve_order_replenishment_notification(&got, wire, 0) == 42);
  equal_reserve_order_replenishment_notification(&got, &sent);

  for (size_t i = 0; i < 42; i++) { wire[i] = arbitrary(); }
  assert(decode_reserve_order_replenishment_notification(&got, wire, 0) == 42);
  assert(encode_reserve_order_replenishment_notification(&got, again, 0) == 42);
  for (size_t i = 0; i < 42; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Request: 66 bytes ------------------------------------------ */

/* Firms can use this format to send a cancel request for a resting order */
typedef struct {
  uint8_t reserved_8[8];                 /* bytes 0 to 7 */
  uint8_t mpid[4];                       /* bytes 8 to 11 */
  uint8_t client_order_id[20];           /* bytes 12 to 31 */
  uint8_t original_client_order_id[20];  /* bytes 32 to 51 */
  uint8_t symbol_id[4];                  /* bytes 52 to 55 */
  uint8_t reserved_10[10];               /* bytes 56 to 65 */
} CancelOrderRequest;

/* any Cancel Order Request at all: every byte one the checker chooses */
static void any_cancel_order_request(CancelOrderRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Cancel Order Request to the wire: 66 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_request(const CancelOrderRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->original_client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Cancel Order Request off the wire: 66 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_request(CancelOrderRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Request is what was written, byte for byte */
static void equal_cancel_order_request(const CancelOrderRequest *read, const CancelOrderRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->original_client_order_id[i] == written->original_client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Cancel Order Request: written and read back, then read and written back */
static void check_cancel_order_request(void) {
  CancelOrderRequest sent;
  CancelOrderRequest got;
  uint8_t wire[66];
  uint8_t again[66];

  any_cancel_order_request(&sent);
  assert(encode_cancel_order_request(&sent, wire, 0) == 66);
  assert(decode_cancel_order_request(&got, wire, 0) == 66);
  equal_cancel_order_request(&got, &sent);

  for (size_t i = 0; i < 66; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_request(&got, wire, 0) == 66);
  assert(encode_cancel_order_request(&got, again, 0) == 66);
  for (size_t i = 0; i < 66; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order By Exchange Order Id Request: 54 bytes --------------------- */

/* Firms can use this format to send a cancel request for a resting order using Exchange assigned Order ID */
typedef struct {
  uint8_t reserved_8[8];        /* bytes 0 to 7 */
  uint8_t mpid[4];              /* bytes 8 to 11 */
  uint8_t client_order_id[20];  /* bytes 12 to 31 */
  uint8_t order_id[8];          /* bytes 32 to 39 */
  uint8_t symbol_id[4];         /* bytes 40 to 43 */
  uint8_t reserved_10[10];      /* bytes 44 to 53 */
} CancelOrderByExchangeOrderIdRequest;

/* any Cancel Order By Exchange Order Id Request at all: every byte one the checker chooses */
static void any_cancel_order_by_exchange_order_id_request(CancelOrderByExchangeOrderIdRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Cancel Order By Exchange Order Id Request to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_by_exchange_order_id_request(const CancelOrderByExchangeOrderIdRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->symbol_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Cancel Order By Exchange Order Id Request off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_by_exchange_order_id_request(CancelOrderByExchangeOrderIdRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->symbol_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order By Exchange Order Id Request is what was written, byte for byte */
static void equal_cancel_order_by_exchange_order_id_request(const CancelOrderByExchangeOrderIdRequest *read, const CancelOrderByExchangeOrderIdRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->symbol_id[i] == written->symbol_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Cancel Order By Exchange Order Id Request: written and read back, then read and written back */
static void check_cancel_order_by_exchange_order_id_request(void) {
  CancelOrderByExchangeOrderIdRequest sent;
  CancelOrderByExchangeOrderIdRequest got;
  uint8_t wire[54];
  uint8_t again[54];

  any_cancel_order_by_exchange_order_id_request(&sent);
  assert(encode_cancel_order_by_exchange_order_id_request(&sent, wire, 0) == 54);
  assert(decode_cancel_order_by_exchange_order_id_request(&got, wire, 0) == 54);
  equal_cancel_order_by_exchange_order_id_request(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_by_exchange_order_id_request(&got, wire, 0) == 54);
  assert(encode_cancel_order_by_exchange_order_id_request(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Request: 44 bytes ------------------------------------------- */

/* Firms can use this message format to request the cancellation of all orders for an MPID */
typedef struct {
  uint8_t reserved_8[8];        /* bytes 0 to 7 */
  uint8_t mpid[4];              /* bytes 8 to 11 */
  uint8_t client_order_id[20];  /* bytes 12 to 31 */
  uint8_t scope;                /* byte 32 */
  uint8_t action;               /* byte 33 */
  uint8_t purge_group;          /* byte 34 */
  uint8_t reserved_9[9];        /* bytes 35 to 43 */
} MassCancelRequest;

/* any Mass Cancel Request at all: every byte one the checker chooses */
static void any_mass_cancel_request(MassCancelRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->scope = arbitrary();
  record->action = arbitrary();
  record->purge_group = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
}

/* Mass Cancel Request to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_request(const MassCancelRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->mpid[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->scope;
  wire[at++] = record->action;
  wire[at++] = record->purge_group;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }

  return at;
}

/* Mass Cancel Request off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_request(MassCancelRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->mpid[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->scope = wire[at++];
  record->action = wire[at++];
  record->purge_group = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Request is what was written, byte for byte */
static void equal_mass_cancel_request(const MassCancelRequest *read, const MassCancelRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->mpid[i] == written->mpid[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->scope == written->scope);
  assert(read->action == written->action);
  assert(read->purge_group == written->purge_group);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
}

/* Mass Cancel Request: written and read back, then read and written back */
static void check_mass_cancel_request(void) {
  MassCancelRequest sent;
  MassCancelRequest got;
  uint8_t wire[44];
  uint8_t again[44];

  any_mass_cancel_request(&sent);
  assert(encode_mass_cancel_request(&sent, wire, 0) == 44);
  assert(decode_mass_cancel_request(&got, wire, 0) == 44);
  equal_mass_cancel_request(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_request(&got, wire, 0) == 44);
  assert(encode_mass_cancel_request(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Synchronization Complete: 1 byte ---------------------------------------- */

/* The ESesM server sends a Synchronization complete packet when it is done replaying all the old packets and is ready to start sending new packets from the Matching Engine */
typedef struct {
  uint8_t matching_engine_id;  /* byte 0 */
} SynchronizationComplete;

/* any Synchronization Complete at all: every byte one the checker chooses */
static void any_synchronization_complete(SynchronizationComplete *record) {
  record->matching_engine_id = arbitrary();
}

/* Synchronization Complete to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_synchronization_complete(const SynchronizationComplete *record, uint8_t *wire, size_t at) {
  wire[at++] = record->matching_engine_id;

  return at;
}

/* Synchronization Complete off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_synchronization_complete(SynchronizationComplete *record, const uint8_t *wire, size_t at) {
  record->matching_engine_id = wire[at++];

  return at;
}

/* what was read of Synchronization Complete is what was written, byte for byte */
static void equal_synchronization_complete(const SynchronizationComplete *read, const SynchronizationComplete *written) {
  assert(read->matching_engine_id == written->matching_engine_id);
}

/* Synchronization Complete: written and read back, then read and written back */
static void check_synchronization_complete(void) {
  SynchronizationComplete sent;
  SynchronizationComplete got;
  uint8_t wire[1];
  uint8_t again[1];

  any_synchronization_complete(&sent);
  assert(encode_synchronization_complete(&sent, wire, 0) == 1);
  assert(decode_synchronization_complete(&got, wire, 0) == 1);
  equal_synchronization_complete(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_synchronization_complete(&got, wire, 0) == 1);
  assert(encode_synchronization_complete(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request: 16 bytes ---------------------------------------- */

/* The ESesM client uses this packet to request a retransmission server to retransmit a range of packets */
typedef struct {
  uint8_t start_sequence_number[8];  /* bytes 0 to 7 */
  uint8_t end_sequence_number[8];    /* bytes 8 to 15 */
} RetransmissionRequest;

/* any Retransmission Request at all: every byte one the checker chooses */
static void any_retransmission_request(RetransmissionRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->start_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->end_sequence_number[i] = arbitrary(); }
}

/* Retransmission Request to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_retransmission_request(const RetransmissionRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->start_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->end_sequence_number[i]; }

  return at;
}

/* Retransmission Request off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_retransmission_request(RetransmissionRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->start_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->end_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Retransmission Request is what was written, byte for byte */
static void equal_retransmission_request(const RetransmissionRequest *read, const RetransmissionRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->start_sequence_number[i] == written->start_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->end_sequence_number[i] == written->end_sequence_number[i]); }
}

/* Retransmission Request: written and read back, then read and written back */
static void check_retransmission_request(void) {
  RetransmissionRequest sent;
  RetransmissionRequest got;
  uint8_t wire[16];
  uint8_t again[16];

  any_retransmission_request(&sent);
  assert(encode_retransmission_request(&sent, wire, 0) == 16);
  assert(decode_retransmission_request(&got, wire, 0) == 16);
  equal_retransmission_request(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_retransmission_request(&got, wire, 0) == 16);
  assert(encode_retransmission_request(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Session Update: 2 bytes ----------------------------------------- */

/* The ESesM server sends a Trading Session Update packet to inform the client that a new trading session is starting on the specified Matching Engine */
typedef struct {
  uint8_t matching_engine_id;  /* byte 0 */
  uint8_t trading_session_id;  /* byte 1 */
} TradingSessionUpdate;

/* any Trading Session Update at all: every byte one the checker chooses */
static void any_trading_session_update(TradingSessionUpdate *record) {
  record->matching_engine_id = arbitrary();
  record->trading_session_id = arbitrary();
}

/* Trading Session Update to the wire: 2 bytes from at, returning where the next byte goes */
static size_t encode_trading_session_update(const TradingSessionUpdate *record, uint8_t *wire, size_t at) {
  wire[at++] = record->matching_engine_id;
  wire[at++] = record->trading_session_id;

  return at;
}

/* Trading Session Update off the wire: 2 bytes from at, returning where the next byte lies */
static size_t decode_trading_session_update(TradingSessionUpdate *record, const uint8_t *wire, size_t at) {
  record->matching_engine_id = wire[at++];
  record->trading_session_id = wire[at++];

  return at;
}

/* what was read of Trading Session Update is what was written, byte for byte */
static void equal_trading_session_update(const TradingSessionUpdate *read, const TradingSessionUpdate *written) {
  assert(read->matching_engine_id == written->matching_engine_id);
  assert(read->trading_session_id == written->trading_session_id);
}

/* Trading Session Update: written and read back, then read and written back */
static void check_trading_session_update(void) {
  TradingSessionUpdate sent;
  TradingSessionUpdate got;
  uint8_t wire[2];
  uint8_t again[2];

  any_trading_session_update(&sent);
  assert(encode_trading_session_update(&sent, wire, 0) == 2);
  assert(decode_trading_session_update(&got, wire, 0) == 2);
  equal_trading_session_update(&got, &sent);

  for (size_t i = 0; i < 2; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_session_update(&got, wire, 0) == 2);
  assert(encode_trading_session_update(&got, again, 0) == 2);
  for (size_t i = 0; i < 2; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_esesm_packet_header();
  check_symbol_update_message();
  check_new_order_response_message();
  check_modify_order_response();
  check_cancel_order_response();
  check_cancel_order_by_exchange_order_id_response_message();
  check_system_state_notification();
  check_cancel_reduce_size_order_notification();
  check_order_price_update_notification();
  check_reserve_order_replenishment_notification();
  check_cancel_order_request();
  check_cancel_order_by_exchange_order_id_request();
  check_mass_cancel_request();
  check_synchronization_complete();
  check_retransmission_request();
  check_trading_session_update();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
