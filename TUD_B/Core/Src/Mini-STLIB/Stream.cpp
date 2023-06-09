#include "Mini-STLIB/Stream.hpp"

vector<Stream*> Stream::streams;
uint8_t Stream::current_id = 0b1000000;
Precision StreamMessage::precision_mode = _8_bits;
map<Precision, unsigned long> StreamMessage::precision_max = {	{_8_bits, 255},
																{_16_bits, 65535},
																{_24_bits, 16777215},
																{_32_bits, 4294967295} };
