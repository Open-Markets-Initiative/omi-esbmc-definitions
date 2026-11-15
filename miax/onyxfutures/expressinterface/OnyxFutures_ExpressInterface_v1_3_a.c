// miax/onyxfutures/expressinterface/OnyxFutures_ExpressInterface_v1_3_a.c
/*
 * Miami International Holdings Express Interface
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

/* ---- Sesm Packet Header: 3 bytes --------------------------------------------- */

/* SesM packet header */
typedef struct {
  uint8_t sesm_packet_length[2];  /* bytes 0 to 1 */
  uint8_t sesm_packet_type;       /* byte 2 */
} SesmPacketHeader;

/* any Sesm Packet Header at all: every byte one the checker chooses */
static void any_sesm_packet_header(SesmPacketHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->sesm_packet_length[i] = arbitrary(); }
  record->sesm_packet_type = arbitrary();
}

/* Sesm Packet Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_sesm_packet_header(const SesmPacketHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->sesm_packet_length[i]; }
  wire[at++] = record->sesm_packet_type;

  return at;
}

/* Sesm Packet Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_sesm_packet_header(SesmPacketHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->sesm_packet_length[i] = wire[at++]; }
  record->sesm_packet_type = wire[at++];

  return at;
}

/* what was read of Sesm Packet Header is what was written, byte for byte */
static void equal_sesm_packet_header(const SesmPacketHeader *read, const SesmPacketHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->sesm_packet_length[i] == written->sesm_packet_length[i]); }
  assert(read->sesm_packet_type == written->sesm_packet_type);
}

/* Sesm Packet Header: written and read back, then read and written back */
static void check_sesm_packet_header(void) {
  SesmPacketHeader sent;
  SesmPacketHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_sesm_packet_header(&sent);
  assert(encode_sesm_packet_header(&sent, wire, 0) == 3);
  assert(decode_sesm_packet_header(&got, wire, 0) == 3);
  equal_sesm_packet_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_sesm_packet_header(&got, wire, 0) == 3);
  assert(encode_sesm_packet_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- New Order Response Message: 56 bytes ------------------------------------ */

/* An acknowledgement for a New Order Request accepted by MIAX Futures Onyx */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t mp_id[5];                 /* bytes 8 to 12 */
  uint8_t client_order_id[20];      /* bytes 13 to 32 */
  uint8_t instrument_id[4];         /* bytes 33 to 36 */
  uint8_t order_id[8];              /* bytes 37 to 44 */
  uint8_t order_status;             /* byte 45 */
  uint8_t reserved_10[10];          /* bytes 46 to 55 */
} NewOrderResponseMessage;

/* any New Order Response Message at all: every byte one the checker chooses */
static void any_new_order_response_message(NewOrderResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->order_status = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* New Order Response Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_new_order_response_message(const NewOrderResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mp_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->order_status;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* New Order Response Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_new_order_response_message(NewOrderResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->order_status = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of New Order Response Message is what was written, byte for byte */
static void equal_new_order_response_message(const NewOrderResponseMessage *read, const NewOrderResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mp_id[i] == written->mp_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->order_status == written->order_status);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* New Order Response Message: written and read back, then read and written back */
static void check_new_order_response_message(void) {
  NewOrderResponseMessage sent;
  NewOrderResponseMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_new_order_response_message(&sent);
  assert(encode_new_order_response_message(&sent, wire, 0) == 56);
  assert(decode_new_order_response_message(&got, wire, 0) == 56);
  equal_new_order_response_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_new_order_response_message(&got, wire, 0) == 56);
  assert(encode_new_order_response_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Modify Order Response: 80 bytes ----------------------------------------- */

/* Acknowledgement for a Modify Order Request accepted by MIAX Futures Onyx */
typedef struct {
  uint8_t matching_engine_time[8];       /* bytes 0 to 7 */
  uint8_t mp_id[5];                      /* bytes 8 to 12 */
  uint8_t client_order_id[20];           /* bytes 13 to 32 */
  uint8_t original_client_order_id[20];  /* bytes 33 to 52 */
  uint8_t instrument_id[4];              /* bytes 53 to 56 */
  uint8_t order_id[8];                   /* bytes 57 to 64 */
  uint8_t leaves_qty[4];                 /* bytes 65 to 68 */
  uint8_t modify_status;                 /* byte 69 */
  uint8_t reserved_10[10];               /* bytes 70 to 79 */
} ModifyOrderResponse;

/* any Modify Order Response at all: every byte one the checker chooses */
static void any_modify_order_response(ModifyOrderResponse *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->modify_status = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Modify Order Response to the wire: 80 bytes from at, returning where the next byte goes */
static size_t encode_modify_order_response(const ModifyOrderResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mp_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->original_client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->modify_status;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Modify Order Response off the wire: 80 bytes from at, returning where the next byte lies */
static size_t decode_modify_order_response(ModifyOrderResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->modify_status = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Modify Order Response is what was written, byte for byte */
static void equal_modify_order_response(const ModifyOrderResponse *read, const ModifyOrderResponse *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mp_id[i] == written->mp_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->original_client_order_id[i] == written->original_client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->modify_status == written->modify_status);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Modify Order Response: written and read back, then read and written back */
static void check_modify_order_response(void) {
  ModifyOrderResponse sent;
  ModifyOrderResponse got;
  uint8_t wire[80];
  uint8_t again[80];

  any_modify_order_response(&sent);
  assert(encode_modify_order_response(&sent, wire, 0) == 80);
  assert(decode_modify_order_response(&got, wire, 0) == 80);
  equal_modify_order_response(&got, &sent);

  for (size_t i = 0; i < 80; i++) { wire[i] = arbitrary(); }
  assert(decode_modify_order_response(&got, wire, 0) == 80);
  assert(encode_modify_order_response(&got, again, 0) == 80);
  for (size_t i = 0; i < 80; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Response: 76 bytes ----------------------------------------- */

/* provides response to an Order Cancel Request */
typedef struct {
  uint8_t matching_engine_time[8];       /* bytes 0 to 7 */
  uint8_t mp_id[5];                      /* bytes 8 to 12 */
  uint8_t client_order_id[20];           /* bytes 13 to 32 */
  uint8_t original_client_order_id[20];  /* bytes 33 to 52 */
  uint8_t instrument_id[4];              /* bytes 53 to 56 */
  uint8_t order_id[8];                   /* bytes 57 to 64 */
  uint8_t cancel_status;                 /* byte 65 */
  uint8_t reserved_10[10];               /* bytes 66 to 75 */
} CancelOrderResponse;

/* any Cancel Order Response at all: every byte one the checker chooses */
static void any_cancel_order_response(CancelOrderResponse *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->cancel_status = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Cancel Order Response to the wire: 76 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_response(const CancelOrderResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mp_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->original_client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->cancel_status;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Cancel Order Response off the wire: 76 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_response(CancelOrderResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->cancel_status = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Response is what was written, byte for byte */
static void equal_cancel_order_response(const CancelOrderResponse *read, const CancelOrderResponse *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mp_id[i] == written->mp_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->original_client_order_id[i] == written->original_client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->cancel_status == written->cancel_status);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Cancel Order Response: written and read back, then read and written back */
static void check_cancel_order_response(void) {
  CancelOrderResponse sent;
  CancelOrderResponse got;
  uint8_t wire[76];
  uint8_t again[76];

  any_cancel_order_response(&sent);
  assert(encode_cancel_order_response(&sent, wire, 0) == 76);
  assert(decode_cancel_order_response(&got, wire, 0) == 76);
  equal_cancel_order_response(&got, &sent);

  for (size_t i = 0; i < 76; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_response(&got, wire, 0) == 76);
  assert(encode_cancel_order_response(&got, again, 0) == 76);
  for (size_t i = 0; i < 76; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Response: 44 bytes ------------------------------------------ */

/* used to inform the Firm about the status of their previous Mass Cancel Request */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t mp_id[5];                 /* bytes 8 to 12 */
  uint8_t client_order_id[20];      /* bytes 13 to 32 */
  uint8_t mass_cancel_status;       /* byte 33 */
  uint8_t reserved_10[10];          /* bytes 34 to 43 */
} MassCancelResponse;

/* any Mass Cancel Response at all: every byte one the checker chooses */
static void any_mass_cancel_response(MassCancelResponse *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->mass_cancel_status = arbitrary();
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Mass Cancel Response to the wire: 44 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_response(const MassCancelResponse *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mp_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->mass_cancel_status;
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Mass Cancel Response off the wire: 44 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_response(MassCancelResponse *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->mass_cancel_status = wire[at++];
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Response is what was written, byte for byte */
static void equal_mass_cancel_response(const MassCancelResponse *read, const MassCancelResponse *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mp_id[i] == written->mp_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->mass_cancel_status == written->mass_cancel_status);
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Mass Cancel Response: written and read back, then read and written back */
static void check_mass_cancel_response(void) {
  MassCancelResponse sent;
  MassCancelResponse got;
  uint8_t wire[44];
  uint8_t again[44];

  any_mass_cancel_response(&sent);
  assert(encode_mass_cancel_response(&sent, wire, 0) == 44);
  assert(decode_mass_cancel_response(&got, wire, 0) == 44);
  equal_mass_cancel_response(&got, &sent);

  for (size_t i = 0; i < 44; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_response(&got, wire, 0) == 44);
  assert(encode_mass_cancel_response(&got, again, 0) == 44);
  for (size_t i = 0; i < 44; i++) { assert(again[i] == wire[i]); }
}

/* ---- Strategy Creation Response Message: 54 bytes ---------------------------- */

/* response to the Strategy Creation Request */
typedef struct {
  uint8_t matching_engine_time[8];   /* bytes 0 to 7 */
  uint8_t mp_id[5];                  /* bytes 8 to 12 */
  uint8_t client_order_id[20];       /* bytes 13 to 32 */
  uint8_t instrument_id[4];          /* bytes 33 to 36 */
  uint8_t strategy_creation_status;  /* byte 37 */
  uint8_t reserved_16[16];           /* bytes 38 to 53 */
} StrategyCreationResponseMessage;

/* any Strategy Creation Response Message at all: every byte one the checker chooses */
static void any_strategy_creation_response_message(StrategyCreationResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  record->strategy_creation_status = arbitrary();
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Strategy Creation Response Message to the wire: 54 bytes from at, returning where the next byte goes */
static size_t encode_strategy_creation_response_message(const StrategyCreationResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mp_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  wire[at++] = record->strategy_creation_status;
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Strategy Creation Response Message off the wire: 54 bytes from at, returning where the next byte lies */
static size_t decode_strategy_creation_response_message(StrategyCreationResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  record->strategy_creation_status = wire[at++];
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Strategy Creation Response Message is what was written, byte for byte */
static void equal_strategy_creation_response_message(const StrategyCreationResponseMessage *read, const StrategyCreationResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mp_id[i] == written->mp_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  assert(read->strategy_creation_status == written->strategy_creation_status);
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Strategy Creation Response Message: written and read back, then read and written back */
static void check_strategy_creation_response_message(void) {
  StrategyCreationResponseMessage sent;
  StrategyCreationResponseMessage got;
  uint8_t wire[54];
  uint8_t again[54];

  any_strategy_creation_response_message(&sent);
  assert(encode_strategy_creation_response_message(&sent, wire, 0) == 54);
  assert(decode_strategy_creation_response_message(&got, wire, 0) == 54);
  equal_strategy_creation_response_message(&got, &sent);

  for (size_t i = 0; i < 54; i++) { wire[i] = arbitrary(); }
  assert(decode_strategy_creation_response_message(&got, wire, 0) == 54);
  assert(encode_strategy_creation_response_message(&got, again, 0) == 54);
  for (size_t i = 0; i < 54; i++) { assert(again[i] == wire[i]); }
}

/* ---- System State Notification Message: 26 bytes ----------------------------- */

/* published whenever system state events take place */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t version[8];               /* bytes 8 to 15 */
  uint8_t session_id;               /* byte 16 */
  uint8_t system_status;            /* byte 17 */
  uint8_t reserved_8[8];            /* bytes 18 to 25 */
} SystemStateNotificationMessage;

/* any System State Notification Message at all: every byte one the checker chooses */
static void any_system_state_notification_message(SystemStateNotificationMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->version[i] = arbitrary(); }
  record->session_id = arbitrary();
  record->system_status = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* System State Notification Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_system_state_notification_message(const SystemStateNotificationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->version[i]; }
  wire[at++] = record->session_id;
  wire[at++] = record->system_status;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* System State Notification Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_system_state_notification_message(SystemStateNotificationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->version[i] = wire[at++]; }
  record->session_id = wire[at++];
  record->system_status = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of System State Notification Message is what was written, byte for byte */
static void equal_system_state_notification_message(const SystemStateNotificationMessage *read, const SystemStateNotificationMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->version[i] == written->version[i]); }
  assert(read->session_id == written->session_id);
  assert(read->system_status == written->system_status);
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* System State Notification Message: written and read back, then read and written back */
static void check_system_state_notification_message(void) {
  SystemStateNotificationMessage sent;
  SystemStateNotificationMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_system_state_notification_message(&sent);
  assert(encode_system_state_notification_message(&sent, wire, 0) == 26);
  assert(decode_system_state_notification_message(&got, wire, 0) == 26);
  equal_system_state_notification_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_system_state_notification_message(&got, wire, 0) == 26);
  assert(encode_system_state_notification_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Reserve Order Replenishment Notification: 48 bytes ---------------------- */

/* published to notify firms of their Reserve Order replenishment events */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t instrument_id[4];         /* bytes 8 to 11 */
  uint8_t order_id[8];              /* bytes 12 to 19 */
  uint8_t secondary_order_id[8];    /* bytes 20 to 27 */
  uint8_t display_qty[4];           /* bytes 28 to 31 */
  uint8_t reserved_16[16];          /* bytes 32 to 47 */
} ReserveOrderReplenishmentNotification;

/* any Reserve Order Replenishment Notification at all: every byte one the checker chooses */
static void any_reserve_order_replenishment_notification(ReserveOrderReplenishmentNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = arbitrary(); }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = arbitrary(); }
}

/* Reserve Order Replenishment Notification to the wire: 48 bytes from at, returning where the next byte goes */
static size_t encode_reserve_order_replenishment_notification(const ReserveOrderReplenishmentNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->secondary_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->display_qty[i]; }
  for (size_t i = 0; i < 16; i++) { wire[at++] = record->reserved_16[i]; }

  return at;
}

/* Reserve Order Replenishment Notification off the wire: 48 bytes from at, returning where the next byte lies */
static size_t decode_reserve_order_replenishment_notification(ReserveOrderReplenishmentNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->secondary_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->display_qty[i] = wire[at++]; }
  for (size_t i = 0; i < 16; i++) { record->reserved_16[i] = wire[at++]; }

  return at;
}

/* what was read of Reserve Order Replenishment Notification is what was written, byte for byte */
static void equal_reserve_order_replenishment_notification(const ReserveOrderReplenishmentNotification *read, const ReserveOrderReplenishmentNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->secondary_order_id[i] == written->secondary_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->display_qty[i] == written->display_qty[i]); }
  for (size_t i = 0; i < 16; i++) { assert(read->reserved_16[i] == written->reserved_16[i]); }
}

/* Reserve Order Replenishment Notification: written and read back, then read and written back */
static void check_reserve_order_replenishment_notification(void) {
  ReserveOrderReplenishmentNotification sent;
  ReserveOrderReplenishmentNotification got;
  uint8_t wire[48];
  uint8_t again[48];

  any_reserve_order_replenishment_notification(&sent);
  assert(encode_reserve_order_replenishment_notification(&sent, wire, 0) == 48);
  assert(decode_reserve_order_replenishment_notification(&got, wire, 0) == 48);
  equal_reserve_order_replenishment_notification(&got, &sent);

  for (size_t i = 0; i < 48; i++) { wire[i] = arbitrary(); }
  assert(decode_reserve_order_replenishment_notification(&got, wire, 0) == 48);
  assert(encode_reserve_order_replenishment_notification(&got, again, 0) == 48);
  for (size_t i = 0; i < 48; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Reduce Size Order Notification: 102 bytes ------------------------ */

/* used when Cancel Order Request is accepted by MIAX Futures Onyx or when unsolicited order cancels or order size reductions are to be notified to firms */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t mp_id[5];                 /* bytes 8 to 12 */
  uint8_t operator_id[18];          /* bytes 13 to 30 */
  uint8_t operator_location[6];     /* bytes 31 to 36 */
  uint8_t client_order_id[20];      /* bytes 37 to 56 */
  uint8_t instrument_id[4];         /* bytes 57 to 60 */
  uint8_t order_id[8];              /* bytes 61 to 68 */
  uint8_t client_send_time[8];      /* bytes 69 to 76 */
  uint8_t leaves_qty[4];            /* bytes 77 to 80 */
  uint8_t cancel_reason;            /* byte 81 */
  uint8_t last_price[8];            /* bytes 82 to 89 */
  uint8_t last_size[4];             /* bytes 90 to 93 */
  uint8_t reserved_8[8];            /* bytes 94 to 101 */
} CancelReduceSizeOrderNotification;

/* any Cancel Reduce Size Order Notification at all: every byte one the checker chooses */
static void any_cancel_reduce_size_order_notification(CancelReduceSizeOrderNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->operator_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->operator_location[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Cancel Reduce Size Order Notification to the wire: 102 bytes from at, returning where the next byte goes */
static size_t encode_cancel_reduce_size_order_notification(const CancelReduceSizeOrderNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mp_id[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->operator_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->operator_location[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_send_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->leaves_qty[i]; }
  wire[at++] = record->cancel_reason;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->last_price[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->last_size[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Cancel Reduce Size Order Notification off the wire: 102 bytes from at, returning where the next byte lies */
static size_t decode_cancel_reduce_size_order_notification(CancelReduceSizeOrderNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->operator_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->operator_location[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->leaves_qty[i] = wire[at++]; }
  record->cancel_reason = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->last_price[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->last_size[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Reduce Size Order Notification is what was written, byte for byte */
static void equal_cancel_reduce_size_order_notification(const CancelReduceSizeOrderNotification *read, const CancelReduceSizeOrderNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mp_id[i] == written->mp_id[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->operator_id[i] == written->operator_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->operator_location[i] == written->operator_location[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->client_send_time[i] == written->client_send_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->leaves_qty[i] == written->leaves_qty[i]); }
  assert(read->cancel_reason == written->cancel_reason);
  for (size_t i = 0; i < 8; i++) { assert(read->last_price[i] == written->last_price[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->last_size[i] == written->last_size[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Cancel Reduce Size Order Notification: written and read back, then read and written back */
static void check_cancel_reduce_size_order_notification(void) {
  CancelReduceSizeOrderNotification sent;
  CancelReduceSizeOrderNotification got;
  uint8_t wire[102];
  uint8_t again[102];

  any_cancel_reduce_size_order_notification(&sent);
  assert(encode_cancel_reduce_size_order_notification(&sent, wire, 0) == 102);
  assert(decode_cancel_reduce_size_order_notification(&got, wire, 0) == 102);
  equal_cancel_reduce_size_order_notification(&got, &sent);

  for (size_t i = 0; i < 102; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_reduce_size_order_notification(&got, wire, 0) == 102);
  assert(encode_cancel_reduce_size_order_notification(&got, again, 0) == 102);
  for (size_t i = 0; i < 102; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Status Update Notification: 53 bytes ------------------------------ */

/* used to notify the firms about order status updates */
typedef struct {
  uint8_t matching_engine_time[8];  /* bytes 0 to 7 */
  uint8_t instrument_id[4];         /* bytes 8 to 11 */
  uint8_t order_id[8];              /* bytes 12 to 19 */
  uint8_t update_status;            /* byte 20 */
  uint8_t order_type;               /* byte 21 */
  uint8_t time_in_force;            /* byte 22 */
  uint8_t reserved_30[30];          /* bytes 23 to 52 */
} OrderStatusUpdateNotification;

/* any Order Status Update Notification at all: every byte one the checker chooses */
static void any_order_status_update_notification(OrderStatusUpdateNotification *record) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  record->update_status = arbitrary();
  record->order_type = arbitrary();
  record->time_in_force = arbitrary();
  for (size_t i = 0; i < 30; i++) { record->reserved_30[i] = arbitrary(); }
}

/* Order Status Update Notification to the wire: 53 bytes from at, returning where the next byte goes */
static size_t encode_order_status_update_notification(const OrderStatusUpdateNotification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->matching_engine_time[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  wire[at++] = record->update_status;
  wire[at++] = record->order_type;
  wire[at++] = record->time_in_force;
  for (size_t i = 0; i < 30; i++) { wire[at++] = record->reserved_30[i]; }

  return at;
}

/* Order Status Update Notification off the wire: 53 bytes from at, returning where the next byte lies */
static size_t decode_order_status_update_notification(OrderStatusUpdateNotification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->matching_engine_time[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  record->update_status = wire[at++];
  record->order_type = wire[at++];
  record->time_in_force = wire[at++];
  for (size_t i = 0; i < 30; i++) { record->reserved_30[i] = wire[at++]; }

  return at;
}

/* what was read of Order Status Update Notification is what was written, byte for byte */
static void equal_order_status_update_notification(const OrderStatusUpdateNotification *read, const OrderStatusUpdateNotification *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->matching_engine_time[i] == written->matching_engine_time[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  assert(read->update_status == written->update_status);
  assert(read->order_type == written->order_type);
  assert(read->time_in_force == written->time_in_force);
  for (size_t i = 0; i < 30; i++) { assert(read->reserved_30[i] == written->reserved_30[i]); }
}

/* Order Status Update Notification: written and read back, then read and written back */
static void check_order_status_update_notification(void) {
  OrderStatusUpdateNotification sent;
  OrderStatusUpdateNotification got;
  uint8_t wire[53];
  uint8_t again[53];

  any_order_status_update_notification(&sent);
  assert(encode_order_status_update_notification(&sent, wire, 0) == 53);
  assert(decode_order_status_update_notification(&got, wire, 0) == 53);
  equal_order_status_update_notification(&got, &sent);

  for (size_t i = 0; i < 53; i++) { wire[i] = arbitrary(); }
  assert(decode_order_status_update_notification(&got, wire, 0) == 53);
  assert(encode_order_status_update_notification(&got, again, 0) == 53);
  for (size_t i = 0; i < 53; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Order Request Message: 99 bytes ---------------------------------- */

/* a cancel request for a resting order */
typedef struct {
  uint8_t client_send_time[8];           /* bytes 0 to 7 */
  uint8_t mp_id[5];                      /* bytes 8 to 12 */
  uint8_t operator_id[18];               /* bytes 13 to 30 */
  uint8_t operator_location[6];          /* bytes 31 to 36 */
  uint8_t order_id[8];                   /* bytes 37 to 44 */
  uint8_t client_order_id[20];           /* bytes 45 to 64 */
  uint8_t original_client_order_id[20];  /* bytes 65 to 84 */
  uint8_t instrument_id[4];              /* bytes 85 to 88 */
  uint8_t reserved_10[10];               /* bytes 89 to 98 */
} CancelOrderRequestMessage;

/* any Cancel Order Request Message at all: every byte one the checker chooses */
static void any_cancel_order_request_message(CancelOrderRequestMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->operator_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->operator_location[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
}

/* Cancel Order Request Message to the wire: 99 bytes from at, returning where the next byte goes */
static size_t encode_cancel_order_request_message(const CancelOrderRequestMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_send_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mp_id[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->operator_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->operator_location[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->original_client_order_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instrument_id[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }

  return at;
}

/* Cancel Order Request Message off the wire: 99 bytes from at, returning where the next byte lies */
static size_t decode_cancel_order_request_message(CancelOrderRequestMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->operator_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->operator_location[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->original_client_order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->instrument_id[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }

  return at;
}

/* what was read of Cancel Order Request Message is what was written, byte for byte */
static void equal_cancel_order_request_message(const CancelOrderRequestMessage *read, const CancelOrderRequestMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->client_send_time[i] == written->client_send_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mp_id[i] == written->mp_id[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->operator_id[i] == written->operator_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->operator_location[i] == written->operator_location[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->original_client_order_id[i] == written->original_client_order_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->instrument_id[i] == written->instrument_id[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
}

/* Cancel Order Request Message: written and read back, then read and written back */
static void check_cancel_order_request_message(void) {
  CancelOrderRequestMessage sent;
  CancelOrderRequestMessage got;
  uint8_t wire[99];
  uint8_t again[99];

  any_cancel_order_request_message(&sent);
  assert(encode_cancel_order_request_message(&sent, wire, 0) == 99);
  assert(decode_cancel_order_request_message(&got, wire, 0) == 99);
  equal_cancel_order_request_message(&got, &sent);

  for (size_t i = 0; i < 99; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_order_request_message(&got, wire, 0) == 99);
  assert(encode_cancel_order_request_message(&got, again, 0) == 99);
  for (size_t i = 0; i < 99; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Request: 93 bytes ------------------------------------------- */

/* request the cancellation of all orders based on the requested scope and the provided criteria */
typedef struct {
  uint8_t client_send_time[8];     /* bytes 0 to 7 */
  uint8_t mp_id[5];                /* bytes 8 to 12 */
  uint8_t operator_id[18];         /* bytes 13 to 30 */
  uint8_t operator_location[6];    /* bytes 31 to 36 */
  uint8_t reserved_10[10];         /* bytes 37 to 46 */
  uint8_t client_order_id[20];     /* bytes 47 to 66 */
  uint8_t scope;                   /* byte 67 */
  uint8_t action;                  /* byte 68 */
  uint8_t product_group_code[13];  /* bytes 69 to 81 */
  uint8_t product_type;            /* byte 82 */
  uint8_t purge_group;             /* byte 83 */
  uint8_t reserved_9[9];           /* bytes 84 to 92 */
} MassCancelRequest;

/* any Mass Cancel Request at all: every byte one the checker chooses */
static void any_mass_cancel_request(MassCancelRequest *record) {
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = arbitrary(); }
  for (size_t i = 0; i < 18; i++) { record->operator_id[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->operator_location[i] = arbitrary(); }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = arbitrary(); }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = arbitrary(); }
  record->scope = arbitrary();
  record->action = arbitrary();
  for (size_t i = 0; i < 13; i++) { record->product_group_code[i] = arbitrary(); }
  record->product_type = arbitrary();
  record->purge_group = arbitrary();
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = arbitrary(); }
}

/* Mass Cancel Request to the wire: 93 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_request(const MassCancelRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->client_send_time[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->mp_id[i]; }
  for (size_t i = 0; i < 18; i++) { wire[at++] = record->operator_id[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->operator_location[i]; }
  for (size_t i = 0; i < 10; i++) { wire[at++] = record->reserved_10[i]; }
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->client_order_id[i]; }
  wire[at++] = record->scope;
  wire[at++] = record->action;
  for (size_t i = 0; i < 13; i++) { wire[at++] = record->product_group_code[i]; }
  wire[at++] = record->product_type;
  wire[at++] = record->purge_group;
  for (size_t i = 0; i < 9; i++) { wire[at++] = record->reserved_9[i]; }

  return at;
}

/* Mass Cancel Request off the wire: 93 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_request(MassCancelRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->client_send_time[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->mp_id[i] = wire[at++]; }
  for (size_t i = 0; i < 18; i++) { record->operator_id[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->operator_location[i] = wire[at++]; }
  for (size_t i = 0; i < 10; i++) { record->reserved_10[i] = wire[at++]; }
  for (size_t i = 0; i < 20; i++) { record->client_order_id[i] = wire[at++]; }
  record->scope = wire[at++];
  record->action = wire[at++];
  for (size_t i = 0; i < 13; i++) { record->product_group_code[i] = wire[at++]; }
  record->product_type = wire[at++];
  record->purge_group = wire[at++];
  for (size_t i = 0; i < 9; i++) { record->reserved_9[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Request is what was written, byte for byte */
static void equal_mass_cancel_request(const MassCancelRequest *read, const MassCancelRequest *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->client_send_time[i] == written->client_send_time[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->mp_id[i] == written->mp_id[i]); }
  for (size_t i = 0; i < 18; i++) { assert(read->operator_id[i] == written->operator_id[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->operator_location[i] == written->operator_location[i]); }
  for (size_t i = 0; i < 10; i++) { assert(read->reserved_10[i] == written->reserved_10[i]); }
  for (size_t i = 0; i < 20; i++) { assert(read->client_order_id[i] == written->client_order_id[i]); }
  assert(read->scope == written->scope);
  assert(read->action == written->action);
  for (size_t i = 0; i < 13; i++) { assert(read->product_group_code[i] == written->product_group_code[i]); }
  assert(read->product_type == written->product_type);
  assert(read->purge_group == written->purge_group);
  for (size_t i = 0; i < 9; i++) { assert(read->reserved_9[i] == written->reserved_9[i]); }
}

/* Mass Cancel Request: written and read back, then read and written back */
static void check_mass_cancel_request(void) {
  MassCancelRequest sent;
  MassCancelRequest got;
  uint8_t wire[93];
  uint8_t again[93];

  any_mass_cancel_request(&sent);
  assert(encode_mass_cancel_request(&sent, wire, 0) == 93);
  assert(decode_mass_cancel_request(&got, wire, 0) == 93);
  equal_mass_cancel_request(&got, &sent);

  for (size_t i = 0; i < 93; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_request(&got, wire, 0) == 93);
  assert(encode_mass_cancel_request(&got, again, 0) == 93);
  for (size_t i = 0; i < 93; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Request: 35 bytes ------------------------------------------------- */

/* The SesM client must send a Login request packet immediately upon establishing a new TCP/IP socket connection to the server */
typedef struct {
  uint8_t sesm_version[5];               /* bytes 0 to 4 */
  uint8_t username[5];                   /* bytes 5 to 9 */
  uint8_t computer_id[8];                /* bytes 10 to 17 */
  uint8_t application_protocol[8];       /* bytes 18 to 25 */
  uint8_t requested_session;             /* byte 26 */
  uint8_t requested_sequence_number[8];  /* bytes 27 to 34 */
} LoginRequest;

/* any Login Request at all: every byte one the checker chooses */
static void any_login_request(LoginRequest *record) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->username[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = arbitrary(); }
  record->requested_session = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = arbitrary(); }
}

/* Login Request to the wire: 35 bytes from at, returning where the next byte goes */
static size_t encode_login_request(const LoginRequest *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->sesm_version[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->username[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->computer_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->application_protocol[i]; }
  wire[at++] = record->requested_session;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->requested_sequence_number[i]; }

  return at;
}

/* Login Request off the wire: 35 bytes from at, returning where the next byte lies */
static size_t decode_login_request(LoginRequest *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 5; i++) { record->sesm_version[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->username[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->computer_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->application_protocol[i] = wire[at++]; }
  record->requested_session = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->requested_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Request is what was written, byte for byte */
static void equal_login_request(const LoginRequest *read, const LoginRequest *written) {
  for (size_t i = 0; i < 5; i++) { assert(read->sesm_version[i] == written->sesm_version[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->username[i] == written->username[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->computer_id[i] == written->computer_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->application_protocol[i] == written->application_protocol[i]); }
  assert(read->requested_session == written->requested_session);
  for (size_t i = 0; i < 8; i++) { assert(read->requested_sequence_number[i] == written->requested_sequence_number[i]); }
}

/* Login Request: written and read back, then read and written back */
static void check_login_request(void) {
  LoginRequest sent;
  LoginRequest got;
  uint8_t wire[35];
  uint8_t again[35];

  any_login_request(&sent);
  assert(encode_login_request(&sent, wire, 0) == 35);
  assert(decode_login_request(&got, wire, 0) == 35);
  equal_login_request(&got, &sent);

  for (size_t i = 0; i < 35; i++) { wire[i] = arbitrary(); }
  assert(decode_login_request(&got, wire, 0) == 35);
  assert(encode_login_request(&got, again, 0) == 35);
  for (size_t i = 0; i < 35; i++) { assert(again[i] == wire[i]); }
}

/* ---- Login Response: 10 bytes ------------------------------------------------ */

/* The SesM server sends a Login response packet in response a Login request packet from the client */
typedef struct {
  uint8_t login_status;                /* byte 0 */
  uint8_t session_id;                  /* byte 1 */
  uint8_t highest_sequence_number[8];  /* bytes 2 to 9 */
} LoginResponse;

/* any Login Response at all: every byte one the checker chooses */
static void any_login_response(LoginResponse *record) {
  record->login_status = arbitrary();
  record->session_id = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = arbitrary(); }
}

/* Login Response to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_login_response(const LoginResponse *record, uint8_t *wire, size_t at) {
  wire[at++] = record->login_status;
  wire[at++] = record->session_id;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_sequence_number[i]; }

  return at;
}

/* Login Response off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_login_response(LoginResponse *record, const uint8_t *wire, size_t at) {
  record->login_status = wire[at++];
  record->session_id = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->highest_sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Login Response is what was written, byte for byte */
static void equal_login_response(const LoginResponse *read, const LoginResponse *written) {
  assert(read->login_status == written->login_status);
  assert(read->session_id == written->session_id);
  for (size_t i = 0; i < 8; i++) { assert(read->highest_sequence_number[i] == written->highest_sequence_number[i]); }
}

/* Login Response: written and read back, then read and written back */
static void check_login_response(void) {
  LoginResponse sent;
  LoginResponse got;
  uint8_t wire[10];
  uint8_t again[10];

  any_login_response(&sent);
  assert(encode_login_response(&sent, wire, 0) == 10);
  assert(decode_login_response(&got, wire, 0) == 10);
  equal_login_response(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_login_response(&got, wire, 0) == 10);
  assert(encode_login_response(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- Retransmission Request: 16 bytes ---------------------------------------- */

/* The SesM client uses this packet to request the server to retransmit a range of packets */
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

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_sesm_packet_header();
  check_new_order_response_message();
  check_modify_order_response();
  check_cancel_order_response();
  check_mass_cancel_response();
  check_strategy_creation_response_message();
  check_system_state_notification_message();
  check_reserve_order_replenishment_notification();
  check_cancel_reduce_size_order_notification();
  check_order_status_update_notification();
  check_cancel_order_request_message();
  check_mass_cancel_request();
  check_login_request();
  check_login_response();
  check_retransmission_request();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
