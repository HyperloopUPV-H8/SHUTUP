#include "Mini-STLIB/Stream.hpp"

vector<Stream*> Stream::streams;
uint8_t Stream::current_id = 0b1000000;
