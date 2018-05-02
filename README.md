PPF - P4 Packet Filter
======================

How hard would it be to implement P4 frontend from scratch? P4 is a
domain-specific language with very simple syntax ([P4 16][p4-16] in
particular). We would use official [LLVM tutorial][t] ('Kaleidoscope' use
case).

Scope of the project is to enable compiling P4 to eBPF bytecode bypassing p4c
and clang. P4 language has other capabilities, like describing abstract
networking hardware, but those are not the focus here (feel free to experiment
with the code though).

Limitations:

- No standalone builds (to do)
- No preprocessor support yet (next iteration)
- No driver yet (next iteration)

To build, checkout llvm and then checkout PPF repository into its tools subdirectory:

```
$ git clone https://github.com/llvm-mirror/llvm.git
$ cd llvm/tools
$ git clone https://github.com/ppenzin/ppf.git
```

```
$ mkdir build
$ cd build
$ cmake ../llvm
$ make
```

[t]: https://llvm.org/docs/tutorial/
[p4-16]: https://p4.org/p4-spec/docs/P4-16-v1.0.0-spec.html
