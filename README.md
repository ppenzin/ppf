PPF - P4 Packet Filter
======================

How hard would it be to implement P4 frontend from scratch? P4 has very simple
syntax ([P4 16][p4-16] in particular). We would use official [LLVM tutorial][t]
('Kaleidoscope' use case).

Limitations:

- No standalone builds (to do)
- No preprocessor support yet (next iteration)

To build, checkout llvm and then checkout PPF repository into its tools subdirectory:

```
$ git clone https://github.com/llvm-mirror/llvm.git
$ cd llvm/tools
$ git clone https://FIXME
```

```
$ mkdir build
$ cd build
$ cmake ../llvm
$ make
```

[t]: https://llvm.org/docs/tutorial/
[p4-16]: https://p4.org/p4-spec/docs/P4-16-v1.0.0-spec.html
