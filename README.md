# **R**everse **P**olish **N**otation language
Inspired by Hewlett-Packard RPL language

**HP28S** user manual is provided as a reference

- This project plans to create a clone of **Hewlett Packard RPN calculator language**, including at least STACK, STORE, BRANCH, TEST, TRIG and LOGS commands of HP28S RPL implementation.

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

## Here is a list of HP28s reserved words.

New commands (nonexistent in RPL) are tagged with * in column new.
Commands already implemented are tagged with * in column impl.

| category | command | new | implemented | tested |
| -------- | ------- | --- | ----------- | ------ |
| GENERAL |     nop      |*|       *|       *|
| GENERAL |     help/h/? |   * |      *| |
| GENERAL |     quit/exit/q| *|       *| |
| GENERAL |     test      |  * |      *| |
| GENERAL |     verbose    | * |      *| |
| GENERAL |     std       | |         *| |
| GENERAL |     fix       | |         *| |
| GENERAL |     sci       | |         *| |
| GENERAL |     version   |  * |      *| |
| GENERAL |     uname      | * |      *| |
| GENERAL |     edit       | |        *| |
| REAL |        +          | |        *| |
| REAL |        -          | |        *| |
| REAL |        neg        | |        *| |
| REAL |        *          | |        *| |
| REAL |        /          | |        *| |
| REAL |        inv        | |        *| |
| REAL |        %          |  |       *| |
| REAL |        %CH        |  |       *| |
| REAL |        ^          | |        *| |
| REAL |        sqrt       | * |      *| |
| REAL |        sq         | * |      *| |
| REAL |        mod         |*|       *| |
| STACK |       drop       | |        *| |
| STACK |       swap       | |        *| |
| STACK |       roll       | | | |
| STACK |       dup        | |        *| |
| STACK |       over | | | |
| STACK |       dup2     |  |         *| |
| STACK |       drop2     | |         *| |
| STACK |       rot      | |          *| |
| STACK |       list-> | | | |
| STACK |       rolld | | | |
| STACK |       pick     | |          *| |
| STACK |       dupn | | | |
| STACK |       dropn | | | |
| STACK |       depth    | |          *| |
| STACK |       ->list | | | |
| STACK |       load_store | * |      *| |
| STACK |       save_store | * |      *| |
| STORE |       sto        | |        * | |
| STORE |       rcl        | |        * | |
| STORE |       purge        | |        * | |
| STORE |       sto+ | | | |
| STORE |       sto- | | | |
| STORE |       sto* | | | |
| STORE |       sto/ | | | |
| STORE |       sneg | | | |
| STORE |       sinv | | | |
| STORE |       sconj | | | |
| STORE |       erase | | * | * |
| STORE |       vars | | * | * |
| STORE |       include | | | |
| STORE |       load_vars | | | |
| STORE |       save_vars | | | |
| PROGRAM |     eval | | * | |
| PROGRAM |     load_prog | | | |
| PROGRAM |     save_prog | | | |
| ALGEBRA |     neg | | * | * |
| ALGEBRA |     colct | | | |
| ALGEBRA |     expan | | | |
| ALGEBRA |     size | | | |
| ALGEBRA |     form | | | |
| ALGEBRA |     obsub | | | |
| ALGEBRA |     exsub | | | |
| ALGEBRA |     taylr | | | |
| ALGEBRA |     isol | | | |
| ALGEBRA |     quad  | | | |
| ALGEBRA |     show  | | | |
| ALGEBRA |     obget | | | |
| ALGEBRA |     exget | | | |
| BINARY |      + | | * | * |
| BINARY |      - | | * | * |
| BINARY |      * | | * | * |
| BINARY |      / | | * | * |
| BINARY |      dec | | * | * |
| BINARY |      hex | | * | * |
| BINARY |      oct | | * | * |
| BINARY |      bin | | * | * |
| BINARY |      stws | | | |
| BINARY |      rcws | | | |
| BINARY |      rl | | | |
| BINARY |      rr | | | |
| BINARY |      rlb | | | |
| BINARY |      rrb | | | |
| BINARY |      r->b | | * | * |
| BINARY |      b->r | | * | * |
| BINARY |      sl | | | |
| BINARY |      sr | | | |
| BINARY |      slb | | | |
| BINARY |      srb | | | |
| BINARY |      asr | | | |
| BINARY |      and | | * | * |
| BINARY |      or | | * | * |
| BINARY |      xor | | * | * |
| BINARY |      not | | * | * |
| STRING |      + | | * | |
| STRING |      ->str | | * | |
| STRING |      str-> | | * | |
| STRING |      chr | | | |
| STRING |      num | | | |
| STRING |      ->lcd | | | |
| STRING |      lcd-> | | | |
| STRING |      pos | | | |
| STRING |      sub | | | |
| STRING |      size | | | |
| STRING |      disp | | | |
| BRANCH |
| BRANCH |      if | | * | * |
| BRANCH |      then | | * | * |
| BRANCH |      else | | * | * |
| BRANCH |      end | | * | * |
| BRANCH |      start | | * | * |
| BRANCH |      for | | * | * |
| BRANCH |      next | | * | * |
| BRANCH |      step | | * | * |
| BRANCH |      ift | | | |
| BRANCH |      ifte | | | |
| BRANCH |      do | | | |
| BRANCH |      until | | | |
| BRANCH |      end | | | |
| BRANCH |      while | | | |
| BRANCH |      repeat | | | |
| BRANCH |      end | | | |
| TEST |        != | | * | |
| TEST |        > | | * | |
| TEST |        >= | | * | |
| TEST |        < | | * | |
| TEST |        <= | | * | |
| TEST |        sf | | | |
| TEST |        cf | | | |
| TEST |        fs? | | | |
| TEST |        fc? | | | |
| TEST |        fs?c | | | |
| TEST |        fc?c | | | |
| TEST |        and | | * | |
| TEST |        or | | * | |
| TEST |        xor | | * | |
| TEST |        not | | * | |
| TEST |        same | | * | |
| TEST |        == | | * | |
| TEST |        stof | | | |
| TEST |        rclf | | | |
| TEST |        type | | | |
| TRIG |        pi  | | * | * |
| TRIG |        sin | | * | |
| TRIG |        asin | | * | |
| TRIG |        cos | | * | |
| TRIG |        acos | | * | |
| TRIG |        tan | | * | |
| TRIG |        atan | | * | |
| TRIG |        p→r | | | |
| TRIG |        r→p | | | |
| TRIG |        r→c | | | |
| TRIG |        c→r | | | |
| TRIG |        arg | | | |
| TRIG |        →hms | | | |
| TRIG |        hms→ | | | |
| TRIG |        hms+ | | | |
| TRIG |        hms- | | | |
| TRIG |        d→r | | * | |
| TRIG |        r→d | | * | |
| LOGS |        log | | * | |
| LOGS |        alog | | * | |
| LOGS |        ln | | * | |
| LOGS |        exp | | * | |
| LOGS |        lnp1 | | | |
| LOGS |        expm | | | |
| LOGS |        sinh | | * | |
| LOGS |        asinh | | * | |
| LOGS |        cosh | | * | |
| LOGS |        acosh | | * | |
| LOGS |        tanh | | * | |
| LOGS |        atanh | | * | |

## Further

**MEMORY**
 mem, menu, order, path, home, crdir, vars, clusr,

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
 sst, halt, abort, kill, wait, key, bepp,  cllcd,  disp,  clmf, errn,
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
