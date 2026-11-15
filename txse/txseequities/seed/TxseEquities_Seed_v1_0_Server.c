// txse/txseequities/seed/TxseEquities_Seed_v1_0_Server.c
/*
 * Texas Stock Exchange Session Enabled Entry Daemon
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
 *   - a field present only on a condition
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

/* ---- Rake Message Header: 3 bytes -------------------------------------------- */

/* Rake Tcp per-message header carrying the frame length and packet-level dispatch byte */
typedef struct {
  uint8_t message_length[2];  /* bytes 0 to 1 */
  uint8_t packet_type;        /* byte 2 */
} RakeMessageHeader;

/* any Rake Message Header at all: every byte one the checker chooses */
static void any_rake_message_header(RakeMessageHeader *record) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = arbitrary(); }
  record->packet_type = arbitrary();
}

/* Rake Message Header to the wire: 3 bytes from at, returning where the next byte goes */
static size_t encode_rake_message_header(const RakeMessageHeader *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->message_length[i]; }
  wire[at++] = record->packet_type;

  return at;
}

/* Rake Message Header off the wire: 3 bytes from at, returning where the next byte lies */
static size_t decode_rake_message_header(RakeMessageHeader *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->message_length[i] = wire[at++]; }
  record->packet_type = wire[at++];

  return at;
}

/* what was read of Rake Message Header is what was written, byte for byte */
static void equal_rake_message_header(const RakeMessageHeader *read, const RakeMessageHeader *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->message_length[i] == written->message_length[i]); }
  assert(read->packet_type == written->packet_type);
}

/* Rake Message Header: written and read back, then read and written back */
static void check_rake_message_header(void) {
  RakeMessageHeader sent;
  RakeMessageHeader got;
  uint8_t wire[3];
  uint8_t again[3];

  any_rake_message_header(&sent);
  assert(encode_rake_message_header(&sent, wire, 0) == 3);
  assert(decode_rake_message_header(&got, wire, 0) == 3);
  equal_rake_message_header(&got, &sent);

  for (size_t i = 0; i < 3; i++) { wire[i] = arbitrary(); }
  assert(decode_rake_message_header(&got, wire, 0) == 3);
  assert(encode_rake_message_header(&got, again, 0) == 3);
  for (size_t i = 0; i < 3; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Response Message: 30 bytes ---------------------------------------- */

/* Response to a logon request */
typedef struct {
  uint8_t session[8];                        /* bytes 0 to 7 */
  uint8_t next_sequence_number[8];           /* bytes 8 to 15 */
  uint8_t highest_known_sequence_number[8];  /* bytes 16 to 23 */
  uint8_t logon_response_code;               /* byte 24 */
  uint8_t number_stream_ids;                 /* byte 25 */
  uint8_t instance[4];                       /* bytes 26 to 29 */
} LogonResponseMessage;

/* any Logon Response Message at all: every byte one the checker chooses */
static void any_logon_response_message(LogonResponseMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->session[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->highest_known_sequence_number[i] = arbitrary(); }
  record->logon_response_code = arbitrary();
  record->number_stream_ids = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->instance[i] = arbitrary(); }
}

/* Logon Response Message to the wire: 30 bytes from at, returning where the next byte goes */
static size_t encode_logon_response_message(const LogonResponseMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->session[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->next_sequence_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->highest_known_sequence_number[i]; }
  wire[at++] = record->logon_response_code;
  wire[at++] = record->number_stream_ids;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->instance[i]; }

  return at;
}

/* Logon Response Message off the wire: 30 bytes from at, returning where the next byte lies */
static size_t decode_logon_response_message(LogonResponseMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->session[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->next_sequence_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->highest_known_sequence_number[i] = wire[at++]; }
  record->logon_response_code = wire[at++];
  record->number_stream_ids = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->instance[i] = wire[at++]; }

  return at;
}

/* what was read of Logon Response Message is what was written, byte for byte */
static void equal_logon_response_message(const LogonResponseMessage *read, const LogonResponseMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->session[i] == written->session[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->next_sequence_number[i] == written->next_sequence_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->highest_known_sequence_number[i] == written->highest_known_sequence_number[i]); }
  assert(read->logon_response_code == written->logon_response_code);
  assert(read->number_stream_ids == written->number_stream_ids);
  for (size_t i = 0; i < 4; i++) { assert(read->instance[i] == written->instance[i]); }
}

/* Logon Response Message: written and read back, then read and written back */
static void check_logon_response_message(void) {
  LogonResponseMessage sent;
  LogonResponseMessage got;
  uint8_t wire[30];
  uint8_t again[30];

  any_logon_response_message(&sent);
  assert(encode_logon_response_message(&sent, wire, 0) == 30);
  assert(decode_logon_response_message(&got, wire, 0) == 30);
  equal_logon_response_message(&got, &sent);

  for (size_t i = 0; i < 30; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_response_message(&got, wire, 0) == 30);
  assert(encode_logon_response_message(&got, again, 0) == 30);
  for (size_t i = 0; i < 30; i++) { assert(again[i] == wire[i]); }
}

/* ---- Order Canceled Message: 25 bytes ---------------------------------------- */

/* This order has been canceled. No shares are left on the Exchange. The Member will receive this message in response to a CancelOrder message, as well as unsolicited messages from the Exchange for various reasons. */
typedef struct {
  uint8_t transact_time[8];   /* bytes 0 to 7 */
  uint8_t order_id[8];        /* bytes 8 to 15 */
  uint8_t orig_cl_ord_id[8];  /* bytes 16 to 23 */
  uint8_t cancel_reason;      /* byte 24 */
} OrderCanceledMessage;

/* any Order Canceled Message at all: every byte one the checker chooses */
static void any_order_canceled_message(OrderCanceledMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->cancel_reason = arbitrary();
}

/* Order Canceled Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_order_canceled_message(const OrderCanceledMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->order_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->cancel_reason;

  return at;
}

/* Order Canceled Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_order_canceled_message(OrderCanceledMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->order_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->cancel_reason = wire[at++];

  return at;
}

/* what was read of Order Canceled Message is what was written, byte for byte */
static void equal_order_canceled_message(const OrderCanceledMessage *read, const OrderCanceledMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->order_id[i] == written->order_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->cancel_reason == written->cancel_reason);
}

/* Order Canceled Message: written and read back, then read and written back */
static void check_order_canceled_message(void) {
  OrderCanceledMessage sent;
  OrderCanceledMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_order_canceled_message(&sent);
  assert(encode_order_canceled_message(&sent, wire, 0) == 25);
  assert(decode_order_canceled_message(&got, wire, 0) == 25);
  equal_order_canceled_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_order_canceled_message(&got, wire, 0) == 25);
  assert(encode_order_canceled_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Cancel Rejected Message: 17 bytes --------------------------------------- */

/* The requested CancelOrder has been rejected. */
typedef struct {
  uint8_t transact_time[8];        /* bytes 0 to 7 */
  uint8_t orig_cl_ord_id[8];       /* bytes 8 to 15 */
  uint8_t cancel_rejected_reason;  /* byte 16 */
} CancelRejectedMessage;

/* any Cancel Rejected Message at all: every byte one the checker chooses */
static void any_cancel_rejected_message(CancelRejectedMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = arbitrary(); }
  record->cancel_rejected_reason = arbitrary();
}

/* Cancel Rejected Message to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_cancel_rejected_message(const CancelRejectedMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->orig_cl_ord_id[i]; }
  wire[at++] = record->cancel_rejected_reason;

  return at;
}

/* Cancel Rejected Message off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_cancel_rejected_message(CancelRejectedMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->orig_cl_ord_id[i] = wire[at++]; }
  record->cancel_rejected_reason = wire[at++];

  return at;
}

/* what was read of Cancel Rejected Message is what was written, byte for byte */
static void equal_cancel_rejected_message(const CancelRejectedMessage *read, const CancelRejectedMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->orig_cl_ord_id[i] == written->orig_cl_ord_id[i]); }
  assert(read->cancel_rejected_reason == written->cancel_rejected_reason);
}

/* Cancel Rejected Message: written and read back, then read and written back */
static void check_cancel_rejected_message(void) {
  CancelRejectedMessage sent;
  CancelRejectedMessage got;
  uint8_t wire[17];
  uint8_t again[17];

  any_cancel_rejected_message(&sent);
  assert(encode_cancel_rejected_message(&sent, wire, 0) == 17);
  assert(decode_cancel_rejected_message(&got, wire, 0) == 17);
  equal_cancel_rejected_message(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_cancel_rejected_message(&got, wire, 0) == 17);
  assert(encode_cancel_rejected_message(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Mass Cancel Result Message: 28 bytes ------------------------------------ */

/* Confirms sweep completion. Sent after all affected orders have been canceled. */
typedef struct {
  uint8_t transact_time[8];           /* bytes 0 to 7 */
  uint8_t mass_cancel_request_id[8];  /* bytes 8 to 15 */
  uint8_t mass_cancel_id[8];          /* bytes 16 to 23 */
  uint8_t canceled_count[4];          /* bytes 24 to 27 */
} MassCancelResultMessage;

/* any Mass Cancel Result Message at all: every byte one the checker chooses */
static void any_mass_cancel_result_message(MassCancelResultMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mass_cancel_request_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->mass_cancel_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->canceled_count[i] = arbitrary(); }
}

/* Mass Cancel Result Message to the wire: 28 bytes from at, returning where the next byte goes */
static size_t encode_mass_cancel_result_message(const MassCancelResultMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->transact_time[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mass_cancel_request_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->mass_cancel_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->canceled_count[i]; }

  return at;
}

/* Mass Cancel Result Message off the wire: 28 bytes from at, returning where the next byte lies */
static size_t decode_mass_cancel_result_message(MassCancelResultMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->transact_time[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mass_cancel_request_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->mass_cancel_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->canceled_count[i] = wire[at++]; }

  return at;
}

/* what was read of Mass Cancel Result Message is what was written, byte for byte */
static void equal_mass_cancel_result_message(const MassCancelResultMessage *read, const MassCancelResultMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->transact_time[i] == written->transact_time[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mass_cancel_request_id[i] == written->mass_cancel_request_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->mass_cancel_id[i] == written->mass_cancel_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->canceled_count[i] == written->canceled_count[i]); }
}

/* Mass Cancel Result Message: written and read back, then read and written back */
static void check_mass_cancel_result_message(void) {
  MassCancelResultMessage sent;
  MassCancelResultMessage got;
  uint8_t wire[28];
  uint8_t again[28];

  any_mass_cancel_result_message(&sent);
  assert(encode_mass_cancel_result_message(&sent, wire, 0) == 28);
  assert(decode_mass_cancel_result_message(&got, wire, 0) == 28);
  equal_mass_cancel_result_message(&got, &sent);

  for (size_t i = 0; i < 28; i++) { wire[i] = arbitrary(); }
  assert(decode_mass_cancel_result_message(&got, wire, 0) == 28);
  assert(encode_mass_cancel_result_message(&got, again, 0) == 28);
  for (size_t i = 0; i < 28; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_rake_message_header();
  check_logon_response_message();
  check_order_canceled_message();
  check_cancel_rejected_message();
  check_mass_cancel_result_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
