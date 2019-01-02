#pragma once
#include <bitset>

namespace ternarylogic {

	namespace bitset {

		namespace priv {

			// primary template
			template<unsigned int k, size_t S> struct ternary_struct {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>&, const std::bitset<S>&) {
					static_assert(k < 256, "Unspecified ternary function");
					return std::bitset<S>();
				}
			};
			template<size_t S> struct ternary_struct<0x00, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>&, const std::bitset<S>&) {
					return std::bitset<S>();
				}
			};
			// code=0x01, function=(A nor (B or C)), lowered=not ((A or (B or C))), set=intel
			template<size_t S> struct ternary_struct<0x01, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A | t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x02, function=(C and (B nor A)), lowered=(C and not ((B or A))), set=intel
			template<size_t S> struct ternary_struct<0x02, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | A;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = C & t1;
					return t2;
				}
			};
			// code=0x03, function=(B nor A), lowered=not ((B or A)), set=intel
			template<size_t S> struct ternary_struct<0x03, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = B | A;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0x04, function=(B and (A nor C)), lowered=(B and not ((A or C))), set=intel
			template<size_t S> struct ternary_struct<0x04, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B & t1;
					return t2;
				}
			};
			// code=0x05, function=(C nor A), lowered=not ((C or A)), set=intel
			template<size_t S> struct ternary_struct<0x05, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C | A;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0x06, function=(not (A) and (B xor C)), lowered=(not (A) and (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x06, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = B ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x07, function=(A nor (B and C)), lowered=not ((A or (B and C))), set=intel
			template<size_t S> struct ternary_struct<0x07, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = A | t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};

			// code=0x08, function=((not (A) and B) and C), lowered=((not (A) and B) and C), set=automat
			template<size_t S> struct ternary_struct<0x08, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S> t2 = t1 & C;
					return t2;
				}
			};
			// code=0x09, function=(A nor (B xor C)), lowered=not ((A or (B xor C))), set=intel
			template<size_t S> struct ternary_struct<0x09, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A | t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x0a, function=(C and not (A)), lowered=(C and not (A)), set=intel
			template<size_t S> struct ternary_struct<0x0a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = C & t0;
					return t1;
				}
			};
			// code=0x0b, function=(not (A) and ((B xor 1) or C)), lowered=(not (A) and ((B xor 1) or C)), set=automat
			template<size_t S> struct ternary_struct<0x0b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = B ^ c1;
					const std::bitset<S> t2 = t1 | C;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x0c, function=(B and not (A)), lowered=(B and not (A)), set=intel
			template<size_t S> struct ternary_struct<0x0c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = B & t0;
					return t1;
				}
			};
			// code=0x0d, function=(not (A) and (B or (C xor 1))), lowered=(not (A) and (B or (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x0d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = C ^ c1;
					const std::bitset<S> t2 = B | t1;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x0e, function=(not (A) and (B or C)), lowered=(not (A) and (B or C)), set=automat
			template<size_t S> struct ternary_struct<0x0e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = B | C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x0f, function=not (A), lowered=not (A), set=intel
			template<size_t S> struct ternary_struct<0x0f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>&) {
					const std::bitset<S> t0 = ~A;
					return t0;
				}
			};
			// code=0x10, function=(A and (B nor C)), lowered=(A and not ((B or C))), set=intel
			template<size_t S> struct ternary_struct<0x10, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A & t1;
					return t2;
				}
			};
			// code=0x11, function=(C nor B), lowered=not ((C or B)), set=intel
			template<size_t S> struct ternary_struct<0x11, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C | B;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0x12, function=(not (B) and (A xor C)), lowered=(not (B) and (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x12, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x13, function=(B nor (A and C)), lowered=not ((B or (A and C))), set=intel
			template<size_t S> struct ternary_struct<0x13, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = B | t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x14, function=(not (C) and (A xor B)), lowered=(not (C) and (A xor B)), set=automat
			template<size_t S> struct ternary_struct<0x14, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = A ^ B;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x15, function=(C nor (B and A)), lowered=not ((C or (B and A))), set=intel
			template<size_t S> struct ternary_struct<0x15, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = C | t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x16, function=(A ? (B nor C) : (B xor C)), lowered=((A and not ((B or C))) or (not (A) and (B xor C))), set=intel
			template<size_t S> struct ternary_struct<0x16, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A & t1;
					const std::bitset<S> t3 = ~A;
					const std::bitset<S> t4 = B ^ C;
					const std::bitset<S> t5 = t3 & t4;
					const std::bitset<S> t6 = t2 | t5;
					return t6;
				}
			};
			// code=0x17, function=not ((A ? (B or C) : (B and C))), lowered=not ((A ? (B or C) : (B and C))), set=intel
			template<size_t S> struct ternary_struct<0x17, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = B & C;
					const std::bitset<S> t2 = (A & t0) | (~A & t1);
					const std::bitset<S> t3 = ~t2;
					return t3;
				}
			};
			// code=0x18, function=((A xor B) and (A xor C)), lowered=((A xor B) and (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x18, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x19, function=not (((B xor C) xor (A and (B and C)))), lowered=not (((B xor C) xor (A and (B and C)))), set=optimized
			template<size_t S> struct ternary_struct<0x19, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = B & C;
					const std::bitset<S> t2 = A & t1;
					const std::bitset<S> t3 = t0 ^ t2;
					const std::bitset<S> t4 = ~t3;
					return t4;
				}
			};
			// code=0x1a, function=(not ((A and B)) and (A xor C)), lowered=(not ((A and B)) and (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x1a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A ^ C;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0x1b, function=(C ? not (A) : not (B)), lowered=((C and not (A)) or (not (C) and not (B))), set=intel
			template<size_t S> struct ternary_struct<0x1b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = C & t0;
					const std::bitset<S> t2 = ~C;
					const std::bitset<S> t3 = ~B;
					const std::bitset<S> t4 = t2 & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x1c, function=(not ((A and C)) and (A xor B)), lowered=(not ((A and C)) and (A xor B)), set=automat
			template<size_t S> struct ternary_struct<0x1c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A ^ B;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0x1d, function=(B ? not (A) : not (C)), lowered=((B and not (A)) or (not (B) and not (C))), set=intel
			template<size_t S> struct ternary_struct<0x1d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = B & t0;
					const std::bitset<S> t2 = ~B;
					const std::bitset<S> t3 = ~C;
					const std::bitset<S> t4 = t2 & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x1e, function=(A xor (B or C)), lowered=(A xor (B or C)), set=intel
			template<size_t S> struct ternary_struct<0x1e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A ^ t0;
					return t1;
				}
			};
			// code=0x1f, function=(A nand (B or C)), lowered=not ((A and (B or C))), set=intel
			template<size_t S> struct ternary_struct<0x1f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A & t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x20, function=((not (B) and A) and C), lowered=((not (B) and A) and C), set=automat
			template<size_t S> struct ternary_struct<0x20, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = t1 & C;
					return t2;
				}
			};
			// code=0x21, function=(B nor (A xor C)), lowered=not ((B or (A xor C))), set=intel
			template<size_t S> struct ternary_struct<0x21, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = B | t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x22, function=(C and not (B)), lowered=(C and not (B)), set=intel
			template<size_t S> struct ternary_struct<0x22, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = C & t0;
					return t1;
				}
			};
			// code=0x23, function=(not (B) and ((A xor 1) or C)), lowered=(not (B) and ((A xor 1) or C)), set=automat
			template<size_t S> struct ternary_struct<0x23, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = A ^ c1;
					const std::bitset<S> t2 = t1 | C;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x24, function=((A xor B) and (B xor C)), lowered=((A xor B) and (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x24, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S> t1 = B ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x25, function=(not ((A and B)) and (A xor (C xor 1))), lowered=(not ((A and B)) and (A xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x25, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = C ^ c1;
					const std::bitset<S> t3 = A ^ t2;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0x26, function=(not ((A and B)) and (B xor C)), lowered=(not ((A and B)) and (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x26, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B ^ C;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0x27, function=(C ? not (B) : not (A)), lowered=((C and not (B)) or (not (C) and not (A))), set=intel
			template<size_t S> struct ternary_struct<0x27, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = C & t0;
					const std::bitset<S> t2 = ~C;
					const std::bitset<S> t3 = ~A;
					const std::bitset<S> t4 = t2 & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x28, function=(C and (B xor A)), lowered=(C and (B xor A)), set=intel
			template<size_t S> struct ternary_struct<0x28, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ A;
					const std::bitset<S> t1 = C & t0;
					return t1;
				}
			};
			// code=0x29, function=(C ? (B xor A) : (B nor A)), lowered=((C and (B xor A)) or (not (C) and not ((B or A)))), set=intel
			template<size_t S> struct ternary_struct<0x29, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ A;
					const std::bitset<S> t1 = C & t0;
					const std::bitset<S> t2 = ~C;
					const std::bitset<S> t3 = B | A;
					const std::bitset<S> t4 = ~t3;
					const std::bitset<S> t5 = t2 & t4;
					const std::bitset<S> t6 = t1 | t5;
					return t6;
				}
			};
			// code=0x2a, function=(C and (B nand A)), lowered=(C and not ((B and A))), set=intel
			template<size_t S> struct ternary_struct<0x2a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = C & t1;
					return t2;
				}
			};
			// code=0x2b, function=(C ? (B nand A) : (B nor A)), lowered=((C and not ((B and A))) or (not (C) and not ((B or A)))), set=intel
			template<size_t S> struct ternary_struct<0x2b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = C & t1;
					const std::bitset<S> t3 = ~C;
					const std::bitset<S> t4 = B | A;
					const std::bitset<S> t5 = ~t4;
					const std::bitset<S> t6 = t3 & t5;
					const std::bitset<S> t7 = t2 | t6;
					return t7;
				}
			};
			// code=0x2c, function=((B or C) and (A xor B)), lowered=((B or C) and (A xor B)), set=automat
			template<size_t S> struct ternary_struct<0x2c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A ^ B;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x2d, function=(A xor (B or not (C))), lowered=(A xor (B or not (C))), set=optimized
			template<size_t S> struct ternary_struct<0x2d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = B | t0;
					const std::bitset<S> t2 = A ^ t1;
					return t2;
				}
			};
			// code=0x2e, function=((B or C) xor (A and B)), lowered=((B or C) xor (A and B)), set=optimized
			template<size_t S> struct ternary_struct<0x2e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A & B;
					const std::bitset<S> t2 = t0 ^ t1;
					return t2;
				}
			};
			// code=0x2f, function=(not (A) or (not (B) and C)), lowered=(not (A) or (not (B) and C)), set=optimized
			template<size_t S> struct ternary_struct<0x2f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = ~B;
					const std::bitset<S> t2 = t1 & C;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x30, function=(A and not (B)), lowered=(A and not (B)), set=intel
			template<size_t S> struct ternary_struct<0x30, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A & t0;
					return t1;
				}
			};
			// code=0x31, function=(not (B) and (A or (C xor 1))), lowered=(not (B) and (A or (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x31, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = C ^ c1;
					const std::bitset<S> t2 = A | t1;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x32, function=(not (B) and (A or C)), lowered=(not (B) and (A or C)), set=automat
			template<size_t S> struct ternary_struct<0x32, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A | C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x33, function=not (B), lowered=not (B), set=intel
			template<size_t S> struct ternary_struct<0x33, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = ~B;
					return t0;
				}
			};
			// code=0x34, function=(not ((B and C)) and (A xor B)), lowered=(not ((B and C)) and (A xor B)), set=automat
			template<size_t S> struct ternary_struct<0x34, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A ^ B;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0x35, function=(A ? not (B) : not (C)), lowered=((A and not (B)) or (not (A) and not (C))), set=intel
			template<size_t S> struct ternary_struct<0x35, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A & t0;
					const std::bitset<S> t2 = ~A;
					const std::bitset<S> t3 = ~C;
					const std::bitset<S> t4 = t2 & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x36, function=(B xor (A or C)), lowered=(B xor (A or C)), set=intel
			template<size_t S> struct ternary_struct<0x36, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = B ^ t0;
					return t1;
				}
			};
			// code=0x37, function=(B nand (A or C)), lowered=not ((B and (A or C))), set=intel
			template<size_t S> struct ternary_struct<0x37, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = B & t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x38, function=((A or C) and (A xor B)), lowered=((A or C) and (A xor B)), set=automat
			template<size_t S> struct ternary_struct<0x38, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = A ^ B;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x39, function=(B xor (A or (C xor 1))), lowered=(B xor (A or (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x39, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t0 = C ^ c1;
					const std::bitset<S> t1 = A | t0;
					const std::bitset<S> t2 = B ^ t1;
					return t2;
				}
			};
			// code=0x3a, function=(A ? not (B) : C), lowered=((A and not (B)) or (not (A) and C)), set=intel
			template<size_t S> struct ternary_struct<0x3a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A & t0;
					const std::bitset<S> t2 = ~A;
					const std::bitset<S> t3 = t2 & C;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0x3b, function=((not (A) and C) or (B xor 1)), lowered=((not (A) and C) or (B xor 1)), set=automat
			template<size_t S> struct ternary_struct<0x3b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = B ^ c1;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0x3c, function=(B xor A), lowered=(B xor A), set=intel
			template<size_t S> struct ternary_struct<0x3c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = B ^ A;
					return t0;
				}
			};
			// code=0x3d, function=((A xor B) or (A nor C)), lowered=((A xor B) or not ((A or C))), set=optimized
			template<size_t S> struct ternary_struct<0x3d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S> t1 = A | C;
					const std::bitset<S> t2 = ~t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x3e, function=((not (A) and C) or (A xor B)), lowered=((not (A) and C) or (A xor B)), set=automat
			template<size_t S> struct ternary_struct<0x3e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S> t2 = A ^ B;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0x3f, function=(B nand A), lowered=not ((B and A)), set=intel
			template<size_t S> struct ternary_struct<0x3f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0x40, function=((not (C) and A) and B), lowered=((not (C) and A) and B), set=automat
			template<size_t S> struct ternary_struct<0x40, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = t1 & B;
					return t2;
				}
			};
			// code=0x41, function=(C nor (B xor A)), lowered=not ((C or (B xor A))), set=intel
			template<size_t S> struct ternary_struct<0x41, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ A;
					const std::bitset<S> t1 = C | t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x42, function=((A xor C) and (B xor C)), lowered=((A xor C) and (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x42, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = B ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x43, function=(not ((A and C)) and (A xor (B xor 1))), lowered=(not ((A and C)) and (A xor (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x43, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = B ^ c1;
					const std::bitset<S> t3 = A ^ t2;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0x44, function=(B and not (C)), lowered=(B and not (C)), set=intel
			template<size_t S> struct ternary_struct<0x44, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = B & t0;
					return t1;
				}
			};
			// code=0x45, function=(not (C) and ((A xor 1) or B)), lowered=(not (C) and ((A xor 1) or B)), set=automat
			template<size_t S> struct ternary_struct<0x45, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = A ^ c1;
					const std::bitset<S> t2 = t1 | B;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x46, function=(not ((A and C)) and (B xor C)), lowered=(not ((A and C)) and (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x46, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B ^ C;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0x47, function=(B ? not (C) : not (A)), lowered=((B and not (C)) or (not (B) and not (A))), set=intel
			template<size_t S> struct ternary_struct<0x47, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = B & t0;
					const std::bitset<S> t2 = ~B;
					const std::bitset<S> t3 = ~A;
					const std::bitset<S> t4 = t2 & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x48, function=(B and (A xor C)), lowered=(B and (A xor C)), set=intel
			template<size_t S> struct ternary_struct<0x48, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = B & t0;
					return t1;
				}
			};
			// code=0x49, function=(B ? (A xor C) : (A nor C)), lowered=((B and (A xor C)) or (not (B) and not ((A or C)))), set=intel
			template<size_t S> struct ternary_struct<0x49, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = B & t0;
					const std::bitset<S> t2 = ~B;
					const std::bitset<S> t3 = A | C;
					const std::bitset<S> t4 = ~t3;
					const std::bitset<S> t5 = t2 & t4;
					const std::bitset<S> t6 = t1 | t5;
					return t6;
				}
			};
			// code=0x4a, function=((B or C) and (A xor C)), lowered=((B or C) and (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x4a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x4b, function=(A xor (not (B) or C)), lowered=(A xor (not (B) or C)), set=optimized
			template<size_t S> struct ternary_struct<0x4b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 | C;
					const std::bitset<S> t2 = A ^ t1;
					return t2;
				}
			};
			// code=0x4c, function=(B and (A nand C)), lowered=(B and not ((A and C))), set=intel
			template<size_t S> struct ternary_struct<0x4c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B & t1;
					return t2;
				}
			};
			// code=0x4d, function=(B ? (A nand C) : (A nor C)), lowered=((B and not ((A and C))) or (not (B) and not ((A or C)))), set=intel
			template<size_t S> struct ternary_struct<0x4d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B & t1;
					const std::bitset<S> t3 = ~B;
					const std::bitset<S> t4 = A | C;
					const std::bitset<S> t5 = ~t4;
					const std::bitset<S> t6 = t3 & t5;
					const std::bitset<S> t7 = t2 | t6;
					return t7;
				}
			};
			// code=0x4e, function=(C ? not (A) : B), lowered=((C and not (A)) or (not (C) and B)), set=intel
			template<size_t S> struct ternary_struct<0x4e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = C & t0;
					const std::bitset<S> t2 = ~C;
					const std::bitset<S> t3 = t2 & B;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0x4f, function=(not (A) or (B and not (C))), lowered=(not (A) or (B and not (C))), set=optimized
			template<size_t S> struct ternary_struct<0x4f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = ~C;
					const std::bitset<S> t2 = B & t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x50, function=(A and not (C)), lowered=(A and not (C)), set=intel
			template<size_t S> struct ternary_struct<0x50, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = A & t0;
					return t1;
				}
			};
			// code=0x51, function=(not (C) and (A or (B xor 1))), lowered=(not (C) and (A or (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x51, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = B ^ c1;
					const std::bitset<S> t2 = A | t1;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x52, function=(not ((B and C)) and (A xor C)), lowered=(not ((B and C)) and (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x52, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A ^ C;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0x53, function=(A ? not (C) : not (B)), lowered=((A and not (C)) or (not (A) and not (B))), set=intel
			template<size_t S> struct ternary_struct<0x53, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = A & t0;
					const std::bitset<S> t2 = ~A;
					const std::bitset<S> t3 = ~B;
					const std::bitset<S> t4 = t2 & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x54, function=(not (C) and (A or B)), lowered=(not (C) and (A or B)), set=automat
			template<size_t S> struct ternary_struct<0x54, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = A | B;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x55, function=not (C), lowered=not (C), set=intel
			template<size_t S> struct ternary_struct<0x55, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					return t0;
				}
			};
			// code=0x56, function=(C xor (B or A)), lowered=(C xor (B or A)), set=intel
			template<size_t S> struct ternary_struct<0x56, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | A;
					const std::bitset<S> t1 = C ^ t0;
					return t1;
				}
			};
			// code=0x57, function=(C nand (B or A)), lowered=not ((C and (B or A))), set=intel
			template<size_t S> struct ternary_struct<0x57, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | A;
					const std::bitset<S> t1 = C & t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x58, function=((A or B) and (A xor C)), lowered=((A or B) and (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x58, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | B;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x59, function=(C xor (A or (B xor 1))), lowered=(C xor (A or (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x59, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t0 = B ^ c1;
					const std::bitset<S> t1 = A | t0;
					const std::bitset<S> t2 = C ^ t1;
					return t2;
				}
			};
			// code=0x5a, function=(C xor A), lowered=(C xor A), set=intel
			template<size_t S> struct ternary_struct<0x5a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C ^ A;
					return t0;
				}
			};
			// code=0x5b, function=((A xor C) or ((A or B) xor 1)), lowered=((A xor C) or ((A or B) xor 1)), set=automat
			template<size_t S> struct ternary_struct<0x5b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = A | B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = t1 ^ c1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x5c, function=(A ? not (C) : B), lowered=((A and not (C)) or (not (A) and B)), set=intel
			template<size_t S> struct ternary_struct<0x5c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = A & t0;
					const std::bitset<S> t2 = ~A;
					const std::bitset<S> t3 = t2 & B;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0x5d, function=(not (C) or (not (A) and B)), lowered=(not (C) or (not (A) and B)), set=optimized
			template<size_t S> struct ternary_struct<0x5d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = ~A;
					const std::bitset<S> t2 = t1 & B;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x5e, function=((not (C) and B) or (A xor C)), lowered=((not (C) and B) or (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x5e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S> t2 = A ^ C;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0x5f, function=(C nand A), lowered=not ((C and A)), set=intel
			template<size_t S> struct ternary_struct<0x5f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C & A;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0x60, function=(A and (B xor C)), lowered=(A and (B xor C)), set=intel
			template<size_t S> struct ternary_struct<0x60, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A & t0;
					return t1;
				}
			};
			// code=0x61, function=(A ? (B xor C) : (B nor C)), lowered=((A and (B xor C)) or (not (A) and not ((B or C)))), set=intel
			template<size_t S> struct ternary_struct<0x61, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A & t0;
					const std::bitset<S> t2 = ~A;
					const std::bitset<S> t3 = B | C;
					const std::bitset<S> t4 = ~t3;
					const std::bitset<S> t5 = t2 & t4;
					const std::bitset<S> t6 = t1 | t5;
					return t6;
				}
			};
			// code=0x62, function=((A or C) and (B xor C)), lowered=((A or C) and (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x62, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = B ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x63, function=(B xor ((A xor 1) or C)), lowered=(B xor ((A xor 1) or C)), set=automat
			template<size_t S> struct ternary_struct<0x63, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t0 = A ^ c1;
					const std::bitset<S> t1 = t0 | C;
					const std::bitset<S> t2 = B ^ t1;
					return t2;
				}
			};
			// code=0x64, function=((A or B) and (B xor C)), lowered=((A or B) and (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x64, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | B;
					const std::bitset<S> t1 = B ^ C;
					const std::bitset<S> t2 = t0 & t1;
					return t2;
				}
			};
			// code=0x65, function=(C xor ((A xor 1) or B)), lowered=(C xor ((A xor 1) or B)), set=automat
			template<size_t S> struct ternary_struct<0x65, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t0 = A ^ c1;
					const std::bitset<S> t1 = t0 | B;
					const std::bitset<S> t2 = C ^ t1;
					return t2;
				}
			};
			// code=0x66, function=(C xor B), lowered=(C xor B), set=intel
			template<size_t S> struct ternary_struct<0x66, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C ^ B;
					return t0;
				}
			};
			// code=0x67, function=((B xor C) or (A nor B)), lowered=((B xor C) or not ((A or B))), set=optimized
			template<size_t S> struct ternary_struct<0x67, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A | B;
					const std::bitset<S> t2 = ~t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x68, function=(A ? (B xor C) : (B and C)), lowered=((A and (B xor C)) or (not (A) and (B and C))), set=intel
			template<size_t S> struct ternary_struct<0x68, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A & t0;
					const std::bitset<S> t2 = ~A;
					const std::bitset<S> t3 = B & C;
					const std::bitset<S> t4 = t2 & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x69, function=(A xnor (B xor C)), lowered=not ((A xor (B xor C))), set=intel
			template<size_t S> struct ternary_struct<0x69, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A ^ t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x6a, function=(C xor (B and A)), lowered=(C xor (B and A)), set=intel
			template<size_t S> struct ternary_struct<0x6a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = C ^ t0;
					return t1;
				}
			};
			// code=0x6b, function=((not (A) and C) or ((A xor 1) xor (B xor C))), lowered=((not (A) and C) or ((A xor 1) xor (B xor C))), set=automat
			template<size_t S> struct ternary_struct<0x6b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = A ^ c1;
					const std::bitset<S> t3 = B ^ C;
					const std::bitset<S> t4 = t2 ^ t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x6c, function=(B xor (A and C)), lowered=(B xor (A and C)), set=intel
			template<size_t S> struct ternary_struct<0x6c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = B ^ t0;
					return t1;
				}
			};
			// code=0x6d, function=((not (A) and B) or ((A xor 1) xor (B xor C))), lowered=((not (A) and B) or ((A xor 1) xor (B xor C))), set=automat
			template<size_t S> struct ternary_struct<0x6d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = A ^ c1;
					const std::bitset<S> t3 = B ^ C;
					const std::bitset<S> t4 = t2 ^ t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x6e, function=((not (A) and B) or (B xor C)), lowered=((not (A) and B) or (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x6e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S> t2 = B ^ C;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0x6f, function=((B xor C) or (A xor 1)), lowered=((B xor C) or (A xor 1)), set=automat
			template<size_t S> struct ternary_struct<0x6f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = A ^ c1;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0x70, function=(A and (B nand C)), lowered=(A and not ((B and C))), set=intel
			template<size_t S> struct ternary_struct<0x70, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A & t1;
					return t2;
				}
			};
			// code=0x71, function=((B nor C) or (A and (B xor C))), lowered=(not ((B or C)) or (A and (B xor C))), set=optimized
			template<size_t S> struct ternary_struct<0x71, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B ^ C;
					const std::bitset<S> t3 = A & t2;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0x72, function=(C ? not (B) : A), lowered=((C and not (B)) or (not (C) and A)), set=intel
			template<size_t S> struct ternary_struct<0x72, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = C & t0;
					const std::bitset<S> t2 = ~C;
					const std::bitset<S> t3 = t2 & A;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0x73, function=(not (B) or (A and not (C))), lowered=(not (B) or (A and not (C))), set=optimized
			template<size_t S> struct ternary_struct<0x73, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = ~C;
					const std::bitset<S> t2 = A & t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x74, function=(B ? not (C) : A), lowered=((B and not (C)) or (not (B) and A)), set=intel
			template<size_t S> struct ternary_struct<0x74, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = B & t0;
					const std::bitset<S> t2 = ~B;
					const std::bitset<S> t3 = t2 & A;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0x75, function=(not (C) or (A and not (B))), lowered=(not (C) or (A and not (B))), set=optimized
			template<size_t S> struct ternary_struct<0x75, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = ~B;
					const std::bitset<S> t2 = A & t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x76, function=((not (B) and A) or (B xor C)), lowered=((not (B) and A) or (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0x76, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = B ^ C;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0x77, function=(C nand B), lowered=not ((C and B)), set=intel
			template<size_t S> struct ternary_struct<0x77, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C & B;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0x78, function=(A xor (B and C)), lowered=(A xor (B and C)), set=intel
			template<size_t S> struct ternary_struct<0x78, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = A ^ t0;
					return t1;
				}
			};
			// code=0x79, function=((not (B) and A) or ((B xor 1) xor (A xor C))), lowered=((not (B) and A) or ((B xor 1) xor (A xor C))), set=automat
			template<size_t S> struct ternary_struct<0x79, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = B ^ c1;
					const std::bitset<S> t3 = A ^ C;
					const std::bitset<S> t4 = t2 ^ t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0x7a, function=((not (B) and A) or (A xor C)), lowered=((not (B) and A) or (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x7a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = A ^ C;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0x7b, function=(not (B) or (A xor C)), lowered=(not (B) or (A xor C)), set=optimized
			template<size_t S> struct ternary_struct<0x7b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0x7c, function=((not (C) and A) or (A xor B)), lowered=((not (C) and A) or (A xor B)), set=automat
			template<size_t S> struct ternary_struct<0x7c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = A ^ B;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0x7d, function=((A xor B) or (C xor 1)), lowered=((A xor B) or (C xor 1)), set=automat
			template<size_t S> struct ternary_struct<0x7d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = C ^ c1;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0x7e, function=((A xor B) or (A xor C)), lowered=((A xor B) or (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0x7e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0x7f, function=(((A and B) and C) xor 1), lowered=(((A and B) and C) xor 1), set=automat
			template<size_t S> struct ternary_struct<0x7f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = t1 ^ c1;
					return t2;
				}
			};
			// code=0x80, function=(A and (B and C)), lowered=(A and (B and C)), set=optimized
			template<size_t S> struct ternary_struct<0x80, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = A & t0;
					return t1;
				}
			};
			// code=0x81, function=(not ((A xor C)) and (A xor (B xor 1))), lowered=(not ((A xor C)) and (A xor (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x81, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = B ^ c1;
					const std::bitset<S> t3 = A ^ t2;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0x82, function=(C and (B xnor A)), lowered=(C and not ((B xor A))), set=intel
			template<size_t S> struct ternary_struct<0x82, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ A;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = C & t1;
					return t2;
				}
			};
			// code=0x83, function=(not ((A xor B)) and ((A xor 1) or C)), lowered=(not ((A xor B)) and ((A xor 1) or C)), set=automat
			template<size_t S> struct ternary_struct<0x83, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = A ^ c1;
					const std::bitset<S> t3 = t2 | C;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0x84, function=(B and (A xnor C)), lowered=(B and not ((A xor C))), set=intel
			template<size_t S> struct ternary_struct<0x84, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B & t1;
					return t2;
				}
			};
			// code=0x85, function=(not ((A xor C)) and (B or (C xor 1))), lowered=(not ((A xor C)) and (B or (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x85, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = C ^ c1;
					const std::bitset<S> t3 = B | t2;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0x86, function=((B or C) and (C xor (A xor B))), lowered=((B or C) and (C xor (A xor B))), set=automat
			template<size_t S> struct ternary_struct<0x86, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A ^ B;
					const std::bitset<S> t2 = C ^ t1;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x87, function=(A xnor (B and C)), lowered=not ((A xor (B and C))), set=intel
			template<size_t S> struct ternary_struct<0x87, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = A ^ t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x88, function=(C and B), lowered=(C and B), set=intel
			template<size_t S> struct ternary_struct<0x88, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C & B;
					return t0;
				}
			};
			// code=0x89, function=(not ((B xor C)) and ((A xor 1) or B)), lowered=(not ((B xor C)) and ((A xor 1) or B)), set=automat
			template<size_t S> struct ternary_struct<0x89, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = A ^ c1;
					const std::bitset<S> t3 = t2 | B;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0x8a, function=(not ((not (B) and A)) and C), lowered=(not ((not (B) and A)) and C), set=automat
			template<size_t S> struct ternary_struct<0x8a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = ~t1;
					const std::bitset<S> t3 = t2 & C;
					return t3;
				}
			};
			// code=0x8b, function=(B ? C : not (A)), lowered=((B and C) or (not (B) and not (A))), set=intel
			template<size_t S> struct ternary_struct<0x8b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = ~B;
					const std::bitset<S> t2 = ~A;
					const std::bitset<S> t3 = t1 & t2;
					const std::bitset<S> t4 = t0 | t3;
					return t4;
				}
			};
			// code=0x8c, function=(not ((not (C) and A)) and B), lowered=(not ((not (C) and A)) and B), set=automat
			template<size_t S> struct ternary_struct<0x8c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = ~t1;
					const std::bitset<S> t3 = t2 & B;
					return t3;
				}
			};
			// code=0x8d, function=(C ? B : not (A)), lowered=((C and B) or (not (C) and not (A))), set=intel
			template<size_t S> struct ternary_struct<0x8d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C & B;
					const std::bitset<S> t1 = ~C;
					const std::bitset<S> t2 = ~A;
					const std::bitset<S> t3 = t1 & t2;
					const std::bitset<S> t4 = t0 | t3;
					return t4;
				}
			};
			// code=0x8e, function=((B and C) or (not (A) and (B xor C))), lowered=((B and C) or (not (A) and (B xor C))), set=optimized
			template<size_t S> struct ternary_struct<0x8e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = ~A;
					const std::bitset<S> t2 = B ^ C;
					const std::bitset<S> t3 = t1 & t2;
					const std::bitset<S> t4 = t0 | t3;
					return t4;
				}
			};
			// code=0x8f, function=(not (A) or (B and C)), lowered=(not (A) or (B and C)), set=optimized
			template<size_t S> struct ternary_struct<0x8f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = B & C;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0x90, function=(A and (B xnor C)), lowered=(A and not ((B xor C))), set=intel
			template<size_t S> struct ternary_struct<0x90, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A & t1;
					return t2;
				}
			};
			// code=0x91, function=(not ((B xor C)) and (A or (B xor 1))), lowered=(not ((B xor C)) and (A or (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x91, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = B ^ c1;
					const std::bitset<S> t3 = A | t2;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0x92, function=((A or C) and (C xor (A xor B))), lowered=((A or C) and (C xor (A xor B))), set=automat
			template<size_t S> struct ternary_struct<0x92, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = A ^ B;
					const std::bitset<S> t2 = C ^ t1;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x93, function=(B xnor (A and C)), lowered=not ((B xor (A and C))), set=intel
			template<size_t S> struct ternary_struct<0x93, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = B ^ t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x94, function=((A or B) and (B xor (A xor C))), lowered=((A or B) and (B xor (A xor C))), set=automat
			template<size_t S> struct ternary_struct<0x94, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | B;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = B ^ t1;
					const std::bitset<S> t3 = t0 & t2;
					return t3;
				}
			};
			// code=0x95, function=(C xnor (B and A)), lowered=not ((C xor (B and A))), set=intel
			template<size_t S> struct ternary_struct<0x95, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = C ^ t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0x96, function=(A xor (B xor C)), lowered=(A xor (B xor C)), set=intel
			template<size_t S> struct ternary_struct<0x96, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A ^ t0;
					return t1;
				}
			};
			// code=0x97, function=(A ? (B xnor C) : (B nand C)), lowered=((A and not ((B xor C))) or (not (A) and not ((B and C)))), set=intel
			template<size_t S> struct ternary_struct<0x97, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A & t1;
					const std::bitset<S> t3 = ~A;
					const std::bitset<S> t4 = B & C;
					const std::bitset<S> t5 = ~t4;
					const std::bitset<S> t6 = t3 & t5;
					const std::bitset<S> t7 = t2 | t6;
					return t7;
				}
			};
			// code=0x98, function=(not ((B xor C)) and (A or B)), lowered=(not ((B xor C)) and (A or B)), set=automat
			template<size_t S> struct ternary_struct<0x98, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A | B;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0x99, function=(C xnor B), lowered=not ((C xor B)), set=intel
			template<size_t S> struct ternary_struct<0x99, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C ^ B;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0x9a, function=((not (B) and A) xor C), lowered=((not (B) and A) xor C), set=automat
			template<size_t S> struct ternary_struct<0x9a, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = t1 ^ C;
					return t2;
				}
			};
			// code=0x9b, function=((not (A) and C) or (B xor (C xor 1))), lowered=((not (A) and C) or (B xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x9b, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = C ^ c1;
					const std::bitset<S> t3 = B ^ t2;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0x9c, function=((not (C) and A) xor B), lowered=((not (C) and A) xor B), set=automat
			template<size_t S> struct ternary_struct<0x9c, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = t1 ^ B;
					return t2;
				}
			};
			// code=0x9d, function=((not (A) and B) or (B xor (C xor 1))), lowered=((not (A) and B) or (B xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0x9d, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = C ^ c1;
					const std::bitset<S> t3 = B ^ t2;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0x9e, function=((B and C) or (C xor (A xor B))), lowered=((B and C) or (C xor (A xor B))), set=automat
			template<size_t S> struct ternary_struct<0x9e, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = A ^ B;
					const std::bitset<S> t2 = C ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0x9f, function=(A nand (B xor C)), lowered=not ((A and (B xor C))), set=intel
			template<size_t S> struct ternary_struct<0x9f, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A & t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0xa0, function=(C and A), lowered=(C and A), set=intel
			template<size_t S> struct ternary_struct<0xa0, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C & A;
					return t0;
				}
			};
			// code=0xa1, function=(not ((A xor C)) and (A or (B xor 1))), lowered=(not ((A xor C)) and (A or (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xa1, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = B ^ c1;
					const std::bitset<S> t3 = A | t2;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0xa2, function=(C and (A or not (B))), lowered=(C and (A or not (B))), set=optimized
			template<size_t S> struct ternary_struct<0xa2, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A | t0;
					const std::bitset<S> t2 = C & t1;
					return t2;
				}
			};
			// code=0xa3, function=(A ? C : not (B)), lowered=((A and C) or (not (A) and not (B))), set=intel
			template<size_t S> struct ternary_struct<0xa3, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = ~A;
					const std::bitset<S> t2 = ~B;
					const std::bitset<S> t3 = t1 & t2;
					const std::bitset<S> t4 = t0 | t3;
					return t4;
				}
			};
			// code=0xa4, function=(not ((A xor C)) and (A or B)), lowered=(not ((A xor C)) and (A or B)), set=automat
			template<size_t S> struct ternary_struct<0xa4, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A | B;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0xa5, function=(C xnor A), lowered=not ((C xor A)), set=intel
			template<size_t S> struct ternary_struct<0xa5, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C ^ A;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0xa6, function=((not (A) and B) xor C), lowered=((not (A) and B) xor C), set=automat
			template<size_t S> struct ternary_struct<0xa6, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S> t2 = t1 ^ C;
					return t2;
				}
			};
			// code=0xa7, function=((not (B) and C) or (A xor (C xor 1))), lowered=((not (B) and C) or (A xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xa7, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = C ^ c1;
					const std::bitset<S> t3 = A ^ t2;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0xa8, function=(C and (A or B)), lowered=(C and (A or B)), set=intel
			template<size_t S> struct ternary_struct<0xa8, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | B;
					const std::bitset<S> t1 = C & t0;
					return t1;
				}
			};
			// code=0xa9, function=(C xnor (B or A)), lowered=not ((C xor (B or A))), set=intel
			template<size_t S> struct ternary_struct<0xa9, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | A;
					const std::bitset<S> t1 = C ^ t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0xaa, function=C, lowered=C, set=intel
			template<size_t S> struct ternary_struct<0xaa, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>&, const std::bitset<S>& C) {
					return C;
				}
			};
			// code=0xab, function=(C or (B nor A)), lowered=(C or not ((B or A))), set=intel
			template<size_t S> struct ternary_struct<0xab, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | A;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = C | t1;
					return t2;
				}
			};
			// code=0xac, function=(A ? C : B), lowered=((A and C) or (not (A) and B)), set=intel
			template<size_t S> struct ternary_struct<0xac, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = ~A;
					const std::bitset<S> t2 = t1 & B;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xad, function=((B and C) or (A xor (C xor 1))), lowered=((B and C) or (A xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xad, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = C ^ c1;
					const std::bitset<S> t2 = A ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xae, function=((not (A) and B) or C), lowered=((not (A) and B) or C), set=automat
			template<size_t S> struct ternary_struct<0xae, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S> t2 = t1 | C;
					return t2;
				}
			};
			// code=0xaf, function=(C or not (A)), lowered=(C or not (A)), set=intel
			template<size_t S> struct ternary_struct<0xaf, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = C | t0;
					return t1;
				}
			};
			// code=0xb0, function=(not ((not (C) and B)) and A), lowered=(not ((not (C) and B)) and A), set=automat
			template<size_t S> struct ternary_struct<0xb0, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S> t2 = ~t1;
					const std::bitset<S> t3 = t2 & A;
					return t3;
				}
			};
			// code=0xb1, function=(C ? A : not (B)), lowered=((C and A) or (not (C) and not (B))), set=intel
			template<size_t S> struct ternary_struct<0xb1, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C & A;
					const std::bitset<S> t1 = ~C;
					const std::bitset<S> t2 = ~B;
					const std::bitset<S> t3 = t1 & t2;
					const std::bitset<S> t4 = t0 | t3;
					return t4;
				}
			};
			// code=0xb2, function=(B ? (A and C) : (A or C)), lowered=((B and (A and C)) or (not (B) and (A or C))), set=intel
			template<size_t S> struct ternary_struct<0xb2, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = B & t0;
					const std::bitset<S> t2 = ~B;
					const std::bitset<S> t3 = A | C;
					const std::bitset<S> t4 = t2 & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0xb3, function=(not (B) or (A and C)), lowered=(not (B) or (A and C)), set=optimized
			template<size_t S> struct ternary_struct<0xb3, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A & C;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0xb4, function=((not (C) and B) xor A), lowered=((not (C) and B) xor A), set=automat
			template<size_t S> struct ternary_struct<0xb4, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S> t2 = t1 ^ A;
					return t2;
				}
			};
			// code=0xb5, function=((not (B) and A) or (A xor (C xor 1))), lowered=((not (B) and A) or (A xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xb5, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = C ^ c1;
					const std::bitset<S> t3 = A ^ t2;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0xb6, function=((A and C) or (C xor (A xor B))), lowered=((A and C) or (C xor (A xor B))), set=automat
			template<size_t S> struct ternary_struct<0xb6, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = A ^ B;
					const std::bitset<S> t2 = C ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xb7, function=(B nand (A xor C)), lowered=not ((B and (A xor C))), set=intel
			template<size_t S> struct ternary_struct<0xb7, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = B & t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0xb8, function=(B ? C : A), lowered=((B and C) or (not (B) and A)), set=intel
			template<size_t S> struct ternary_struct<0xb8, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = ~B;
					const std::bitset<S> t2 = t1 & A;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xb9, function=((A and C) or (B xor (C xor 1))), lowered=((A and C) or (B xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xb9, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = C ^ c1;
					const std::bitset<S> t2 = B ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xba, function=((not (B) and A) or C), lowered=((not (B) and A) or C), set=automat
			template<size_t S> struct ternary_struct<0xba, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = t1 | C;
					return t2;
				}
			};
			// code=0xbb, function=(C or not (B)), lowered=(C or not (B)), set=intel
			template<size_t S> struct ternary_struct<0xbb, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = C | t0;
					return t1;
				}
			};
			// code=0xbc, function=((A and C) or (A xor B)), lowered=((A and C) or (A xor B)), set=automat
			template<size_t S> struct ternary_struct<0xbc, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = A ^ B;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0xbd, function=((A xor B) or (A xor (C xor 1))), lowered=((A xor B) or (A xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xbd, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = C ^ c1;
					const std::bitset<S> t2 = A ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xbe, function=(C or (B xor A)), lowered=(C or (B xor A)), set=intel
			template<size_t S> struct ternary_struct<0xbe, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ A;
					const std::bitset<S> t1 = C | t0;
					return t1;
				}
			};
			// code=0xbf, function=(C or (B nand A)), lowered=(C or not ((B and A))), set=intel
			template<size_t S> struct ternary_struct<0xbf, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = C | t1;
					return t2;
				}
			};
			// code=0xc0, function=(B and A), lowered=(B and A), set=intel
			template<size_t S> struct ternary_struct<0xc0, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = B & A;
					return t0;
				}
			};
			// code=0xc1, function=(not ((A xor B)) and (A or (C xor 1))), lowered=(not ((A xor B)) and (A or (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xc1, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = C ^ c1;
					const std::bitset<S> t3 = A | t2;
					const std::bitset<S> t4 = t1 & t3;
					return t4;
				}
			};
			// code=0xc2, function=(not ((A xor B)) and (A or C)), lowered=(not ((A xor B)) and (A or C)), set=automat
			template<size_t S> struct ternary_struct<0xc2, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ B;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A | C;
					const std::bitset<S> t3 = t1 & t2;
					return t3;
				}
			};
			// code=0xc3, function=(B xnor A), lowered=not ((B xor A)), set=intel
			template<size_t S> struct ternary_struct<0xc3, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = B ^ A;
					const std::bitset<S> t1 = ~t0;
					return t1;
				}
			};
			// code=0xc4, function=(not ((not (A) and C)) and B), lowered=(not ((not (A) and C)) and B), set=automat
			template<size_t S> struct ternary_struct<0xc4, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S> t2 = ~t1;
					const std::bitset<S> t3 = t2 & B;
					return t3;
				}
			};
			// code=0xc5, function=(A ? B : not (C)), lowered=((A and B) or (not (A) and not (C))), set=intel
			template<size_t S> struct ternary_struct<0xc5, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = ~A;
					const std::bitset<S> t2 = ~C;
					const std::bitset<S> t3 = t1 & t2;
					const std::bitset<S> t4 = t0 | t3;
					return t4;
				}
			};
			// code=0xc6, function=((not (A) and C) xor B), lowered=((not (A) and C) xor B), set=automat
			template<size_t S> struct ternary_struct<0xc6, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S> t2 = t1 ^ B;
					return t2;
				}
			};
			// code=0xc7, function=((not (C) and B) or (A xor (B xor 1))), lowered=((not (C) and B) or (A xor (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xc7, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = B ^ c1;
					const std::bitset<S> t3 = A ^ t2;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0xc8, function=(B and (A or C)), lowered=(B and (A or C)), set=intel
			template<size_t S> struct ternary_struct<0xc8, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = B & t0;
					return t1;
				}
			};
			// code=0xc9, function=(B xnor (A or C)), lowered=not ((B xor (A or C))), set=intel
			template<size_t S> struct ternary_struct<0xc9, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = B ^ t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0xca, function=(A ? B : C), lowered=((A and B) or (not (A) and C)), set=intel
			template<size_t S> struct ternary_struct<0xca, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = ~A;
					const std::bitset<S> t2 = t1 & C;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xcb, function=((B and C) or (A xor (B xor 1))), lowered=((B and C) or (A xor (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xcb, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = B ^ c1;
					const std::bitset<S> t2 = A ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xcc, function=B, lowered=B, set=intel
			template<size_t S> struct ternary_struct<0xcc, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>&) {
					return B;
				}
			};
			// code=0xcd, function=(B or (A nor C)), lowered=(B or not ((A or C))), set=intel
			template<size_t S> struct ternary_struct<0xcd, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A | C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B | t1;
					return t2;
				}
			};
			// code=0xce, function=((not (A) and C) or B), lowered=((not (A) and C) or B), set=automat
			template<size_t S> struct ternary_struct<0xce, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S> t2 = t1 | B;
					return t2;
				}
			};
			// code=0xcf, function=(B or not (A)), lowered=(B or not (A)), set=intel
			template<size_t S> struct ternary_struct<0xcf, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = B | t0;
					return t1;
				}
			};
			// code=0xd0, function=(A and (B or not (C))), lowered=(A and (B or not (C))), set=optimized
			template<size_t S> struct ternary_struct<0xd0, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = B | t0;
					const std::bitset<S> t2 = A & t1;
					return t2;
				}
			};
			// code=0xd1, function=((B nor C) or (A and B)), lowered=(not ((B or C)) or (A and B)), set=optimized
			template<size_t S> struct ternary_struct<0xd1, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A & B;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0xd2, function=((not (B) and C) xor A), lowered=((not (B) and C) xor A), set=automat
			template<size_t S> struct ternary_struct<0xd2, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S> t2 = t1 ^ A;
					return t2;
				}
			};
			// code=0xd3, function=((not (C) and A) or (A xor (B xor 1))), lowered=((not (C) and A) or (A xor (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xd3, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t2 = B ^ c1;
					const std::bitset<S> t3 = A ^ t2;
					const std::bitset<S> t4 = t1 | t3;
					return t4;
				}
			};
			// code=0xd4, function=((B and not (C)) or (A and (B xnor C))), lowered=((B and not (C)) or (A and not ((B xor C)))), set=optimized
			template<size_t S> struct ternary_struct<0xd4, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = B & t0;
					const std::bitset<S> t2 = B ^ C;
					const std::bitset<S> t3 = ~t2;
					const std::bitset<S> t4 = A & t3;
					const std::bitset<S> t5 = t1 | t4;
					return t5;
				}
			};
			// code=0xd5, function=(not (C) or (A and B)), lowered=(not (C) or (A and B)), set=optimized
			template<size_t S> struct ternary_struct<0xd5, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = A & B;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0xd6, function=((A and B) or (B xor (A xor C))), lowered=((A and B) or (B xor (A xor C))), set=automat
			template<size_t S> struct ternary_struct<0xd6, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = B ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xd7, function=(C nand (B xor A)), lowered=not ((C and (B xor A))), set=intel
			template<size_t S> struct ternary_struct<0xd7, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ A;
					const std::bitset<S> t1 = C & t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0xd8, function=(C ? B : A), lowered=((C and B) or (not (C) and A)), set=intel
			template<size_t S> struct ternary_struct<0xd8, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C & B;
					const std::bitset<S> t1 = ~C;
					const std::bitset<S> t2 = t1 & A;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xd9, function=((B xnor C) or (A and B)), lowered=(not ((B xor C)) or (A and B)), set=optimized
			template<size_t S> struct ternary_struct<0xd9, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A & B;
					const std::bitset<S> t3 = t1 | t2;
					return t3;
				}
			};
			// code=0xda, function=((A and B) or (A xor C)), lowered=((A and B) or (A xor C)), set=automat
			template<size_t S> struct ternary_struct<0xda, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = A ^ C;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0xdb, function=((A xor C) or (A xor (B xor 1))), lowered=((A xor C) or (A xor (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xdb, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = B ^ c1;
					const std::bitset<S> t2 = A ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xdc, function=((not (C) and A) or B), lowered=((not (C) and A) or B), set=automat
			template<size_t S> struct ternary_struct<0xdc, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & A;
					const std::bitset<S> t2 = t1 | B;
					return t2;
				}
			};
			// code=0xdd, function=(B or not (C)), lowered=(B or not (C)), set=intel
			template<size_t S> struct ternary_struct<0xdd, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = B | t0;
					return t1;
				}
			};
			// code=0xde, function=(B or (A xor C)), lowered=(B or (A xor C)), set=intel
			template<size_t S> struct ternary_struct<0xde, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = B | t0;
					return t1;
				}
			};
			// code=0xdf, function=(B or (A nand C)), lowered=(B or not ((A and C))), set=intel
			template<size_t S> struct ternary_struct<0xdf, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B | t1;
					return t2;
				}
			};
			// code=0xe0, function=(A and (B or C)), lowered=(A and (B or C)), set=intel
			template<size_t S> struct ternary_struct<0xe0, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A & t0;
					return t1;
				}
			};
			// code=0xe1, function=(A xnor (B or C)), lowered=not ((A xor (B or C))), set=intel
			template<size_t S> struct ternary_struct<0xe1, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A ^ t0;
					const std::bitset<S> t2 = ~t1;
					return t2;
				}
			};
			// code=0xe2, function=(B ? A : C), lowered=((B and A) or (not (B) and C)), set=intel
			template<size_t S> struct ternary_struct<0xe2, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = ~B;
					const std::bitset<S> t2 = t1 & C;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xe3, function=((A and C) or (A xor (B xor 1))), lowered=((A and C) or (A xor (B xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xe3, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = B ^ c1;
					const std::bitset<S> t2 = A ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xe4, function=(C ? A : B), lowered=((C and A) or (not (C) and B)), set=intel
			template<size_t S> struct ternary_struct<0xe4, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C & A;
					const std::bitset<S> t1 = ~C;
					const std::bitset<S> t2 = t1 & B;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xe5, function=((A and B) or (A xor (C xor 1))), lowered=((A and B) or (A xor (C xor 1))), set=automat
			template<size_t S> struct ternary_struct<0xe5, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S>& c1 = std::bitset<S>().set();
					const std::bitset<S> t1 = C ^ c1;
					const std::bitset<S> t2 = A ^ t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xe6, function=((A and B) or (B xor C)), lowered=((A and B) or (B xor C)), set=automat
			template<size_t S> struct ternary_struct<0xe6, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & B;
					const std::bitset<S> t1 = B ^ C;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0xe7, function=((B xor C) or (not (A) xor C)), lowered=((B xor C) or (not (A) xor C)), set=optimized
			template<size_t S> struct ternary_struct<0xe7, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = ~A;
					const std::bitset<S> t2 = t1 ^ C;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xe8, function=((B and C) or (A and (B xor C))), lowered=((B and C) or (A and (B xor C))), set=optimized
			template<size_t S> struct ternary_struct<0xe8, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = B ^ C;
					const std::bitset<S> t2 = A & t1;
					const std::bitset<S> t3 = t0 | t2;
					return t3;
				}
			};
			// code=0xe9, function=((not (A) xor (B xor C)) or (A and B)), lowered=((not (A) xor (B xor C)) or (A and B)), set=optimized
			template<size_t S> struct ternary_struct<0xe9, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = B ^ C;
					const std::bitset<S> t2 = t0 ^ t1;
					const std::bitset<S> t3 = A & B;
					const std::bitset<S> t4 = t2 | t3;
					return t4;
				}
			};
			// code=0xea, function=(C or (B and A)), lowered=(C or (B and A)), set=intel
			template<size_t S> struct ternary_struct<0xea, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & A;
					const std::bitset<S> t1 = C | t0;
					return t1;
				}
			};
			// code=0xeb, function=(C or (B xnor A)), lowered=(C or not ((B xor A))), set=intel
			template<size_t S> struct ternary_struct<0xeb, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ A;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = C | t1;
					return t2;
				}
			};
			// code=0xec, function=(B or (A and C)), lowered=(B or (A and C)), set=intel
			template<size_t S> struct ternary_struct<0xec, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A & C;
					const std::bitset<S> t1 = B | t0;
					return t1;
				}
			};
			// code=0xed, function=(B or (A xnor C)), lowered=(B or not ((A xor C))), set=intel
			template<size_t S> struct ternary_struct<0xed, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = A ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = B | t1;
					return t2;
				}
			};
			// code=0xee, function=(C or B), lowered=(C or B), set=intel
			template<size_t S> struct ternary_struct<0xee, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C | B;
					return t0;
				}
			};
			// code=0xef, function=(not (A) or (B or C)), lowered=(not (A) or (B or C)), set=optimized
			template<size_t S> struct ternary_struct<0xef, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~A;
					const std::bitset<S> t1 = B | C;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0xf0, function=A, lowered=A, set=intel
			template<size_t S> struct ternary_struct<0xf0, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>&) {
					return A;
				}
			};
			// code=0xf1, function=(A or (B nor C)), lowered=(A or not ((B or C))), set=intel
			template<size_t S> struct ternary_struct<0xf1, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A | t1;
					return t2;
				}
			};
			// code=0xf2, function=((not (B) and C) or A), lowered=((not (B) and C) or A), set=automat
			template<size_t S> struct ternary_struct<0xf2, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 & C;
					const std::bitset<S> t2 = t1 | A;
					return t2;
				}
			};
			// code=0xf3, function=(A or not (B)), lowered=(A or not (B)), set=intel
			template<size_t S> struct ternary_struct<0xf3, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = A | t0;
					return t1;
				}
			};
			// code=0xf4, function=((not (C) and B) or A), lowered=((not (C) and B) or A), set=automat
			template<size_t S> struct ternary_struct<0xf4, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = t0 & B;
					const std::bitset<S> t2 = t1 | A;
					return t2;
				}
			};
			// code=0xf5, function=(A or not (C)), lowered=(A or not (C)), set=intel
			template<size_t S> struct ternary_struct<0xf5, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = A | t0;
					return t1;
				}
			};
			// code=0xf6, function=(A or (B xor C)), lowered=(A or (B xor C)), set=intel
			template<size_t S> struct ternary_struct<0xf6, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = A | t0;
					return t1;
				}
			};
			// code=0xf7, function=(A or (B nand C)), lowered=(A or not ((B and C))), set=intel
			template<size_t S> struct ternary_struct<0xf7, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A | t1;
					return t2;
				}
			};
			// code=0xf8, function=(A or (B and C)), lowered=(A or (B and C)), set=intel
			template<size_t S> struct ternary_struct<0xf8, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B & C;
					const std::bitset<S> t1 = A | t0;
					return t1;
				}
			};
			// code=0xf9, function=(A or (B xnor C)), lowered=(A or not ((B xor C))), set=intel
			template<size_t S> struct ternary_struct<0xf9, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B ^ C;
					const std::bitset<S> t1 = ~t0;
					const std::bitset<S> t2 = A | t1;
					return t2;
				}
			};
			// code=0xfa, function=(C or A), lowered=(C or A), set=intel
			template<size_t S> struct ternary_struct<0xfa, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>&, const std::bitset<S>& C) {
					const std::bitset<S> t0 = C | A;
					return t0;
				}
			};
			// code=0xfb, function=(A or (not (B) or C)), lowered=(A or (not (B) or C)), set=optimized
			template<size_t S> struct ternary_struct<0xfb, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~B;
					const std::bitset<S> t1 = t0 | C;
					const std::bitset<S> t2 = A | t1;
					return t2;
				}
			};
			// code=0xfc, function=(B or A), lowered=(B or A), set=intel
			template<size_t S> struct ternary_struct<0xfc, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>&) {
					const std::bitset<S> t0 = B | A;
					return t0;
				}
			};
			// code=0xfd, function=(not (C) or (A or B)), lowered=(not (C) or (A or B)), set=optimized
			template<size_t S> struct ternary_struct<0xfd, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = ~C;
					const std::bitset<S> t1 = A | B;
					const std::bitset<S> t2 = t0 | t1;
					return t2;
				}
			};
			// code=0xfe, function=(A or (B or C)), lowered=(A or (B or C)), set=intel
			template<size_t S> struct ternary_struct<0xfe, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
					const std::bitset<S> t0 = B | C;
					const std::bitset<S> t1 = A | t0;
					return t1;
				}
			};
			// code=0xff, function=1, lowered=1, set=intel
			template<size_t S> struct ternary_struct<0xff, S> {
				static constexpr std::bitset<S> ternary(const std::bitset<S>&, const std::bitset<S>&, const std::bitset<S>&) {
					const std::bitset<S> c1 = std::bitset<S>().set();
					return c1;
				}
			};
		}

		template<unsigned int k, size_t S> constexpr std::bitset<S> ternary(const std::bitset<S>& A, const std::bitset<S>& B, const std::bitset<S>& C) {
			return priv::ternary_struct<k, S>::ternary(A, B, C);
		}
	} // namespace sse
}// namespace ternarylogic
// eof
