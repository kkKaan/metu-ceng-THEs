syn iskeyword @,48-57,%,.,_

syn keyword y86Opcode addq subq andq xorq halt nop irmovq rrmovq mrmovq rmmovq call ret pushq popq jmp jle jl je jne jge jg cmovle cmovl cmove cmovne cmovge cmovg leaq icmpq
syn keyword y86Reg %rax %rcx %rdx %rbx %rsp %rbp %rsi %rdi %r8 %r9 %r10 %r11 %r12 %r13 %r14
syn keyword y86Directive .align .pos .quad .byte .word .long

" Simple enough
syn match y86Comment    "#.*$"
" For offsets or directives, preceded by whitespace, NOT followed by ,
syn match y86Constant   "\v\s[-+]?((0x[a-fA-F0-9]+)|(\d+)),@!"
" Followed by comma implies an immediate move, do not highlight without $
syn match y86Immediate  "\v\$[-+]?((0x[a-fA-F-0-9]+)|(\d+)),"he=e-1
" Anything at the start of the line followed by :, pretty much
syn match y86Label      "^[\._a-zA-Z0-9]\+:"

hi def link y86Opcode       Statement 
hi def link y86Reg          Identifier
hi def link y86Comment      Comment
hi def link y86Constant     Constant
hi def link y86Immediate    Constant
hi def link y86Label        Type
hi def link y86Directive    PreProc
