# Fast bedGraph normalization to TPM

TPM is the new standard metric for normalizing sequencing data. Unlike
previous methods, TPM ensures that the sum of all read values in a
sample is always 1e7. Since the sum of reads is always 1e7, the
relative expression of different genomic regions can be effectively
compared regardless of differences in sequencing depth.

Here, we present a small C++ program to normalize bedGraph files to
TPM. The program performs TPM normalization quickly, and is primarily
by the speed of your hard disk. Initial testing shows that the program
should take about `(FILESIZE / DISK_WRITE_SPEED) * 2 ` seconds to run
on modern hardware. The program performs internal checks to verify the
normalization, and will print diagnostic information if the normalized
data deviates too far from expected values.

## Usage

Given a standard bedGraph without a header named `$yourFile.bedGraph`,
outputting to a new file called `$normalized.bedGraph`, use the
command:
``` shell
./normalizeBedgraph $yourFile.bedGraph > $normalized.bedGraph
```

## Building

Building this program requires a C++11 compliant compiler. We
recommend the use of either clang++ or g++. If you choose to use g++,
you will have to change the variable CXX in the Makefile.

To build, simply run `make`. This will build an optimized binary.

## License

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 3, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth
Floor, Boston, MA 02110-1301, USA.
