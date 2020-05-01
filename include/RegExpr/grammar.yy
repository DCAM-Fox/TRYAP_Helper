%require "3.2"
%language "c++"
%define api.value.type variant
%define api.token.constructor
%param {std::istream& stream}
%parse-param {std::shared_ptr<Node<NData>>& root}

%%

%code top
{
#include "rexpnode.hpp"
};

//хранит умные указатели на узлы дерева
%nterm <std::shared_ptr<Node<NData>>> U;
%nterm <std::shared_ptr<Node<NData>>> C;
%nterm <std::shared_ptr<Node<NData>>> I;
%nterm <std::shared_ptr<Node<NData>>> L;
%token <std::pair<char, size_t>> LETTER;
%token OPEN;
%token CLOSE;
%token UNION;
%token ITER;

GETROOT:    U
        {
            root = $1;
        }
;

U:        C
        {
            $$ = $1;
        }
        | C UNION U
        {
            $$ = std::make_shared<Node<NData>>();
            $$->add_child($1);
            $$->add_child($3);
            $$->value.type = NData::Type::Union;
        }
        //| OPEN U CLOSE 
        //{
        //    $$ = $2;
        //}
;

C:        I C
        {
            $$ = std::make_shared<Node<NData>>();
            $$->add_child($1);
            $$->add_child($2);
            $$->value.type = NData::Type::Conc;
        }
        | I
        {
            $$ = $1;
        }
        //| OPEN U CLOSE
        //{
        //    $$ = $2;
        //}
;

I:       L
        {
            $$ = $1;
        }
        | L ITER
        {
            $$ = std::make_shared<Node<NData>>();
            $$->add_child($1);
            $$->value.type = NData::Type::Iter;
        }
        //| OPEN U CLOSE
        //{
        //    $$ = $2;
        //}
;

L:       LETTER
        {
            $$ = std::make_shared<Node<NData>>();
            $$->value.type = NData::Type::Char;
            $$->value.firstpos.insert($1);
            $$->value.lastpos.insert($1);
        }
        | OPEN U CLOSE
        {
            $$ = $2;
        }
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
      static size_t i = 0;

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
            ++i;
            return parser::make_LETTER(std::make_pair(input, i));
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

//int main ()
//{
//  yy::parser parse(std::cin);
//  return parse();
//}
