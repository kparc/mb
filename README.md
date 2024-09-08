# fast month boundary

we revisit an old problem: it is very inefficient to represent dates of Gregorian calendar in computer memory in a way most humans are accustomed to perceive them. for instance, there is a galaxy of ways to write down `February 1st, 1981` in some human-readable format, e.g. `020181`, `1981-02-01` or "1-e февраля 1981 года н.э." but none of them are good for a computer to store and perform efficient arithmetic on them.

for that reason, computers usually do it differently.

## epoch date

let `ymd()` be a function which accepts an arbitrary triple (year, month, day) which represents a valid Gregorian date, and returns a unique signed integer which represents the number of days prior to or after some chosen fixed point in time, known as _epoch_. for example:

```c
int ymd(int y,int m,int d){return y-=2001,m=12*y+m+9,m/12*1461/4+mb(m%12)-307+d;}
```

in this C implementation, `ymd(2001,1,1)` yields `0`, which means that January 1st, 2001 must be its _epoch date_. the reason it doesn't use a much more famous epoch date which marks the beginning of _Aerae vulgaris_ is much more down to earth: beyond any doubt, Jan 1st 2001 was a `Monday`. 

> in contrast, although it's commonly accepted that the first day of 1 BCE fell on a weekend day, modern scholars seem to differ in opinion when it comes to the days of old. as any computer programmer would agree, we should at least be thankful for the lapse of 0 BCE, mostly because the concept of zero became popular in certain parts much later on.

computer programmers also rely on great many texts written on the subject of date arithmetic, and any such [text](https://howardhinnant.github.io/date_algorithms.html) usually begins with elucidation of why it happens to be more convenient to "begin" a Gregorian year in March. if the reason for this oddity isn't immediately clear, it helps to revisit the idea of _leap years_, which is a fundamental feature of Gregorian system that makes it remarkably accurate in the long term while keeping it sufficiently simple for humans. it states that every fourth year is a leap year except for century years that are not divisible by 400. in simpler terms, this rule eliminates 3 leap years every 4 centuries, making the Gregorian calendar sufficiently correct for common purposes.

> the leap year formula is due to the Vatican librarian Aloysius Giglio, who lived around mid 16th century. little is known about this man, but his tremendous contribution lives on: although the concept of occasional *leap second* is based on modern science, it adjusts Giglio's calculations only so slightly as to keep the general population mostly unaware of it.

however, as of today efficient translation of relative epoch offsets back and forth to human-readable format remains a non-trivial task, a small part of which we would like to illustrate below.

## month boundary

we focus on a critical moving part of `ymd()` implementation, which is the `mb()` routine, or _month boundary_, which we define as follows:

> "a map of month indices `0..11` where `0` represents `March`, to the number of days elapsed since 1st of March up to the 1st day of a given month", which results in the following static sequence for _any_ given year, be it a leap year or not:

```
0 31 61 92 122 153 184 214 245 275 306 337
```

before we continue, we must appreciate the fact that calculations relying on `mb()` are taking place countless times per second all over the planet Earth, all day, every day, and they require time, space and energy. luckily enough, one might say, at least the `mb()` part is a *no-brainer*.

## two mb() implementations

the code in this repository implements a simple linear benchmark of two equivalent implementations of `mb()` in ISO C:

1. no-brainer way:

```c
// lut [1]
static const I lut[12]={0,31,61,92,122,153,184,214,245,275,306,337};
#define mb(m) lut[m]
```

2. another way:

```c
// kpc [2]
#define mb(m) (((short)((m*979)+15))>>5)
```

3. try them on your hardware using your compiler:

```sh
$ git clone https://github.com/kparc/mb && cd mb && make

Apple clang version 15.0.0 (clang-1500.3.9.4)
Target: arm64-apple-darwin24.0.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin

month boundary benchmark (lut):

arena 3072 mb, 1 laps:
2008-2-24 61 2610
2059-11-9 337 21496
2045-3-27 92 16156
...
checksum: 1225299026794 wall time: 0.165590s

month boundary benchmark (kpc):

arena 3072 mb, 1 laps:
2008-2-24 61 2610
2059-11-9 337 21496
2045-3-27 92 16156
...
checksum: 1225299026794 wall time: 0.062350s
```

the code pre-generates about 3 gigabytes of random valid `(y,m,d)` triplets, and then benchmarks both versions of `mb()` using this dataset. `checksum` value ensures that both versions correctly perform identical work. `wall time` is the measure how fast.

## how

in short, our approach abandons the idea of static lookup table in favor of computing the correct value on the fly every time `mb()` is invoked. since [2] requires nothing except a dash of register memory, two artithmetic and one bitwise operation, it requires very little time, space and energy.

we admit that the C expression [2] does not reveal much about the origin of the chosen constants and their connection to the Gregorian calendar. to that end, we can assure the reader that such a connection exists, and leave the sheer joy of self-discovery to the technically inclined. for those equipped with self-designed sat solver, we suggest to use a softer touch instead, e.g. a decent [graphing calculator](https://desmos.com) should suffice.

## conclusions

while we acknowledge that the chosen benchmarking method could have been less synthetic, we assume it to be sufficiently precise to make the following claims:

* [2] is considerably and reproducibly faster than [1] on all tested (micro-)architectures within our reach. your mileage may vary, feel free to share your results.

* we claim that the performance of [2] can be said to be deterministic within the limitations of available opcode timings which are famously freely (not)available from the majority of CPU vendors.

* we claim that the performance of [1] must be fundamentally dependent on the probability of a cache eviction event, which we assume to be deterministically greater than 0.

* we are aware of the argument which states "it takes a fool to assume that modern CPUs can be as foolish as to evict a tiny yet critical LUT under any thinkable cuircumstance, no matter how heavy and random the cache pressure may be". to that end, we respectfully refer the reader to propositions (b-c) and delegate the burden of proof to where it belongs by a long-standing convention.

* although [2] wins neglibily little space, it does not trade it for time, since it also wins on time. it wins.

* last but not least, solutions [1] and [2] display very different behaviours on invalid aka insecure input, which we assume to be sufficiently self-evident as not to require extra prose.

please let us know if you are aware of prior art of [2] or a more efficient way to implement `mb()` in case you are at liberty to share it.


copyright (c) 2020-2024 regents of kparc, MIT license

_in memoriam of [aab](https://peps.python.org/pep-0495/)._

`/:~`
