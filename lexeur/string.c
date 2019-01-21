#include "arguments.h"
#include "library.h"

uint64_t CHAR_EOF          =  -1; // end of file
uint64_t CHAR_BACKSPACE    =   8; // ASCII code 8  = backspace
uint64_t CHAR_TAB          =   9; // ASCII code 9  = tabulator
uint64_t CHAR_LF           =  10; // ASCII code 10 = line feed
uint64_t CHAR_CR           =  13; // ASCII code 13 = carriage return
uint64_t CHAR_SINGLEQUOTE  =  39; // ASCII code 39
uint64_t CHAR_DOUBLEQUOTE  = '"';


uint64_t load_character(uint64_t* s, uint64_t i) {
  // assert: i >= 0
  uint64_t a;

  // a is the index of the double word where
  // the to-be-loaded i-th character in s is
  a = i / SIZEOFUINT64;

  // return i-th 8-bit character in s
  return get_bits(*(s + a), (i % SIZEOFUINT64) * 8, 8);
}

uint64_t* store_character(uint64_t* s, uint64_t i, uint64_t c) {
  // assert: i >= 0, 0 <= c < 2^8 (all characters are 8-bit)
  uint64_t a;

  // a is the index of the double word where
  // the with c to-be-overwritten i-th character in s is
  a = i / SIZEOFUINT64;

  // subtract the to-be-overwritten character to reset its bits in s
  // then add c to set its bits at the i-th position in s
  *(s + a) = (*(s + a) - left_shift(load_character(s, i), (i % SIZEOFUINT64) * 8)) + left_shift(c, (i % SIZEOFUINT64) * 8);

  return s;
}

uint64_t string_length(uint64_t* s) {
  uint64_t i;

  i = 0;

  while (load_character(s, i) != 0)
    i = i + 1;

  return i;
}

uint64_t* string_copy(uint64_t* s) {
  uint64_t l;
  uint64_t* t;
  uint64_t i;

  l = string_length(s);

  t = zalloc(l + 1);

  i = 0;

  while (i <= l) {
    store_character(t, i, load_character(s, i));

    i = i + 1;
  }

  return t;
}

void string_reverse(uint64_t* s) {
  uint64_t i;
  uint64_t j;
  uint64_t tmp;

  i = 0;
  j = string_length(s) - 1;

  while (i < j) {
    tmp = load_character(s, i);

    store_character(s, i, load_character(s, j));
    store_character(s, j, tmp);

    i = i + 1;
    j = j - 1;
  }
}

uint64_t string_compare(uint64_t* s, uint64_t* t) {
  uint64_t i;

  i = 0;

  while (1)
    if (load_character(s, i) == 0)
      if (load_character(t, i) == 0)
        return 1;
      else
        return 0;
    else if (load_character(s, i) == load_character(t, i))
      i = i + 1;
    else
      return 0;
}

uint64_t atoi(uint64_t* s) {
  uint64_t i;
  uint64_t n;
  uint64_t c;

  // the conversion of the ASCII string in s to its
  // numerical value n begins with the leftmost digit in s
  i = 0;

  // and the numerical value 0 for n
  n = 0;

  // load character (one byte) at index i in s from memory requires
  // bit shifting since memory access can only be done in double words
  c = load_character(s, i);

  // loop until s is terminated
  while (c != 0) {
    // the numerical value of ASCII-encoded decimal digits
    // is offset by the ASCII code of '0' (which is 48)
    c = c - '0';

    if (c > 9) {
      printf2((uint64_t*) "%s: cannot convert non-decimal number %s\n", get_myname(), s);

      exit(EXITCODE_BADARGUMENTS);
    }

    // assert: s contains a decimal number

    // use base 10 but detect wrap around
    if (n < UINT64_MAX / 10)
      n = n * 10 + c;
    else if (n == UINT64_MAX / 10)
      if (c <= UINT64_MAX % 10)
        n = n * 10 + c;
      else {
        // s contains a decimal number larger than UINT64_MAX
        printf2((uint64_t*) "%s: cannot convert out-of-bound number %s\n", get_myname(), s);

        exit(EXITCODE_BADARGUMENTS);
      }
    else {
      // s contains a decimal number larger than UINT64_MAX
      printf2((uint64_t*) "%s: cannot convert out-of-bound number %s\n", get_myname(), s);

      exit(EXITCODE_BADARGUMENTS);
    }

    // go to the next digit
    i = i + 1;

    // load character (one byte) at index i in s from memory requires
    // bit shifting since memory access can only be done in double words
    c = load_character(s, i);
  }

  return n;
}

uint64_t* itoa(uint64_t n, uint64_t* s, uint64_t b, uint64_t a) {
  // assert: b in {2,4,8,10,16}

  uint64_t i;
  uint64_t sign;

  // the conversion of the integer n to an ASCII string in s with
  // base b and alignment a begins with the leftmost digit in s
  i = 0;

  // for now assuming n is positive
  sign = 0;

  if (n == 0) {
    store_character(s, 0, '0');

    i = 1;
  } else if (signed_less_than(n, 0)) {
    if (b == 10) {
      // n is represented as two's complement
      // convert n to a positive number but remember the sign
      n = -n;

      sign = 1;
    }
  }

  while (n != 0) {
    if (n % b > 9)
      // the ASCII code of hexadecimal digits larger than 9
      // is offset by the ASCII code of 'A' (which is 65)
      store_character(s, i, n % b - 10 + 'A');
    else
      // the ASCII code of digits less than or equal to 9
      // is offset by the ASCII code of '0' (which is 48)
      store_character(s, i, n % b + '0');

    // convert n by dividing n with base b
    n = n / b;

    i = i + 1;
  }

  if (b == 10) {
    if (sign) {
      store_character(s, i, '-'); // negative decimal numbers start with -

      i = i + 1;
    }

    while (i < a) {
      store_character(s, i, ' '); // align with spaces

      i = i + 1;
    }
  } else {
    while (i < a) {
      store_character(s, i, '0'); // align with 0s

      i = i + 1;
    }

    if (b == 8) {
      store_character(s, i, '0');   // octal numbers start with 00
      store_character(s, i + 1, '0');

      i = i + 2;
    } else if (b == 16) {
      store_character(s, i, 'x');   // hexadecimal numbers start with 0x
      store_character(s, i + 1, '0');

      i = i + 2;
    }
  }

  store_character(s, i, 0); // null-terminated string

  // our numeral system is positional hindu-arabic, that is,
  // the weight of digits increases right to left, which means
  // that we need to reverse the string we computed above
  string_reverse(s);

  return s;
}


