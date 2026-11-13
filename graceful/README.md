# A399946: Gilbreath reduction of graceful paths

[A399946](https://oeis.org/A399946) is the maximum terminal value of the Gilbreath reduction
(iterated absolute differences) over all graceful paths of order n. A graceful path of order n
is a permutation of {0, ..., n-1} whose consecutive differences are exactly {1, ..., n-1}.
The sequence was created by Eliott Grillet in September 2026 (A400K Winners) with terms up to a(18).

## New terms (Nov 2026)

| n | a(n) |
|---|------|
| 19 | 7 |
| 20 | 9 |
| 21 | 9 |
| 22 | 9 |
| 23 | 9 |
| 24 | 12 |
| 25 | 10 |
| 26 | 14 |
| 27 | 16 |

## Method

`grace3.cpp` builds each graceful path edge by edge instead of vertex by vertex. It places the
differences d = n-1, n-2, ..., 1 in turn, each as an edge {x, x+d}, while keeping:

- every vertex degree at most 2;
- no cycle (union-find with rollback);
- every remaining difference still able to fit between two vertices of degree below 2.

A tree with maximum degree 2 is a path, so each graceful path is produced exactly once, up to
reversal. The terminal value does not change under reversal. This approach is many orders of
magnitude faster than permutation backtracking: n = 18 takes 0.1 s, and n = 25 about 5 minutes.
`grace3p.cpp` is the same program, split into P chunks for parallel runs:
`./grace3p n P p`.

## Verification

- `grace3` reproduces every known term, a(1)–a(18).
- For every n up to 27, the number of graceful paths enumerated (`perms=`) equals
  [A006967](https://oeis.org/A006967)(n). This shows that the enumeration is complete.
- `grace2.cpp` is an independent permutation backtracking program that updates the difference
  triangle incrementally. It agrees with `grace3`, giving the same maximum and the same set of
  terminal values, for every n it was run on, up to n = 19.

`distributions.txt` gives the full distribution of terminal values for every n, counted over
permutations. For n = 26 and 27 the lines are for chunk 0 of 2; the two chunks are identical,
so the totals are twice these values.

Observation: for n = 19, 20, 24, 26 and 27, the maximum is reached by exactly 4 permutations.
That is a single graceful path, up to reversal and complement.
