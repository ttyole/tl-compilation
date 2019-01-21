extern uint64_t CHAR_EOF; // end of file
extern uint64_t CHAR_BACKSPACE; // ASCII code 8  = backspace
extern uint64_t CHAR_TAB; // ASCII code 9  = tabulator
extern uint64_t CHAR_LF; // ASCII code 10 = line feed
extern uint64_t CHAR_CR; // ASCII code 13 = carriage return
extern uint64_t CHAR_SINGLEQUOTE; // ASCII code 39 = '
extern uint64_t CHAR_DOUBLEQUOTE;


extern uint64_t  load_character(uint64_t* s, uint64_t i);
extern uint64_t* store_character(uint64_t* s, uint64_t i, uint64_t c);

extern uint64_t  string_length(uint64_t* s);
extern uint64_t* string_copy(uint64_t* s);
extern void      string_reverse(uint64_t* s);
extern uint64_t  string_compare(uint64_t* s, uint64_t* t);

extern uint64_t  atoi(uint64_t* s);
extern uint64_t* itoa(uint64_t n, uint64_t* s, uint64_t b, uint64_t a);

