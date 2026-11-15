// taifex/taifexderivatives/orderentry/TaifexDerivatives_OrderEntry_v2_18_7.c
/*
 * Taiwan Futures Exchange Order Entry
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
 *   - a Reassemble rule
 *   - a length prefix framing what follows
 *   - the dispatch that chooses a message by its type
 *   - a run of a stated number of entries
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

/* ---- Header Time: 6 bytes ---------------------------------------------------- */

/* Message time, the Tmp time format of section 2.1 carried by the common message header */
typedef struct {
  uint8_t header_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t header_ms[2];       /* bytes 4 to 5 */
} HeaderTime;

/* any Header Time at all: every byte one the checker chooses */
static void any_header_time(HeaderTime *record) {
  for (size_t i = 0; i < 4; i++) { record->header_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->header_ms[i] = arbitrary(); }
}

/* Header Time to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_header_time(const HeaderTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->header_epoch_s[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->header_ms[i]; }

  return at;
}

/* Header Time off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_header_time(HeaderTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->header_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->header_ms[i] = wire[at++]; }

  return at;
}

/* what was read of Header Time is what was written, byte for byte */
static void equal_header_time(const HeaderTime *read, const HeaderTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->header_epoch_s[i] == written->header_epoch_s[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->header_ms[i] == written->header_ms[i]); }
}

/* Header Time: written and read back, then read and written back */
static void check_header_time(void) {
  HeaderTime sent;
  HeaderTime got;
  uint8_t wire[6];
  uint8_t again[6];

  any_header_time(&sent);
  assert(encode_header_time(&sent, wire, 0) == 6);
  assert(decode_header_time(&got, wire, 0) == 6);
  equal_header_time(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_header_time(&got, wire, 0) == 6);
  assert(encode_header_time(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Hdr: 17 bytes ----------------------------------------------------------- */

/* Tmp Common message header, carried by every Tmp message */
typedef struct {
  uint8_t msg_length[2];   /* bytes 0 to 1 */
  uint8_t msg_seq_num[4];  /* bytes 2 to 5 */
  HeaderTime header_time;  /* bytes 6 to 11 */
  uint8_t message_type;    /* byte 12 */
  uint8_t fcm_id[2];       /* bytes 13 to 14 */
  uint8_t session_id[2];   /* bytes 15 to 16 */
} Hdr;

/* any Hdr at all: every byte one the checker chooses */
static void any_hdr(Hdr *record) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = arbitrary(); }
  any_header_time(&record->header_time);
  record->message_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
}

/* Hdr to the wire: 17 bytes from at, returning where the next byte goes */
static size_t encode_hdr(const Hdr *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->msg_length[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_seq_num[i]; }
  at = encode_header_time(&record->header_time, wire, at);
  wire[at++] = record->message_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fcm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }

  return at;
}

/* Hdr off the wire: 17 bytes from at, returning where the next byte lies */
static size_t decode_hdr(Hdr *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->msg_length[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->msg_seq_num[i] = wire[at++]; }
  at = decode_header_time(&record->header_time, wire, at);
  record->message_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }

  return at;
}

/* what was read of Hdr is what was written, byte for byte */
static void equal_hdr(const Hdr *read, const Hdr *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->msg_length[i] == written->msg_length[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->msg_seq_num[i] == written->msg_seq_num[i]); }
  equal_header_time(&read->header_time, &written->header_time);
  assert(read->message_type == written->message_type);
  for (size_t i = 0; i < 2; i++) { assert(read->fcm_id[i] == written->fcm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
}

/* Hdr: written and read back, then read and written back */
static void check_hdr(void) {
  Hdr sent;
  Hdr got;
  uint8_t wire[17];
  uint8_t again[17];

  any_hdr(&sent);
  assert(encode_hdr(&sent, wire, 0) == 17);
  assert(decode_hdr(&got, wire, 0) == 17);
  equal_hdr(&got, &sent);

  for (size_t i = 0; i < 17; i++) { wire[i] = arbitrary(); }
  assert(decode_hdr(&got, wire, 0) == 17);
  assert(encode_hdr(&got, again, 0) == 17);
  for (size_t i = 0; i < 17; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wake Up Call Message: 5 bytes ------------------------------------------- */

/* Wake up call message, which either Taifex or the futures commission merchant may initiate in the logon phase of the Link Subsystem. */
typedef struct {
  uint8_t status_code;            /* byte 0 */
  uint8_t start_in_bound_num[4];  /* bytes 1 to 4 */
} WakeUpCallMessage;

/* any Wake Up Call Message at all: every byte one the checker chooses */
static void any_wake_up_call_message(WakeUpCallMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->start_in_bound_num[i] = arbitrary(); }
}

/* Wake Up Call Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_wake_up_call_message(const WakeUpCallMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->start_in_bound_num[i]; }

  return at;
}

/* Wake Up Call Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_wake_up_call_message(WakeUpCallMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->start_in_bound_num[i] = wire[at++]; }

  return at;
}

/* what was read of Wake Up Call Message is what was written, byte for byte */
static void equal_wake_up_call_message(const WakeUpCallMessage *read, const WakeUpCallMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 4; i++) { assert(read->start_in_bound_num[i] == written->start_in_bound_num[i]); }
}

/* Wake Up Call Message: written and read back, then read and written back */
static void check_wake_up_call_message(void) {
  WakeUpCallMessage sent;
  WakeUpCallMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_wake_up_call_message(&sent);
  assert(encode_wake_up_call_message(&sent, wire, 0) == 5);
  assert(decode_wake_up_call_message(&got, wire, 0) == 5);
  equal_wake_up_call_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_wake_up_call_message(&got, wire, 0) == 5);
  assert(encode_wake_up_call_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Wake Up Call Confirmed Message: 1 byte ---------------------------------- */

/* Wake up call confirmed message, sent by the futures commission merchant to Taifex. */
typedef struct {
  uint8_t version;  /* byte 0 */
} WakeUpCallConfirmedMessage;

/* any Wake Up Call Confirmed Message at all: every byte one the checker chooses */
static void any_wake_up_call_confirmed_message(WakeUpCallConfirmedMessage *record) {
  record->version = arbitrary();
}

/* Wake Up Call Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_wake_up_call_confirmed_message(const WakeUpCallConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->version;

  return at;
}

/* Wake Up Call Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_wake_up_call_confirmed_message(WakeUpCallConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->version = wire[at++];

  return at;
}

/* what was read of Wake Up Call Confirmed Message is what was written, byte for byte */
static void equal_wake_up_call_confirmed_message(const WakeUpCallConfirmedMessage *read, const WakeUpCallConfirmedMessage *written) {
  assert(read->version == written->version);
}

/* Wake Up Call Confirmed Message: written and read back, then read and written back */
static void check_wake_up_call_confirmed_message(void) {
  WakeUpCallConfirmedMessage sent;
  WakeUpCallConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_wake_up_call_confirmed_message(&sent);
  assert(encode_wake_up_call_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_wake_up_call_confirmed_message(&got, wire, 0) == 1);
  equal_wake_up_call_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_wake_up_call_confirmed_message(&got, wire, 0) == 1);
  assert(encode_wake_up_call_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logon Notice Message: 9 bytes ------------------------------------------- */

/* Logon notice message, carrying the sequence No of the last message Taifex sent the futures commission merchant in the session. */
typedef struct {
  uint8_t status_code;           /* byte 0 */
  uint8_t append_no[2];          /* bytes 1 to 2 */
  uint8_t end_out_bound_num[4];  /* bytes 3 to 6 */
  uint8_t system_type;           /* byte 7 */
  uint8_t encrypt_method;        /* byte 8 */
} LogonNoticeMessage;

/* any Logon Notice Message at all: every byte one the checker chooses */
static void any_logon_notice_message(LogonNoticeMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->append_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->end_out_bound_num[i] = arbitrary(); }
  record->system_type = arbitrary();
  record->encrypt_method = arbitrary();
}

/* Logon Notice Message to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_logon_notice_message(const LogonNoticeMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->append_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_out_bound_num[i]; }
  wire[at++] = record->system_type;
  wire[at++] = record->encrypt_method;

  return at;
}

/* Logon Notice Message off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_logon_notice_message(LogonNoticeMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->append_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->end_out_bound_num[i] = wire[at++]; }
  record->system_type = wire[at++];
  record->encrypt_method = wire[at++];

  return at;
}

/* what was read of Logon Notice Message is what was written, byte for byte */
static void equal_logon_notice_message(const LogonNoticeMessage *read, const LogonNoticeMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 2; i++) { assert(read->append_no[i] == written->append_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->end_out_bound_num[i] == written->end_out_bound_num[i]); }
  assert(read->system_type == written->system_type);
  assert(read->encrypt_method == written->encrypt_method);
}

/* Logon Notice Message: written and read back, then read and written back */
static void check_logon_notice_message(void) {
  LogonNoticeMessage sent;
  LogonNoticeMessage got;
  uint8_t wire[9];
  uint8_t again[9];

  any_logon_notice_message(&sent);
  assert(encode_logon_notice_message(&sent, wire, 0) == 9);
  assert(decode_logon_notice_message(&got, wire, 0) == 9);
  equal_logon_notice_message(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_logon_notice_message(&got, wire, 0) == 9);
  assert(encode_logon_notice_message(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sub Hdr: 6 bytes -------------------------------------------------------- */

/* Tmp Expanded Message Header, which assigns different functionalities to a MessageType by defining additional subcategories for it */
typedef struct {
  uint8_t msg_type_ext;    /* byte 0 */
  uint8_t preserve;        /* byte 1 */
  uint8_t msg_time_ns[4];  /* bytes 2 to 5 */
} SubHdr;

/* any Sub Hdr at all: every byte one the checker chooses */
static void any_sub_hdr(SubHdr *record) {
  record->msg_type_ext = arbitrary();
  record->preserve = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->msg_time_ns[i] = arbitrary(); }
}

/* Sub Hdr to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_sub_hdr(const SubHdr *record, uint8_t *wire, size_t at) {
  wire[at++] = record->msg_type_ext;
  wire[at++] = record->preserve;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_ns[i]; }

  return at;
}

/* Sub Hdr off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_sub_hdr(SubHdr *record, const uint8_t *wire, size_t at) {
  record->msg_type_ext = wire[at++];
  record->preserve = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->msg_time_ns[i] = wire[at++]; }

  return at;
}

/* what was read of Sub Hdr is what was written, byte for byte */
static void equal_sub_hdr(const SubHdr *read, const SubHdr *written) {
  assert(read->msg_type_ext == written->msg_type_ext);
  assert(read->preserve == written->preserve);
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_ns[i] == written->msg_time_ns[i]); }
}

/* Sub Hdr: written and read back, then read and written back */
static void check_sub_hdr(void) {
  SubHdr sent;
  SubHdr got;
  uint8_t wire[6];
  uint8_t again[6];

  any_sub_hdr(&sent);
  assert(encode_sub_hdr(&sent, wire, 0) == 6);
  assert(decode_sub_hdr(&got, wire, 0) == 6);
  equal_sub_hdr(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_sub_hdr(&got, wire, 0) == 6);
  assert(encode_sub_hdr(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Final Sequential Number Notification For Group Message: 21 bytes -------- */

/* Final Sequential Number Notification Message for Group, transmitting the group's last report sequence number to the futures commission merchant. */
typedef struct {
  SubHdr sub_hdr;                /* bytes 0 to 5 */
  uint8_t wide_status_code[2];   /* bytes 6 to 7 */
  uint8_t part_id;               /* byte 8 */
  uint8_t end_out_bound_num[4];  /* bytes 9 to 12 */
  uint8_t reserved_8[8];         /* bytes 13 to 20 */
} FinalSequentialNumberNotificationForGroupMessage;

/* any Final Sequential Number Notification For Group Message at all: every byte one the checker chooses */
static void any_final_sequential_number_notification_for_group_message(FinalSequentialNumberNotificationForGroupMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = arbitrary(); }
  record->part_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->end_out_bound_num[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = arbitrary(); }
}

/* Final Sequential Number Notification For Group Message to the wire: 21 bytes from at, returning where the next byte goes */
static size_t encode_final_sequential_number_notification_for_group_message(const FinalSequentialNumberNotificationForGroupMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->wide_status_code[i]; }
  wire[at++] = record->part_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->end_out_bound_num[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->reserved_8[i]; }

  return at;
}

/* Final Sequential Number Notification For Group Message off the wire: 21 bytes from at, returning where the next byte lies */
static size_t decode_final_sequential_number_notification_for_group_message(FinalSequentialNumberNotificationForGroupMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = wire[at++]; }
  record->part_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->end_out_bound_num[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->reserved_8[i] = wire[at++]; }

  return at;
}

/* what was read of Final Sequential Number Notification For Group Message is what was written, byte for byte */
static void equal_final_sequential_number_notification_for_group_message(const FinalSequentialNumberNotificationForGroupMessage *read, const FinalSequentialNumberNotificationForGroupMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  for (size_t i = 0; i < 2; i++) { assert(read->wide_status_code[i] == written->wide_status_code[i]); }
  assert(read->part_id == written->part_id);
  for (size_t i = 0; i < 4; i++) { assert(read->end_out_bound_num[i] == written->end_out_bound_num[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->reserved_8[i] == written->reserved_8[i]); }
}

/* Final Sequential Number Notification For Group Message: written and read back, then read and written back */
static void check_final_sequential_number_notification_for_group_message(void) {
  FinalSequentialNumberNotificationForGroupMessage sent;
  FinalSequentialNumberNotificationForGroupMessage got;
  uint8_t wire[21];
  uint8_t again[21];

  any_final_sequential_number_notification_for_group_message(&sent);
  assert(encode_final_sequential_number_notification_for_group_message(&sent, wire, 0) == 21);
  assert(decode_final_sequential_number_notification_for_group_message(&got, wire, 0) == 21);
  equal_final_sequential_number_notification_for_group_message(&got, &sent);

  for (size_t i = 0; i < 21; i++) { wire[i] = arbitrary(); }
  assert(decode_final_sequential_number_notification_for_group_message(&got, wire, 0) == 21);
  assert(encode_final_sequential_number_notification_for_group_message(&got, again, 0) == 21);
  for (size_t i = 0; i < 21; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request Logon Message: 15 bytes ----------------------------------------- */

/* Request logon, sent by the futures commission merchant to Taifex with the start sequence of the messages it requests Taifex to resend. */
typedef struct {
  uint8_t status_code;           /* byte 0 */
  uint8_t append_no[2];          /* bytes 1 to 2 */
  uint8_t fcm_id[2];             /* bytes 3 to 4 */
  uint8_t session_id[2];         /* bytes 5 to 6 */
  uint8_t system_type;           /* byte 7 */
  uint8_t ap_code;               /* byte 8 */
  uint8_t key_value;             /* byte 9 */
  uint8_t request_start_seq[4];  /* bytes 10 to 13 */
  uint8_t cancel_order_sec;      /* byte 14 */
} RequestLogonMessage;

/* any Request Logon Message at all: every byte one the checker chooses */
static void any_request_logon_message(RequestLogonMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->append_no[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = arbitrary(); }
  record->system_type = arbitrary();
  record->ap_code = arbitrary();
  record->key_value = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_start_seq[i] = arbitrary(); }
  record->cancel_order_sec = arbitrary();
}

/* Request Logon Message to the wire: 15 bytes from at, returning where the next byte goes */
static size_t encode_request_logon_message(const RequestLogonMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->append_no[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fcm_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->session_id[i]; }
  wire[at++] = record->system_type;
  wire[at++] = record->ap_code;
  wire[at++] = record->key_value;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_start_seq[i]; }
  wire[at++] = record->cancel_order_sec;

  return at;
}

/* Request Logon Message off the wire: 15 bytes from at, returning where the next byte lies */
static size_t decode_request_logon_message(RequestLogonMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->append_no[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->session_id[i] = wire[at++]; }
  record->system_type = wire[at++];
  record->ap_code = wire[at++];
  record->key_value = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_start_seq[i] = wire[at++]; }
  record->cancel_order_sec = wire[at++];

  return at;
}

/* what was read of Request Logon Message is what was written, byte for byte */
static void equal_request_logon_message(const RequestLogonMessage *read, const RequestLogonMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 2; i++) { assert(read->append_no[i] == written->append_no[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->fcm_id[i] == written->fcm_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->session_id[i] == written->session_id[i]); }
  assert(read->system_type == written->system_type);
  assert(read->ap_code == written->ap_code);
  assert(read->key_value == written->key_value);
  for (size_t i = 0; i < 4; i++) { assert(read->request_start_seq[i] == written->request_start_seq[i]); }
  assert(read->cancel_order_sec == written->cancel_order_sec);
}

/* Request Logon Message: written and read back, then read and written back */
static void check_request_logon_message(void) {
  RequestLogonMessage sent;
  RequestLogonMessage got;
  uint8_t wire[15];
  uint8_t again[15];

  any_request_logon_message(&sent);
  assert(encode_request_logon_message(&sent, wire, 0) == 15);
  assert(decode_request_logon_message(&got, wire, 0) == 15);
  equal_request_logon_message(&got, &sent);

  for (size_t i = 0; i < 15; i++) { wire[i] = arbitrary(); }
  assert(decode_request_logon_message(&got, wire, 0) == 15);
  assert(encode_request_logon_message(&got, again, 0) == 15);
  for (size_t i = 0; i < 15; i++) { assert(again[i] == wire[i]); }
}

/* ---- Resend Report Confirmed Message: 1 byte --------------------------------- */

/* Resend report message confirmed, sent by the futures commission merchant to Taifex. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} ResendReportConfirmedMessage;

/* any Resend Report Confirmed Message at all: every byte one the checker chooses */
static void any_resend_report_confirmed_message(ResendReportConfirmedMessage *record) {
  record->status_code = arbitrary();
}

/* Resend Report Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_resend_report_confirmed_message(const ResendReportConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Resend Report Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_resend_report_confirmed_message(ResendReportConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Resend Report Confirmed Message is what was written, byte for byte */
static void equal_resend_report_confirmed_message(const ResendReportConfirmedMessage *read, const ResendReportConfirmedMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Resend Report Confirmed Message: written and read back, then read and written back */
static void check_resend_report_confirmed_message(void) {
  ResendReportConfirmedMessage sent;
  ResendReportConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_resend_report_confirmed_message(&sent);
  assert(encode_resend_report_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_resend_report_confirmed_message(&got, wire, 0) == 1);
  equal_resend_report_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_resend_report_confirmed_message(&got, wire, 0) == 1);
  assert(encode_resend_report_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Activate Application System Message: 4 bytes ---------------------------- */

/* Activate application system, sent by Taifex to the futures commission merchant. */
typedef struct {
  uint8_t status_code;           /* byte 0 */
  uint8_t heart_bt_int;          /* byte 1 */
  uint8_t max_flow_ctrl_cnt[2];  /* bytes 2 to 3 */
} ActivateApplicationSystemMessage;

/* any Activate Application System Message at all: every byte one the checker chooses */
static void any_activate_application_system_message(ActivateApplicationSystemMessage *record) {
  record->status_code = arbitrary();
  record->heart_bt_int = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->max_flow_ctrl_cnt[i] = arbitrary(); }
}

/* Activate Application System Message to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_activate_application_system_message(const ActivateApplicationSystemMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  wire[at++] = record->heart_bt_int;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->max_flow_ctrl_cnt[i]; }

  return at;
}

/* Activate Application System Message off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_activate_application_system_message(ActivateApplicationSystemMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  record->heart_bt_int = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->max_flow_ctrl_cnt[i] = wire[at++]; }

  return at;
}

/* what was read of Activate Application System Message is what was written, byte for byte */
static void equal_activate_application_system_message(const ActivateApplicationSystemMessage *read, const ActivateApplicationSystemMessage *written) {
  assert(read->status_code == written->status_code);
  assert(read->heart_bt_int == written->heart_bt_int);
  for (size_t i = 0; i < 2; i++) { assert(read->max_flow_ctrl_cnt[i] == written->max_flow_ctrl_cnt[i]); }
}

/* Activate Application System Message: written and read back, then read and written back */
static void check_activate_application_system_message(void) {
  ActivateApplicationSystemMessage sent;
  ActivateApplicationSystemMessage got;
  uint8_t wire[4];
  uint8_t again[4];

  any_activate_application_system_message(&sent);
  assert(encode_activate_application_system_message(&sent, wire, 0) == 4);
  assert(decode_activate_application_system_message(&got, wire, 0) == 4);
  equal_activate_application_system_message(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_activate_application_system_message(&got, wire, 0) == 4);
  assert(encode_activate_application_system_message(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Activate Application System Confirmed Message: 1 byte ------------------- */

/* Activate application system confirmed, from which Taifex calculates the round trip time of the L50 message to determine the maximum peak flow per second. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} ActivateApplicationSystemConfirmedMessage;

/* any Activate Application System Confirmed Message at all: every byte one the checker chooses */
static void any_activate_application_system_confirmed_message(ActivateApplicationSystemConfirmedMessage *record) {
  record->status_code = arbitrary();
}

/* Activate Application System Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_activate_application_system_confirmed_message(const ActivateApplicationSystemConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Activate Application System Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_activate_application_system_confirmed_message(ActivateApplicationSystemConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Activate Application System Confirmed Message is what was written, byte for byte */
static void equal_activate_application_system_confirmed_message(const ActivateApplicationSystemConfirmedMessage *read, const ActivateApplicationSystemConfirmedMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Activate Application System Confirmed Message: written and read back, then read and written back */
static void check_activate_application_system_confirmed_message(void) {
  ActivateApplicationSystemConfirmedMessage sent;
  ActivateApplicationSystemConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_activate_application_system_confirmed_message(&sent);
  assert(encode_activate_application_system_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_activate_application_system_confirmed_message(&got, wire, 0) == 1);
  equal_activate_application_system_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_activate_application_system_confirmed_message(&got, wire, 0) == 1);
  assert(encode_activate_application_system_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Logout Confirmed Message: 1 byte ---------------------------------------- */

/* Logout confirmed message, sent by Taifex to the futures commission merchant. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} LogoutConfirmedMessage;

/* any Logout Confirmed Message at all: every byte one the checker chooses */
static void any_logout_confirmed_message(LogoutConfirmedMessage *record) {
  record->status_code = arbitrary();
}

/* Logout Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_logout_confirmed_message(const LogoutConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Logout Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_logout_confirmed_message(LogoutConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Logout Confirmed Message is what was written, byte for byte */
static void equal_logout_confirmed_message(const LogoutConfirmedMessage *read, const LogoutConfirmedMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Logout Confirmed Message: written and read back, then read and written back */
static void check_logout_confirmed_message(void) {
  LogoutConfirmedMessage sent;
  LogoutConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_logout_confirmed_message(&sent);
  assert(encode_logout_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_logout_confirmed_message(&got, wire, 0) == 1);
  equal_logout_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_logout_confirmed_message(&got, wire, 0) == 1);
  assert(encode_logout_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Confirm Connection Message: 1 byte -------------------------------------- */

/* Confirm connection message, which either party sends when no new message has arrived from the other after the number of seconds set in the HeartBtInt field of L50. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} ConfirmConnectionMessage;

/* any Confirm Connection Message at all: every byte one the checker chooses */
static void any_confirm_connection_message(ConfirmConnectionMessage *record) {
  record->status_code = arbitrary();
}

/* Confirm Connection Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_confirm_connection_message(const ConfirmConnectionMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Confirm Connection Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_confirm_connection_message(ConfirmConnectionMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Confirm Connection Message is what was written, byte for byte */
static void equal_confirm_connection_message(const ConfirmConnectionMessage *read, const ConfirmConnectionMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Confirm Connection Message: written and read back, then read and written back */
static void check_confirm_connection_message(void) {
  ConfirmConnectionMessage sent;
  ConfirmConnectionMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_confirm_connection_message(&sent);
  assert(encode_confirm_connection_message(&sent, wire, 0) == 1);
  assert(decode_confirm_connection_message(&got, wire, 0) == 1);
  equal_confirm_connection_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_confirm_connection_message(&got, wire, 0) == 1);
  assert(encode_confirm_connection_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Connection Confirmed Message: 1 byte ------------------------------------ */

/* Connection confirmed message, with which a party answers the confirm connection message of the other. */
typedef struct {
  uint8_t status_code;  /* byte 0 */
} ConnectionConfirmedMessage;

/* any Connection Confirmed Message at all: every byte one the checker chooses */
static void any_connection_confirmed_message(ConnectionConfirmedMessage *record) {
  record->status_code = arbitrary();
}

/* Connection Confirmed Message to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_connection_confirmed_message(const ConnectionConfirmedMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;

  return at;
}

/* Connection Confirmed Message off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_connection_confirmed_message(ConnectionConfirmedMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];

  return at;
}

/* what was read of Connection Confirmed Message is what was written, byte for byte */
static void equal_connection_confirmed_message(const ConnectionConfirmedMessage *read, const ConnectionConfirmedMessage *written) {
  assert(read->status_code == written->status_code);
}

/* Connection Confirmed Message: written and read back, then read and written back */
static void check_connection_confirmed_message(void) {
  ConnectionConfirmedMessage sent;
  ConnectionConfirmedMessage got;
  uint8_t wire[1];
  uint8_t again[1];

  any_connection_confirmed_message(&sent);
  assert(encode_connection_confirmed_message(&sent, wire, 0) == 1);
  assert(decode_connection_confirmed_message(&got, wire, 0) == 1);
  equal_connection_confirmed_message(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_connection_confirmed_message(&got, wire, 0) == 1);
  assert(encode_connection_confirmed_message(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Session Status Request Message: 5 bytes --------------------------- */

/* Trade session status request, with which a futures commission merchant queries the trade session status and determines whether the trading system is halted. */
typedef struct {
  uint8_t status_code;                /* byte 0 */
  uint8_t trade_req_id[2];            /* bytes 1 to 2 */
  uint8_t flow_group_no;              /* byte 3 */
  uint8_t subscription_request_type;  /* byte 4 */
} TradeSessionStatusRequestMessage;

/* any Trade Session Status Request Message at all: every byte one the checker chooses */
static void any_trade_session_status_request_message(TradeSessionStatusRequestMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_req_id[i] = arbitrary(); }
  record->flow_group_no = arbitrary();
  record->subscription_request_type = arbitrary();
}

/* Trade Session Status Request Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_trade_session_status_request_message(const TradeSessionStatusRequestMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_req_id[i]; }
  wire[at++] = record->flow_group_no;
  wire[at++] = record->subscription_request_type;

  return at;
}

/* Trade Session Status Request Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_trade_session_status_request_message(TradeSessionStatusRequestMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_req_id[i] = wire[at++]; }
  record->flow_group_no = wire[at++];
  record->subscription_request_type = wire[at++];

  return at;
}

/* what was read of Trade Session Status Request Message is what was written, byte for byte */
static void equal_trade_session_status_request_message(const TradeSessionStatusRequestMessage *read, const TradeSessionStatusRequestMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_req_id[i] == written->trade_req_id[i]); }
  assert(read->flow_group_no == written->flow_group_no);
  assert(read->subscription_request_type == written->subscription_request_type);
}

/* Trade Session Status Request Message: written and read back, then read and written back */
static void check_trade_session_status_request_message(void) {
  TradeSessionStatusRequestMessage sent;
  TradeSessionStatusRequestMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_trade_session_status_request_message(&sent);
  assert(encode_trade_session_status_request_message(&sent, wire, 0) == 5);
  assert(decode_trade_session_status_request_message(&got, wire, 0) == 5);
  equal_trade_session_status_request_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_session_status_request_message(&got, wire, 0) == 5);
  assert(encode_trade_session_status_request_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trade Session Status Report Message: 5 bytes ---------------------------- */

/* Trade session status report, with which Taifex answers a trade session status request and reports each subsequent change of status. */
typedef struct {
  uint8_t status_code;      /* byte 0 */
  uint8_t trade_req_id[2];  /* bytes 1 to 2 */
  uint8_t flow_group_no;    /* byte 3 */
  uint8_t trade_status;     /* byte 4 */
} TradeSessionStatusReportMessage;

/* any Trade Session Status Report Message at all: every byte one the checker chooses */
static void any_trade_session_status_report_message(TradeSessionStatusReportMessage *record) {
  record->status_code = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->trade_req_id[i] = arbitrary(); }
  record->flow_group_no = arbitrary();
  record->trade_status = arbitrary();
}

/* Trade Session Status Report Message to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_trade_session_status_report_message(const TradeSessionStatusReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->trade_req_id[i]; }
  wire[at++] = record->flow_group_no;
  wire[at++] = record->trade_status;

  return at;
}

/* Trade Session Status Report Message off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_trade_session_status_report_message(TradeSessionStatusReportMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->trade_req_id[i] = wire[at++]; }
  record->flow_group_no = wire[at++];
  record->trade_status = wire[at++];

  return at;
}

/* what was read of Trade Session Status Report Message is what was written, byte for byte */
static void equal_trade_session_status_report_message(const TradeSessionStatusReportMessage *read, const TradeSessionStatusReportMessage *written) {
  assert(read->status_code == written->status_code);
  for (size_t i = 0; i < 2; i++) { assert(read->trade_req_id[i] == written->trade_req_id[i]); }
  assert(read->flow_group_no == written->flow_group_no);
  assert(read->trade_status == written->trade_status);
}

/* Trade Session Status Report Message: written and read back, then read and written back */
static void check_trade_session_status_report_message(void) {
  TradeSessionStatusReportMessage sent;
  TradeSessionStatusReportMessage got;
  uint8_t wire[5];
  uint8_t again[5];

  any_trade_session_status_report_message(&sent);
  assert(encode_trade_session_status_report_message(&sent, wire, 0) == 5);
  assert(decode_trade_session_status_report_message(&got, wire, 0) == 5);
  equal_trade_session_status_report_message(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_trade_session_status_report_message(&got, wire, 0) == 5);
  assert(encode_trade_session_status_report_message(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Text: 20 bytes --------------------------------------------------- */

/* Text product ID, naming a product by its Ascii character string symbol */
typedef struct {
  uint8_t symbol[20];  /* bytes 0 to 19 */
} SymbolText;

/* any Symbol Text at all: every byte one the checker chooses */
static void any_symbol_text(SymbolText *record) {
  for (size_t i = 0; i < 20; i++) { record->symbol[i] = arbitrary(); }
}

/* Symbol Text to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_symbol_text(const SymbolText *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->symbol[i]; }

  return at;
}

/* Symbol Text off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_symbol_text(SymbolText *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Text is what was written, byte for byte */
static void equal_symbol_text(const SymbolText *read, const SymbolText *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->symbol[i] == written->symbol[i]); }
}

/* Symbol Text: written and read back, then read and written back */
static void check_symbol_text(void) {
  SymbolText sent;
  SymbolText got;
  uint8_t wire[20];
  uint8_t again[20];

  any_symbol_text(&sent);
  assert(encode_symbol_text(&sent, wire, 0) == 20);
  assert(decode_symbol_text(&got, wire, 0) == 20);
  equal_symbol_text(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_text(&got, wire, 0) == 20);
  assert(encode_symbol_text(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Long Symbol Text: 40 bytes ---------------------------------------------- */

/* Text product ID in the long product format, naming a product by its Ascii character string symbol */
typedef struct {
  uint8_t long_symbol[40];  /* bytes 0 to 39 */
} LongSymbolText;

/* any Long Symbol Text at all: every byte one the checker chooses */
static void any_long_symbol_text(LongSymbolText *record) {
  for (size_t i = 0; i < 40; i++) { record->long_symbol[i] = arbitrary(); }
}

/* Long Symbol Text to the wire: 40 bytes from at, returning where the next byte goes */
static size_t encode_long_symbol_text(const LongSymbolText *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { wire[at++] = record->long_symbol[i]; }

  return at;
}

/* Long Symbol Text off the wire: 40 bytes from at, returning where the next byte lies */
static size_t decode_long_symbol_text(LongSymbolText *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 40; i++) { record->long_symbol[i] = wire[at++]; }

  return at;
}

/* what was read of Long Symbol Text is what was written, byte for byte */
static void equal_long_symbol_text(const LongSymbolText *read, const LongSymbolText *written) {
  for (size_t i = 0; i < 40; i++) { assert(read->long_symbol[i] == written->long_symbol[i]); }
}

/* Long Symbol Text: written and read back, then read and written back */
static void check_long_symbol_text(void) {
  LongSymbolText sent;
  LongSymbolText got;
  uint8_t wire[40];
  uint8_t again[40];

  any_long_symbol_text(&sent);
  assert(encode_long_symbol_text(&sent, wire, 0) == 40);
  assert(decode_long_symbol_text(&got, wire, 0) == 40);
  equal_long_symbol_text(&got, &sent);

  for (size_t i = 0; i < 40; i++) { wire[i] = arbitrary(); }
  assert(decode_long_symbol_text(&got, wire, 0) == 40);
  assert(encode_long_symbol_text(&got, again, 0) == 40);
  for (size_t i = 0; i < 40; i++) { assert(again[i] == wire[i]); }
}

/* ---- Org Trans Time Msg Time: 6 bytes ---------------------------------------- */

/* Tmp time format, the seconds since the epoch and the thousandth of a second */
typedef struct {
  uint8_t msg_time_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t ms[2];                /* bytes 4 to 5 */
} OrgTransTimeMsgTime;

/* any Org Trans Time Msg Time at all: every byte one the checker chooses */
static void any_org_trans_time_msg_time(OrgTransTimeMsgTime *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = arbitrary(); }
}

/* Org Trans Time Msg Time to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_org_trans_time_msg_time(const OrgTransTimeMsgTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_epoch_s[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ms[i]; }

  return at;
}

/* Org Trans Time Msg Time off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_org_trans_time_msg_time(OrgTransTimeMsgTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = wire[at++]; }

  return at;
}

/* what was read of Org Trans Time Msg Time is what was written, byte for byte */
static void equal_org_trans_time_msg_time(const OrgTransTimeMsgTime *read, const OrgTransTimeMsgTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_epoch_s[i] == written->msg_time_epoch_s[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ms[i] == written->ms[i]); }
}

/* Org Trans Time Msg Time: written and read back, then read and written back */
static void check_org_trans_time_msg_time(void) {
  OrgTransTimeMsgTime sent;
  OrgTransTimeMsgTime got;
  uint8_t wire[6];
  uint8_t again[6];

  any_org_trans_time_msg_time(&sent);
  assert(encode_org_trans_time_msg_time(&sent, wire, 0) == 6);
  assert(decode_org_trans_time_msg_time(&got, wire, 0) == 6);
  equal_org_trans_time_msg_time(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_org_trans_time_msg_time(&got, wire, 0) == 6);
  assert(encode_org_trans_time_msg_time(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transact Time Msg Time: 6 bytes ----------------------------------------- */

/* Tmp time format, the seconds since the epoch and the thousandth of a second */
typedef struct {
  uint8_t msg_time_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t ms[2];                /* bytes 4 to 5 */
} TransactTimeMsgTime;

/* any Transact Time Msg Time at all: every byte one the checker chooses */
static void any_transact_time_msg_time(TransactTimeMsgTime *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = arbitrary(); }
}

/* Transact Time Msg Time to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_transact_time_msg_time(const TransactTimeMsgTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_epoch_s[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ms[i]; }

  return at;
}

/* Transact Time Msg Time off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_transact_time_msg_time(TransactTimeMsgTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = wire[at++]; }

  return at;
}

/* what was read of Transact Time Msg Time is what was written, byte for byte */
static void equal_transact_time_msg_time(const TransactTimeMsgTime *read, const TransactTimeMsgTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_epoch_s[i] == written->msg_time_epoch_s[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ms[i] == written->ms[i]); }
}

/* Transact Time Msg Time: written and read back, then read and written back */
static void check_transact_time_msg_time(void) {
  TransactTimeMsgTime sent;
  TransactTimeMsgTime got;
  uint8_t wire[6];
  uint8_t again[6];

  any_transact_time_msg_time(&sent);
  assert(encode_transact_time_msg_time(&sent, wire, 0) == 6);
  assert(decode_transact_time_msg_time(&got, wire, 0) == 6);
  equal_transact_time_msg_time(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_transact_time_msg_time(&got, wire, 0) == 6);
  assert(encode_transact_time_msg_time(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Error Report Message: 26 bytes ------------------------------------------ */

/* Error report, with which Taifex rejects an order, quote or inquiry the futures commission merchant sent. */
typedef struct {
  uint8_t status_code;     /* byte 0 */
  uint8_t exec_type;       /* byte 1 */
  uint8_t fcm_id[2];       /* bytes 2 to 3 */
  uint8_t order_no[5];     /* bytes 4 to 8 */
  uint8_t ord_id[4];       /* bytes 9 to 12 */
  uint8_t user_define[8];  /* bytes 13 to 20 */
  uint8_t rpt_seq[4];      /* bytes 21 to 24 */
  uint8_t side;            /* byte 25 */
} ErrorReportMessage;

/* any Error Report Message at all: every byte one the checker chooses */
static void any_error_report_message(ErrorReportMessage *record) {
  record->status_code = arbitrary();
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->order_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_define[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rpt_seq[i] = arbitrary(); }
  record->side = arbitrary();
}

/* Error Report Message to the wire: 26 bytes from at, returning where the next byte goes */
static size_t encode_error_report_message(const ErrorReportMessage *record, uint8_t *wire, size_t at) {
  wire[at++] = record->status_code;
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fcm_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->order_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_define[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rpt_seq[i]; }
  wire[at++] = record->side;

  return at;
}

/* Error Report Message off the wire: 26 bytes from at, returning where the next byte lies */
static size_t decode_error_report_message(ErrorReportMessage *record, const uint8_t *wire, size_t at) {
  record->status_code = wire[at++];
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->order_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_define[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rpt_seq[i] = wire[at++]; }
  record->side = wire[at++];

  return at;
}

/* what was read of Error Report Message is what was written, byte for byte */
static void equal_error_report_message(const ErrorReportMessage *read, const ErrorReportMessage *written) {
  assert(read->status_code == written->status_code);
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 2; i++) { assert(read->fcm_id[i] == written->fcm_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->order_no[i] == written->order_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ord_id[i] == written->ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_define[i] == written->user_define[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rpt_seq[i] == written->rpt_seq[i]); }
  assert(read->side == written->side);
}

/* Error Report Message: written and read back, then read and written back */
static void check_error_report_message(void) {
  ErrorReportMessage sent;
  ErrorReportMessage got;
  uint8_t wire[26];
  uint8_t again[26];

  any_error_report_message(&sent);
  assert(encode_error_report_message(&sent, wire, 0) == 26);
  assert(decode_error_report_message(&got, wire, 0) == 26);
  equal_error_report_message(&got, &sent);

  for (size_t i = 0; i < 26; i++) { wire[i] = arbitrary(); }
  assert(decode_error_report_message(&got, wire, 0) == 26);
  assert(encode_error_report_message(&got, again, 0) == 26);
  for (size_t i = 0; i < 26; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bulletin Time Msg Time: 6 bytes ----------------------------------------- */

/* Tmp time format, the seconds since the epoch and the thousandth of a second */
typedef struct {
  uint8_t msg_time_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t ms[2];                /* bytes 4 to 5 */
} BulletinTimeMsgTime;

/* any Bulletin Time Msg Time at all: every byte one the checker chooses */
static void any_bulletin_time_msg_time(BulletinTimeMsgTime *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = arbitrary(); }
}

/* Bulletin Time Msg Time to the wire: 6 bytes from at, returning where the next byte goes */
static size_t encode_bulletin_time_msg_time(const BulletinTimeMsgTime *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_epoch_s[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->ms[i]; }

  return at;
}

/* Bulletin Time Msg Time off the wire: 6 bytes from at, returning where the next byte lies */
static size_t decode_bulletin_time_msg_time(BulletinTimeMsgTime *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->ms[i] = wire[at++]; }

  return at;
}

/* what was read of Bulletin Time Msg Time is what was written, byte for byte */
static void equal_bulletin_time_msg_time(const BulletinTimeMsgTime *read, const BulletinTimeMsgTime *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_epoch_s[i] == written->msg_time_epoch_s[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->ms[i] == written->ms[i]); }
}

/* Bulletin Time Msg Time: written and read back, then read and written back */
static void check_bulletin_time_msg_time(void) {
  BulletinTimeMsgTime sent;
  BulletinTimeMsgTime got;
  uint8_t wire[6];
  uint8_t again[6];

  any_bulletin_time_msg_time(&sent);
  assert(encode_bulletin_time_msg_time(&sent, wire, 0) == 6);
  assert(decode_bulletin_time_msg_time(&got, wire, 0) == 6);
  equal_bulletin_time_msg_time(&got, &sent);

  for (size_t i = 0; i < 6; i++) { wire[i] = arbitrary(); }
  assert(decode_bulletin_time_msg_time(&got, wire, 0) == 6);
  assert(encode_bulletin_time_msg_time(&got, again, 0) == 6);
  for (size_t i = 0; i < 6; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Num X: 4 bytes --------------------------------------------------- */

/* FLEX Numeric Single Product Serial number, naming a FLEX product by the serial number of the XP08 product and time flow group definition file */
typedef struct {
  uint8_t pseq[4];  /* bytes 0 to 3 */
} SymbolNumX;

/* any Symbol Num X at all: every byte one the checker chooses */
static void any_symbol_num_x(SymbolNumX *record) {
  for (size_t i = 0; i < 4; i++) { record->pseq[i] = arbitrary(); }
}

/* Symbol Num X to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_symbol_num_x(const SymbolNumX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pseq[i]; }

  return at;
}

/* Symbol Num X off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_symbol_num_x(SymbolNumX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->pseq[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Num X is what was written, byte for byte */
static void equal_symbol_num_x(const SymbolNumX *read, const SymbolNumX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->pseq[i] == written->pseq[i]); }
}

/* Symbol Num X: written and read back, then read and written back */
static void check_symbol_num_x(void) {
  SymbolNumX sent;
  SymbolNumX got;
  uint8_t wire[4];
  uint8_t again[4];

  any_symbol_num_x(&sent);
  assert(encode_symbol_num_x(&sent, wire, 0) == 4);
  assert(decode_symbol_num_x(&got, wire, 0) == 4);
  equal_symbol_num_x(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_num_x(&got, wire, 0) == 4);
  assert(encode_symbol_num_x(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Symbol Txt X: 20 bytes -------------------------------------------------- */

/* FLEX Textual Single Product Symbol, naming a FLEX product by the product symbol of the XP08 product and time flow group definition file */
typedef struct {
  uint8_t prod_id[20];  /* bytes 0 to 19 */
} SymbolTxtX;

/* any Symbol Txt X at all: every byte one the checker chooses */
static void any_symbol_txt_x(SymbolTxtX *record) {
  for (size_t i = 0; i < 20; i++) { record->prod_id[i] = arbitrary(); }
}

/* Symbol Txt X to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_symbol_txt_x(const SymbolTxtX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->prod_id[i]; }

  return at;
}

/* Symbol Txt X off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_symbol_txt_x(SymbolTxtX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->prod_id[i] = wire[at++]; }

  return at;
}

/* what was read of Symbol Txt X is what was written, byte for byte */
static void equal_symbol_txt_x(const SymbolTxtX *read, const SymbolTxtX *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->prod_id[i] == written->prod_id[i]); }
}

/* Symbol Txt X: written and read back, then read and written back */
static void check_symbol_txt_x(void) {
  SymbolTxtX sent;
  SymbolTxtX got;
  uint8_t wire[20];
  uint8_t again[20];

  any_symbol_txt_x(&sent);
  assert(encode_symbol_txt_x(&sent, wire, 0) == 20);
  assert(decode_symbol_txt_x(&got, wire, 0) == 20);
  equal_symbol_txt_x(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_symbol_txt_x(&got, wire, 0) == 20);
  assert(encode_symbol_txt_x(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Sym Symbol Num X: 4 bytes ------------------------------------------- */

/* FLEX Numeric Single Product Serial number, naming a FLEX product by the serial number of the XP08 product and time flow group definition file */
typedef struct {
  uint8_t pseq[4];  /* bytes 0 to 3 */
} LegSymSymbolNumX;

/* any Leg Sym Symbol Num X at all: every byte one the checker chooses */
static void any_leg_sym_symbol_num_x(LegSymSymbolNumX *record) {
  for (size_t i = 0; i < 4; i++) { record->pseq[i] = arbitrary(); }
}

/* Leg Sym Symbol Num X to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_leg_sym_symbol_num_x(const LegSymSymbolNumX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->pseq[i]; }

  return at;
}

/* Leg Sym Symbol Num X off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_leg_sym_symbol_num_x(LegSymSymbolNumX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->pseq[i] = wire[at++]; }

  return at;
}

/* what was read of Leg Sym Symbol Num X is what was written, byte for byte */
static void equal_leg_sym_symbol_num_x(const LegSymSymbolNumX *read, const LegSymSymbolNumX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->pseq[i] == written->pseq[i]); }
}

/* Leg Sym Symbol Num X: written and read back, then read and written back */
static void check_leg_sym_symbol_num_x(void) {
  LegSymSymbolNumX sent;
  LegSymSymbolNumX got;
  uint8_t wire[4];
  uint8_t again[4];

  any_leg_sym_symbol_num_x(&sent);
  assert(encode_leg_sym_symbol_num_x(&sent, wire, 0) == 4);
  assert(decode_leg_sym_symbol_num_x(&got, wire, 0) == 4);
  equal_leg_sym_symbol_num_x(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_sym_symbol_num_x(&got, wire, 0) == 4);
  assert(encode_leg_sym_symbol_num_x(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Leg Sym Symbol Txt X: 20 bytes ------------------------------------------ */

/* FLEX Textual Single Product Symbol, naming a FLEX product by the product symbol of the XP08 product and time flow group definition file */
typedef struct {
  uint8_t prod_id[20];  /* bytes 0 to 19 */
} LegSymSymbolTxtX;

/* any Leg Sym Symbol Txt X at all: every byte one the checker chooses */
static void any_leg_sym_symbol_txt_x(LegSymSymbolTxtX *record) {
  for (size_t i = 0; i < 20; i++) { record->prod_id[i] = arbitrary(); }
}

/* Leg Sym Symbol Txt X to the wire: 20 bytes from at, returning where the next byte goes */
static size_t encode_leg_sym_symbol_txt_x(const LegSymSymbolTxtX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->prod_id[i]; }

  return at;
}

/* Leg Sym Symbol Txt X off the wire: 20 bytes from at, returning where the next byte lies */
static size_t decode_leg_sym_symbol_txt_x(LegSymSymbolTxtX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 20; i++) { record->prod_id[i] = wire[at++]; }

  return at;
}

/* what was read of Leg Sym Symbol Txt X is what was written, byte for byte */
static void equal_leg_sym_symbol_txt_x(const LegSymSymbolTxtX *read, const LegSymSymbolTxtX *written) {
  for (size_t i = 0; i < 20; i++) { assert(read->prod_id[i] == written->prod_id[i]); }
}

/* Leg Sym Symbol Txt X: written and read back, then read and written back */
static void check_leg_sym_symbol_txt_x(void) {
  LegSymSymbolTxtX sent;
  LegSymSymbolTxtX got;
  uint8_t wire[20];
  uint8_t again[20];

  any_leg_sym_symbol_txt_x(&sent);
  assert(encode_leg_sym_symbol_txt_x(&sent, wire, 0) == 20);
  assert(decode_leg_sym_symbol_txt_x(&got, wire, 0) == 20);
  equal_leg_sym_symbol_txt_x(&got, &sent);

  for (size_t i = 0; i < 20; i++) { wire[i] = arbitrary(); }
  assert(decode_leg_sym_symbol_txt_x(&got, wire, 0) == 20);
  assert(encode_leg_sym_symbol_txt_x(&got, again, 0) == 20);
  for (size_t i = 0; i < 20; i++) { assert(again[i] == wire[i]); }
}

/* ---- Request For Supplementary Flex Group Report Message: 11 bytes ----------- */

/* Request for supplementary FLEX group report message, with which the futures commission merchant requests the group messages from request_start_seq plus one to end_out_bound_num. */
typedef struct {
  SubHdr sub_hdr;                /* bytes 0 to 5 */
  uint8_t part_id;               /* byte 6 */
  uint8_t request_start_seq[4];  /* bytes 7 to 10 */
} RequestForSupplementaryFlexGroupReportMessage;

/* any Request For Supplementary Flex Group Report Message at all: every byte one the checker chooses */
static void any_request_for_supplementary_flex_group_report_message(RequestForSupplementaryFlexGroupReportMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  record->part_id = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->request_start_seq[i] = arbitrary(); }
}

/* Request For Supplementary Flex Group Report Message to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_request_for_supplementary_flex_group_report_message(const RequestForSupplementaryFlexGroupReportMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  wire[at++] = record->part_id;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->request_start_seq[i]; }

  return at;
}

/* Request For Supplementary Flex Group Report Message off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_request_for_supplementary_flex_group_report_message(RequestForSupplementaryFlexGroupReportMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  record->part_id = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->request_start_seq[i] = wire[at++]; }

  return at;
}

/* what was read of Request For Supplementary Flex Group Report Message is what was written, byte for byte */
static void equal_request_for_supplementary_flex_group_report_message(const RequestForSupplementaryFlexGroupReportMessage *read, const RequestForSupplementaryFlexGroupReportMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  assert(read->part_id == written->part_id);
  for (size_t i = 0; i < 4; i++) { assert(read->request_start_seq[i] == written->request_start_seq[i]); }
}

/* Request For Supplementary Flex Group Report Message: written and read back, then read and written back */
static void check_request_for_supplementary_flex_group_report_message(void) {
  RequestForSupplementaryFlexGroupReportMessage sent;
  RequestForSupplementaryFlexGroupReportMessage got;
  uint8_t wire[11];
  uint8_t again[11];

  any_request_for_supplementary_flex_group_report_message(&sent);
  assert(encode_request_for_supplementary_flex_group_report_message(&sent, wire, 0) == 11);
  assert(decode_request_for_supplementary_flex_group_report_message(&got, wire, 0) == 11);
  equal_request_for_supplementary_flex_group_report_message(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_request_for_supplementary_flex_group_report_message(&got, wire, 0) == 11);
  assert(encode_request_for_supplementary_flex_group_report_message(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Temporary Suspension Of Supplementary Flex Group Report Message: 7 bytes ---- */

/* Temporary suspension of supplementary FLEX group report message, with which the futures commission merchant pauses the supplementation of a partition. */
typedef struct {
  SubHdr sub_hdr;   /* bytes 0 to 5 */
  uint8_t part_id;  /* byte 6 */
} TemporarySuspensionOfSupplementaryFlexGroupReportMessage;

/* any Temporary Suspension Of Supplementary Flex Group Report Message at all: every byte one the checker chooses */
static void any_temporary_suspension_of_supplementary_flex_group_report_message(TemporarySuspensionOfSupplementaryFlexGroupReportMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  record->part_id = arbitrary();
}

/* Temporary Suspension Of Supplementary Flex Group Report Message to the wire: 7 bytes from at, returning where the next byte goes */
static size_t encode_temporary_suspension_of_supplementary_flex_group_report_message(const TemporarySuspensionOfSupplementaryFlexGroupReportMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  wire[at++] = record->part_id;

  return at;
}

/* Temporary Suspension Of Supplementary Flex Group Report Message off the wire: 7 bytes from at, returning where the next byte lies */
static size_t decode_temporary_suspension_of_supplementary_flex_group_report_message(TemporarySuspensionOfSupplementaryFlexGroupReportMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  record->part_id = wire[at++];

  return at;
}

/* what was read of Temporary Suspension Of Supplementary Flex Group Report Message is what was written, byte for byte */
static void equal_temporary_suspension_of_supplementary_flex_group_report_message(const TemporarySuspensionOfSupplementaryFlexGroupReportMessage *read, const TemporarySuspensionOfSupplementaryFlexGroupReportMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  assert(read->part_id == written->part_id);
}

/* Temporary Suspension Of Supplementary Flex Group Report Message: written and read back, then read and written back */
static void check_temporary_suspension_of_supplementary_flex_group_report_message(void) {
  TemporarySuspensionOfSupplementaryFlexGroupReportMessage sent;
  TemporarySuspensionOfSupplementaryFlexGroupReportMessage got;
  uint8_t wire[7];
  uint8_t again[7];

  any_temporary_suspension_of_supplementary_flex_group_report_message(&sent);
  assert(encode_temporary_suspension_of_supplementary_flex_group_report_message(&sent, wire, 0) == 7);
  assert(decode_temporary_suspension_of_supplementary_flex_group_report_message(&got, wire, 0) == 7);
  equal_temporary_suspension_of_supplementary_flex_group_report_message(&got, &sent);

  for (size_t i = 0; i < 7; i++) { wire[i] = arbitrary(); }
  assert(decode_temporary_suspension_of_supplementary_flex_group_report_message(&got, wire, 0) == 7);
  assert(encode_temporary_suspension_of_supplementary_flex_group_report_message(&got, again, 0) == 7);
  for (size_t i = 0; i < 7; i++) { assert(again[i] == wire[i]); }
}

/* ---- Flex Product Definition Request Message: 56 bytes ----------------------- */

/* FLEX Product Definition request message, which the futures commission merchant submits through the order and execution report line and Taifex answers with RX20. */
typedef struct {
  SubHdr sub_hdr;                 /* bytes 0 to 5 */
  uint8_t security_request_type;  /* byte 6 */
  uint8_t security_req_id[4];     /* bytes 7 to 10 */
  uint8_t type;                   /* byte 11 */
  uint8_t fcm_id[2];              /* bytes 12 to 13 */
  uint8_t investor_acno[4];       /* bytes 14 to 17 */
  uint8_t application_type;       /* byte 18 */
  uint8_t root_symbol[3];         /* bytes 19 to 21 */
  uint8_t expiry_type;            /* byte 22 */
  uint8_t contract_date[8];       /* bytes 23 to 30 */
  uint8_t strike_price[4];        /* bytes 31 to 34 */
  uint8_t call_put_code;          /* byte 35 */
  uint8_t reserved_20[20];        /* bytes 36 to 55 */
} FlexProductDefinitionRequestMessage;

/* any Flex Product Definition Request Message at all: every byte one the checker chooses */
static void any_flex_product_definition_request_message(FlexProductDefinitionRequestMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  record->security_request_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = arbitrary(); }
  record->type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->investor_acno[i] = arbitrary(); }
  record->application_type = arbitrary();
  for (size_t i = 0; i < 3; i++) { record->root_symbol[i] = arbitrary(); }
  record->expiry_type = arbitrary();
  for (size_t i = 0; i < 8; i++) { record->contract_date[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = arbitrary(); }
  record->call_put_code = arbitrary();
  for (size_t i = 0; i < 20; i++) { record->reserved_20[i] = arbitrary(); }
}

/* Flex Product Definition Request Message to the wire: 56 bytes from at, returning where the next byte goes */
static size_t encode_flex_product_definition_request_message(const FlexProductDefinitionRequestMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  wire[at++] = record->security_request_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_req_id[i]; }
  wire[at++] = record->type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fcm_id[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->investor_acno[i]; }
  wire[at++] = record->application_type;
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->root_symbol[i]; }
  wire[at++] = record->expiry_type;
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->contract_date[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->strike_price[i]; }
  wire[at++] = record->call_put_code;
  for (size_t i = 0; i < 20; i++) { wire[at++] = record->reserved_20[i]; }

  return at;
}

/* Flex Product Definition Request Message off the wire: 56 bytes from at, returning where the next byte lies */
static size_t decode_flex_product_definition_request_message(FlexProductDefinitionRequestMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  record->security_request_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = wire[at++]; }
  record->type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->investor_acno[i] = wire[at++]; }
  record->application_type = wire[at++];
  for (size_t i = 0; i < 3; i++) { record->root_symbol[i] = wire[at++]; }
  record->expiry_type = wire[at++];
  for (size_t i = 0; i < 8; i++) { record->contract_date[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->strike_price[i] = wire[at++]; }
  record->call_put_code = wire[at++];
  for (size_t i = 0; i < 20; i++) { record->reserved_20[i] = wire[at++]; }

  return at;
}

/* what was read of Flex Product Definition Request Message is what was written, byte for byte */
static void equal_flex_product_definition_request_message(const FlexProductDefinitionRequestMessage *read, const FlexProductDefinitionRequestMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  assert(read->security_request_type == written->security_request_type);
  for (size_t i = 0; i < 4; i++) { assert(read->security_req_id[i] == written->security_req_id[i]); }
  assert(read->type == written->type);
  for (size_t i = 0; i < 2; i++) { assert(read->fcm_id[i] == written->fcm_id[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->investor_acno[i] == written->investor_acno[i]); }
  assert(read->application_type == written->application_type);
  for (size_t i = 0; i < 3; i++) { assert(read->root_symbol[i] == written->root_symbol[i]); }
  assert(read->expiry_type == written->expiry_type);
  for (size_t i = 0; i < 8; i++) { assert(read->contract_date[i] == written->contract_date[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->strike_price[i] == written->strike_price[i]); }
  assert(read->call_put_code == written->call_put_code);
  for (size_t i = 0; i < 20; i++) { assert(read->reserved_20[i] == written->reserved_20[i]); }
}

/* Flex Product Definition Request Message: written and read back, then read and written back */
static void check_flex_product_definition_request_message(void) {
  FlexProductDefinitionRequestMessage sent;
  FlexProductDefinitionRequestMessage got;
  uint8_t wire[56];
  uint8_t again[56];

  any_flex_product_definition_request_message(&sent);
  assert(encode_flex_product_definition_request_message(&sent, wire, 0) == 56);
  assert(decode_flex_product_definition_request_message(&got, wire, 0) == 56);
  equal_flex_product_definition_request_message(&got, &sent);

  for (size_t i = 0; i < 56; i++) { wire[i] = arbitrary(); }
  assert(decode_flex_product_definition_request_message(&got, wire, 0) == 56);
  assert(encode_flex_product_definition_request_message(&got, again, 0) == 56);
  for (size_t i = 0; i < 56; i++) { assert(again[i] == wire[i]); }
}

/* ---- Org Trans Time Msg Time X: 8 bytes -------------------------------------- */

/* Tmp Expanded Time Format, the seconds since the epoch and the billionth of a second, which the FLEX reports carry in place of msg_time */
typedef struct {
  uint8_t msg_time_x_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t nanosecond[4];          /* bytes 4 to 7 */
} OrgTransTimeMsgTimeX;

/* any Org Trans Time Msg Time X at all: every byte one the checker chooses */
static void any_org_trans_time_msg_time_x(OrgTransTimeMsgTimeX *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
}

/* Org Trans Time Msg Time X to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_org_trans_time_msg_time_x(const OrgTransTimeMsgTimeX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_x_epoch_s[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }

  return at;
}

/* Org Trans Time Msg Time X off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_org_trans_time_msg_time_x(OrgTransTimeMsgTimeX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }

  return at;
}

/* what was read of Org Trans Time Msg Time X is what was written, byte for byte */
static void equal_org_trans_time_msg_time_x(const OrgTransTimeMsgTimeX *read, const OrgTransTimeMsgTimeX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_x_epoch_s[i] == written->msg_time_x_epoch_s[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
}

/* Org Trans Time Msg Time X: written and read back, then read and written back */
static void check_org_trans_time_msg_time_x(void) {
  OrgTransTimeMsgTimeX sent;
  OrgTransTimeMsgTimeX got;
  uint8_t wire[8];
  uint8_t again[8];

  any_org_trans_time_msg_time_x(&sent);
  assert(encode_org_trans_time_msg_time_x(&sent, wire, 0) == 8);
  assert(decode_org_trans_time_msg_time_x(&got, wire, 0) == 8);
  equal_org_trans_time_msg_time_x(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_org_trans_time_msg_time_x(&got, wire, 0) == 8);
  assert(encode_org_trans_time_msg_time_x(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Transact Time Msg Time X: 8 bytes --------------------------------------- */

/* Tmp Expanded Time Format, the seconds since the epoch and the billionth of a second, which the FLEX reports carry in place of msg_time */
typedef struct {
  uint8_t msg_time_x_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t nanosecond[4];          /* bytes 4 to 7 */
} TransactTimeMsgTimeX;

/* any Transact Time Msg Time X at all: every byte one the checker chooses */
static void any_transact_time_msg_time_x(TransactTimeMsgTimeX *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
}

/* Transact Time Msg Time X to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_transact_time_msg_time_x(const TransactTimeMsgTimeX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_x_epoch_s[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }

  return at;
}

/* Transact Time Msg Time X off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_transact_time_msg_time_x(TransactTimeMsgTimeX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }

  return at;
}

/* what was read of Transact Time Msg Time X is what was written, byte for byte */
static void equal_transact_time_msg_time_x(const TransactTimeMsgTimeX *read, const TransactTimeMsgTimeX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_x_epoch_s[i] == written->msg_time_x_epoch_s[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
}

/* Transact Time Msg Time X: written and read back, then read and written back */
static void check_transact_time_msg_time_x(void) {
  TransactTimeMsgTimeX sent;
  TransactTimeMsgTimeX got;
  uint8_t wire[8];
  uint8_t again[8];

  any_transact_time_msg_time_x(&sent);
  assert(encode_transact_time_msg_time_x(&sent, wire, 0) == 8);
  assert(decode_transact_time_msg_time_x(&got, wire, 0) == 8);
  equal_transact_time_msg_time_x(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_transact_time_msg_time_x(&got, wire, 0) == 8);
  assert(encode_transact_time_msg_time_x(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Flex Error Report Message: 47 bytes ------------------------------------- */

/* FLEX Error Report, with which Taifex rejects a FLEX order, quote or inquiry. */
typedef struct {
  SubHdr sub_hdr;               /* bytes 0 to 5 */
  uint8_t part_id;              /* byte 6 */
  uint8_t ori_message_type;     /* byte 7 */
  uint8_t wide_status_code[2];  /* bytes 8 to 9 */
  uint8_t exec_type;            /* byte 10 */
  uint8_t fcm_id[2];            /* bytes 11 to 12 */
  uint8_t order_no[5];          /* bytes 13 to 17 */
  uint8_t ord_id[4];            /* bytes 18 to 21 */
  uint8_t user_define[8];       /* bytes 22 to 29 */
  uint8_t rpt_seq[4];           /* bytes 30 to 33 */
  uint8_t side;                 /* byte 34 */
  uint8_t reserved_12[12];      /* bytes 35 to 46 */
} FlexErrorReportMessage;

/* any Flex Error Report Message at all: every byte one the checker chooses */
static void any_flex_error_report_message(FlexErrorReportMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  record->part_id = arbitrary();
  record->ori_message_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = arbitrary(); }
  record->exec_type = arbitrary();
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = arbitrary(); }
  for (size_t i = 0; i < 5; i++) { record->order_no[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->ord_id[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->user_define[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->rpt_seq[i] = arbitrary(); }
  record->side = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = arbitrary(); }
}

/* Flex Error Report Message to the wire: 47 bytes from at, returning where the next byte goes */
static size_t encode_flex_error_report_message(const FlexErrorReportMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  wire[at++] = record->part_id;
  wire[at++] = record->ori_message_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->wide_status_code[i]; }
  wire[at++] = record->exec_type;
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->fcm_id[i]; }
  for (size_t i = 0; i < 5; i++) { wire[at++] = record->order_no[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->ord_id[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->user_define[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->rpt_seq[i]; }
  wire[at++] = record->side;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->reserved_12[i]; }

  return at;
}

/* Flex Error Report Message off the wire: 47 bytes from at, returning where the next byte lies */
static size_t decode_flex_error_report_message(FlexErrorReportMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  record->part_id = wire[at++];
  record->ori_message_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = wire[at++]; }
  record->exec_type = wire[at++];
  for (size_t i = 0; i < 2; i++) { record->fcm_id[i] = wire[at++]; }
  for (size_t i = 0; i < 5; i++) { record->order_no[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->ord_id[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->user_define[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->rpt_seq[i] = wire[at++]; }
  record->side = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->reserved_12[i] = wire[at++]; }

  return at;
}

/* what was read of Flex Error Report Message is what was written, byte for byte */
static void equal_flex_error_report_message(const FlexErrorReportMessage *read, const FlexErrorReportMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  assert(read->part_id == written->part_id);
  assert(read->ori_message_type == written->ori_message_type);
  for (size_t i = 0; i < 2; i++) { assert(read->wide_status_code[i] == written->wide_status_code[i]); }
  assert(read->exec_type == written->exec_type);
  for (size_t i = 0; i < 2; i++) { assert(read->fcm_id[i] == written->fcm_id[i]); }
  for (size_t i = 0; i < 5; i++) { assert(read->order_no[i] == written->order_no[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->ord_id[i] == written->ord_id[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->user_define[i] == written->user_define[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->rpt_seq[i] == written->rpt_seq[i]); }
  assert(read->side == written->side);
  for (size_t i = 0; i < 12; i++) { assert(read->reserved_12[i] == written->reserved_12[i]); }
}

/* Flex Error Report Message: written and read back, then read and written back */
static void check_flex_error_report_message(void) {
  FlexErrorReportMessage sent;
  FlexErrorReportMessage got;
  uint8_t wire[47];
  uint8_t again[47];

  any_flex_error_report_message(&sent);
  assert(encode_flex_error_report_message(&sent, wire, 0) == 47);
  assert(decode_flex_error_report_message(&got, wire, 0) == 47);
  equal_flex_error_report_message(&got, &sent);

  for (size_t i = 0; i < 47; i++) { wire[i] = arbitrary(); }
  assert(decode_flex_error_report_message(&got, wire, 0) == 47);
  assert(encode_flex_error_report_message(&got, again, 0) == 47);
  for (size_t i = 0; i < 47; i++) { assert(again[i] == wire[i]); }
}

/* ---- Flex Product Definition Message: 13 bytes ------------------------------- */

/* FLEX Product Definition message, with which Taifex answers a FLEX Product Definition request. */
typedef struct {
  SubHdr sub_hdr;                 /* bytes 0 to 5 */
  uint8_t security_request_type;  /* byte 6 */
  uint8_t security_req_id[4];     /* bytes 7 to 10 */
  uint8_t wide_status_code[2];    /* bytes 11 to 12 */
} FlexProductDefinitionMessage;

/* any Flex Product Definition Message at all: every byte one the checker chooses */
static void any_flex_product_definition_message(FlexProductDefinitionMessage *record) {
  any_sub_hdr(&record->sub_hdr);
  record->security_request_type = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = arbitrary(); }
}

/* Flex Product Definition Message to the wire: 13 bytes from at, returning where the next byte goes */
static size_t encode_flex_product_definition_message(const FlexProductDefinitionMessage *record, uint8_t *wire, size_t at) {
  at = encode_sub_hdr(&record->sub_hdr, wire, at);
  wire[at++] = record->security_request_type;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->security_req_id[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->wide_status_code[i]; }

  return at;
}

/* Flex Product Definition Message off the wire: 13 bytes from at, returning where the next byte lies */
static size_t decode_flex_product_definition_message(FlexProductDefinitionMessage *record, const uint8_t *wire, size_t at) {
  at = decode_sub_hdr(&record->sub_hdr, wire, at);
  record->security_request_type = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->security_req_id[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->wide_status_code[i] = wire[at++]; }

  return at;
}

/* what was read of Flex Product Definition Message is what was written, byte for byte */
static void equal_flex_product_definition_message(const FlexProductDefinitionMessage *read, const FlexProductDefinitionMessage *written) {
  equal_sub_hdr(&read->sub_hdr, &written->sub_hdr);
  assert(read->security_request_type == written->security_request_type);
  for (size_t i = 0; i < 4; i++) { assert(read->security_req_id[i] == written->security_req_id[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->wide_status_code[i] == written->wide_status_code[i]); }
}

/* Flex Product Definition Message: written and read back, then read and written back */
static void check_flex_product_definition_message(void) {
  FlexProductDefinitionMessage sent;
  FlexProductDefinitionMessage got;
  uint8_t wire[13];
  uint8_t again[13];

  any_flex_product_definition_message(&sent);
  assert(encode_flex_product_definition_message(&sent, wire, 0) == 13);
  assert(decode_flex_product_definition_message(&got, wire, 0) == 13);
  equal_flex_product_definition_message(&got, &sent);

  for (size_t i = 0; i < 13; i++) { wire[i] = arbitrary(); }
  assert(decode_flex_product_definition_message(&got, wire, 0) == 13);
  assert(encode_flex_product_definition_message(&got, again, 0) == 13);
  for (size_t i = 0; i < 13; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bulletin Time Msg Time X: 8 bytes --------------------------------------- */

/* Tmp Expanded Time Format, the seconds since the epoch and the billionth of a second, which the FLEX reports carry in place of msg_time */
typedef struct {
  uint8_t msg_time_x_epoch_s[4];  /* bytes 0 to 3 */
  uint8_t nanosecond[4];          /* bytes 4 to 7 */
} BulletinTimeMsgTimeX;

/* any Bulletin Time Msg Time X at all: every byte one the checker chooses */
static void any_bulletin_time_msg_time_x(BulletinTimeMsgTimeX *record) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = arbitrary(); }
}

/* Bulletin Time Msg Time X to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_bulletin_time_msg_time_x(const BulletinTimeMsgTimeX *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->msg_time_x_epoch_s[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->nanosecond[i]; }

  return at;
}

/* Bulletin Time Msg Time X off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_bulletin_time_msg_time_x(BulletinTimeMsgTimeX *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 4; i++) { record->msg_time_x_epoch_s[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->nanosecond[i] = wire[at++]; }

  return at;
}

/* what was read of Bulletin Time Msg Time X is what was written, byte for byte */
static void equal_bulletin_time_msg_time_x(const BulletinTimeMsgTimeX *read, const BulletinTimeMsgTimeX *written) {
  for (size_t i = 0; i < 4; i++) { assert(read->msg_time_x_epoch_s[i] == written->msg_time_x_epoch_s[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->nanosecond[i] == written->nanosecond[i]); }
}

/* Bulletin Time Msg Time X: written and read back, then read and written back */
static void check_bulletin_time_msg_time_x(void) {
  BulletinTimeMsgTimeX sent;
  BulletinTimeMsgTimeX got;
  uint8_t wire[8];
  uint8_t again[8];

  any_bulletin_time_msg_time_x(&sent);
  assert(encode_bulletin_time_msg_time_x(&sent, wire, 0) == 8);
  assert(decode_bulletin_time_msg_time_x(&got, wire, 0) == 8);
  equal_bulletin_time_msg_time_x(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_bulletin_time_msg_time_x(&got, wire, 0) == 8);
  assert(encode_bulletin_time_msg_time_x(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Message Tail: 1 byte ---------------------------------------------------- */

/* Tmp Message Tail, carrying the check sum of a message */
typedef struct {
  uint8_t check_sum;  /* byte 0 */
} MessageTail;

/* any Message Tail at all: every byte one the checker chooses */
static void any_message_tail(MessageTail *record) {
  record->check_sum = arbitrary();
}

/* Message Tail to the wire: 1 byte from at, returning where the next byte goes */
static size_t encode_message_tail(const MessageTail *record, uint8_t *wire, size_t at) {
  wire[at++] = record->check_sum;

  return at;
}

/* Message Tail off the wire: 1 byte from at, returning where the next byte lies */
static size_t decode_message_tail(MessageTail *record, const uint8_t *wire, size_t at) {
  record->check_sum = wire[at++];

  return at;
}

/* what was read of Message Tail is what was written, byte for byte */
static void equal_message_tail(const MessageTail *read, const MessageTail *written) {
  assert(read->check_sum == written->check_sum);
}

/* Message Tail: written and read back, then read and written back */
static void check_message_tail(void) {
  MessageTail sent;
  MessageTail got;
  uint8_t wire[1];
  uint8_t again[1];

  any_message_tail(&sent);
  assert(encode_message_tail(&sent, wire, 0) == 1);
  assert(decode_message_tail(&got, wire, 0) == 1);
  equal_message_tail(&got, &sent);

  for (size_t i = 0; i < 1; i++) { wire[i] = arbitrary(); }
  assert(decode_message_tail(&got, wire, 0) == 1);
  assert(encode_message_tail(&got, again, 0) == 1);
  for (size_t i = 0; i < 1; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_header_time();
  check_hdr();
  check_wake_up_call_message();
  check_wake_up_call_confirmed_message();
  check_logon_notice_message();
  check_sub_hdr();
  check_final_sequential_number_notification_for_group_message();
  check_request_logon_message();
  check_resend_report_confirmed_message();
  check_activate_application_system_message();
  check_activate_application_system_confirmed_message();
  check_logout_confirmed_message();
  check_confirm_connection_message();
  check_connection_confirmed_message();
  check_trade_session_status_request_message();
  check_trade_session_status_report_message();
  check_symbol_text();
  check_long_symbol_text();
  check_org_trans_time_msg_time();
  check_transact_time_msg_time();
  check_error_report_message();
  check_bulletin_time_msg_time();
  check_symbol_num_x();
  check_symbol_txt_x();
  check_leg_sym_symbol_num_x();
  check_leg_sym_symbol_txt_x();
  check_request_for_supplementary_flex_group_report_message();
  check_temporary_suspension_of_supplementary_flex_group_report_message();
  check_flex_product_definition_request_message();
  check_org_trans_time_msg_time_x();
  check_transact_time_msg_time_x();
  check_flex_error_report_message();
  check_flex_product_definition_message();
  check_bulletin_time_msg_time_x();
  check_message_tail();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
