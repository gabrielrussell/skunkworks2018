## MongoDB Skunkworks 2018
# subprocess io demultiplexor
Demultiplex the output of arbitrary subprocess. While this POC doesn't actually demultiplex into separate streams, the output is logically demultiplexed via the labeling and could easily be turned in to real demultiplexing.

### compiling
```sh
gcc -Wall -Werror  -o demux demux.c
```

Alternatively you can build it to output in cdbmake format which might be easier to write a parser against

```sh
gcc -Wall -Werror -DCDBM_FORMAT  -o demux demux.c
```

### example regular format
This format lines of pid surrounded by parentheses, followed by either a space or a backslash, followed by the output of the process, followed by a newline
The space indicates that the output was terminated with a newline, and the backslash indicates that it was not.

```sh
./demux gcc -v -Wall -Werror -o demux demux.c
```

```
(1455583) Using built-in specs.
(1455583) COLLECT_GCC=gcc
(1455583) COLLECT_LTO_WRAPPER=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/lto-wrapper
(1455583) Target: x86_64-mongodb-linux
(1455583) Configured with: ../src/combined/configure --with-tune=generic --with-arch_33=nocona --enable-multilib --enable-__cxa_atexit --with-linker-hash-style=gnu --enable-gold --enable-plugins --enable-linker-build-id --with-build-time-tools=/usr/bin --prefix=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU --enable-bootstrap --enable-threads=posix --enable-checking=release --with-pic --with-system-zlib --enable-languages=c,c++,lto --build=x86_64-mongodb-linux
(1455583) Thread model: posix
(1455583) gcc version 8.2.0 (GCC) 
(1455583) COLLECT_GCC_OPTIONS='-v' '-Wall' '-Werror' '-o' 'demux' '-mtune=generic' '-march=x86-64'
(1455583)\ /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/cc1
(1455583)\ -quiet -v demux.c -quiet -dumpbase
(1455583)\ demux.c
(1455583)\ -mtune=generic -march=x86-64
(1455583)\ -auxbase
(1455583)\ demux
(1455583)\ -Wall -Werror
(1455583)\ -version
(1455583)\ -o
(1455583)\ /tmp/ccLlFTrz.s
(1455583) 
(1455584) GNU C17 (GCC) version 8.2.0 (x86_64-mongodb-linux)
(1455584) 	compiled by GNU C version 8.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP
(1455584) 
(1455584) GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
(1455584) ignoring nonexistent directory "/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/include"
(1455584) #include "..." search starts here:
(1455584) #include <...> search starts here:
(1455584)  /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/include
(1455584)  /usr/local/include
(1455584)  /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/include
(1455584)  /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/include-fixed
(1455584)  /usr/include
(1455584) End of search list.
(1455584) GNU C17 (GCC) version 8.2.0 (x86_64-mongodb-linux)
(1455584)\	compiled by GNU C version 8.2.0, 
(1455584) GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP
(1455584) 
(1455584) GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
(1455584) Compiler executable checksum: 3a714022699ea43387875b8a837f3557
(1455583) COLLECT_GCC_OPTIONS='-v' '-Wall' '-Werror' '-o' 'demux' '-mtune=generic' '-march=x86-64'
(1455583)  /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/bin/as -v --64 -o /tmp/cc8ZlCvx.o /tmp/ccLlFTrz.s
(1455585) GNU assembler version 2.30 (x86_64-mongodb-linux) using BFD version (GNU Binutils) 2.30
(1455583) COMPILER_PATH=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/bin/
(1455583) LIBRARY_PATH=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../lib64/:/lib/../lib64/:/usr/lib/../lib64/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/lib/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../:/lib/:/usr/lib/
(1455583) COLLECT_GCC_OPTIONS='-v' '-Wall' '-Werror' '-o' 'demux' '-mtune=generic' '-march=x86-64'
(1455583)\ /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/collect2 -plugin /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/liblto_plugin.so -plugin-opt=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/lto-wrapper -plugin-opt=-fresolution=/tmp/ccOLbj4z.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr --hash-style=gnu -m elf_x86_64 -dynamic-linker
(1455583)\ /lib64/ld-linux-x86-64.so.2 -o demux /lib/../lib64/crt1.o /lib/../lib64/crti.o /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/crtbegin.o -L/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0
(1455583)\ -L/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../lib64 -L/lib/../lib64
(1455583)\ -L/usr/lib/../lib64 -L/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/lib
(1455583)\ -L/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../..
(1455583)\ /tmp/cc8ZlCvx.o -lgcc
(1455583)\ --as-needed
(1455583)\ -lgcc_s
(1455583)\ --no-as-needed
(1455583)\ -lc -lgcc
(1455583)\ --as-needed
(1455583)\ -lgcc_s
(1455583)\ --no-as-needed /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/crtend.o
(1455583)\ /lib/../lib64/crtn.o
(1455583) 
(1455583) COLLECT_GCC_OPTIONS='-v' '-Wall' '-Werror' '-o' 'demux' '-mtune=generic' '-march=x86-64'
```

### example cdbmake format
The cdbmake format is a key-value format whihch is described at http://cr.yp.to/cdb/cdbmake.html

In this case, the keys are pids, and the values are the stdout of the process

```sh
./demux gcc -v -Wall -Werror -DCDBM_FORMAT -o demux demux.c
```

```
+7,22:1455424->Using built-in specs.

+7,722:1455424->COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/lto-wrapper
Target: x86_64-mongodb-linux
Configured with: ../src/combined/configure --with-tune=generic --with-arch_33=nocona --enable-multilib --enable-__cxa_atexit --with-linker-hash-style=gnu --enable-gold --enable-plugins --enable-linker-build-id --with-build-time-tools=/usr/bin --prefix=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU --enable-bootstrap --enable-threads=posix --enable-checking=release --with-pic --with-system-zlib --enable-languages=c,c++,lto --build=x86_64-mongodb-linux
Thread model: posix

+7,25:1455424->gcc version 8.2.0 (GCC) 

+7,342:1455424->COLLECT_GCC_OPTIONS='-v' '-Wall' '-Werror' '-D' 'CDBM_FORMAT' '-o' 'demux' '-mtune=generic' '-march=x86-64'
 /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/cc1 -quiet -v -D CDBM_FORMAT demux.c -quiet -dumpbase demux.c -mtune=generic -march=x86-64 -auxbase demux
+7,43:1455424-> -Wall -Werror -version -o /tmp/cch9Ba4w.s

+7,244:1455425->GNU C17 (GCC) version 8.2.0 (x86_64-mongodb-linux)
	compiled by GNU C version 8.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072

+7,692:1455425->ignoring nonexistent directory "/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/include"
#include "..." search starts here:
#include <...> search starts here:
 /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/include
 /usr/local/include
 /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/include
 /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/include-fixed
 /usr/include
End of search list.

+7,244:1455425->GNU C17 (GCC) version 8.2.0 (x86_64-mongodb-linux)
	compiled by GNU C version 8.2.0, GMP version 6.1.0, MPFR version 3.1.4, MPC version 1.0.3, isl version isl-0.18-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072

+7,63:1455425->Compiler executable checksum: 3a714022699ea43387875b8a837f3557

+7,299:1455424->COLLECT_GCC_OPTIONS='-v' '-Wall' '-Werror' '-D' 'CDBM_FORMAT' '-o' 'demux' '-mtune=generic' '-march=x86-64'
 /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/bin/as -v --64 -o /tmp/ccV7vUPx.o
+7,17:1455424-> /tmp/cch9Ba4w.s

+7,88:1455426->GNU assembler version 2.30 (x86_64-mongodb-linux) using BFD version (GNU Binutils) 2.30

+7,801:1455424->COMPILER_PATH=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/bin/

+7,627:1455424->LIBRARY_PATH=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../lib64/:/lib/../lib64/:/usr/lib/../lib64/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/lib/:/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../:/lib/:/usr/lib/

+7,1042:1455424->COLLECT_GCC_OPTIONS='-v' '-Wall' '-Werror' '-D' 'CDBM_FORMAT' '-o' 'demux' '-mtune=generic' '-march=x86-64'
 /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/collect2 -plugin /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/liblto_plugin.so -plugin-opt=/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/libexec/gcc/x86_64-mongodb-linux/8.2.0/lto-wrapper -plugin-opt=-fresolution=/tmp/ccYqY9Zv.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr --hash-style=gnu -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o demux /lib/../lib64/crt1.o /lib/../lib64/crti.o /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/crtbegin.o
+7,638:1455424-> -L/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0 -L/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../lib64 -L/lib/../lib64 -L/usr/lib/../lib64 -L/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../../../x86_64-mongodb-linux/lib -L/opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/../../.. /tmp/ccV7vUPx.o -lgcc --as-needed
+7,8:1455424-> -lgcc_s
+7,19:1455424-> --no-as-needed -lc
+7,18:1455424-> -lgcc --as-needed
+7,8:1455424-> -lgcc_s
+7,148:1455424-> --no-as-needed /opt/mongodbtoolchain/revisions/4666020dcdac5e2c493adc9e1638877b50ee26c6/stow/gcc-v3.ytU/lib/gcc/x86_64-mongodb-linux/8.2.0/crtend.o
+7,21:1455424-> /lib/../lib64/crtn.o
+7,1:1455424->

+7,108:1455424->COLLECT_GCC_OPTIONS='-v' '-Wall' '-Werror' '-D' 'CDBM_FORMAT' '-o' 'demux' '-mtune=generic' '-march=x86-64'
```
