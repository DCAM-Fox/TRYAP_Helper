%require "3.2"
%language "c++"
%define api.value.type variant
%define api.token.constructor

%%

%nterm <std::string> EXPR;
%nterm <std::string> TERM;
%token <char> LETTER;
%token OPEN;
%token CLOSE;
%token UNION;
%token ITER;

PRINT:    EXPR { std::cout << $1 << '\n'; }
;

EXPR:     TERM
        | TERM UNION EXPR { $$ = $1 + "++" + $3; }
        | TERM EXPR { $$ = $1 + $2; }
;

TERM:     LETTER   { $$ = $1; }
        | TERM ITER { $$ = $1 + "**"; }
        | OPEN EXPR CLOSE  { $$ = "[" + $2 + "]"; }
;

%token END_OF_FILE 0
;

%code
{
  namespace yy
  {
    // Return the next token.
    auto yylex(std::istream& stream) -> parser::symbol_type
    {
      //std::string input;
      //cin.getline(input);

      while(true)
      {
        char input = stream.get();
        switch (input)
        {
          case '#':
          {
            return parser::make_END_OF_FILE ();
            break;
          }
          case '(':
          {
            return parser::make_OPEN ();
            break;
          }
          case ')':
          {
            return parser::make_CLOSE ();
            break;
          }
          case '+':
          {
            return parser::make_UNION ();
            break;
          }
          case '*':
          {
            return parser::make_ITER ();
            break;
          }
          case '\n':
          {
            continue;
            break;
          }
          default:
          {
            return parser::make_LETTER (input);
            break;
          }
        }
      }
    }
  }
}
;

%%

namespace yy
{
  // Report an error to the user.
  auto parser::error (const std::string& msg) -> void
  {
    std::cerr << msg << '\n';
  }
}

int main ()
{
  yy::parser parse;
  return parse();
}
