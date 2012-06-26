#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <sstream>

#define Str(__what) [&]() -> std::string {std::stringstream __tmp; __tmp << __what; return __tmp.str(); }()
#define ExpStr(__exp) Str(#__exp << " = " << __exp << " ")

#endif
