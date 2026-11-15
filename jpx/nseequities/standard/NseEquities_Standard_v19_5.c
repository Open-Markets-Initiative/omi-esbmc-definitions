// jpx/nseequities/standard/NseEquities_Standard_v19_5.c
/*
 * Japan Exchange Group Standard
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
 *   - the dispatch that chooses a message by its type
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

/* ---- Message Serial No: 11 bytes --------------------------------------------- */

/* Numbered from 1 on each Multicast Group, with the multicast group number in the first to third byte */
typedef struct {
  uint8_t multicast_group_number[3];  /* bytes 0 to 2 */
  uint8_t sequence_number[8];         /* bytes 3 to 10 */
} MessageSerialNo;

/* any Message Serial No at all: every byte one the checker chooses */
static void any_message_serial_no(MessageSerialNo *record) {
  for (size_t i = 0; i < 3; i++) { record->multicast_group_number[i] = arbitrary(); }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = arbitrary(); }
}

/* Message Serial No to the wire: 11 bytes from at, returning where the next byte goes */
static size_t encode_message_serial_no(const MessageSerialNo *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->multicast_group_number[i]; }
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->sequence_number[i]; }

  return at;
}

/* Message Serial No off the wire: 11 bytes from at, returning where the next byte lies */
static size_t decode_message_serial_no(MessageSerialNo *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->multicast_group_number[i] = wire[at++]; }
  for (size_t i = 0; i < 8; i++) { record->sequence_number[i] = wire[at++]; }

  return at;
}

/* what was read of Message Serial No is what was written, byte for byte */
static void equal_message_serial_no(const MessageSerialNo *read, const MessageSerialNo *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->multicast_group_number[i] == written->multicast_group_number[i]); }
  for (size_t i = 0; i < 8; i++) { assert(read->sequence_number[i] == written->sequence_number[i]); }
}

/* Message Serial No: written and read back, then read and written back */
static void check_message_serial_no(void) {
  MessageSerialNo sent;
  MessageSerialNo got;
  uint8_t wire[11];
  uint8_t again[11];

  any_message_serial_no(&sent);
  assert(encode_message_serial_no(&sent, wire, 0) == 11);
  assert(decode_message_serial_no(&got, wire, 0) == 11);
  equal_message_serial_no(&got, &sent);

  for (size_t i = 0; i < 11; i++) { wire[i] = arbitrary(); }
  assert(decode_message_serial_no(&got, wire, 0) == 11);
  assert(encode_message_serial_no(&got, again, 0) == 11);
  for (size_t i = 0; i < 11; i++) { assert(again[i] == wire[i]); }
}

/* ---- Issue Classification: 4 bytes ------------------------------------------- */

/* Set in issue realtime message and issue basic message. In the case of Control, Index and Statistics Message, space is set. */
typedef struct {
  uint8_t issue_classification_large_classification[2];   /* bytes 0 to 1 */
  uint8_t issue_classification_medium_classification[2];  /* bytes 2 to 3 */
} IssueClassification;

/* any Issue Classification at all: every byte one the checker chooses */
static void any_issue_classification(IssueClassification *record) {
  for (size_t i = 0; i < 2; i++) { record->issue_classification_large_classification[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->issue_classification_medium_classification[i] = arbitrary(); }
}

/* Issue Classification to the wire: 4 bytes from at, returning where the next byte goes */
static size_t encode_issue_classification(const IssueClassification *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_classification_large_classification[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_classification_medium_classification[i]; }

  return at;
}

/* Issue Classification off the wire: 4 bytes from at, returning where the next byte lies */
static size_t decode_issue_classification(IssueClassification *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->issue_classification_large_classification[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->issue_classification_medium_classification[i] = wire[at++]; }

  return at;
}

/* what was read of Issue Classification is what was written, byte for byte */
static void equal_issue_classification(const IssueClassification *read, const IssueClassification *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->issue_classification_large_classification[i] == written->issue_classification_large_classification[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->issue_classification_medium_classification[i] == written->issue_classification_medium_classification[i]); }
}

/* Issue Classification: written and read back, then read and written back */
static void check_issue_classification(void) {
  IssueClassification sent;
  IssueClassification got;
  uint8_t wire[4];
  uint8_t again[4];

  any_issue_classification(&sent);
  assert(encode_issue_classification(&sent, wire, 0) == 4);
  assert(decode_issue_classification(&got, wire, 0) == 4);
  equal_issue_classification(&got, &sent);

  for (size_t i = 0; i < 4; i++) { wire[i] = arbitrary(); }
  assert(decode_issue_classification(&got, wire, 0) == 4);
  assert(encode_issue_classification(&got, again, 0) == 4);
  for (size_t i = 0; i < 4; i++) { assert(again[i] == wire[i]); }
}

/* ---- Stock Issue Code: 12 bytes ---------------------------------------------- */

/* Issue Code layout a. Stocks, used when Issue Classification Large Classification is 01 Stock-Related. FLEX Issue Code is set with right-align. */
typedef struct {
  uint8_t stock_space[7];             /* bytes 0 to 6 */
  uint8_t stock_proper_name_code[4];  /* bytes 7 to 10 */
  uint8_t stock_reserved_code;        /* byte 11 */
} StockIssueCode;

/* any Stock Issue Code at all: every byte one the checker chooses */
static void any_stock_issue_code(StockIssueCode *record) {
  for (size_t i = 0; i < 7; i++) { record->stock_space[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->stock_proper_name_code[i] = arbitrary(); }
  record->stock_reserved_code = arbitrary();
}

/* Stock Issue Code to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_stock_issue_code(const StockIssueCode *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { wire[at++] = record->stock_space[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->stock_proper_name_code[i]; }
  wire[at++] = record->stock_reserved_code;

  return at;
}

/* Stock Issue Code off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_stock_issue_code(StockIssueCode *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 7; i++) { record->stock_space[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->stock_proper_name_code[i] = wire[at++]; }
  record->stock_reserved_code = wire[at++];

  return at;
}

/* what was read of Stock Issue Code is what was written, byte for byte */
static void equal_stock_issue_code(const StockIssueCode *read, const StockIssueCode *written) {
  for (size_t i = 0; i < 7; i++) { assert(read->stock_space[i] == written->stock_space[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->stock_proper_name_code[i] == written->stock_proper_name_code[i]); }
  assert(read->stock_reserved_code == written->stock_reserved_code);
}

/* Stock Issue Code: written and read back, then read and written back */
static void check_stock_issue_code(void) {
  StockIssueCode sent;
  StockIssueCode got;
  uint8_t wire[12];
  uint8_t again[12];

  any_stock_issue_code(&sent);
  assert(encode_stock_issue_code(&sent, wire, 0) == 12);
  assert(decode_stock_issue_code(&got, wire, 0) == 12);
  equal_stock_issue_code(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_stock_issue_code(&got, wire, 0) == 12);
  assert(encode_stock_issue_code(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- CB Issue Code: 12 bytes ------------------------------------------------- */

/* Issue Code layout used when Issue Classification Large Classification is 02 CB-Related. The figure carries no label of its own in 5.3.3 (7). FLEX Issue Code is set with right-align. */
typedef struct {
  uint8_t c_b_space[3];             /* bytes 0 to 2 */
  uint8_t c_b_reserved_code;        /* byte 3 */
  uint8_t time_symbol[4];           /* bytes 4 to 7 */
  uint8_t c_b_proper_name_code[4];  /* bytes 8 to 11 */
} CBIssueCode;

/* any CB Issue Code at all: every byte one the checker chooses */
static void any_c_b_issue_code(CBIssueCode *record) {
  for (size_t i = 0; i < 3; i++) { record->c_b_space[i] = arbitrary(); }
  record->c_b_reserved_code = arbitrary();
  for (size_t i = 0; i < 4; i++) { record->time_symbol[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->c_b_proper_name_code[i] = arbitrary(); }
}

/* CB Issue Code to the wire: 12 bytes from at, returning where the next byte goes */
static size_t encode_c_b_issue_code(const CBIssueCode *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { wire[at++] = record->c_b_space[i]; }
  wire[at++] = record->c_b_reserved_code;
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->time_symbol[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->c_b_proper_name_code[i]; }

  return at;
}

/* CB Issue Code off the wire: 12 bytes from at, returning where the next byte lies */
static size_t decode_c_b_issue_code(CBIssueCode *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 3; i++) { record->c_b_space[i] = wire[at++]; }
  record->c_b_reserved_code = wire[at++];
  for (size_t i = 0; i < 4; i++) { record->time_symbol[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->c_b_proper_name_code[i] = wire[at++]; }

  return at;
}

/* what was read of CB Issue Code is what was written, byte for byte */
static void equal_c_b_issue_code(const CBIssueCode *read, const CBIssueCode *written) {
  for (size_t i = 0; i < 3; i++) { assert(read->c_b_space[i] == written->c_b_space[i]); }
  assert(read->c_b_reserved_code == written->c_b_reserved_code);
  for (size_t i = 0; i < 4; i++) { assert(read->time_symbol[i] == written->time_symbol[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->c_b_proper_name_code[i] == written->c_b_proper_name_code[i]); }
}

/* CB Issue Code: written and read back, then read and written back */
static void check_c_b_issue_code(void) {
  CBIssueCode sent;
  CBIssueCode got;
  uint8_t wire[12];
  uint8_t again[12];

  any_c_b_issue_code(&sent);
  assert(encode_c_b_issue_code(&sent, wire, 0) == 12);
  assert(decode_c_b_issue_code(&got, wire, 0) == 12);
  equal_c_b_issue_code(&got, &sent);

  for (size_t i = 0; i < 12; i++) { wire[i] = arbitrary(); }
  assert(decode_c_b_issue_code(&got, wire, 0) == 12);
  assert(encode_c_b_issue_code(&got, again, 0) == 12);
  for (size_t i = 0; i < 12; i++) { assert(again[i] == wire[i]); }
}

/* ---- Update No Message: 8 bytes ---------------------------------------------- */

/* In this tag, Update Number for each issue is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t update_no[8];  /* bytes 0 to 7 */
} UpdateNoMessage;

/* any Update No Message at all: every byte one the checker chooses */
static void any_update_no_message(UpdateNoMessage *record) {
  for (size_t i = 0; i < 8; i++) { record->update_no[i] = arbitrary(); }
}

/* Update No Message to the wire: 8 bytes from at, returning where the next byte goes */
static size_t encode_update_no_message(const UpdateNoMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->update_no[i]; }

  return at;
}

/* Update No Message off the wire: 8 bytes from at, returning where the next byte lies */
static size_t decode_update_no_message(UpdateNoMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->update_no[i] = wire[at++]; }

  return at;
}

/* what was read of Update No Message is what was written, byte for byte */
static void equal_update_no_message(const UpdateNoMessage *read, const UpdateNoMessage *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->update_no[i] == written->update_no[i]); }
}

/* Update No Message: written and read back, then read and written back */
static void check_update_no_message(void) {
  UpdateNoMessage sent;
  UpdateNoMessage got;
  uint8_t wire[8];
  uint8_t again[8];

  any_update_no_message(&sent);
  assert(encode_update_no_message(&sent, wire, 0) == 8);
  assert(decode_update_no_message(&got, wire, 0) == 8);
  equal_update_no_message(&got, &sent);

  for (size_t i = 0; i < 8; i++) { wire[i] = arbitrary(); }
  assert(decode_update_no_message(&got, wire, 0) == 8);
  assert(encode_update_no_message(&got, again, 0) == 8);
  for (size_t i = 0; i < 8; i++) { assert(again[i] == wire[i]); }
}

/* ---- Status Information: 5 bytes --------------------------------------------- */

/* Status Information */
typedef struct {
  uint8_t issue_status[2];                /* bytes 0 to 1 */
  uint8_t status_flag[2];                 /* bytes 2 to 3 */
  uint8_t short_selling_regulation_flag;  /* byte 4 */
} StatusInformation;

/* any Status Information at all: every byte one the checker chooses */
static void any_status_information(StatusInformation *record) {
  for (size_t i = 0; i < 2; i++) { record->issue_status[i] = arbitrary(); }
  for (size_t i = 0; i < 2; i++) { record->status_flag[i] = arbitrary(); }
  record->short_selling_regulation_flag = arbitrary();
}

/* Status Information to the wire: 5 bytes from at, returning where the next byte goes */
static size_t encode_status_information(const StatusInformation *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->issue_status[i]; }
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->status_flag[i]; }
  wire[at++] = record->short_selling_regulation_flag;

  return at;
}

/* Status Information off the wire: 5 bytes from at, returning where the next byte lies */
static size_t decode_status_information(StatusInformation *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->issue_status[i] = wire[at++]; }
  for (size_t i = 0; i < 2; i++) { record->status_flag[i] = wire[at++]; }
  record->short_selling_regulation_flag = wire[at++];

  return at;
}

/* what was read of Status Information is what was written, byte for byte */
static void equal_status_information(const StatusInformation *read, const StatusInformation *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->issue_status[i] == written->issue_status[i]); }
  for (size_t i = 0; i < 2; i++) { assert(read->status_flag[i] == written->status_flag[i]); }
  assert(read->short_selling_regulation_flag == written->short_selling_regulation_flag);
}

/* Status Information: written and read back, then read and written back */
static void check_status_information(void) {
  StatusInformation sent;
  StatusInformation got;
  uint8_t wire[5];
  uint8_t again[5];

  any_status_information(&sent);
  assert(encode_status_information(&sent, wire, 0) == 5);
  assert(decode_status_information(&got, wire, 0) == 5);
  equal_status_information(&got, &sent);

  for (size_t i = 0; i < 5; i++) { wire[i] = arbitrary(); }
  assert(decode_status_information(&got, wire, 0) == 5);
  assert(encode_status_information(&got, again, 0) == 5);
  for (size_t i = 0; i < 5; i++) { assert(again[i] == wire[i]); }
}

/* ---- Status Information Message: 24 bytes ------------------------------------ */

/* In this tag, status information (Issue Status, Status Flag and Short Selling Regulation Flag) is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];                 /* bytes 0 to 1 */
  uint8_t change_flag;                   /* byte 2 */
  StatusInformation status_information;  /* bytes 3 to 7 */
  uint8_t time_c_12[12];                 /* bytes 8 to 19 */
  uint8_t reserved_4[4];                 /* bytes 20 to 23 */
} StatusInformationMessage;

/* any Status Information Message at all: every byte one the checker chooses */
static void any_status_information_message(StatusInformationMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->change_flag = arbitrary();
  any_status_information(&record->status_information);
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = arbitrary(); }
}

/* Status Information Message to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_status_information_message(const StatusInformationMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->change_flag;
  at = encode_status_information(&record->status_information, wire, at);
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }
  for (size_t i = 0; i < 4; i++) { wire[at++] = record->reserved_4[i]; }

  return at;
}

/* Status Information Message off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_status_information_message(StatusInformationMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->change_flag = wire[at++];
  at = decode_status_information(&record->status_information, wire, at);
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }
  for (size_t i = 0; i < 4; i++) { record->reserved_4[i] = wire[at++]; }

  return at;
}

/* what was read of Status Information Message is what was written, byte for byte */
static void equal_status_information_message(const StatusInformationMessage *read, const StatusInformationMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->change_flag == written->change_flag);
  equal_status_information(&read->status_information, &written->status_information);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
  for (size_t i = 0; i < 4; i++) { assert(read->reserved_4[i] == written->reserved_4[i]); }
}

/* Status Information Message: written and read back, then read and written back */
static void check_status_information_message(void) {
  StatusInformationMessage sent;
  StatusInformationMessage got;
  uint8_t wire[24];
  uint8_t again[24];

  any_status_information_message(&sent);
  assert(encode_status_information_message(&sent, wire, 0) == 24);
  assert(decode_status_information_message(&got, wire, 0) == 24);
  equal_status_information_message(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_status_information_message(&got, wire, 0) == 24);
  assert(encode_status_information_message(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Price: 16 bytes --------------------------------------------------------- */

/* Price */
typedef struct {
  uint8_t unit_flag;       /* byte 0 */
  uint8_t price_c_14[14];  /* bytes 1 to 14 */
  uint8_t sign;            /* byte 15 */
} Price;

/* any Price at all: every byte one the checker chooses */
static void any_price(Price *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->price_c_14[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Price to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_price(const Price *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->price_c_14[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Price off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_price(Price *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->price_c_14[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Price is what was written, byte for byte */
static void equal_price(const Price *read, const Price *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->price_c_14[i] == written->price_c_14[i]); }
  assert(read->sign == written->sign);
}

/* Price: written and read back, then read and written back */
static void check_price(void) {
  Price sent;
  Price got;
  uint8_t wire[16];
  uint8_t again[16];

  any_price(&sent);
  assert(encode_price(&sent, wire, 0) == 16);
  assert(decode_price(&got, wire, 0) == 16);
  equal_price(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_price(&got, wire, 0) == 16);
  assert(encode_price(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open: 23 bytes ---------------------------------------------------------- */

/* Open */
typedef struct {
  Price price;          /* bytes 0 to 15 */
  uint8_t time_c_6[6];  /* bytes 16 to 21 */
  uint8_t change_flag;  /* byte 22 */
} Open;

/* any Open at all: every byte one the checker chooses */
static void any_open(Open *record) {
  any_price(&record->price);
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->change_flag = arbitrary();
}

/* Open to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_open(const Open *record, uint8_t *wire, size_t at) {
  at = encode_price(&record->price, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->change_flag;

  return at;
}

/* Open off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_open(Open *record, const uint8_t *wire, size_t at) {
  at = decode_price(&record->price, wire, at);
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->change_flag = wire[at++];

  return at;
}

/* what was read of Open is what was written, byte for byte */
static void equal_open(const Open *read, const Open *written) {
  equal_price(&read->price, &written->price);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->change_flag == written->change_flag);
}

/* Open: written and read back, then read and written back */
static void check_open(void) {
  Open sent;
  Open got;
  uint8_t wire[23];
  uint8_t again[23];

  any_open(&sent);
  assert(encode_open(&sent, wire, 0) == 23);
  assert(decode_open(&got, wire, 0) == 23);
  equal_open(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_open(&got, wire, 0) == 23);
  assert(encode_open(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- High: 24 bytes ---------------------------------------------------------- */

/* High */
typedef struct {
  uint8_t limit_up_flag;  /* byte 0 */
  Price price;            /* bytes 1 to 16 */
  uint8_t time_c_6[6];    /* bytes 17 to 22 */
  uint8_t change_flag;    /* byte 23 */
} High;

/* any High at all: every byte one the checker chooses */
static void any_high(High *record) {
  record->limit_up_flag = arbitrary();
  any_price(&record->price);
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->change_flag = arbitrary();
}

/* High to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_high(const High *record, uint8_t *wire, size_t at) {
  wire[at++] = record->limit_up_flag;
  at = encode_price(&record->price, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->change_flag;

  return at;
}

/* High off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_high(High *record, const uint8_t *wire, size_t at) {
  record->limit_up_flag = wire[at++];
  at = decode_price(&record->price, wire, at);
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->change_flag = wire[at++];

  return at;
}

/* what was read of High is what was written, byte for byte */
static void equal_high(const High *read, const High *written) {
  assert(read->limit_up_flag == written->limit_up_flag);
  equal_price(&read->price, &written->price);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->change_flag == written->change_flag);
}

/* High: written and read back, then read and written back */
static void check_high(void) {
  High sent;
  High got;
  uint8_t wire[24];
  uint8_t again[24];

  any_high(&sent);
  assert(encode_high(&sent, wire, 0) == 24);
  assert(decode_high(&got, wire, 0) == 24);
  equal_high(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_high(&got, wire, 0) == 24);
  assert(encode_high(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Low: 24 bytes ----------------------------------------------------------- */

/* Low */
typedef struct {
  uint8_t limit_down_flag;  /* byte 0 */
  Price price;              /* bytes 1 to 16 */
  uint8_t time_c_6[6];      /* bytes 17 to 22 */
  uint8_t change_flag;      /* byte 23 */
} Low;

/* any Low at all: every byte one the checker chooses */
static void any_low(Low *record) {
  record->limit_down_flag = arbitrary();
  any_price(&record->price);
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->change_flag = arbitrary();
}

/* Low to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_low(const Low *record, uint8_t *wire, size_t at) {
  wire[at++] = record->limit_down_flag;
  at = encode_price(&record->price, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->change_flag;

  return at;
}

/* Low off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_low(Low *record, const uint8_t *wire, size_t at) {
  record->limit_down_flag = wire[at++];
  at = decode_price(&record->price, wire, at);
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->change_flag = wire[at++];

  return at;
}

/* what was read of Low is what was written, byte for byte */
static void equal_low(const Low *read, const Low *written) {
  assert(read->limit_down_flag == written->limit_down_flag);
  equal_price(&read->price, &written->price);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->change_flag == written->change_flag);
}

/* Low: written and read back, then read and written back */
static void check_low(void) {
  Low sent;
  Low got;
  uint8_t wire[24];
  uint8_t again[24];

  any_low(&sent);
  assert(encode_low(&sent, wire, 0) == 24);
  assert(decode_low(&got, wire, 0) == 24);
  equal_low(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_low(&got, wire, 0) == 24);
  assert(encode_low(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Current: 32 bytes ------------------------------------------------------- */

/* Current */
typedef struct {
  Price price;                       /* bytes 0 to 15 */
  uint8_t time_c_12[12];             /* bytes 16 to 27 */
  uint8_t current_change_flag;       /* byte 28 */
  uint8_t stq_reference_point_flag;  /* byte 29 */
  uint8_t reserved_1;                /* byte 30 */
  uint8_t closing_price_input_flag;  /* byte 31 */
} Current;

/* any Current at all: every byte one the checker chooses */
static void any_current(Current *record) {
  any_price(&record->price);
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
  record->current_change_flag = arbitrary();
  record->stq_reference_point_flag = arbitrary();
  record->reserved_1 = arbitrary();
  record->closing_price_input_flag = arbitrary();
}

/* Current to the wire: 32 bytes from at, returning where the next byte goes */
static size_t encode_current(const Current *record, uint8_t *wire, size_t at) {
  at = encode_price(&record->price, wire, at);
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }
  wire[at++] = record->current_change_flag;
  wire[at++] = record->stq_reference_point_flag;
  wire[at++] = record->reserved_1;
  wire[at++] = record->closing_price_input_flag;

  return at;
}

/* Current off the wire: 32 bytes from at, returning where the next byte lies */
static size_t decode_current(Current *record, const uint8_t *wire, size_t at) {
  at = decode_price(&record->price, wire, at);
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }
  record->current_change_flag = wire[at++];
  record->stq_reference_point_flag = wire[at++];
  record->reserved_1 = wire[at++];
  record->closing_price_input_flag = wire[at++];

  return at;
}

/* what was read of Current is what was written, byte for byte */
static void equal_current(const Current *read, const Current *written) {
  equal_price(&read->price, &written->price);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
  assert(read->current_change_flag == written->current_change_flag);
  assert(read->stq_reference_point_flag == written->stq_reference_point_flag);
  assert(read->reserved_1 == written->reserved_1);
  assert(read->closing_price_input_flag == written->closing_price_input_flag);
}

/* Current: written and read back, then read and written back */
static void check_current(void) {
  Current sent;
  Current got;
  uint8_t wire[32];
  uint8_t again[32];

  any_current(&sent);
  assert(encode_current(&sent, wire, 0) == 32);
  assert(decode_current(&got, wire, 0) == 32);
  equal_current(&got, &sent);

  for (size_t i = 0; i < 32; i++) { wire[i] = arbitrary(); }
  assert(decode_current(&got, wire, 0) == 32);
  assert(encode_current(&got, again, 0) == 32);
  for (size_t i = 0; i < 32; i++) { assert(again[i] == wire[i]); }
}

/* ---- Open High Low And Current Price Message: 105 bytes ---------------------- */

/* In this tag, Open, High, Low and Current Price and other information are set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  Open open;              /* bytes 2 to 24 */
  High high;              /* bytes 25 to 48 */
  Low low;                /* bytes 49 to 72 */
  Current current;        /* bytes 73 to 104 */
} OpenHighLowAndCurrentPriceMessage;

/* any Open High Low And Current Price Message at all: every byte one the checker chooses */
static void any_open_high_low_and_current_price_message(OpenHighLowAndCurrentPriceMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_open(&record->open);
  any_high(&record->high);
  any_low(&record->low);
  any_current(&record->current);
}

/* Open High Low And Current Price Message to the wire: 105 bytes from at, returning where the next byte goes */
static size_t encode_open_high_low_and_current_price_message(const OpenHighLowAndCurrentPriceMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_open(&record->open, wire, at);
  at = encode_high(&record->high, wire, at);
  at = encode_low(&record->low, wire, at);
  at = encode_current(&record->current, wire, at);

  return at;
}

/* Open High Low And Current Price Message off the wire: 105 bytes from at, returning where the next byte lies */
static size_t decode_open_high_low_and_current_price_message(OpenHighLowAndCurrentPriceMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_open(&record->open, wire, at);
  at = decode_high(&record->high, wire, at);
  at = decode_low(&record->low, wire, at);
  at = decode_current(&record->current, wire, at);

  return at;
}

/* what was read of Open High Low And Current Price Message is what was written, byte for byte */
static void equal_open_high_low_and_current_price_message(const OpenHighLowAndCurrentPriceMessage *read, const OpenHighLowAndCurrentPriceMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_open(&read->open, &written->open);
  equal_high(&read->high, &written->high);
  equal_low(&read->low, &written->low);
  equal_current(&read->current, &written->current);
}

/* Open High Low And Current Price Message: written and read back, then read and written back */
static void check_open_high_low_and_current_price_message(void) {
  OpenHighLowAndCurrentPriceMessage sent;
  OpenHighLowAndCurrentPriceMessage got;
  uint8_t wire[105];
  uint8_t again[105];

  any_open_high_low_and_current_price_message(&sent);
  assert(encode_open_high_low_and_current_price_message(&sent, wire, 0) == 105);
  assert(decode_open_high_low_and_current_price_message(&got, wire, 0) == 105);
  equal_open_high_low_and_current_price_message(&got, &sent);

  for (size_t i = 0; i < 105; i++) { wire[i] = arbitrary(); }
  assert(decode_open_high_low_and_current_price_message(&got, wire, 0) == 105);
  assert(encode_open_high_low_and_current_price_message(&got, again, 0) == 105);
  for (size_t i = 0; i < 105; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote Quantity: 16 bytes ------------------------------------------------ */

/* Quote Quantity */
typedef struct {
  uint8_t trading_volume_turnover_unit_flag;  /* byte 0 */
  uint8_t quantity[14];                       /* bytes 1 to 14 */
  uint8_t sign;                               /* byte 15 */
} QuoteQuantity;

/* any Quote Quantity at all: every byte one the checker chooses */
static void any_quote_quantity(QuoteQuantity *record) {
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->quantity[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Quote Quantity to the wire: 16 bytes from at, returning where the next byte goes */
static size_t encode_quote_quantity(const QuoteQuantity *record, uint8_t *wire, size_t at) {
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->quantity[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Quote Quantity off the wire: 16 bytes from at, returning where the next byte lies */
static size_t decode_quote_quantity(QuoteQuantity *record, const uint8_t *wire, size_t at) {
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->quantity[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Quote Quantity is what was written, byte for byte */
static void equal_quote_quantity(const QuoteQuantity *read, const QuoteQuantity *written) {
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->quantity[i] == written->quantity[i]); }
  assert(read->sign == written->sign);
}

/* Quote Quantity: written and read back, then read and written back */
static void check_quote_quantity(void) {
  QuoteQuantity sent;
  QuoteQuantity got;
  uint8_t wire[16];
  uint8_t again[16];

  any_quote_quantity(&sent);
  assert(encode_quote_quantity(&sent, wire, 0) == 16);
  assert(decode_quote_quantity(&got, wire, 0) == 16);
  equal_quote_quantity(&got, &sent);

  for (size_t i = 0; i < 16; i++) { wire[i] = arbitrary(); }
  assert(decode_quote_quantity(&got, wire, 0) == 16);
  assert(encode_quote_quantity(&got, again, 0) == 16);
  for (size_t i = 0; i < 16; i++) { assert(again[i] == wire[i]); }
}

/* ---- Ask Quote: 46 bytes ----------------------------------------------------- */

/* Ask Quote */
typedef struct {
  uint8_t change_flag;           /* byte 0 */
  Price price;                   /* bytes 1 to 16 */
  uint8_t time_c_12[12];         /* bytes 17 to 28 */
  uint8_t quote_flag;            /* byte 29 */
  QuoteQuantity quote_quantity;  /* bytes 30 to 45 */
} AskQuote;

/* any Ask Quote at all: every byte one the checker chooses */
static void any_ask_quote(AskQuote *record) {
  record->change_flag = arbitrary();
  any_price(&record->price);
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
  record->quote_flag = arbitrary();
  any_quote_quantity(&record->quote_quantity);
}

/* Ask Quote to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_ask_quote(const AskQuote *record, uint8_t *wire, size_t at) {
  wire[at++] = record->change_flag;
  at = encode_price(&record->price, wire, at);
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }
  wire[at++] = record->quote_flag;
  at = encode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* Ask Quote off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_ask_quote(AskQuote *record, const uint8_t *wire, size_t at) {
  record->change_flag = wire[at++];
  at = decode_price(&record->price, wire, at);
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }
  record->quote_flag = wire[at++];
  at = decode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* what was read of Ask Quote is what was written, byte for byte */
static void equal_ask_quote(const AskQuote *read, const AskQuote *written) {
  assert(read->change_flag == written->change_flag);
  equal_price(&read->price, &written->price);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
  assert(read->quote_flag == written->quote_flag);
  equal_quote_quantity(&read->quote_quantity, &written->quote_quantity);
}

/* Ask Quote: written and read back, then read and written back */
static void check_ask_quote(void) {
  AskQuote sent;
  AskQuote got;
  uint8_t wire[46];
  uint8_t again[46];

  any_ask_quote(&sent);
  assert(encode_ask_quote(&sent, wire, 0) == 46);
  assert(decode_ask_quote(&got, wire, 0) == 46);
  equal_ask_quote(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_ask_quote(&got, wire, 0) == 46);
  assert(encode_ask_quote(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Bid Quote: 46 bytes ----------------------------------------------------- */

/* Bid Quote */
typedef struct {
  uint8_t change_flag;           /* byte 0 */
  Price price;                   /* bytes 1 to 16 */
  uint8_t time_c_12[12];         /* bytes 17 to 28 */
  uint8_t quote_flag;            /* byte 29 */
  QuoteQuantity quote_quantity;  /* bytes 30 to 45 */
} BidQuote;

/* any Bid Quote at all: every byte one the checker chooses */
static void any_bid_quote(BidQuote *record) {
  record->change_flag = arbitrary();
  any_price(&record->price);
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
  record->quote_flag = arbitrary();
  any_quote_quantity(&record->quote_quantity);
}

/* Bid Quote to the wire: 46 bytes from at, returning where the next byte goes */
static size_t encode_bid_quote(const BidQuote *record, uint8_t *wire, size_t at) {
  wire[at++] = record->change_flag;
  at = encode_price(&record->price, wire, at);
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }
  wire[at++] = record->quote_flag;
  at = encode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* Bid Quote off the wire: 46 bytes from at, returning where the next byte lies */
static size_t decode_bid_quote(BidQuote *record, const uint8_t *wire, size_t at) {
  record->change_flag = wire[at++];
  at = decode_price(&record->price, wire, at);
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }
  record->quote_flag = wire[at++];
  at = decode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* what was read of Bid Quote is what was written, byte for byte */
static void equal_bid_quote(const BidQuote *read, const BidQuote *written) {
  assert(read->change_flag == written->change_flag);
  equal_price(&read->price, &written->price);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
  assert(read->quote_flag == written->quote_flag);
  equal_quote_quantity(&read->quote_quantity, &written->quote_quantity);
}

/* Bid Quote: written and read back, then read and written back */
static void check_bid_quote(void) {
  BidQuote sent;
  BidQuote got;
  uint8_t wire[46];
  uint8_t again[46];

  any_bid_quote(&sent);
  assert(encode_bid_quote(&sent, wire, 0) == 46);
  assert(decode_bid_quote(&got, wire, 0) == 46);
  equal_bid_quote(&got, &sent);

  for (size_t i = 0; i < 46; i++) { wire[i] = arbitrary(); }
  assert(decode_bid_quote(&got, wire, 0) == 46);
  assert(encode_bid_quote(&got, again, 0) == 46);
  for (size_t i = 0; i < 46; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 1 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 1 (Ask and Bid Quotes with the Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote1Message;

/* any Quote 1 Message at all: every byte one the checker chooses */
static void any_quote1_message(Quote1Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 1 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote1_message(const Quote1Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 1 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote1_message(Quote1Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 1 Message is what was written, byte for byte */
static void equal_quote1_message(const Quote1Message *read, const Quote1Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 1 Message: written and read back, then read and written back */
static void check_quote1_message(void) {
  Quote1Message sent;
  Quote1Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote1_message(&sent);
  assert(encode_quote1_message(&sent, wire, 0) == 94);
  assert(decode_quote1_message(&got, wire, 0) == 94);
  equal_quote1_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote1_message(&got, wire, 0) == 94);
  assert(encode_quote1_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 2 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 2 (ask and bid quotes with the 2nd Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote2Message;

/* any Quote 2 Message at all: every byte one the checker chooses */
static void any_quote2_message(Quote2Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 2 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote2_message(const Quote2Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 2 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote2_message(Quote2Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 2 Message is what was written, byte for byte */
static void equal_quote2_message(const Quote2Message *read, const Quote2Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 2 Message: written and read back, then read and written back */
static void check_quote2_message(void) {
  Quote2Message sent;
  Quote2Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote2_message(&sent);
  assert(encode_quote2_message(&sent, wire, 0) == 94);
  assert(decode_quote2_message(&got, wire, 0) == 94);
  equal_quote2_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote2_message(&got, wire, 0) == 94);
  assert(encode_quote2_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 3 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 3 (ask and bid quotes with the 3rd Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote3Message;

/* any Quote 3 Message at all: every byte one the checker chooses */
static void any_quote3_message(Quote3Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 3 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote3_message(const Quote3Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 3 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote3_message(Quote3Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 3 Message is what was written, byte for byte */
static void equal_quote3_message(const Quote3Message *read, const Quote3Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 3 Message: written and read back, then read and written back */
static void check_quote3_message(void) {
  Quote3Message sent;
  Quote3Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote3_message(&sent);
  assert(encode_quote3_message(&sent, wire, 0) == 94);
  assert(decode_quote3_message(&got, wire, 0) == 94);
  equal_quote3_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote3_message(&got, wire, 0) == 94);
  assert(encode_quote3_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 4 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 4 (ask and bid quotes with the 4th Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote4Message;

/* any Quote 4 Message at all: every byte one the checker chooses */
static void any_quote4_message(Quote4Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 4 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote4_message(const Quote4Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 4 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote4_message(Quote4Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 4 Message is what was written, byte for byte */
static void equal_quote4_message(const Quote4Message *read, const Quote4Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 4 Message: written and read back, then read and written back */
static void check_quote4_message(void) {
  Quote4Message sent;
  Quote4Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote4_message(&sent);
  assert(encode_quote4_message(&sent, wire, 0) == 94);
  assert(decode_quote4_message(&got, wire, 0) == 94);
  equal_quote4_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote4_message(&got, wire, 0) == 94);
  assert(encode_quote4_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 5 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 5 (ask and bid quotes with the 5th Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote5Message;

/* any Quote 5 Message at all: every byte one the checker chooses */
static void any_quote5_message(Quote5Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 5 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote5_message(const Quote5Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 5 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote5_message(Quote5Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 5 Message is what was written, byte for byte */
static void equal_quote5_message(const Quote5Message *read, const Quote5Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 5 Message: written and read back, then read and written back */
static void check_quote5_message(void) {
  Quote5Message sent;
  Quote5Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote5_message(&sent);
  assert(encode_quote5_message(&sent, wire, 0) == 94);
  assert(decode_quote5_message(&got, wire, 0) == 94);
  equal_quote5_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote5_message(&got, wire, 0) == 94);
  assert(encode_quote5_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 6 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 6 (ask and bid quotes with the 6th Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote6Message;

/* any Quote 6 Message at all: every byte one the checker chooses */
static void any_quote6_message(Quote6Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 6 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote6_message(const Quote6Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 6 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote6_message(Quote6Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 6 Message is what was written, byte for byte */
static void equal_quote6_message(const Quote6Message *read, const Quote6Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 6 Message: written and read back, then read and written back */
static void check_quote6_message(void) {
  Quote6Message sent;
  Quote6Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote6_message(&sent);
  assert(encode_quote6_message(&sent, wire, 0) == 94);
  assert(decode_quote6_message(&got, wire, 0) == 94);
  equal_quote6_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote6_message(&got, wire, 0) == 94);
  assert(encode_quote6_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 7 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 7 (ask and bid quotes with the 7th Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote7Message;

/* any Quote 7 Message at all: every byte one the checker chooses */
static void any_quote7_message(Quote7Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 7 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote7_message(const Quote7Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 7 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote7_message(Quote7Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 7 Message is what was written, byte for byte */
static void equal_quote7_message(const Quote7Message *read, const Quote7Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 7 Message: written and read back, then read and written back */
static void check_quote7_message(void) {
  Quote7Message sent;
  Quote7Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote7_message(&sent);
  assert(encode_quote7_message(&sent, wire, 0) == 94);
  assert(decode_quote7_message(&got, wire, 0) == 94);
  equal_quote7_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote7_message(&got, wire, 0) == 94);
  assert(encode_quote7_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 8 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 8 (ask and bid quotes with the 8th Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote8Message;

/* any Quote 8 Message at all: every byte one the checker chooses */
static void any_quote8_message(Quote8Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 8 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote8_message(const Quote8Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 8 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote8_message(Quote8Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 8 Message is what was written, byte for byte */
static void equal_quote8_message(const Quote8Message *read, const Quote8Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 8 Message: written and read back, then read and written back */
static void check_quote8_message(void) {
  Quote8Message sent;
  Quote8Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote8_message(&sent);
  assert(encode_quote8_message(&sent, wire, 0) == 94);
  assert(decode_quote8_message(&got, wire, 0) == 94);
  equal_quote8_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote8_message(&got, wire, 0) == 94);
  assert(encode_quote8_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 9 Message: 94 bytes ----------------------------------------------- */

/* In this tag, Quote 9 (ask and bid quotes with the 9th Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote9Message;

/* any Quote 9 Message at all: every byte one the checker chooses */
static void any_quote9_message(Quote9Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 9 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote9_message(const Quote9Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 9 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote9_message(Quote9Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 9 Message is what was written, byte for byte */
static void equal_quote9_message(const Quote9Message *read, const Quote9Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 9 Message: written and read back, then read and written back */
static void check_quote9_message(void) {
  Quote9Message sent;
  Quote9Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote9_message(&sent);
  assert(encode_quote9_message(&sent, wire, 0) == 94);
  assert(decode_quote9_message(&got, wire, 0) == 94);
  equal_quote9_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote9_message(&got, wire, 0) == 94);
  assert(encode_quote9_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Quote 10 Message: 94 bytes ---------------------------------------------- */

/* In this tag, Quote 10 (ask and bid quotes with the 10th Highest Priority) information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  AskQuote ask_quote;     /* bytes 2 to 47 */
  BidQuote bid_quote;     /* bytes 48 to 93 */
} Quote10Message;

/* any Quote 10 Message at all: every byte one the checker chooses */
static void any_quote10_message(Quote10Message *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_ask_quote(&record->ask_quote);
  any_bid_quote(&record->bid_quote);
}

/* Quote 10 Message to the wire: 94 bytes from at, returning where the next byte goes */
static size_t encode_quote10_message(const Quote10Message *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_ask_quote(&record->ask_quote, wire, at);
  at = encode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* Quote 10 Message off the wire: 94 bytes from at, returning where the next byte lies */
static size_t decode_quote10_message(Quote10Message *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_ask_quote(&record->ask_quote, wire, at);
  at = decode_bid_quote(&record->bid_quote, wire, at);

  return at;
}

/* what was read of Quote 10 Message is what was written, byte for byte */
static void equal_quote10_message(const Quote10Message *read, const Quote10Message *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_ask_quote(&read->ask_quote, &written->ask_quote);
  equal_bid_quote(&read->bid_quote, &written->bid_quote);
}

/* Quote 10 Message: written and read back, then read and written back */
static void check_quote10_message(void) {
  Quote10Message sent;
  Quote10Message got;
  uint8_t wire[94];
  uint8_t again[94];

  any_quote10_message(&sent);
  assert(encode_quote10_message(&sent, wire, 0) == 94);
  assert(decode_quote10_message(&got, wire, 0) == 94);
  equal_quote10_message(&got, &sent);

  for (size_t i = 0; i < 94; i++) { wire[i] = arbitrary(); }
  assert(decode_quote10_message(&got, wire, 0) == 94);
  assert(encode_quote10_message(&got, again, 0) == 94);
  for (size_t i = 0; i < 94; i++) { assert(again[i] == wire[i]); }
}

/* ---- Sell Order: 29 bytes ---------------------------------------------------- */

/* Sell Order */
typedef struct {
  uint8_t change_flag;           /* byte 0 */
  uint8_t time_c_12[12];         /* bytes 1 to 12 */
  QuoteQuantity quote_quantity;  /* bytes 13 to 28 */
} SellOrder;

/* any Sell Order at all: every byte one the checker chooses */
static void any_sell_order(SellOrder *record) {
  record->change_flag = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
  any_quote_quantity(&record->quote_quantity);
}

/* Sell Order to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_sell_order(const SellOrder *record, uint8_t *wire, size_t at) {
  wire[at++] = record->change_flag;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }
  at = encode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* Sell Order off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_sell_order(SellOrder *record, const uint8_t *wire, size_t at) {
  record->change_flag = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }
  at = decode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* what was read of Sell Order is what was written, byte for byte */
static void equal_sell_order(const SellOrder *read, const SellOrder *written) {
  assert(read->change_flag == written->change_flag);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
  equal_quote_quantity(&read->quote_quantity, &written->quote_quantity);
}

/* Sell Order: written and read back, then read and written back */
static void check_sell_order(void) {
  SellOrder sent;
  SellOrder got;
  uint8_t wire[29];
  uint8_t again[29];

  any_sell_order(&sent);
  assert(encode_sell_order(&sent, wire, 0) == 29);
  assert(decode_sell_order(&got, wire, 0) == 29);
  equal_sell_order(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_sell_order(&got, wire, 0) == 29);
  assert(encode_sell_order(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Buy Order: 29 bytes ----------------------------------------------------- */

/* Buy Order */
typedef struct {
  uint8_t change_flag;           /* byte 0 */
  uint8_t time_c_12[12];         /* bytes 1 to 12 */
  QuoteQuantity quote_quantity;  /* bytes 13 to 28 */
} BuyOrder;

/* any Buy Order at all: every byte one the checker chooses */
static void any_buy_order(BuyOrder *record) {
  record->change_flag = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
  any_quote_quantity(&record->quote_quantity);
}

/* Buy Order to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_buy_order(const BuyOrder *record, uint8_t *wire, size_t at) {
  wire[at++] = record->change_flag;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }
  at = encode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* Buy Order off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_buy_order(BuyOrder *record, const uint8_t *wire, size_t at) {
  record->change_flag = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }
  at = decode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* what was read of Buy Order is what was written, byte for byte */
static void equal_buy_order(const BuyOrder *read, const BuyOrder *written) {
  assert(read->change_flag == written->change_flag);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
  equal_quote_quantity(&read->quote_quantity, &written->quote_quantity);
}

/* Buy Order: written and read back, then read and written back */
static void check_buy_order(void) {
  BuyOrder sent;
  BuyOrder got;
  uint8_t wire[29];
  uint8_t again[29];

  any_buy_order(&sent);
  assert(encode_buy_order(&sent, wire, 0) == 29);
  assert(decode_buy_order(&got, wire, 0) == 29);
  equal_buy_order(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_buy_order(&got, wire, 0) == 29);
  assert(encode_buy_order(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Market Order Message: 60 bytes ------------------------------------------ */

/* In this tag, both Ask and Bid Market Order Information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];  /* bytes 0 to 1 */
  SellOrder sell_order;   /* bytes 2 to 30 */
  BuyOrder buy_order;     /* bytes 31 to 59 */
} MarketOrderMessage;

/* any Market Order Message at all: every byte one the checker chooses */
static void any_market_order_message(MarketOrderMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_sell_order(&record->sell_order);
  any_buy_order(&record->buy_order);
}

/* Market Order Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_market_order_message(const MarketOrderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_sell_order(&record->sell_order, wire, at);
  at = encode_buy_order(&record->buy_order, wire, at);

  return at;
}

/* Market Order Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_market_order_message(MarketOrderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_sell_order(&record->sell_order, wire, at);
  at = decode_buy_order(&record->buy_order, wire, at);

  return at;
}

/* what was read of Market Order Message is what was written, byte for byte */
static void equal_market_order_message(const MarketOrderMessage *read, const MarketOrderMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_sell_order(&read->sell_order, &written->sell_order);
  equal_buy_order(&read->buy_order, &written->buy_order);
}

/* Market Order Message: written and read back, then read and written back */
static void check_market_order_message(void) {
  MarketOrderMessage sent;
  MarketOrderMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_market_order_message(&sent);
  assert(encode_market_order_message(&sent, wire, 0) == 60);
  assert(decode_market_order_message(&got, wire, 0) == 60);
  equal_market_order_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_market_order_message(&got, wire, 0) == 60);
  assert(encode_market_order_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Over Quote: 29 bytes ---------------------------------------------------- */

/* OVER Quote */
typedef struct {
  uint8_t change_flag;           /* byte 0 */
  uint8_t time_c_12[12];         /* bytes 1 to 12 */
  QuoteQuantity quote_quantity;  /* bytes 13 to 28 */
} OverQuote;

/* any Over Quote at all: every byte one the checker chooses */
static void any_over_quote(OverQuote *record) {
  record->change_flag = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
  any_quote_quantity(&record->quote_quantity);
}

/* Over Quote to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_over_quote(const OverQuote *record, uint8_t *wire, size_t at) {
  wire[at++] = record->change_flag;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }
  at = encode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* Over Quote off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_over_quote(OverQuote *record, const uint8_t *wire, size_t at) {
  record->change_flag = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }
  at = decode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* what was read of Over Quote is what was written, byte for byte */
static void equal_over_quote(const OverQuote *read, const OverQuote *written) {
  assert(read->change_flag == written->change_flag);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
  equal_quote_quantity(&read->quote_quantity, &written->quote_quantity);
}

/* Over Quote: written and read back, then read and written back */
static void check_over_quote(void) {
  OverQuote sent;
  OverQuote got;
  uint8_t wire[29];
  uint8_t again[29];

  any_over_quote(&sent);
  assert(encode_over_quote(&sent, wire, 0) == 29);
  assert(decode_over_quote(&got, wire, 0) == 29);
  equal_over_quote(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_over_quote(&got, wire, 0) == 29);
  assert(encode_over_quote(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Under Quote: 29 bytes --------------------------------------------------- */

/* UNDER Quote */
typedef struct {
  uint8_t change_flag;           /* byte 0 */
  uint8_t time_c_12[12];         /* bytes 1 to 12 */
  QuoteQuantity quote_quantity;  /* bytes 13 to 28 */
} UnderQuote;

/* any Under Quote at all: every byte one the checker chooses */
static void any_under_quote(UnderQuote *record) {
  record->change_flag = arbitrary();
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = arbitrary(); }
  any_quote_quantity(&record->quote_quantity);
}

/* Under Quote to the wire: 29 bytes from at, returning where the next byte goes */
static size_t encode_under_quote(const UnderQuote *record, uint8_t *wire, size_t at) {
  wire[at++] = record->change_flag;
  for (size_t i = 0; i < 12; i++) { wire[at++] = record->time_c_12[i]; }
  at = encode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* Under Quote off the wire: 29 bytes from at, returning where the next byte lies */
static size_t decode_under_quote(UnderQuote *record, const uint8_t *wire, size_t at) {
  record->change_flag = wire[at++];
  for (size_t i = 0; i < 12; i++) { record->time_c_12[i] = wire[at++]; }
  at = decode_quote_quantity(&record->quote_quantity, wire, at);

  return at;
}

/* what was read of Under Quote is what was written, byte for byte */
static void equal_under_quote(const UnderQuote *read, const UnderQuote *written) {
  assert(read->change_flag == written->change_flag);
  for (size_t i = 0; i < 12; i++) { assert(read->time_c_12[i] == written->time_c_12[i]); }
  equal_quote_quantity(&read->quote_quantity, &written->quote_quantity);
}

/* Under Quote: written and read back, then read and written back */
static void check_under_quote(void) {
  UnderQuote sent;
  UnderQuote got;
  uint8_t wire[29];
  uint8_t again[29];

  any_under_quote(&sent);
  assert(encode_under_quote(&sent, wire, 0) == 29);
  assert(decode_under_quote(&got, wire, 0) == 29);
  equal_under_quote(&got, &sent);

  for (size_t i = 0; i < 29; i++) { wire[i] = arbitrary(); }
  assert(decode_under_quote(&got, wire, 0) == 29);
  assert(encode_under_quote(&got, again, 0) == 29);
  for (size_t i = 0; i < 29; i++) { assert(again[i] == wire[i]); }
}

/* ---- Over Under Message: 60 bytes -------------------------------------------- */

/* In this tag, OVER/UNDER quote (Total of quote 11 (Ask) and above or quote 11 (Bid) and below) information is set. This tag is appeared as one of realtime data. */
typedef struct {
  uint8_t reserved_2[2];   /* bytes 0 to 1 */
  OverQuote over_quote;    /* bytes 2 to 30 */
  UnderQuote under_quote;  /* bytes 31 to 59 */
} OverUnderMessage;

/* any Over Under Message at all: every byte one the checker chooses */
static void any_over_under_message(OverUnderMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_over_quote(&record->over_quote);
  any_under_quote(&record->under_quote);
}

/* Over Under Message to the wire: 60 bytes from at, returning where the next byte goes */
static size_t encode_over_under_message(const OverUnderMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_over_quote(&record->over_quote, wire, at);
  at = encode_under_quote(&record->under_quote, wire, at);

  return at;
}

/* Over Under Message off the wire: 60 bytes from at, returning where the next byte lies */
static size_t decode_over_under_message(OverUnderMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_over_quote(&record->over_quote, wire, at);
  at = decode_under_quote(&record->under_quote, wire, at);

  return at;
}

/* what was read of Over Under Message is what was written, byte for byte */
static void equal_over_under_message(const OverUnderMessage *read, const OverUnderMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_over_quote(&read->over_quote, &written->over_quote);
  equal_under_quote(&read->under_quote, &written->under_quote);
}

/* Over Under Message: written and read back, then read and written back */
static void check_over_under_message(void) {
  OverUnderMessage sent;
  OverUnderMessage got;
  uint8_t wire[60];
  uint8_t again[60];

  any_over_under_message(&sent);
  assert(encode_over_under_message(&sent, wire, 0) == 60);
  assert(decode_over_under_message(&got, wire, 0) == 60);
  equal_over_under_message(&got, &sent);

  for (size_t i = 0; i < 60; i++) { wire[i] = arbitrary(); }
  assert(decode_over_under_message(&got, wire, 0) == 60);
  assert(encode_over_under_message(&got, again, 0) == 60);
  for (size_t i = 0; i < 60; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Volume: 23 bytes ------------------------------------------------ */

/* Trading Volume */
typedef struct {
  uint8_t reserved_1;                         /* byte 0 */
  uint8_t trading_volume_turnover_unit_flag;  /* byte 1 */
  uint8_t trading_volume_c_14[14];            /* bytes 2 to 15 */
  uint8_t time_c_6[6];                        /* bytes 16 to 21 */
  uint8_t second_reserved_1;                  /* byte 22 */
} TradingVolume;

/* any Trading Volume at all: every byte one the checker chooses */
static void any_trading_volume(TradingVolume *record) {
  record->reserved_1 = arbitrary();
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->trading_volume_c_14[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->second_reserved_1 = arbitrary();
}

/* Trading Volume to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_trading_volume(const TradingVolume *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->trading_volume_c_14[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Trading Volume off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_trading_volume(TradingVolume *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->trading_volume_c_14[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Trading Volume is what was written, byte for byte */
static void equal_trading_volume(const TradingVolume *read, const TradingVolume *written) {
  assert(read->reserved_1 == written->reserved_1);
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->trading_volume_c_14[i] == written->trading_volume_c_14[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Trading Volume: written and read back, then read and written back */
static void check_trading_volume(void) {
  TradingVolume sent;
  TradingVolume got;
  uint8_t wire[23];
  uint8_t again[23];

  any_trading_volume(&sent);
  assert(encode_trading_volume(&sent, wire, 0) == 23);
  assert(decode_trading_volume(&got, wire, 0) == 23);
  equal_trading_volume(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_volume(&got, wire, 0) == 23);
  assert(encode_trading_volume(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Trading Volume Message: 25 bytes ---------------------------------------- */

/* In this tag, by-issue trading volume information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];         /* bytes 0 to 1 */
  TradingVolume trading_volume;  /* bytes 2 to 24 */
} TradingVolumeMessage;

/* any Trading Volume Message at all: every byte one the checker chooses */
static void any_trading_volume_message(TradingVolumeMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_trading_volume(&record->trading_volume);
}

/* Trading Volume Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_trading_volume_message(const TradingVolumeMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_trading_volume(&record->trading_volume, wire, at);

  return at;
}

/* Trading Volume Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_trading_volume_message(TradingVolumeMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_trading_volume(&record->trading_volume, wire, at);

  return at;
}

/* what was read of Trading Volume Message is what was written, byte for byte */
static void equal_trading_volume_message(const TradingVolumeMessage *read, const TradingVolumeMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_trading_volume(&read->trading_volume, &written->trading_volume);
}

/* Trading Volume Message: written and read back, then read and written back */
static void check_trading_volume_message(void) {
  TradingVolumeMessage sent;
  TradingVolumeMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_trading_volume_message(&sent);
  assert(encode_trading_volume_message(&sent, wire, 0) == 25);
  assert(decode_trading_volume_message(&got, wire, 0) == 25);
  equal_trading_volume_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_trading_volume_message(&got, wire, 0) == 25);
  assert(encode_trading_volume_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Turnover In Yen Value: 23 bytes ----------------------------------------- */

/* Turnover in yen value */
typedef struct {
  uint8_t reserved_1;                         /* byte 0 */
  uint8_t trading_volume_turnover_unit_flag;  /* byte 1 */
  uint8_t turnover_value[14];                 /* bytes 2 to 15 */
  uint8_t time_c_6[6];                        /* bytes 16 to 21 */
  uint8_t second_reserved_1;                  /* byte 22 */
} TurnoverInYenValue;

/* any Turnover In Yen Value at all: every byte one the checker chooses */
static void any_turnover_in_yen_value(TurnoverInYenValue *record) {
  record->reserved_1 = arbitrary();
  record->trading_volume_turnover_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->turnover_value[i] = arbitrary(); }
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->second_reserved_1 = arbitrary();
}

/* Turnover In Yen Value to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_turnover_in_yen_value(const TurnoverInYenValue *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  wire[at++] = record->trading_volume_turnover_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->turnover_value[i]; }
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Turnover In Yen Value off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_turnover_in_yen_value(TurnoverInYenValue *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  record->trading_volume_turnover_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->turnover_value[i] = wire[at++]; }
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Turnover In Yen Value is what was written, byte for byte */
static void equal_turnover_in_yen_value(const TurnoverInYenValue *read, const TurnoverInYenValue *written) {
  assert(read->reserved_1 == written->reserved_1);
  assert(read->trading_volume_turnover_unit_flag == written->trading_volume_turnover_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->turnover_value[i] == written->turnover_value[i]); }
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Turnover In Yen Value: written and read back, then read and written back */
static void check_turnover_in_yen_value(void) {
  TurnoverInYenValue sent;
  TurnoverInYenValue got;
  uint8_t wire[23];
  uint8_t again[23];

  any_turnover_in_yen_value(&sent);
  assert(encode_turnover_in_yen_value(&sent, wire, 0) == 23);
  assert(decode_turnover_in_yen_value(&got, wire, 0) == 23);
  equal_turnover_in_yen_value(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_turnover_in_yen_value(&got, wire, 0) == 23);
  assert(encode_turnover_in_yen_value(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Turnover Message: 25 bytes ---------------------------------------------- */

/* In this tag, by-issue Turnover Information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];                     /* bytes 0 to 1 */
  TurnoverInYenValue turnover_in_yen_value;  /* bytes 2 to 24 */
} TurnoverMessage;

/* any Turnover Message at all: every byte one the checker chooses */
static void any_turnover_message(TurnoverMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_turnover_in_yen_value(&record->turnover_in_yen_value);
}

/* Turnover Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_turnover_message(const TurnoverMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_turnover_in_yen_value(&record->turnover_in_yen_value, wire, at);

  return at;
}

/* Turnover Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_turnover_message(TurnoverMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_turnover_in_yen_value(&record->turnover_in_yen_value, wire, at);

  return at;
}

/* what was read of Turnover Message is what was written, byte for byte */
static void equal_turnover_message(const TurnoverMessage *read, const TurnoverMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_turnover_in_yen_value(&read->turnover_in_yen_value, &written->turnover_in_yen_value);
}

/* Turnover Message: written and read back, then read and written back */
static void check_turnover_message(void) {
  TurnoverMessage sent;
  TurnoverMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_turnover_message(&sent);
  assert(encode_turnover_message(&sent, wire, 0) == 25);
  assert(decode_turnover_message(&got, wire, 0) == 25);
  equal_turnover_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_turnover_message(&got, wire, 0) == 25);
  assert(encode_turnover_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- All Day Vwap: 24 bytes -------------------------------------------------- */

/* All-Day VWAP */
typedef struct {
  uint8_t reserved_1;             /* byte 0 */
  uint8_t lot_size_unit_flag;     /* byte 1 */
  uint8_t all_day_vwap_c_14[14];  /* bytes 2 to 15 */
  uint8_t sign;                   /* byte 16 */
  uint8_t time_c_6[6];            /* bytes 17 to 22 */
  uint8_t second_reserved_1;      /* byte 23 */
} AllDayVwap;

/* any All Day Vwap at all: every byte one the checker chooses */
static void any_all_day_vwap(AllDayVwap *record) {
  record->reserved_1 = arbitrary();
  record->lot_size_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->all_day_vwap_c_14[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->second_reserved_1 = arbitrary();
}

/* All Day Vwap to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_all_day_vwap(const AllDayVwap *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  wire[at++] = record->lot_size_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->all_day_vwap_c_14[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->second_reserved_1;

  return at;
}

/* All Day Vwap off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_all_day_vwap(AllDayVwap *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  record->lot_size_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->all_day_vwap_c_14[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of All Day Vwap is what was written, byte for byte */
static void equal_all_day_vwap(const AllDayVwap *read, const AllDayVwap *written) {
  assert(read->reserved_1 == written->reserved_1);
  assert(read->lot_size_unit_flag == written->lot_size_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->all_day_vwap_c_14[i] == written->all_day_vwap_c_14[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* All Day Vwap: written and read back, then read and written back */
static void check_all_day_vwap(void) {
  AllDayVwap sent;
  AllDayVwap got;
  uint8_t wire[24];
  uint8_t again[24];

  any_all_day_vwap(&sent);
  assert(encode_all_day_vwap(&sent, wire, 0) == 24);
  assert(decode_all_day_vwap(&got, wire, 0) == 24);
  equal_all_day_vwap(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_all_day_vwap(&got, wire, 0) == 24);
  assert(encode_all_day_vwap(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Current Session Vwap: 24 bytes ------------------------------------------ */

/* Current-Session VWAP */
typedef struct {
  uint8_t reserved_1;                     /* byte 0 */
  uint8_t lot_size_unit_flag;             /* byte 1 */
  uint8_t current_session_vwap_c_14[14];  /* bytes 2 to 15 */
  uint8_t sign;                           /* byte 16 */
  uint8_t time_c_6[6];                    /* bytes 17 to 22 */
  uint8_t second_reserved_1;              /* byte 23 */
} CurrentSessionVwap;

/* any Current Session Vwap at all: every byte one the checker chooses */
static void any_current_session_vwap(CurrentSessionVwap *record) {
  record->reserved_1 = arbitrary();
  record->lot_size_unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->current_session_vwap_c_14[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->second_reserved_1 = arbitrary();
}

/* Current Session Vwap to the wire: 24 bytes from at, returning where the next byte goes */
static size_t encode_current_session_vwap(const CurrentSessionVwap *record, uint8_t *wire, size_t at) {
  wire[at++] = record->reserved_1;
  wire[at++] = record->lot_size_unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->current_session_vwap_c_14[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->second_reserved_1;

  return at;
}

/* Current Session Vwap off the wire: 24 bytes from at, returning where the next byte lies */
static size_t decode_current_session_vwap(CurrentSessionVwap *record, const uint8_t *wire, size_t at) {
  record->reserved_1 = wire[at++];
  record->lot_size_unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->current_session_vwap_c_14[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->second_reserved_1 = wire[at++];

  return at;
}

/* what was read of Current Session Vwap is what was written, byte for byte */
static void equal_current_session_vwap(const CurrentSessionVwap *read, const CurrentSessionVwap *written) {
  assert(read->reserved_1 == written->reserved_1);
  assert(read->lot_size_unit_flag == written->lot_size_unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->current_session_vwap_c_14[i] == written->current_session_vwap_c_14[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->second_reserved_1 == written->second_reserved_1);
}

/* Current Session Vwap: written and read back, then read and written back */
static void check_current_session_vwap(void) {
  CurrentSessionVwap sent;
  CurrentSessionVwap got;
  uint8_t wire[24];
  uint8_t again[24];

  any_current_session_vwap(&sent);
  assert(encode_current_session_vwap(&sent, wire, 0) == 24);
  assert(decode_current_session_vwap(&got, wire, 0) == 24);
  equal_current_session_vwap(&got, &sent);

  for (size_t i = 0; i < 24; i++) { wire[i] = arbitrary(); }
  assert(decode_current_session_vwap(&got, wire, 0) == 24);
  assert(encode_current_session_vwap(&got, again, 0) == 24);
  for (size_t i = 0; i < 24; i++) { assert(again[i] == wire[i]); }
}

/* ---- Vwap Message: 50 bytes -------------------------------------------------- */

/* In this tag, by-issue Volume Weighted Stock Price average (VWAP) Information is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];                    /* bytes 0 to 1 */
  AllDayVwap all_day_vwap;                  /* bytes 2 to 25 */
  CurrentSessionVwap current_session_vwap;  /* bytes 26 to 49 */
} VwapMessage;

/* any Vwap Message at all: every byte one the checker chooses */
static void any_vwap_message(VwapMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_all_day_vwap(&record->all_day_vwap);
  any_current_session_vwap(&record->current_session_vwap);
}

/* Vwap Message to the wire: 50 bytes from at, returning where the next byte goes */
static size_t encode_vwap_message(const VwapMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_all_day_vwap(&record->all_day_vwap, wire, at);
  at = encode_current_session_vwap(&record->current_session_vwap, wire, at);

  return at;
}

/* Vwap Message off the wire: 50 bytes from at, returning where the next byte lies */
static size_t decode_vwap_message(VwapMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_all_day_vwap(&record->all_day_vwap, wire, at);
  at = decode_current_session_vwap(&record->current_session_vwap, wire, at);

  return at;
}

/* what was read of Vwap Message is what was written, byte for byte */
static void equal_vwap_message(const VwapMessage *read, const VwapMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_all_day_vwap(&read->all_day_vwap, &written->all_day_vwap);
  equal_current_session_vwap(&read->current_session_vwap, &written->current_session_vwap);
}

/* Vwap Message: written and read back, then read and written back */
static void check_vwap_message(void) {
  VwapMessage sent;
  VwapMessage got;
  uint8_t wire[50];
  uint8_t again[50];

  any_vwap_message(&sent);
  assert(encode_vwap_message(&sent, wire, 0) == 50);
  assert(decode_vwap_message(&got, wire, 0) == 50);
  equal_vwap_message(&got, &sent);

  for (size_t i = 0; i < 50; i++) { wire[i] = arbitrary(); }
  assert(decode_vwap_message(&got, wire, 0) == 50);
  assert(encode_vwap_message(&got, again, 0) == 50);
  for (size_t i = 0; i < 50; i++) { assert(again[i] == wire[i]); }
}

/* ---- Parity Estimated Price: 23 bytes ---------------------------------------- */

/* Parity/Estimated Price */
typedef struct {
  uint8_t unit_flag;                        /* byte 0 */
  uint8_t parity_estimated_price_c_14[14];  /* bytes 1 to 14 */
  uint8_t sign;                             /* byte 15 */
  uint8_t time_c_6[6];                      /* bytes 16 to 21 */
  uint8_t reserved_1;                       /* byte 22 */
} ParityEstimatedPrice;

/* any Parity Estimated Price at all: every byte one the checker chooses */
static void any_parity_estimated_price(ParityEstimatedPrice *record) {
  record->unit_flag = arbitrary();
  for (size_t i = 0; i < 14; i++) { record->parity_estimated_price_c_14[i] = arbitrary(); }
  record->sign = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Parity Estimated Price to the wire: 23 bytes from at, returning where the next byte goes */
static size_t encode_parity_estimated_price(const ParityEstimatedPrice *record, uint8_t *wire, size_t at) {
  wire[at++] = record->unit_flag;
  for (size_t i = 0; i < 14; i++) { wire[at++] = record->parity_estimated_price_c_14[i]; }
  wire[at++] = record->sign;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Parity Estimated Price off the wire: 23 bytes from at, returning where the next byte lies */
static size_t decode_parity_estimated_price(ParityEstimatedPrice *record, const uint8_t *wire, size_t at) {
  record->unit_flag = wire[at++];
  for (size_t i = 0; i < 14; i++) { record->parity_estimated_price_c_14[i] = wire[at++]; }
  record->sign = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Parity Estimated Price is what was written, byte for byte */
static void equal_parity_estimated_price(const ParityEstimatedPrice *read, const ParityEstimatedPrice *written) {
  assert(read->unit_flag == written->unit_flag);
  for (size_t i = 0; i < 14; i++) { assert(read->parity_estimated_price_c_14[i] == written->parity_estimated_price_c_14[i]); }
  assert(read->sign == written->sign);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Parity Estimated Price: written and read back, then read and written back */
static void check_parity_estimated_price(void) {
  ParityEstimatedPrice sent;
  ParityEstimatedPrice got;
  uint8_t wire[23];
  uint8_t again[23];

  any_parity_estimated_price(&sent);
  assert(encode_parity_estimated_price(&sent, wire, 0) == 23);
  assert(decode_parity_estimated_price(&got, wire, 0) == 23);
  equal_parity_estimated_price(&got, &sent);

  for (size_t i = 0; i < 23; i++) { wire[i] = arbitrary(); }
  assert(decode_parity_estimated_price(&got, wire, 0) == 23);
  assert(encode_parity_estimated_price(&got, again, 0) == 23);
  for (size_t i = 0; i < 23; i++) { assert(again[i] == wire[i]); }
}

/* ---- Parity Message: 25 bytes ------------------------------------------------ */

/* In this tag, estimated Price Information for parity of CB is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];                        /* bytes 0 to 1 */
  ParityEstimatedPrice parity_estimated_price;  /* bytes 2 to 24 */
} ParityMessage;

/* any Parity Message at all: every byte one the checker chooses */
static void any_parity_message(ParityMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_parity_estimated_price(&record->parity_estimated_price);
}

/* Parity Message to the wire: 25 bytes from at, returning where the next byte goes */
static size_t encode_parity_message(const ParityMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_parity_estimated_price(&record->parity_estimated_price, wire, at);

  return at;
}

/* Parity Message off the wire: 25 bytes from at, returning where the next byte lies */
static size_t decode_parity_message(ParityMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_parity_estimated_price(&record->parity_estimated_price, wire, at);

  return at;
}

/* what was read of Parity Message is what was written, byte for byte */
static void equal_parity_message(const ParityMessage *read, const ParityMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_parity_estimated_price(&read->parity_estimated_price, &written->parity_estimated_price);
}

/* Parity Message: written and read back, then read and written back */
static void check_parity_message(void) {
  ParityMessage sent;
  ParityMessage got;
  uint8_t wire[25];
  uint8_t again[25];

  any_parity_message(&sent);
  assert(encode_parity_message(&sent, wire, 0) == 25);
  assert(decode_parity_message(&got, wire, 0) == 25);
  equal_parity_message(&got, &sent);

  for (size_t i = 0; i < 25; i++) { wire[i] = arbitrary(); }
  assert(decode_parity_message(&got, wire, 0) == 25);
  assert(encode_parity_message(&got, again, 0) == 25);
  for (size_t i = 0; i < 25; i++) { assert(again[i] == wire[i]); }
}

/* ---- Direct Yield: 9 bytes --------------------------------------------------- */

/* Direct Yield */
typedef struct {
  uint8_t direct_yield_c_8[8];  /* bytes 0 to 7 */
  uint8_t sign;                 /* byte 8 */
} DirectYield;

/* any Direct Yield at all: every byte one the checker chooses */
static void any_direct_yield(DirectYield *record) {
  for (size_t i = 0; i < 8; i++) { record->direct_yield_c_8[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Direct Yield to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_direct_yield(const DirectYield *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->direct_yield_c_8[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Direct Yield off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_direct_yield(DirectYield *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->direct_yield_c_8[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Direct Yield is what was written, byte for byte */
static void equal_direct_yield(const DirectYield *read, const DirectYield *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->direct_yield_c_8[i] == written->direct_yield_c_8[i]); }
  assert(read->sign == written->sign);
}

/* Direct Yield: written and read back, then read and written back */
static void check_direct_yield(void) {
  DirectYield sent;
  DirectYield got;
  uint8_t wire[9];
  uint8_t again[9];

  any_direct_yield(&sent);
  assert(encode_direct_yield(&sent, wire, 0) == 9);
  assert(decode_direct_yield(&got, wire, 0) == 9);
  equal_direct_yield(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_direct_yield(&got, wire, 0) == 9);
  assert(encode_direct_yield(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Final Yield: 9 bytes ---------------------------------------------------- */

/* Final Yield */
typedef struct {
  uint8_t final_yield_c_8[8];  /* bytes 0 to 7 */
  uint8_t sign;                /* byte 8 */
} FinalYield;

/* any Final Yield at all: every byte one the checker chooses */
static void any_final_yield(FinalYield *record) {
  for (size_t i = 0; i < 8; i++) { record->final_yield_c_8[i] = arbitrary(); }
  record->sign = arbitrary();
}

/* Final Yield to the wire: 9 bytes from at, returning where the next byte goes */
static size_t encode_final_yield(const FinalYield *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { wire[at++] = record->final_yield_c_8[i]; }
  wire[at++] = record->sign;

  return at;
}

/* Final Yield off the wire: 9 bytes from at, returning where the next byte lies */
static size_t decode_final_yield(FinalYield *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 8; i++) { record->final_yield_c_8[i] = wire[at++]; }
  record->sign = wire[at++];

  return at;
}

/* what was read of Final Yield is what was written, byte for byte */
static void equal_final_yield(const FinalYield *read, const FinalYield *written) {
  for (size_t i = 0; i < 8; i++) { assert(read->final_yield_c_8[i] == written->final_yield_c_8[i]); }
  assert(read->sign == written->sign);
}

/* Final Yield: written and read back, then read and written back */
static void check_final_yield(void) {
  FinalYield sent;
  FinalYield got;
  uint8_t wire[9];
  uint8_t again[9];

  any_final_yield(&sent);
  assert(encode_final_yield(&sent, wire, 0) == 9);
  assert(decode_final_yield(&got, wire, 0) == 9);
  equal_final_yield(&got, &sent);

  for (size_t i = 0; i < 9; i++) { wire[i] = arbitrary(); }
  assert(decode_final_yield(&got, wire, 0) == 9);
  assert(encode_final_yield(&got, again, 0) == 9);
  for (size_t i = 0; i < 9; i++) { assert(again[i] == wire[i]); }
}

/* ---- Yield Message: 27 bytes ------------------------------------------------- */

/* In this tag, Direct and Final Yield Information for CB is set. This tag appears as part of realtime data. */
typedef struct {
  uint8_t reserved_2[2];     /* bytes 0 to 1 */
  DirectYield direct_yield;  /* bytes 2 to 10 */
  FinalYield final_yield;    /* bytes 11 to 19 */
  uint8_t time_c_6[6];       /* bytes 20 to 25 */
  uint8_t reserved_1;        /* byte 26 */
} YieldMessage;

/* any Yield Message at all: every byte one the checker chooses */
static void any_yield_message(YieldMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  any_direct_yield(&record->direct_yield);
  any_final_yield(&record->final_yield);
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
  record->reserved_1 = arbitrary();
}

/* Yield Message to the wire: 27 bytes from at, returning where the next byte goes */
static size_t encode_yield_message(const YieldMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  at = encode_direct_yield(&record->direct_yield, wire, at);
  at = encode_final_yield(&record->final_yield, wire, at);
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }
  wire[at++] = record->reserved_1;

  return at;
}

/* Yield Message off the wire: 27 bytes from at, returning where the next byte lies */
static size_t decode_yield_message(YieldMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  at = decode_direct_yield(&record->direct_yield, wire, at);
  at = decode_final_yield(&record->final_yield, wire, at);
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }
  record->reserved_1 = wire[at++];

  return at;
}

/* what was read of Yield Message is what was written, byte for byte */
static void equal_yield_message(const YieldMessage *read, const YieldMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  equal_direct_yield(&read->direct_yield, &written->direct_yield);
  equal_final_yield(&read->final_yield, &written->final_yield);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
  assert(read->reserved_1 == written->reserved_1);
}

/* Yield Message: written and read back, then read and written back */
static void check_yield_message(void) {
  YieldMessage sent;
  YieldMessage got;
  uint8_t wire[27];
  uint8_t again[27];

  any_yield_message(&sent);
  assert(encode_yield_message(&sent, wire, 0) == 27);
  assert(decode_yield_message(&got, wire, 0) == 27);
  equal_yield_message(&got, &sent);

  for (size_t i = 0; i < 27; i++) { wire[i] = arbitrary(); }
  assert(decode_yield_message(&got, wire, 0) == 27);
  assert(encode_yield_message(&got, again, 0) == 27);
  for (size_t i = 0; i < 27; i++) { assert(again[i] == wire[i]); }
}

/* ---- Control Message: 10 bytes ----------------------------------------------- */

/* In this tag, the Test Mode Flag and the Start/End Flag that are used in a Control Message are set. This tag appears as part of a Control Message. */
typedef struct {
  uint8_t reserved_2[2];   /* bytes 0 to 1 */
  uint8_t test_mode_flag;  /* byte 2 */
  uint8_t start_end_flag;  /* byte 3 */
  uint8_t time_c_6[6];     /* bytes 4 to 9 */
} ControlMessage;

/* any Control Message at all: every byte one the checker chooses */
static void any_control_message(ControlMessage *record) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = arbitrary(); }
  record->test_mode_flag = arbitrary();
  record->start_end_flag = arbitrary();
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = arbitrary(); }
}

/* Control Message to the wire: 10 bytes from at, returning where the next byte goes */
static size_t encode_control_message(const ControlMessage *record, uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { wire[at++] = record->reserved_2[i]; }
  wire[at++] = record->test_mode_flag;
  wire[at++] = record->start_end_flag;
  for (size_t i = 0; i < 6; i++) { wire[at++] = record->time_c_6[i]; }

  return at;
}

/* Control Message off the wire: 10 bytes from at, returning where the next byte lies */
static size_t decode_control_message(ControlMessage *record, const uint8_t *wire, size_t at) {
  for (size_t i = 0; i < 2; i++) { record->reserved_2[i] = wire[at++]; }
  record->test_mode_flag = wire[at++];
  record->start_end_flag = wire[at++];
  for (size_t i = 0; i < 6; i++) { record->time_c_6[i] = wire[at++]; }

  return at;
}

/* what was read of Control Message is what was written, byte for byte */
static void equal_control_message(const ControlMessage *read, const ControlMessage *written) {
  for (size_t i = 0; i < 2; i++) { assert(read->reserved_2[i] == written->reserved_2[i]); }
  assert(read->test_mode_flag == written->test_mode_flag);
  assert(read->start_end_flag == written->start_end_flag);
  for (size_t i = 0; i < 6; i++) { assert(read->time_c_6[i] == written->time_c_6[i]); }
}

/* Control Message: written and read back, then read and written back */
static void check_control_message(void) {
  ControlMessage sent;
  ControlMessage got;
  uint8_t wire[10];
  uint8_t again[10];

  any_control_message(&sent);
  assert(encode_control_message(&sent, wire, 0) == 10);
  assert(decode_control_message(&got, wire, 0) == 10);
  equal_control_message(&got, &sent);

  for (size_t i = 0; i < 10; i++) { wire[i] = arbitrary(); }
  assert(decode_control_message(&got, wire, 0) == 10);
  assert(encode_control_message(&got, again, 0) == 10);
  for (size_t i = 0; i < 10; i++) { assert(again[i] == wire[i]); }
}

/* ---- What esbmc checks ------------------------------------------------------- */

/* every record of the protocol, each on its own buffers */
static void checks(void) {
  check_message_serial_no();
  check_issue_classification();
  check_stock_issue_code();
  check_c_b_issue_code();
  check_update_no_message();
  check_status_information();
  check_status_information_message();
  check_price();
  check_open();
  check_high();
  check_low();
  check_current();
  check_open_high_low_and_current_price_message();
  check_quote_quantity();
  check_ask_quote();
  check_bid_quote();
  check_quote1_message();
  check_quote2_message();
  check_quote3_message();
  check_quote4_message();
  check_quote5_message();
  check_quote6_message();
  check_quote7_message();
  check_quote8_message();
  check_quote9_message();
  check_quote10_message();
  check_sell_order();
  check_buy_order();
  check_market_order_message();
  check_over_quote();
  check_under_quote();
  check_over_under_message();
  check_trading_volume();
  check_trading_volume_message();
  check_turnover_in_yen_value();
  check_turnover_message();
  check_all_day_vwap();
  check_current_session_vwap();
  check_vwap_message();
  check_parity_estimated_price();
  check_parity_message();
  check_direct_yield();
  check_final_yield();
  check_yield_message();
  check_control_message();
}

int main(void) {
#ifdef CONCRETE
  for (pattern = 0; pattern < 4; pattern++) { checks(); }
#else
  checks();
#endif

  return 0;
}
