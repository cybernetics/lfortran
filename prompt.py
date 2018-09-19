#!/usr/bin/env python

from ctypes import CFUNCTYPE, c_double

from pygments.lexers import FortranLexer

from prompt_toolkit import PromptSession, print_formatted_text, HTML
from prompt_toolkit.lexers import PygmentsLexer
from prompt_toolkit.key_binding import KeyBindings

import llvmlite.binding as llvm

from liblfort.ast import parse, dump, SyntaxErrorException
from liblfort.codegen.evaluator import FortranEvaluator
from liblfort.codegen.gen import codegen
from liblfort.semantic.analyze import create_symbol_table, annotate_tree


def print_bold(text):
    print_formatted_text(HTML('<ansiblue><b>%s</b></ansiblue>' % text))

def handle_input(engine, evaluator, source):
    print_bold("Input:")
    print(source)

    result = evaluator.evaluate(source)

    print()
    print_bold("AST:")
    print(dump(evaluator.ast_tree))

    print()
    print_bold("Symbol table:")
    print(evaluator.symbol_table)

    print()
    print_bold("LLVM IR:")
    print(evaluator._source_ll)

    print_bold("Result:")
    print(result)

kb = KeyBindings()

@kb.add('escape', 'enter')
def _(event):
    event.current_buffer.insert_text('\n')

@kb.add('enter')
def _(event):
    event.current_buffer.validate_and_handle()

def main():
    llvm.initialize()
    llvm.initialize_native_asmprinter()
    llvm.initialize_native_target()

    target = llvm.Target.from_triple(llvm.get_default_triple())
    target_machine = target.create_target_machine()
    target_machine.set_asm_verbosity(True)

    # Empty backing module
    backing_mod = llvm.parse_assembly("")
    backing_mod.verify()
    engine = llvm.create_mcjit_compiler(backing_mod, target_machine)

    print("Interactive Fortran.")
    print("  * Use Ctrl-D to exit.")
    print("  * Use Enter to submit.")
    print("  * Features:")
    print("    - Multi-line editing (use Alt-Enter)")
    print("    - History")
    print("    - Syntax highlighting")
    print()

    fortran_evaluator = FortranEvaluator()

    session = PromptSession('> ', lexer=PygmentsLexer(FortranLexer),
            multiline=True, key_bindings=kb)
    try:
        while True:
            text = session.prompt()
            print()
            handle_input(engine, fortran_evaluator, text)
            print()
    except EOFError:
        print("Exiting.")

if __name__ == "__main__":
    main()