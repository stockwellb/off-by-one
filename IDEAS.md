# Daily C Practice Ideas

Trivial but complete programs — each one teaches one real thing. The goal is
getting the details right (signedness, terminators, allocation ownership, return
values), not scope.

## Ideas

- **`wc`-lite** — count bytes/words/lines from stdin.
  Teaches: state machines (in-word vs. between-words) and the `getline` loop.

- **`head -n`** — print the first N lines, N from `argv`.
  Teaches: `argv` parsing + `strtol` (and its own error-checking edge cases).

- **`rot13` / `xor` filter** — byte-in, byte-out `getchar`/`putchar` loop.
  Teaches: the pure-passthrough shape and `unsigned char`.

- **`tac`-lite** — read all lines, print them in reverse.
  Teaches: growing an array of pointers (`realloc`) and freeing all of them.

- **trim trailing whitespace** from each line.
  Teaches: in-place buffer editing and the off-by-one on the walk-back.

## C footguns worth drilling

Small programs are a good way to make these automatic:

- Check every return value (`fgets`, `getline`, `fread`, `strtol`, `malloc`).
- Fixed buffers silently truncate — know your caps.
- NUL-terminator vs. byte-count: string functions stop at `\0`; binary needs a length.
- Signed `char` + `<ctype.h>` is UB on negative values — cast to `unsigned char`.
- `malloc`/`getline` ownership: whoever allocates decides who frees.
