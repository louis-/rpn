# Reverse Polish Notation language

- This project plans to create a clone of **Hewlett Packard RPN calculator language**, including at least STACK, STORE, BRANCH, TEST, TRIG and LOGS commands of HP28S RPL implementation.

- Inspired by Hewlett-Packard RPL language. **HP28S** user manual is provided as a reference.

- Following objects are managed: numbers, binaries, symbols, strings,
 programs, plus keywords (ie langage commands and flow controls).

- The special feature of this language is to make no difference between
keywords and functions, even user functions.

- Numbers (ie scalars) are in 128-bit quadruple precision format (long
double). Binaries are 64-bits longwords format (long long int).

- A GNU-readline-based interactive editor with autocompletion is provided.

- Language extensions will soon be included:
 - file objects and functions,
 - date and time objects and functions,
 - shell-calling objects with return code, stdout and stderr treatment,
 - loading and saving | STACK |, variables, | PROGRAM |s from / to filesystem

## Implemented commands

This commands list match HP28s reserved words. Commands marked as 'new' do not exist in HP28s.

| category | command | new | implemented | tested |
| -------- | ------- | --- | ----------- | ------ |
| GENERAL | nop |yes| yes| yes|
| GENERAL | help/h/? | yes | yes| |
| GENERAL | quit/exit/q| yes| yes| |
| GENERAL | test | yes | yes| |
| GENERAL | verbose | yes | yes| |
| GENERAL | std | | yes| |
| GENERAL | fix | | yes| |
| GENERAL | sci | | yes| |
| GENERAL | version | yes | yes| |
| GENERAL | uname | yes | yes| |
| GENERAL | edit | | yes| |
| REAL | + | | yes| |
| REAL | - | | yes| |
| REAL | neg | | yes| |
| REAL | * | | yes| |
| REAL | / | | yes| |
| REAL | inv | | yes| |
| REAL | % | | yes| |
| REAL | %CH | | yes| |
| REAL | ^ | | yes| |
| REAL | sqrt | yes | yes| |
| REAL | sq | yes | yes| |
| REAL | mod |yes| yes| |
| STACK | drop | | yes| |
| STACK | swap | | yes| |
| STACK | roll | | | |
| STACK | dup | | yes| |
| STACK | over | | | |
| STACK | dup2 | | yes| |
| STACK | drop2 | | yes| |
| STACK | rot | | yes| |
| STACK | list-> | | | |
| STACK | rolld | | | |
| STACK | pick | | yes| |
| STACK | dupn | | | |
| STACK | dropn | | | |
| STACK | depth | | yes| |
| STACK | ->list | | | |
| STACK | load_store | yes | yes| |
| STACK | save_store | yes | yes| |
| STORE | sto | | yes | |
| STORE | rcl | | yes | |
| STORE | purge | | yes | |
| STORE | sto+ | | | |
| STORE | sto- | | | |
| STORE | sto* | | | |
| STORE | sto/ | | | |
| STORE | sneg | | | |
| STORE | sinv | | | |
| STORE | sconj | | | |
| STORE | erase | | yes | yes |
| STORE | vars | | yes | yes |
| STORE | include | | | |
| STORE | load_vars | | | |
| STORE | save_vars | | | |
| PROGRAM | eval | | yes | |
| PROGRAM | load_prog | | | |
| PROGRAM | save_prog | | | |
| ALGEBRA | neg | | yes | yes |
| ALGEBRA | colct | | | |
| ALGEBRA | expan | | | |
| ALGEBRA | size | | | |
| ALGEBRA | form | | | |
| ALGEBRA | obsub | | | |
| ALGEBRA | exsub | | | |
| ALGEBRA | taylr | | | |
| ALGEBRA | isol | | | |
| ALGEBRA | quad | | | |
| ALGEBRA | show | | | |
| ALGEBRA | obget | | | |
| ALGEBRA | exget | | | |
| BINARY | + | | yes | yes |
| BINARY | - | | yes | yes |
| BINARY | * | | yes | yes |
| BINARY | / | | yes | yes |
| BINARY | dec | | yes | yes |
| BINARY | hex | | yes | yes |
| BINARY | oct | | yes | yes |
| BINARY | bin | | yes | yes |
| BINARY | stws | | | |
| BINARY | rcws | | | |
| BINARY | rl | | | |
| BINARY | rr | | | |
| BINARY | rlb | | | |
| BINARY | rrb | | | |
| BINARY | r->b | | yes | yes |
| BINARY | b->r | | yes | yes |
| BINARY | sl | | | |
| BINARY | sr | | | |
| BINARY | slb | | | |
| BINARY | srb | | | |
| BINARY | asr | | | |
| BINARY | and | | yes | yes |
| BINARY | or | | yes | yes |
| BINARY | xor | | yes | yes |
| BINARY | not | | yes | yes |
| STRING | + | | yes | |
| STRING | ->str | | yes | |
| STRING | str-> | | yes | |
| STRING | chr | | | |
| STRING | num | | | |
| STRING | ->lcd | | | |
| STRING | lcd-> | | | |
| STRING | pos | | | |
| STRING | sub | | | |
| STRING | size | | | |
| STRING | disp | | | |
| BRANCH |
| BRANCH | if | | yes | yes |
| BRANCH | then | | yes | yes |
| BRANCH | else | | yes | yes |
| BRANCH | end | | yes | yes |
| BRANCH | start | | yes | yes |
| BRANCH | for | | yes | yes |
| BRANCH | next | | yes | yes |
| BRANCH | step | | yes | yes |
| BRANCH | ift | | | |
| BRANCH | ifte | | | |
| BRANCH | do | | | |
| BRANCH | until | | | |
| BRANCH | end | | | |
| BRANCH | while | | | |
| BRANCH | repeat | | | |
| BRANCH | end | | | |
| TEST | != | | yes | |
| TEST | > | | yes | |
| TEST | >= | | yes | |
| TEST | < | | yes | |
| TEST | <= | | yes | |
| TEST | sf | | | |
| TEST | cf | | | |
| TEST | fs? | | | |
| TEST | fc? | | | |
| TEST | fs?c | | | |
| TEST | fc?c | | | |
| TEST | and | | yes | |
| TEST | or | | yes | |
| TEST | xor | | yes | |
| TEST | not | | yes | |
| TEST | same | | yes | |
| TEST | == | | yes | |
| TEST | stof | | | |
| TEST | rclf | | | |
| TEST | type | | | |
| TRIG | pi | | yes | yes |
| TRIG | sin | | yes | |
| TRIG | asin | | yes | |
| TRIG | cos | | yes | |
| TRIG | acos | | yes | |
| TRIG | tan | | yes | |
| TRIG | atan | | yes | |
| TRIG | p->r | | | |
| TRIG | r->p | | | |
| TRIG | r->c | | | |
| TRIG | c->r | | | |
| TRIG | arg | | | |
| TRIG | ->hms | | | |
| TRIG | hms-> | | | |
| TRIG | hms+ | | | |
| TRIG | hms- | | | |
| TRIG | d->r | | yes | |
| TRIG | r->d | | yes | |
| LOGS | log | | yes | |
| LOGS | alog | | yes | |
| LOGS | ln | | yes | |
| LOGS | exp | | yes | |
| LOGS | lnp1 | | | |
| LOGS | expm | | | |
| LOGS | sinh | | yes | |
| LOGS | asinh | | yes | |
| LOGS | cosh | | yes | |
| LOGS | acosh | | yes | |
| LOGS | tanh | | yes | |
| LOGS | atanh | | yes | | |
| MEMORY | vars | | yes | | |

## HP28s commands which won't be implemented

**MEMORY**
 mem, menu, order, path, home, crdir, clusr,

**STAT**
 ∑dat, ∑par, ∑+, ∑-, n∑, cl∑, sto∑, rcl∑, tot, mean, sdev, var, max∑,
 min∑, col∑, corr, cov, lr, predev, utpc, utpf, utpn, utpt, comb, perm

**PRINT**
 pr1, prst, prvar, prlcd, cr, trac, prstc, prusr, prmd

**SOLV**
 steq, rceq, isol, quad, show, root,

**PLOT**
 ppar, steq, rceq, pmin, pmax, indep, draw, res, axes, centr, \*w, \*h,
 sto∑, rcl∑, col∑, scl∑, drw∑, cllcd, digtiz

**CURSOR**
 ins, del, ← → ↑ ↓, cmd, undo, last, ml, rdx, prmd

**CONTRL**
 sst, halt, abort, kill, wait, key, bepp, cllcd, disp, clmf, errn,
 errm

**CATALOG**
 next, prev, scan, use, fetch, quit

**UNITS**
 convert

**CUSTOM**
 menu, custom

## Notes
 Compiled with g++ Makefile generated by automake.
 External dependencies needed: automake, readline (libreadline-dev)
