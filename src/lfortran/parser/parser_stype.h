#ifndef LFORTRAN_PARSER_STYPE_H
#define LFORTRAN_PARSER_STYPE_H

#include <cstring>
#include <lfortran/ast.h>
#include <lfortran/parser/location.h>
#include <lfortran/containers.h>

namespace LFortran
{

struct VarType {
    Location loc;
    Str string;
    Vec<AST::kind_item_t> kind;
};

struct FnArg {
    bool keyword;
    union {
        AST::fnarg_t arg;
        AST::keyword_t kw;
    };
};

union YYSTYPE {
    unsigned long n;
    Str string;

    AST::ast_t* ast;
    Vec<AST::ast_t*> vec_ast;

    AST::decl_t *decl; // Pointer, to reduce size of YYSTYPE
    Vec<AST::decl_t> vec_decl;

    AST::dimension_t dim;
    Vec<AST::dimension_t> vec_dim;

    AST::reduce_opType reduce_op_type;

    AST::parameter_item_t parameter_item;
    Vec<AST::parameter_item_t> vec_parameter_item;

    VarType *var_type;

    AST::kind_item_t *kind_arg;
    Vec<AST::kind_item_t> vec_kind_arg;

    FnArg *fnarg;
    Vec<FnArg> vec_fnarg;
};

static_assert(std::is_standard_layout<YYSTYPE>::value);
static_assert(std::is_trivial<YYSTYPE>::value);
// Ensure the YYSTYPE size is equal to Vec<AST::ast_t*>, which is a required member, so
// YYSTYPE has to be at least as big, but it should not be bigger, otherwise it
// would reduce performance.
static_assert(sizeof(YYSTYPE) == sizeof(Vec<AST::ast_t*>));

} // namespace LFortran


typedef struct LFortran::Location YYLTYPE;
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1


#endif
