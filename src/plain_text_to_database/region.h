#pragma once

#include <initializer_list>
using std::initializer_list;

#include <list>
using std::list;

#include <string>
using std::string;

namespace PlainTextToDatabase {

// Represent a region on positional file.
struct Region {
  // Construct simple region 
  // where field name, start position and length are defined.
  Region (string name, size_t position, size_t length) : 
    name(name), position(position), length(length) {}

  // Construct simple region 
  // where field name and length are defined.
  Region (string name, size_t length) : 
    name(name), position(0), length(length) {}


  // Construct a root region.
  // This region haven't a name and by assumption starts at begin.
  Region (std::initializer_list<Region> regions) : 
    name(""), position(0), regions(regions) {}

  // Construct a region defined by subregions.
  // This region have subregions that define his structure.
  Region (string name, unsigned position, initializer_list<Region> regions) : 
    name(name), position(position), regions(regions) {}

  size_t CalculateLength() {
    if (this->length > 0) return this->length;

    for (Region sub_region : this->regions)
      this->length += sub_region.CalculateLength();

    return this->length;
  }

  string name;
  size_t position, length = 0;

  list<Region> regions;

  string end_delimiter;
};

} /* PlainTextToDatabase */ 