# fast month boundary

a fresh take on a very common problem.

## epoch date

let `ymd()` be a routine which accepts an arbitrary triple (year, month, day) which represents a valid Gregorian date, and returns a unique signed integer which represents the number of days from/to given date relative to some chosen "epoch time". for example:

```
int ymd(int y,int m,int d){return y-=2001,m=12*y+m+9,m/12*1461/4+mb(m%12)-307+d;}
```

in this implementation, `ymd(2001,1,1)` yields `0`, that is January 1st, 2001 must be the epoch date.

we also observe a critical moving part of `ymd()`, which is the `mb()` routine, or _month boundary_ which is defined as follows:

> a map of month indices `0..11` where `0` represents `March`, to the number of days elapsed since March 1st up to
  the 1st day of a given month, which gives the following sequence:

```
0 31 61 92 122 153 184 214 245 275 306 337
```

a great many texts have been written on this and related algorighms, a typical such [text](https://howardhinnant.github.io/date_algorithms.html) usually begins with an elucidation why it happens to be more convenient to "begin" a Gregorian year in March for this particular purpose.

## some mb() routines

the code in this repository implements a simple linear benchmark of two different implementations of `mb()` in plain ISO C:

 1. a straightforward constant lookup table (LUT) solution.
 2. a less naive technique offered by the regents of kparc.

```
$ cd mb && make

month boundary benchmark (lut):
arena 1536 mb, 512 rounds:
2084-11-19 337 30638
2016-6-26 184 5655
2087-1-7 31 31417
...
checksum: 313672978615296 wall time: 40.845529s


month boundary benchmark (kpc):
arena 1536 mb, 512 rounds:
2084-11-19 337 30638
2016-6-26 184 5655
2087-1-7 31 31417
...
checksum: 313672978615296 wall time: 5.535038s

```

please let us know if you are aware of prior art of the latter techique, or a better one.


copyright (c) 2020-2024 regents of kparc, MIT license

`/:~`
