/* normalizeBedGraph.cpp --- normalize bedGraph to TPM
 *
 * Filename: normalizeBedGraph.cpp
 * Description: normalize bedGraph to TPM
 * Author: Zachary Maas <zama8258@colorado.edu>
 * Maintainer: Zachary Maas <zama8258@colorado.edu>
 * Created: Wed Aug 21 13:38:37 2019 (-0600)
 * Version: 1.0.0
 * URL: https://github.com/Dowell-Lab/normalizeBedGraph
 *
 */

/* Commentary:
 *
 * Quickly normalize a bedGraph file using TPM.
 *
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */

#include <cmath>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  // Initialization
  if (argc < 2) {
    std::cerr << "Must provide bedGraph file as argument." << std::endl;
    return -1;
  }

  // Load bedGraph
  std::ifstream bedGraph(argv[1]);

  // Calculate sum for TPM
  unsigned long sum = 0;
  if (bedGraph) {
    std::string line;
    unsigned long currLine = 1;
    while (std::getline(bedGraph, line)) {
      // Split each line
      std::istringstream lineItems(line);
      std::string item;
      std::string items[4];
      unsigned int itemSize = 0;

      while (std::getline(lineItems, item, '\t')) {
        items[itemSize] = item;
        itemSize++;
      }
      if (itemSize < 4) {
        std::cerr << "Malformed entry on line " << currLine << std::endl;
        return -1;
      }
      currLine++;
      const unsigned long start = std::stoul(items[1]);
      const unsigned long stop = std::stoul(items[2]);
      const unsigned long reads = std::stoul(items[3]);
      unsigned long length = stop - start;

      // Must account for single bp regions
      if (length <= 2) {
        length = 1;
      }

      sum += (reads / length);
    }

    // Reset to start of file
    bedGraph.clear();
    bedGraph.seekg(0, std::ios::beg);
    double tpmSum = 0;

		// Normalize and print out
    while (std::getline(bedGraph, line)) {
      // Split each line
      std::istringstream lineItems(line);
      std::string item;
      std::vector<std::string> items;

      while (std::getline(lineItems, item, '\t')) {
        items.push_back(item);
      }
      if (items.size() < 4) {
        std::cerr << "Malformed entry on line " << currLine << std::endl;
        return -1;
      }
      std::string chr = items[0];
      const unsigned long start = std::stoul(items[1]);
      const unsigned long stop = std::stoul(items[2]);
      unsigned long length = stop - start;

      // Must account for single bp regions
      if (length <= 2) {
        length = 1;
      }

      // Calculate tpm value
      float tpm = 10e6 * ((stof(items[3]) / float(length)) / float(sum));
      tpmSum += tpm;
      std::cout << chr << "\t" << start << "\t" << stop << "\t" << tpm << "\n";
    }
    if (std::fabs(1e7 - tpmSum) > 10) {
      std::cerr << "Higher than expected error in sum of tpm values.\n";
      std::cerr << "Sum of TPM Values: " << tpmSum << "\n";
      std::cerr << "Distance from 1e7: " << 1e7 - tpmSum << "\n";
    }
  }

  bedGraph.close();
  return 0;
}

/* normalizeBedGraph.c ends here */
