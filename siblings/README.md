# Sibling sequences: A363002 and A363003

The same column-wise transfer method that gave A080839(14) extends directly to two
sibling sequences. Only the rule for the first row (the sequence itself) changes:

| Mode | Sequence | Row-0 rule | Weight of a step with row-1 entry s |
|------|----------|------------|--------------------------------------|
| 0 | A080839 (increasing, positive) | x' = x + s, s > 0 | [s > 0] |
| 1 | A363002 (nondecreasing, positive) | x' = x + s | 1 |
| 2 | A363003 (all integers) | x' = x ± s | 2 if s > 0, else 1 |

Rows below row 0 follow the same transitions in every mode, so modes 1 and 2 share one
state graph and differ only in the weights.

## New terms (Nov 2026)

| Sequence | n | a(n) |
|----------|---|------|
| A363002 | 13 | 187385419983 |
| A363003 | 11 | 35893184070 |
| A363003 | 12 | 3319196894026 |
| A363003 | 13 | 447304468741942 |

## Verification

Each new term was computed by two independent programs:

- `gilw.cpp`: hash-merged BFS plus DFS with a cache (generalization of `a080839.cpp`).
  Usage: `./gilw MODE n [P p]`.
- `verify4.cpp`: a separate level-by-level forward merge using sorted vectors and a
  different state encoding (mixed radix). Usage: `./verify4 MODE n`.

`transfer_py.py` (plain Python dictionaries) confirms the terms up to n = 12.
`definitional.py` checks the model directly against the definition of the Gilbreath
transform for small n. Every program reproduces all terms previously in the OEIS.

Timings on 2 cores: A363003(13) takes about 4 minutes with either program, and
A363002(13) about 3.5 to 4 minutes.

Build: `g++ -O3 -march=native -o gilw gilw.cpp` and `g++ -O2 -o verify4 verify4.cpp`.
