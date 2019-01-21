extern uint64_t CHAR_SPACE;
extern uint64_t CHAR_SEMICOLON;
extern uint64_t CHAR_PLUS;
extern uint64_t CHAR_DASH;
extern uint64_t CHAR_ASTERISK;
extern uint64_t CHAR_SLASH;
extern uint64_t CHAR_UNDERSCORE;
extern uint64_t CHAR_EQUAL;
extern uint64_t CHAR_LPARENTHESIS;
extern uint64_t CHAR_RPARENTHESIS;
extern uint64_t CHAR_LBRACE;
extern uint64_t CHAR_RBRACE;
extern uint64_t CHAR_COMMA;
extern uint64_t CHAR_LT;
extern uint64_t CHAR_GT;
extern uint64_t CHAR_EXCLAMATION;
extern uint64_t CHAR_PERCENTAGE;
extern uint64_t CHAR_BACKSLASH; // ASCII code 92 = backslash


// ------------------------ GLOBAL VARIABLES -----------------------

extern uint64_t line_number; // current line number for error reporting

extern uint64_t* identifier; // stores scanned identifier as string
extern uint64_t* integer; // stores scanned integer as string
extern uint64_t* string; // stores scanned string
extern uint64_t literal; // stores numerical value of scanned integer or character

extern uint64_t MAX_IDENTIFIER_LENGTH;  // maximum number of characters in an identifier
extern uint64_t MAX_INTEGER_LENGTH;  // maximum number of characters in an unsigned integer
extern uint64_t MAX_STRING_LENGTH; // maximum number of characters in a string



extern uint64_t integer_is_signed; // enforce INT64_MIN limit if '-' was scanned before

extern uint64_t character; // most recently read character

extern uint64_t number_of_read_characters;

extern uint64_t symbol; // most recently recognized symbol

extern uint64_t number_of_ignored_characters;
extern uint64_t number_of_comments;
extern uint64_t number_of_scanned_symbols;

extern void init_scanner();
extern void get_character();
extern void get_symbol();
extern void print_line_number(uint64_t* message, uint64_t line);
extern void print_symbol(uint64_t symbol);
extern void reset_scanner();
