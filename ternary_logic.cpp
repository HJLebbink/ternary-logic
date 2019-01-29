#pragma once
#include <string>
#include <chrono>
#include <sstream>
#include <iostream>		// for cout
#include <bitset>
#include <algorithm>	// for min
#include <iomanip>      // std::setprecision

#include <intrin.h>

#define rdtsc __rdtsc

#include "ternary_x86_32.cpp"
#include "ternary_x86_64.cpp"
#include "ternary_sse.cpp"
#include "ternary_avx2.cpp"
#include "ternary_avx512.cpp"
#include "ternary_bitset.cpp"


/*
from Intel® Xeon® Scalable Processor Instruction Throughput and Latency 

 vpternlogd xmm1{ k1 }, xmm2, xmm3, 1	1	0.33
 vpternlogd ymm1{ k1 }, ymm2, ymm3, 1	1	0.33
 vpternlogd zmm1{ k1 }, zmm2, zmm3, 1	1	0.5

 vpxord xmm1{k1}, xmm2, xmm3	1	0.33
 vpxord ymm1{k1}, ymm2, ymm3	1	0.33
 vpxord zmm1{k1}, zmm2, zmm3	1	0.5

 from https://github.com/InstLatx64/InstLatx64/blob/master/GenuineIntel0050654_SkylakeX_InstLatX64.txt

 3819 AVX512VL        :VPTERNLOGD xmm, xmm, xmm, imm8        L:   0.30ns=  1.0c  T:   0.15ns=  0.48c
 3820 AVX512VL        :VPTERNLOGD ymm, ymm, ymm, imm8        L:   0.30ns=  1.0c  T:   0.15ns=  0.48c
 3821 AVX512F         :VPTERNLOGD zmm, zmm, zmm, imm8        L:   0.30ns=  1.0c  T:   0.15ns=  0.50c

 3523 AVX512VL        :{EVEX} VPXORD xmm1, xmm1, xmm2        L:   0.30ns=  1.0c  T:   0.11ns=  0.37c
 3525 AVX512VL        :{EVEX} VPXORD ymm1, ymm1, ymm2        L:   0.30ns=  1.0c  T:   0.11ns=  0.37c
 3527 AVX512F         :VPXORD zmm1, zmm1, zmm2               L:   0.30ns=  1.0c  T:   0.15ns=  0.50c

 from http://users.atw.hu/instlatx64/AVX512_SKX_PortAssign_v102_PUB.ods
 
 3819	AVX512VL	VPTERNLOGD xmm, xmm, xmm, imm8	1	0.48	1	0.33	1	P015
 3820	AVX512VL	VPTERNLOGD ymm, ymm, ymm, imm8	1	0.48	1	0.33	1	P015
 3821	AVX512F	VPTERNLOGD zmm, zmm, zmm, imm8	1	0.5	1	0.5	1	P05

 3523	AVX512VL	{EVEX} VPXORD xmm1, xmm1, xmm2	1	0.37	1	0.33	1	P015	Zeroing idiom for same source registers
 3525	AVX512VL	{EVEX} VPXORD ymm1, ymm1, ymm2	1	0.37	1	0.33	1	P015	Zeroing idiom for same source registers
 3527	AVX512F	VPXORD zmm1, zmm1, zmm2	1	0.5	1	0.5	1	P05	Zeroing idiom for same source registers


 for execution port assignment see: https://en.wikichip.org/wiki/intel/microarchitectures/skylake_(server)
 */

namespace ternarylogic
{
	using bf_type = unsigned long long;

	namespace priv
	{
		#pragma region Ternary Intern


		template<bf_type K, size_t S>
		__forceinline constexpr std::bitset<S> ternary_intern(const std::bitset<S>& a, const std::bitset<S>& b, const std::bitset<S>& c)
		{
			return ternarylogic::bitset::ternary<K, S>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr uint32_t ternary_intern(const uint32_t a, const uint32_t b, const uint32_t c)
		{
			return ternarylogic::x86_32::ternary<K>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr uint64_t ternary_intern(const uint64_t a, const uint64_t b, const uint64_t c)
		{
			return ternarylogic::x86_64::ternary<K>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr __m128i ternary_intern(const __m128i a, const __m128i b, const __m128i c)
		{
			return ternarylogic::sse::ternary<K>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr __m256i ternary_intern(const __m256i a, const __m256i b, const __m256i c)
		{
			return ternarylogic::avx2::ternary<K>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr __m512i ternary_intern(const __m512i a, const __m512i b, const __m512i c)
		{
			return ternarylogic::avx512raw::ternary<K>(a, b, c); 
		}
		#pragma endregion

		#pragma region Ternary Intern No Vpternlog
		template<bf_type K>
		__forceinline constexpr uint32_t ternary_intern_no_vpternlog(const uint32_t a, const uint32_t b, const uint32_t c)
		{
			return ternarylogic::x86_32::ternary<K>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr uint64_t ternary_intern_no_vpternlog(const uint64_t a, const uint64_t b, const uint64_t c)
		{
			return ternarylogic::x86_64::ternary<K>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr __m128i ternary_intern_no_vpternlog(const __m128i a, const __m128i b, const __m128i c)
		{
			return ternarylogic::sse::ternary<K>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr __m256i ternary_intern_no_vpternlog(const __m256i a, const __m256i b, const __m256i c)
		{
			return ternarylogic::avx2::ternary<K>(a, b, c);
		}

		template<bf_type K>
		__forceinline constexpr __m512i ternary_intern_no_vpternlog(const __m512i a, const __m512i b, const __m512i c)
		{
			return ternarylogic::avx512::ternary<K>(a, b, c);
		}
		#pragma endregion

		template<typename T>
		inline constexpr T ternary_not_reduced(const T& a, const T& b, const T& c, const bf_type k)
		{
			switch (k)
			{
				case 0: return ternary_intern<0>(a, b, c);
				case 1: return ternary_intern<1>(a, b, c);
				case 2: return ternary_intern<2>(a, b, c);
				case 3: return ternary_intern<3>(a, b, c);
				case 4: return ternary_intern<4>(a, b, c);
				case 5: return ternary_intern<5>(a, b, c);
				case 6: return ternary_intern<6>(a, b, c);
				case 7: return ternary_intern<7>(a, b, c);
				case 8: return ternary_intern<8>(a, b, c);
				case 9: return ternary_intern<9>(a, b, c);

				case 10: return ternary_intern<10>(a, b, c);
				case 11: return ternary_intern<11>(a, b, c);
				case 12: return ternary_intern<12>(a, b, c);
				case 13: return ternary_intern<13>(a, b, c);
				case 14: return ternary_intern<14>(a, b, c);
				case 15: return ternary_intern<15>(a, b, c);
				case 16: return ternary_intern<16>(a, b, c);
				case 17: return ternary_intern<17>(a, b, c);
				case 18: return ternary_intern<18>(a, b, c);
				case 19: return ternary_intern<19>(a, b, c);

				case 20: return ternary_intern<20>(a, b, c);
				case 21: return ternary_intern<21>(a, b, c);
				case 22: return ternary_intern<22>(a, b, c);
				case 23: return ternary_intern<23>(a, b, c);
				case 24: return ternary_intern<24>(a, b, c);
				case 25: return ternary_intern<25>(a, b, c);
				case 26: return ternary_intern<26>(a, b, c);
				case 27: return ternary_intern<27>(a, b, c);
				case 28: return ternary_intern<28>(a, b, c);
				case 29: return ternary_intern<29>(a, b, c);

				case 30: return ternary_intern<30>(a, b, c);
				case 31: return ternary_intern<31>(a, b, c);
				case 32: return ternary_intern<32>(a, b, c);
				case 33: return ternary_intern<33>(a, b, c);
				case 34: return ternary_intern<34>(a, b, c);
				case 35: return ternary_intern<35>(a, b, c);
				case 36: return ternary_intern<36>(a, b, c);
				case 37: return ternary_intern<37>(a, b, c);
				case 38: return ternary_intern<38>(a, b, c);
				case 39: return ternary_intern<39>(a, b, c);

				case 40: return ternary_intern<40>(a, b, c);
				case 41: return ternary_intern<41>(a, b, c);
				case 42: return ternary_intern<42>(a, b, c);
				case 43: return ternary_intern<43>(a, b, c);
				case 44: return ternary_intern<44>(a, b, c);
				case 45: return ternary_intern<45>(a, b, c);
				case 46: return ternary_intern<46>(a, b, c);
				case 47: return ternary_intern<47>(a, b, c);
				case 48: return ternary_intern<48>(a, b, c);
				case 49: return ternary_intern<49>(a, b, c);

				case 50: return ternary_intern<50>(a, b, c);
				case 51: return ternary_intern<51>(a, b, c);
				case 52: return ternary_intern<52>(a, b, c);
				case 53: return ternary_intern<53>(a, b, c);
				case 54: return ternary_intern<54>(a, b, c);
				case 55: return ternary_intern<55>(a, b, c);
				case 56: return ternary_intern<56>(a, b, c);
				case 57: return ternary_intern<57>(a, b, c);
				case 58: return ternary_intern<58>(a, b, c);
				case 59: return ternary_intern<59>(a, b, c);

				case 60: return ternary_intern<60>(a, b, c);
				case 61: return ternary_intern<61>(a, b, c);
				case 62: return ternary_intern<62>(a, b, c);
				case 63: return ternary_intern<63>(a, b, c);
				case 64: return ternary_intern<64>(a, b, c);
				case 65: return ternary_intern<65>(a, b, c);
				case 66: return ternary_intern<66>(a, b, c);
				case 67: return ternary_intern<67>(a, b, c);
				case 68: return ternary_intern<68>(a, b, c);
				case 69: return ternary_intern<69>(a, b, c);

				case 70: return ternary_intern<70>(a, b, c);
				case 71: return ternary_intern<71>(a, b, c);
				case 72: return ternary_intern<72>(a, b, c);
				case 73: return ternary_intern<73>(a, b, c);
				case 74: return ternary_intern<74>(a, b, c);
				case 75: return ternary_intern<75>(a, b, c);
				case 76: return ternary_intern<76>(a, b, c);
				case 77: return ternary_intern<77>(a, b, c);
				case 78: return ternary_intern<78>(a, b, c);
				case 79: return ternary_intern<79>(a, b, c);

				case 80: return ternary_intern<80>(a, b, c);
				case 81: return ternary_intern<81>(a, b, c);
				case 82: return ternary_intern<82>(a, b, c);
				case 83: return ternary_intern<83>(a, b, c);
				case 84: return ternary_intern<84>(a, b, c);
				case 85: return ternary_intern<85>(a, b, c);
				case 86: return ternary_intern<86>(a, b, c);
				case 87: return ternary_intern<87>(a, b, c);
				case 88: return ternary_intern<88>(a, b, c);
				case 89: return ternary_intern<89>(a, b, c);

				case 90: return ternary_intern<90>(a, b, c);
				case 91: return ternary_intern<91>(a, b, c);
				case 92: return ternary_intern<92>(a, b, c);
				case 93: return ternary_intern<93>(a, b, c);
				case 94: return ternary_intern<94>(a, b, c);
				case 95: return ternary_intern<95>(a, b, c);
				case 96: return ternary_intern<96>(a, b, c);
				case 97: return ternary_intern<97>(a, b, c);
				case 98: return ternary_intern<98>(a, b, c);
				case 99: return ternary_intern<99>(a, b, c);

				case 100: return ternary_intern<100>(a, b, c);
				case 101: return ternary_intern<101>(a, b, c);
				case 102: return ternary_intern<102>(a, b, c);
				case 103: return ternary_intern<103>(a, b, c);
				case 104: return ternary_intern<104>(a, b, c);
				case 105: return ternary_intern<105>(a, b, c);
				case 106: return ternary_intern<106>(a, b, c);
				case 107: return ternary_intern<107>(a, b, c);
				case 108: return ternary_intern<108>(a, b, c);
				case 109: return ternary_intern<109>(a, b, c);

				case 110: return ternary_intern<110>(a, b, c);
				case 111: return ternary_intern<111>(a, b, c);
				case 112: return ternary_intern<112>(a, b, c);
				case 113: return ternary_intern<113>(a, b, c);
				case 114: return ternary_intern<114>(a, b, c);
				case 115: return ternary_intern<115>(a, b, c);
				case 116: return ternary_intern<116>(a, b, c);
				case 117: return ternary_intern<117>(a, b, c);
				case 118: return ternary_intern<118>(a, b, c);
				case 119: return ternary_intern<119>(a, b, c);

				case 120: return ternary_intern<120>(a, b, c);
				case 121: return ternary_intern<121>(a, b, c);
				case 122: return ternary_intern<122>(a, b, c);
				case 123: return ternary_intern<123>(a, b, c);
				case 124: return ternary_intern<124>(a, b, c);
				case 125: return ternary_intern<125>(a, b, c);
				case 126: return ternary_intern<126>(a, b, c);
				case 127: return ternary_intern<127>(a, b, c);
				case 128: return ternary_intern<128>(a, b, c);
				case 129: return ternary_intern<129>(a, b, c);

				case 130: return ternary_intern<130>(a, b, c);
				case 131: return ternary_intern<131>(a, b, c);
				case 132: return ternary_intern<132>(a, b, c);
				case 133: return ternary_intern<133>(a, b, c);
				case 134: return ternary_intern<134>(a, b, c);
				case 135: return ternary_intern<135>(a, b, c);
				case 136: return ternary_intern<136>(a, b, c);
				case 137: return ternary_intern<137>(a, b, c);
				case 138: return ternary_intern<138>(a, b, c);
				case 139: return ternary_intern<139>(a, b, c);

				case 140: return ternary_intern<140>(a, b, c);
				case 141: return ternary_intern<141>(a, b, c);
				case 142: return ternary_intern<142>(a, b, c);
				case 143: return ternary_intern<143>(a, b, c);
				case 144: return ternary_intern<144>(a, b, c);
				case 145: return ternary_intern<145>(a, b, c);
				case 146: return ternary_intern<146>(a, b, c);
				case 147: return ternary_intern<147>(a, b, c);
				case 148: return ternary_intern<148>(a, b, c);
				case 149: return ternary_intern<149>(a, b, c);

				case 150: return ternary_intern<150>(a, b, c);
				case 151: return ternary_intern<151>(a, b, c);
				case 152: return ternary_intern<152>(a, b, c);
				case 153: return ternary_intern<153>(a, b, c);
				case 154: return ternary_intern<154>(a, b, c);
				case 155: return ternary_intern<155>(a, b, c);
				case 156: return ternary_intern<156>(a, b, c);
				case 157: return ternary_intern<157>(a, b, c);
				case 158: return ternary_intern<158>(a, b, c);
				case 159: return ternary_intern<159>(a, b, c);

				case 160: return ternary_intern<160>(a, b, c);
				case 161: return ternary_intern<161>(a, b, c);
				case 162: return ternary_intern<162>(a, b, c);
				case 163: return ternary_intern<163>(a, b, c);
				case 164: return ternary_intern<164>(a, b, c);
				case 165: return ternary_intern<165>(a, b, c);
				case 166: return ternary_intern<166>(a, b, c);
				case 167: return ternary_intern<167>(a, b, c);
				case 168: return ternary_intern<168>(a, b, c);
				case 169: return ternary_intern<169>(a, b, c);

				case 170: return ternary_intern<170>(a, b, c);
				case 171: return ternary_intern<171>(a, b, c);
				case 172: return ternary_intern<172>(a, b, c);
				case 173: return ternary_intern<173>(a, b, c);
				case 174: return ternary_intern<174>(a, b, c);
				case 175: return ternary_intern<175>(a, b, c);
				case 176: return ternary_intern<176>(a, b, c);
				case 177: return ternary_intern<177>(a, b, c);
				case 178: return ternary_intern<178>(a, b, c);
				case 179: return ternary_intern<179>(a, b, c);

				case 180: return ternary_intern<180>(a, b, c);
				case 181: return ternary_intern<181>(a, b, c);
				case 182: return ternary_intern<182>(a, b, c);
				case 183: return ternary_intern<183>(a, b, c);
				case 184: return ternary_intern<184>(a, b, c);
				case 185: return ternary_intern<185>(a, b, c);
				case 186: return ternary_intern<186>(a, b, c);
				case 187: return ternary_intern<187>(a, b, c);
				case 188: return ternary_intern<188>(a, b, c);
				case 189: return ternary_intern<189>(a, b, c);

				case 190: return ternary_intern<190>(a, b, c);
				case 191: return ternary_intern<191>(a, b, c);
				case 192: return ternary_intern<192>(a, b, c);
				case 193: return ternary_intern<193>(a, b, c);
				case 194: return ternary_intern<194>(a, b, c);
				case 195: return ternary_intern<195>(a, b, c);
				case 196: return ternary_intern<196>(a, b, c);
				case 197: return ternary_intern<197>(a, b, c);
				case 198: return ternary_intern<198>(a, b, c);
				case 199: return ternary_intern<199>(a, b, c);

				case 200: return ternary_intern<200>(a, b, c);
				case 201: return ternary_intern<201>(a, b, c);
				case 202: return ternary_intern<202>(a, b, c);
				case 203: return ternary_intern<203>(a, b, c);
				case 204: return ternary_intern<204>(a, b, c);
				case 205: return ternary_intern<205>(a, b, c);
				case 206: return ternary_intern<206>(a, b, c);
				case 207: return ternary_intern<207>(a, b, c);
				case 208: return ternary_intern<208>(a, b, c);
				case 209: return ternary_intern<209>(a, b, c);

				case 210: return ternary_intern<210>(a, b, c);
				case 211: return ternary_intern<211>(a, b, c);
				case 212: return ternary_intern<212>(a, b, c);
				case 213: return ternary_intern<213>(a, b, c);
				case 214: return ternary_intern<214>(a, b, c);
				case 215: return ternary_intern<215>(a, b, c);
				case 216: return ternary_intern<216>(a, b, c);
				case 217: return ternary_intern<217>(a, b, c);
				case 218: return ternary_intern<218>(a, b, c);
				case 219: return ternary_intern<219>(a, b, c);

				case 220: return ternary_intern<220>(a, b, c);
				case 221: return ternary_intern<221>(a, b, c);
				case 222: return ternary_intern<222>(a, b, c);
				case 223: return ternary_intern<223>(a, b, c);
				case 224: return ternary_intern<224>(a, b, c);
				case 225: return ternary_intern<225>(a, b, c);
				case 226: return ternary_intern<226>(a, b, c);
				case 227: return ternary_intern<227>(a, b, c);
				case 228: return ternary_intern<228>(a, b, c);
				case 229: return ternary_intern<229>(a, b, c);

				case 230: return ternary_intern<230>(a, b, c);
				case 231: return ternary_intern<231>(a, b, c);
				case 232: return ternary_intern<232>(a, b, c);
				case 233: return ternary_intern<233>(a, b, c);
				case 234: return ternary_intern<234>(a, b, c);
				case 235: return ternary_intern<235>(a, b, c);
				case 236: return ternary_intern<236>(a, b, c);
				case 237: return ternary_intern<237>(a, b, c);
				case 238: return ternary_intern<238>(a, b, c);
				case 239: return ternary_intern<239>(a, b, c);

				case 240: return ternary_intern<240>(a, b, c);
				case 241: return ternary_intern<241>(a, b, c);
				case 242: return ternary_intern<242>(a, b, c);
				case 243: return ternary_intern<243>(a, b, c);
				case 244: return ternary_intern<244>(a, b, c);
				case 245: return ternary_intern<245>(a, b, c);
				case 246: return ternary_intern<246>(a, b, c);
				case 247: return ternary_intern<247>(a, b, c);
				case 248: return ternary_intern<248>(a, b, c);
				case 249: return ternary_intern<249>(a, b, c);

				case 250: return ternary_intern<250>(a, b, c);
				case 251: return ternary_intern<251>(a, b, c);
				case 252: return ternary_intern<252>(a, b, c);
				case 253: return ternary_intern<253>(a, b, c);
				case 254: return ternary_intern<254>(a, b, c);
				case 255: return ternary_intern<255>(a, b, c);

				default: return ternary_intern<0>(a, b, c);
			}
		}
 	
		template<typename T>
		inline constexpr T ternary_reduced(const T& a, const T& b, const T& c, const bf_type k)
		{
			// method is generated with test::create_method_reduced_ternary()
			switch (k)
			{
				case 0: return priv::ternary_intern<0>(a, b, c);
				case 1: return priv::ternary_intern<1>(a, b, c);
				case 2: return priv::ternary_intern<2>(a, b, c);
				case 3: return priv::ternary_intern<3>(a, b, c);
				case 4: return priv::ternary_intern<2>(a, c, b);
				case 5: return priv::ternary_intern<3>(a, c, b);
				case 6: return priv::ternary_intern<6>(a, b, c);
				case 7: return priv::ternary_intern<7>(a, b, c);
				case 8: return priv::ternary_intern<8>(a, b, c);
				case 9: return priv::ternary_intern<9>(a, b, c);
				case 10: return priv::ternary_intern<10>(a, b, c);
				case 11: return priv::ternary_intern<11>(a, b, c);
				case 12: return priv::ternary_intern<10>(a, c, b);
				case 13: return priv::ternary_intern<11>(a, c, b);
				case 14: return priv::ternary_intern<14>(a, b, c);
				case 15: return priv::ternary_intern<15>(a, b, c);
				case 16: return priv::ternary_intern<2>(c, b, a);
				case 17: return priv::ternary_intern<3>(c, b, a);
				case 18: return priv::ternary_intern<6>(b, a, c);
				case 19: return priv::ternary_intern<7>(b, a, c);
				case 20: return priv::ternary_intern<6>(c, b, a);
				case 21: return priv::ternary_intern<7>(c, b, a);
				case 22: return priv::ternary_intern<22>(a, b, c);
				case 23: return priv::ternary_intern<23>(a, b, c);
				case 24: return priv::ternary_intern<24>(a, b, c);
				case 25: return priv::ternary_intern<25>(a, b, c);
				case 26: return priv::ternary_intern<26>(a, b, c);
				case 27: return priv::ternary_intern<27>(a, b, c);
				case 28: return priv::ternary_intern<26>(a, c, b);
				case 29: return priv::ternary_intern<27>(a, c, b);
				case 30: return priv::ternary_intern<30>(a, b, c);
				case 31: return priv::ternary_intern<31>(a, b, c);
				case 32: return priv::ternary_intern<8>(b, a, c);
				case 33: return priv::ternary_intern<9>(b, a, c);
				case 34: return priv::ternary_intern<10>(b, a, c);
				case 35: return priv::ternary_intern<11>(b, a, c);
				case 36: return priv::ternary_intern<24>(b, a, c);
				case 37: return priv::ternary_intern<25>(b, a, c);
				case 38: return priv::ternary_intern<26>(b, a, c);
				case 39: return priv::ternary_intern<27>(b, a, c);
				case 40: return priv::ternary_intern<40>(a, b, c);
				case 41: return priv::ternary_intern<41>(a, b, c);
				case 42: return priv::ternary_intern<42>(a, b, c);
				case 43: return priv::ternary_intern<43>(a, b, c);
				case 44: return priv::ternary_intern<44>(a, b, c);
				case 45: return priv::ternary_intern<45>(a, b, c);
				case 46: return priv::ternary_intern<46>(a, b, c);
				case 47: return priv::ternary_intern<47>(a, b, c);
				case 48: return priv::ternary_intern<10>(b, c, a);
				case 49: return priv::ternary_intern<11>(b, c, a);
				case 50: return priv::ternary_intern<14>(b, a, c);
				case 51: return priv::ternary_intern<15>(b, a, c);
				case 52: return priv::ternary_intern<26>(b, c, a);
				case 53: return priv::ternary_intern<27>(b, c, a);
				case 54: return priv::ternary_intern<30>(b, a, c);
				case 55: return priv::ternary_intern<31>(b, a, c);
				case 56: return priv::ternary_intern<44>(b, a, c);
				case 57: return priv::ternary_intern<45>(b, a, c);
				case 58: return priv::ternary_intern<46>(b, a, c);
				case 59: return priv::ternary_intern<47>(b, a, c);
				case 60: return priv::ternary_intern<60>(a, b, c);
				case 61: return priv::ternary_intern<61>(a, b, c);
				case 62: return priv::ternary_intern<62>(a, b, c);
				case 63: return priv::ternary_intern<63>(a, b, c);
				case 64: return priv::ternary_intern<8>(c, b, a);
				case 65: return priv::ternary_intern<9>(c, b, a);
				case 66: return priv::ternary_intern<24>(c, b, a);
				case 67: return priv::ternary_intern<25>(c, b, a);
				case 68: return priv::ternary_intern<10>(c, a, b);
				case 69: return priv::ternary_intern<11>(c, a, b);
				case 70: return priv::ternary_intern<26>(c, a, b);
				case 71: return priv::ternary_intern<27>(c, a, b);
				case 72: return priv::ternary_intern<40>(a, c, b);
				case 73: return priv::ternary_intern<41>(a, c, b);
				case 74: return priv::ternary_intern<44>(a, c, b);
				case 75: return priv::ternary_intern<45>(a, c, b);
				case 76: return priv::ternary_intern<42>(a, c, b);
				case 77: return priv::ternary_intern<43>(a, c, b);
				case 78: return priv::ternary_intern<46>(a, c, b);
				case 79: return priv::ternary_intern<47>(a, c, b);
				case 80: return priv::ternary_intern<10>(c, b, a);
				case 81: return priv::ternary_intern<11>(c, b, a);
				case 82: return priv::ternary_intern<26>(c, b, a);
				case 83: return priv::ternary_intern<27>(c, b, a);
				case 84: return priv::ternary_intern<14>(c, b, a);
				case 85: return priv::ternary_intern<15>(c, b, a);
				case 86: return priv::ternary_intern<30>(c, b, a);
				case 87: return priv::ternary_intern<31>(c, b, a);
				case 88: return priv::ternary_intern<44>(c, a, b);
				case 89: return priv::ternary_intern<45>(c, a, b);
				case 90: return priv::ternary_intern<60>(a, c, b);
				case 91: return priv::ternary_intern<61>(a, c, b);
				case 92: return priv::ternary_intern<46>(c, a, b);
				case 93: return priv::ternary_intern<47>(c, a, b);
				case 94: return priv::ternary_intern<62>(a, c, b);
				case 95: return priv::ternary_intern<63>(a, c, b);
				case 96: return priv::ternary_intern<40>(c, b, a);
				case 97: return priv::ternary_intern<41>(c, b, a);
				case 98: return priv::ternary_intern<44>(b, c, a);
				case 99: return priv::ternary_intern<45>(b, c, a);
				case 100: return priv::ternary_intern<44>(c, b, a);
				case 101: return priv::ternary_intern<45>(c, b, a);
				case 102: return priv::ternary_intern<60>(c, b, a);
				case 103: return priv::ternary_intern<61>(c, b, a);
				case 104: return priv::ternary_intern<104>(a, b, c);
				case 105: return priv::ternary_intern<105>(a, b, c);
				case 106: return priv::ternary_intern<106>(a, b, c);
				case 107: return priv::ternary_intern<107>(a, b, c);
				case 108: return priv::ternary_intern<106>(a, c, b);
				case 109: return priv::ternary_intern<107>(a, c, b);
				case 110: return priv::ternary_intern<110>(a, b, c);
				case 111: return priv::ternary_intern<111>(a, b, c);
				case 112: return priv::ternary_intern<42>(c, b, a);
				case 113: return priv::ternary_intern<43>(c, b, a);
				case 114: return priv::ternary_intern<46>(b, c, a);
				case 115: return priv::ternary_intern<47>(b, c, a);
				case 116: return priv::ternary_intern<46>(c, b, a);
				case 117: return priv::ternary_intern<47>(c, b, a);
				case 118: return priv::ternary_intern<62>(c, b, a);
				case 119: return priv::ternary_intern<63>(c, b, a);
				case 120: return priv::ternary_intern<106>(c, b, a);
				case 121: return priv::ternary_intern<107>(c, b, a);
				case 122: return priv::ternary_intern<110>(b, a, c);
				case 123: return priv::ternary_intern<111>(b, a, c);
				case 124: return priv::ternary_intern<110>(c, b, a);
				case 125: return priv::ternary_intern<111>(c, b, a);
				case 126: return priv::ternary_intern<126>(a, b, c);
				case 127: return priv::ternary_intern<127>(a, b, c);
				case 128: return priv::ternary_intern<128>(a, b, c);
				case 129: return priv::ternary_intern<129>(a, b, c);
				case 130: return priv::ternary_intern<130>(a, b, c);
				case 131: return priv::ternary_intern<131>(a, b, c);
				case 132: return priv::ternary_intern<130>(a, c, b);
				case 133: return priv::ternary_intern<131>(a, c, b);
				case 134: return priv::ternary_intern<134>(a, b, c);
				case 135: return priv::ternary_intern<135>(a, b, c);
				case 136: return priv::ternary_intern<136>(a, b, c);
				case 137: return priv::ternary_intern<137>(a, b, c);
				case 138: return priv::ternary_intern<138>(a, b, c);
				case 139: return priv::ternary_intern<139>(a, b, c);
				case 140: return priv::ternary_intern<138>(a, c, b);
				case 141: return priv::ternary_intern<139>(a, c, b);
				case 142: return priv::ternary_intern<142>(a, b, c);
				case 143: return priv::ternary_intern<143>(a, b, c);
				case 144: return priv::ternary_intern<130>(c, b, a);
				case 145: return priv::ternary_intern<131>(c, b, a);
				case 146: return priv::ternary_intern<134>(b, a, c);
				case 147: return priv::ternary_intern<135>(b, a, c);
				case 148: return priv::ternary_intern<134>(c, b, a);
				case 149: return priv::ternary_intern<135>(c, b, a);
				case 150: return priv::ternary_intern<150>(a, b, c);
				case 151: return priv::ternary_intern<151>(a, b, c);
				case 152: return priv::ternary_intern<152>(a, b, c);
				case 153: return priv::ternary_intern<153>(a, b, c);
				case 154: return priv::ternary_intern<154>(a, b, c);
				case 155: return priv::ternary_intern<155>(a, b, c);
				case 156: return priv::ternary_intern<154>(a, c, b);
				case 157: return priv::ternary_intern<155>(a, c, b);
				case 158: return priv::ternary_intern<158>(a, b, c);
				case 159: return priv::ternary_intern<159>(a, b, c);
				case 160: return priv::ternary_intern<136>(b, a, c);
				case 161: return priv::ternary_intern<137>(b, a, c);
				case 162: return priv::ternary_intern<138>(b, a, c);
				case 163: return priv::ternary_intern<139>(b, a, c);
				case 164: return priv::ternary_intern<152>(b, a, c);
				case 165: return priv::ternary_intern<153>(b, a, c);
				case 166: return priv::ternary_intern<154>(b, a, c);
				case 167: return priv::ternary_intern<155>(b, a, c);
				case 168: return priv::ternary_intern<168>(a, b, c);
				case 169: return priv::ternary_intern<169>(a, b, c);
				case 170: return priv::ternary_intern<170>(a, b, c);
				case 171: return priv::ternary_intern<171>(a, b, c);
				case 172: return priv::ternary_intern<172>(a, b, c);
				case 173: return priv::ternary_intern<173>(a, b, c);
				case 174: return priv::ternary_intern<174>(a, b, c);
				case 175: return priv::ternary_intern<175>(a, b, c);
				case 176: return priv::ternary_intern<138>(b, c, a);
				case 177: return priv::ternary_intern<139>(b, c, a);
				case 178: return priv::ternary_intern<142>(b, a, c);
				case 179: return priv::ternary_intern<143>(b, a, c);
				case 180: return priv::ternary_intern<154>(b, c, a);
				case 181: return priv::ternary_intern<155>(b, c, a);
				case 182: return priv::ternary_intern<158>(b, a, c);
				case 183: return priv::ternary_intern<159>(b, a, c);
				case 184: return priv::ternary_intern<172>(b, a, c);
				case 185: return priv::ternary_intern<173>(b, a, c);
				case 186: return priv::ternary_intern<174>(b, a, c);
				case 187: return priv::ternary_intern<175>(b, a, c);
				case 188: return priv::ternary_intern<188>(a, b, c);
				case 189: return priv::ternary_intern<189>(a, b, c);
				case 190: return priv::ternary_intern<190>(a, b, c);
				case 191: return priv::ternary_intern<191>(a, b, c);
				case 192: return priv::ternary_intern<136>(c, b, a);
				case 193: return priv::ternary_intern<137>(c, b, a);
				case 194: return priv::ternary_intern<152>(c, b, a);
				case 195: return priv::ternary_intern<153>(c, b, a);
				case 196: return priv::ternary_intern<138>(c, a, b);
				case 197: return priv::ternary_intern<139>(c, a, b);
				case 198: return priv::ternary_intern<154>(c, a, b);
				case 199: return priv::ternary_intern<155>(c, a, b);
				case 200: return priv::ternary_intern<168>(a, c, b);
				case 201: return priv::ternary_intern<169>(a, c, b);
				case 202: return priv::ternary_intern<172>(a, c, b);
				case 203: return priv::ternary_intern<173>(a, c, b);
				case 204: return priv::ternary_intern<170>(a, c, b);
				case 205: return priv::ternary_intern<171>(a, c, b);
				case 206: return priv::ternary_intern<174>(a, c, b);
				case 207: return priv::ternary_intern<175>(a, c, b);
				case 208: return priv::ternary_intern<138>(c, b, a);
				case 209: return priv::ternary_intern<139>(c, b, a);
				case 210: return priv::ternary_intern<154>(c, b, a);
				case 211: return priv::ternary_intern<155>(c, b, a);
				case 212: return priv::ternary_intern<142>(c, b, a);
				case 213: return priv::ternary_intern<143>(c, b, a);
				case 214: return priv::ternary_intern<158>(c, b, a);
				case 215: return priv::ternary_intern<159>(c, b, a);
				case 216: return priv::ternary_intern<172>(c, a, b);
				case 217: return priv::ternary_intern<173>(c, a, b);
				case 218: return priv::ternary_intern<188>(a, c, b);
				case 219: return priv::ternary_intern<189>(a, c, b);
				case 220: return priv::ternary_intern<174>(c, a, b);
				case 221: return priv::ternary_intern<175>(c, a, b);
				case 222: return priv::ternary_intern<190>(a, c, b);
				case 223: return priv::ternary_intern<191>(a, c, b);
				case 224: return priv::ternary_intern<168>(c, b, a);
				case 225: return priv::ternary_intern<169>(c, b, a);
				case 226: return priv::ternary_intern<172>(b, c, a);
				case 227: return priv::ternary_intern<173>(b, c, a);
				case 228: return priv::ternary_intern<172>(c, b, a);
				case 229: return priv::ternary_intern<173>(c, b, a);
				case 230: return priv::ternary_intern<188>(c, b, a);
				case 231: return priv::ternary_intern<189>(c, b, a);
				case 232: return priv::ternary_intern<232>(a, b, c);
				case 233: return priv::ternary_intern<233>(a, b, c);
				case 234: return priv::ternary_intern<234>(a, b, c);
				case 235: return priv::ternary_intern<235>(a, b, c);
				case 236: return priv::ternary_intern<234>(a, c, b);
				case 237: return priv::ternary_intern<235>(a, c, b);
				case 238: return priv::ternary_intern<238>(a, b, c);
				case 239: return priv::ternary_intern<239>(a, b, c);
				case 240: return priv::ternary_intern<170>(c, b, a);
				case 241: return priv::ternary_intern<171>(c, b, a);
				case 242: return priv::ternary_intern<174>(b, c, a);
				case 243: return priv::ternary_intern<175>(b, c, a);
				case 244: return priv::ternary_intern<174>(c, b, a);
				case 245: return priv::ternary_intern<175>(c, b, a);
				case 246: return priv::ternary_intern<190>(c, b, a);
				case 247: return priv::ternary_intern<191>(c, b, a);
				case 248: return priv::ternary_intern<234>(c, b, a);
				case 249: return priv::ternary_intern<235>(c, b, a);
				case 250: return priv::ternary_intern<238>(b, a, c);
				case 251: return priv::ternary_intern<239>(b, a, c);
				case 252: return priv::ternary_intern<238>(c, b, a);
				case 253: return priv::ternary_intern<239>(c, b, a);
				case 254: return priv::ternary_intern<254>(a, b, c);
				case 255: return priv::ternary_intern<255>(a, b, c);
				default: return priv::ternary_intern<0>(a, b, c);
			}
		}

		template<typename T>
		inline constexpr T ternary_no_vpternlog(const T& a, const T& b, const T& c, const bf_type k)
		{
			switch (k)
			{
				case 0: return ternary_intern_no_vpternlog<0>(a, b, c);
				case 1: return ternary_intern_no_vpternlog<1>(a, b, c);
				case 2: return ternary_intern_no_vpternlog<2>(a, b, c);
				case 3: return ternary_intern_no_vpternlog<3>(a, b, c);
				case 4: return ternary_intern_no_vpternlog<4>(a, b, c);
				case 5: return ternary_intern_no_vpternlog<5>(a, b, c);
				case 6: return ternary_intern_no_vpternlog<6>(a, b, c);
				case 7: return ternary_intern_no_vpternlog<7>(a, b, c);
				case 8: return ternary_intern_no_vpternlog<8>(a, b, c);
				case 9: return ternary_intern_no_vpternlog<9>(a, b, c);

				case 10: return ternary_intern_no_vpternlog<10>(a, b, c);
				case 11: return ternary_intern_no_vpternlog<11>(a, b, c);
				case 12: return ternary_intern_no_vpternlog<12>(a, b, c);
				case 13: return ternary_intern_no_vpternlog<13>(a, b, c);
				case 14: return ternary_intern_no_vpternlog<14>(a, b, c);
				case 15: return ternary_intern_no_vpternlog<15>(a, b, c);
				case 16: return ternary_intern_no_vpternlog<16>(a, b, c);
				case 17: return ternary_intern_no_vpternlog<17>(a, b, c);
				case 18: return ternary_intern_no_vpternlog<18>(a, b, c);
				case 19: return ternary_intern_no_vpternlog<19>(a, b, c);

				case 20: return ternary_intern_no_vpternlog<20>(a, b, c);
				case 21: return ternary_intern_no_vpternlog<21>(a, b, c);
				case 22: return ternary_intern_no_vpternlog<22>(a, b, c);
				case 23: return ternary_intern_no_vpternlog<23>(a, b, c);
				case 24: return ternary_intern_no_vpternlog<24>(a, b, c);
				case 25: return ternary_intern_no_vpternlog<25>(a, b, c);
				case 26: return ternary_intern_no_vpternlog<26>(a, b, c);
				case 27: return ternary_intern_no_vpternlog<27>(a, b, c);
				case 28: return ternary_intern_no_vpternlog<28>(a, b, c);
				case 29: return ternary_intern_no_vpternlog<29>(a, b, c);

				case 30: return ternary_intern_no_vpternlog<30>(a, b, c);
				case 31: return ternary_intern_no_vpternlog<31>(a, b, c);
				case 32: return ternary_intern_no_vpternlog<32>(a, b, c);
				case 33: return ternary_intern_no_vpternlog<33>(a, b, c);
				case 34: return ternary_intern_no_vpternlog<34>(a, b, c);
				case 35: return ternary_intern_no_vpternlog<35>(a, b, c);
				case 36: return ternary_intern_no_vpternlog<36>(a, b, c);
				case 37: return ternary_intern_no_vpternlog<37>(a, b, c);
				case 38: return ternary_intern_no_vpternlog<38>(a, b, c);
				case 39: return ternary_intern_no_vpternlog<39>(a, b, c);

				case 40: return ternary_intern_no_vpternlog<40>(a, b, c);
				case 41: return ternary_intern_no_vpternlog<41>(a, b, c);
				case 42: return ternary_intern_no_vpternlog<42>(a, b, c);
				case 43: return ternary_intern_no_vpternlog<43>(a, b, c);
				case 44: return ternary_intern_no_vpternlog<44>(a, b, c);
				case 45: return ternary_intern_no_vpternlog<45>(a, b, c);
				case 46: return ternary_intern_no_vpternlog<46>(a, b, c);
				case 47: return ternary_intern_no_vpternlog<47>(a, b, c);
				case 48: return ternary_intern_no_vpternlog<48>(a, b, c);
				case 49: return ternary_intern_no_vpternlog<49>(a, b, c);

				case 50: return ternary_intern_no_vpternlog<50>(a, b, c);
				case 51: return ternary_intern_no_vpternlog<51>(a, b, c);
				case 52: return ternary_intern_no_vpternlog<52>(a, b, c);
				case 53: return ternary_intern_no_vpternlog<53>(a, b, c);
				case 54: return ternary_intern_no_vpternlog<54>(a, b, c);
				case 55: return ternary_intern_no_vpternlog<55>(a, b, c);
				case 56: return ternary_intern_no_vpternlog<56>(a, b, c);
				case 57: return ternary_intern_no_vpternlog<57>(a, b, c);
				case 58: return ternary_intern_no_vpternlog<58>(a, b, c);
				case 59: return ternary_intern_no_vpternlog<59>(a, b, c);

				case 60: return ternary_intern_no_vpternlog<60>(a, b, c);
				case 61: return ternary_intern_no_vpternlog<61>(a, b, c);
				case 62: return ternary_intern_no_vpternlog<62>(a, b, c);
				case 63: return ternary_intern_no_vpternlog<63>(a, b, c);
				case 64: return ternary_intern_no_vpternlog<64>(a, b, c);
				case 65: return ternary_intern_no_vpternlog<65>(a, b, c);
				case 66: return ternary_intern_no_vpternlog<66>(a, b, c);
				case 67: return ternary_intern_no_vpternlog<67>(a, b, c);
				case 68: return ternary_intern_no_vpternlog<68>(a, b, c);
				case 69: return ternary_intern_no_vpternlog<69>(a, b, c);

				case 70: return ternary_intern_no_vpternlog<70>(a, b, c);
				case 71: return ternary_intern_no_vpternlog<71>(a, b, c);
				case 72: return ternary_intern_no_vpternlog<72>(a, b, c);
				case 73: return ternary_intern_no_vpternlog<73>(a, b, c);
				case 74: return ternary_intern_no_vpternlog<74>(a, b, c);
				case 75: return ternary_intern_no_vpternlog<75>(a, b, c);
				case 76: return ternary_intern_no_vpternlog<76>(a, b, c);
				case 77: return ternary_intern_no_vpternlog<77>(a, b, c);
				case 78: return ternary_intern_no_vpternlog<78>(a, b, c);
				case 79: return ternary_intern_no_vpternlog<79>(a, b, c);

				case 80: return ternary_intern_no_vpternlog<80>(a, b, c);
				case 81: return ternary_intern_no_vpternlog<81>(a, b, c);
				case 82: return ternary_intern_no_vpternlog<82>(a, b, c);
				case 83: return ternary_intern_no_vpternlog<83>(a, b, c);
				case 84: return ternary_intern_no_vpternlog<84>(a, b, c);
				case 85: return ternary_intern_no_vpternlog<85>(a, b, c);
				case 86: return ternary_intern_no_vpternlog<86>(a, b, c);
				case 87: return ternary_intern_no_vpternlog<87>(a, b, c);
				case 88: return ternary_intern_no_vpternlog<88>(a, b, c);
				case 89: return ternary_intern_no_vpternlog<89>(a, b, c);

				case 90: return ternary_intern_no_vpternlog<90>(a, b, c);
				case 91: return ternary_intern_no_vpternlog<91>(a, b, c);
				case 92: return ternary_intern_no_vpternlog<92>(a, b, c);
				case 93: return ternary_intern_no_vpternlog<93>(a, b, c);
				case 94: return ternary_intern_no_vpternlog<94>(a, b, c);
				case 95: return ternary_intern_no_vpternlog<95>(a, b, c);
				case 96: return ternary_intern_no_vpternlog<96>(a, b, c);
				case 97: return ternary_intern_no_vpternlog<97>(a, b, c);
				case 98: return ternary_intern_no_vpternlog<98>(a, b, c);
				case 99: return ternary_intern_no_vpternlog<99>(a, b, c);

				case 100: return ternary_intern_no_vpternlog<100>(a, b, c);
				case 101: return ternary_intern_no_vpternlog<101>(a, b, c);
				case 102: return ternary_intern_no_vpternlog<102>(a, b, c);
				case 103: return ternary_intern_no_vpternlog<103>(a, b, c);
				case 104: return ternary_intern_no_vpternlog<104>(a, b, c);
				case 105: return ternary_intern_no_vpternlog<105>(a, b, c);
				case 106: return ternary_intern_no_vpternlog<106>(a, b, c);
				case 107: return ternary_intern_no_vpternlog<107>(a, b, c);
				case 108: return ternary_intern_no_vpternlog<108>(a, b, c);
				case 109: return ternary_intern_no_vpternlog<109>(a, b, c);

				case 110: return ternary_intern_no_vpternlog<110>(a, b, c);
				case 111: return ternary_intern_no_vpternlog<111>(a, b, c);
				case 112: return ternary_intern_no_vpternlog<112>(a, b, c);
				case 113: return ternary_intern_no_vpternlog<113>(a, b, c);
				case 114: return ternary_intern_no_vpternlog<114>(a, b, c);
				case 115: return ternary_intern_no_vpternlog<115>(a, b, c);
				case 116: return ternary_intern_no_vpternlog<116>(a, b, c);
				case 117: return ternary_intern_no_vpternlog<117>(a, b, c);
				case 118: return ternary_intern_no_vpternlog<118>(a, b, c);
				case 119: return ternary_intern_no_vpternlog<119>(a, b, c);

				case 120: return ternary_intern_no_vpternlog<120>(a, b, c);
				case 121: return ternary_intern_no_vpternlog<121>(a, b, c);
				case 122: return ternary_intern_no_vpternlog<122>(a, b, c);
				case 123: return ternary_intern_no_vpternlog<123>(a, b, c);
				case 124: return ternary_intern_no_vpternlog<124>(a, b, c);
				case 125: return ternary_intern_no_vpternlog<125>(a, b, c);
				case 126: return ternary_intern_no_vpternlog<126>(a, b, c);
				case 127: return ternary_intern_no_vpternlog<127>(a, b, c);
				case 128: return ternary_intern_no_vpternlog<128>(a, b, c);
				case 129: return ternary_intern_no_vpternlog<129>(a, b, c);

				case 130: return ternary_intern_no_vpternlog<130>(a, b, c);
				case 131: return ternary_intern_no_vpternlog<131>(a, b, c);
				case 132: return ternary_intern_no_vpternlog<132>(a, b, c);
				case 133: return ternary_intern_no_vpternlog<133>(a, b, c);
				case 134: return ternary_intern_no_vpternlog<134>(a, b, c);
				case 135: return ternary_intern_no_vpternlog<135>(a, b, c);
				case 136: return ternary_intern_no_vpternlog<136>(a, b, c);
				case 137: return ternary_intern_no_vpternlog<137>(a, b, c);
				case 138: return ternary_intern_no_vpternlog<138>(a, b, c);
				case 139: return ternary_intern_no_vpternlog<139>(a, b, c);

				case 140: return ternary_intern_no_vpternlog<140>(a, b, c);
				case 141: return ternary_intern_no_vpternlog<141>(a, b, c);
				case 142: return ternary_intern_no_vpternlog<142>(a, b, c);
				case 143: return ternary_intern_no_vpternlog<143>(a, b, c);
				case 144: return ternary_intern_no_vpternlog<144>(a, b, c);
				case 145: return ternary_intern_no_vpternlog<145>(a, b, c);
				case 146: return ternary_intern_no_vpternlog<146>(a, b, c);
				case 147: return ternary_intern_no_vpternlog<147>(a, b, c);
				case 148: return ternary_intern_no_vpternlog<148>(a, b, c);
				case 149: return ternary_intern_no_vpternlog<149>(a, b, c);

				case 150: return ternary_intern_no_vpternlog<150>(a, b, c);
				case 151: return ternary_intern_no_vpternlog<151>(a, b, c);
				case 152: return ternary_intern_no_vpternlog<152>(a, b, c);
				case 153: return ternary_intern_no_vpternlog<153>(a, b, c);
				case 154: return ternary_intern_no_vpternlog<154>(a, b, c);
				case 155: return ternary_intern_no_vpternlog<155>(a, b, c);
				case 156: return ternary_intern_no_vpternlog<156>(a, b, c);
				case 157: return ternary_intern_no_vpternlog<157>(a, b, c);
				case 158: return ternary_intern_no_vpternlog<158>(a, b, c);
				case 159: return ternary_intern_no_vpternlog<159>(a, b, c);

				case 160: return ternary_intern_no_vpternlog<160>(a, b, c);
				case 161: return ternary_intern_no_vpternlog<161>(a, b, c);
				case 162: return ternary_intern_no_vpternlog<162>(a, b, c);
				case 163: return ternary_intern_no_vpternlog<163>(a, b, c);
				case 164: return ternary_intern_no_vpternlog<164>(a, b, c);
				case 165: return ternary_intern_no_vpternlog<165>(a, b, c);
				case 166: return ternary_intern_no_vpternlog<166>(a, b, c);
				case 167: return ternary_intern_no_vpternlog<167>(a, b, c);
				case 168: return ternary_intern_no_vpternlog<168>(a, b, c);
				case 169: return ternary_intern_no_vpternlog<169>(a, b, c);

				case 170: return ternary_intern_no_vpternlog<170>(a, b, c);
				case 171: return ternary_intern_no_vpternlog<171>(a, b, c);
				case 172: return ternary_intern_no_vpternlog<172>(a, b, c);
				case 173: return ternary_intern_no_vpternlog<173>(a, b, c);
				case 174: return ternary_intern_no_vpternlog<174>(a, b, c);
				case 175: return ternary_intern_no_vpternlog<175>(a, b, c);
				case 176: return ternary_intern_no_vpternlog<176>(a, b, c);
				case 177: return ternary_intern_no_vpternlog<177>(a, b, c);
				case 178: return ternary_intern_no_vpternlog<178>(a, b, c);
				case 179: return ternary_intern_no_vpternlog<179>(a, b, c);

				case 180: return ternary_intern_no_vpternlog<180>(a, b, c);
				case 181: return ternary_intern_no_vpternlog<181>(a, b, c);
				case 182: return ternary_intern_no_vpternlog<182>(a, b, c);
				case 183: return ternary_intern_no_vpternlog<183>(a, b, c);
				case 184: return ternary_intern_no_vpternlog<184>(a, b, c);
				case 185: return ternary_intern_no_vpternlog<185>(a, b, c);
				case 186: return ternary_intern_no_vpternlog<186>(a, b, c);
				case 187: return ternary_intern_no_vpternlog<187>(a, b, c);
				case 188: return ternary_intern_no_vpternlog<188>(a, b, c);
				case 189: return ternary_intern_no_vpternlog<189>(a, b, c);

				case 190: return ternary_intern_no_vpternlog<190>(a, b, c);
				case 191: return ternary_intern_no_vpternlog<191>(a, b, c);
				case 192: return ternary_intern_no_vpternlog<192>(a, b, c);
				case 193: return ternary_intern_no_vpternlog<193>(a, b, c);
				case 194: return ternary_intern_no_vpternlog<194>(a, b, c);
				case 195: return ternary_intern_no_vpternlog<195>(a, b, c);
				case 196: return ternary_intern_no_vpternlog<196>(a, b, c);
				case 197: return ternary_intern_no_vpternlog<197>(a, b, c);
				case 198: return ternary_intern_no_vpternlog<198>(a, b, c);
				case 199: return ternary_intern_no_vpternlog<199>(a, b, c);

				case 200: return ternary_intern_no_vpternlog<200>(a, b, c);
				case 201: return ternary_intern_no_vpternlog<201>(a, b, c);
				case 202: return ternary_intern_no_vpternlog<202>(a, b, c);
				case 203: return ternary_intern_no_vpternlog<203>(a, b, c);
				case 204: return ternary_intern_no_vpternlog<204>(a, b, c);
				case 205: return ternary_intern_no_vpternlog<205>(a, b, c);
				case 206: return ternary_intern_no_vpternlog<206>(a, b, c);
				case 207: return ternary_intern_no_vpternlog<207>(a, b, c);
				case 208: return ternary_intern_no_vpternlog<208>(a, b, c);
				case 209: return ternary_intern_no_vpternlog<209>(a, b, c);

				case 210: return ternary_intern_no_vpternlog<210>(a, b, c);
				case 211: return ternary_intern_no_vpternlog<211>(a, b, c);
				case 212: return ternary_intern_no_vpternlog<212>(a, b, c);
				case 213: return ternary_intern_no_vpternlog<213>(a, b, c);
				case 214: return ternary_intern_no_vpternlog<214>(a, b, c);
				case 215: return ternary_intern_no_vpternlog<215>(a, b, c);
				case 216: return ternary_intern_no_vpternlog<216>(a, b, c);
				case 217: return ternary_intern_no_vpternlog<217>(a, b, c);
				case 218: return ternary_intern_no_vpternlog<218>(a, b, c);
				case 219: return ternary_intern_no_vpternlog<219>(a, b, c);

				case 220: return ternary_intern_no_vpternlog<220>(a, b, c);
				case 221: return ternary_intern_no_vpternlog<221>(a, b, c);
				case 222: return ternary_intern_no_vpternlog<222>(a, b, c);
				case 223: return ternary_intern_no_vpternlog<223>(a, b, c);
				case 224: return ternary_intern_no_vpternlog<224>(a, b, c);
				case 225: return ternary_intern_no_vpternlog<225>(a, b, c);
				case 226: return ternary_intern_no_vpternlog<226>(a, b, c);
				case 227: return ternary_intern_no_vpternlog<227>(a, b, c);
				case 228: return ternary_intern_no_vpternlog<228>(a, b, c);
				case 229: return ternary_intern_no_vpternlog<229>(a, b, c);

				case 230: return ternary_intern_no_vpternlog<230>(a, b, c);
				case 231: return ternary_intern_no_vpternlog<231>(a, b, c);
				case 232: return ternary_intern_no_vpternlog<232>(a, b, c);
				case 233: return ternary_intern_no_vpternlog<233>(a, b, c);
				case 234: return ternary_intern_no_vpternlog<234>(a, b, c);
				case 235: return ternary_intern_no_vpternlog<235>(a, b, c);
				case 236: return ternary_intern_no_vpternlog<236>(a, b, c);
				case 237: return ternary_intern_no_vpternlog<237>(a, b, c);
				case 238: return ternary_intern_no_vpternlog<238>(a, b, c);
				case 239: return ternary_intern_no_vpternlog<239>(a, b, c);

				case 240: return ternary_intern_no_vpternlog<240>(a, b, c);
				case 241: return ternary_intern_no_vpternlog<241>(a, b, c);
				case 242: return ternary_intern_no_vpternlog<242>(a, b, c);
				case 243: return ternary_intern_no_vpternlog<243>(a, b, c);
				case 244: return ternary_intern_no_vpternlog<244>(a, b, c);
				case 245: return ternary_intern_no_vpternlog<245>(a, b, c);
				case 246: return ternary_intern_no_vpternlog<246>(a, b, c);
				case 247: return ternary_intern_no_vpternlog<247>(a, b, c);
				case 248: return ternary_intern_no_vpternlog<248>(a, b, c);
				case 249: return ternary_intern_no_vpternlog<249>(a, b, c);

				case 250: return ternary_intern_no_vpternlog<250>(a, b, c);
				case 251: return ternary_intern_no_vpternlog<251>(a, b, c);
				case 252: return ternary_intern_no_vpternlog<252>(a, b, c);
				case 253: return ternary_intern_no_vpternlog<253>(a, b, c);
				case 254: return ternary_intern_no_vpternlog<254>(a, b, c);
				case 255: return ternary_intern_no_vpternlog<255>(a, b, c);

				default: return ternary_intern_no_vpternlog<0>(a, b, c);
			}
		}
	}
	

	template<bf_type K, typename T>
	inline constexpr T ternary(const T a, const T b, const T c)
	{
		return priv::ternary_intern<K>(a, b, c);
		//return priv::ternary_intern_no_vpternlog<K>(a, b, c);
	}

	template<typename T>
	inline constexpr T ternary(const T a, const T b, const T c, const bf_type k)
	{
		return priv::ternary_reduced(a, b, c, k);
	}

	namespace test
	{
		void inline test_equal_sse_equals_avx512()
		{
			std::cout << "test_equal_sse_equals_avx512" << std::endl;

			const auto a1 = _mm_set1_epi8(0b10101010);
			const auto b1 = _mm_set1_epi8(0b11001100);
			const auto c1 = _mm_set1_epi8(0b11110000);

			const auto a2 = _mm512_set1_epi8(0b10101010);
			const auto b2 = _mm512_set1_epi8(0b11001100);
			const auto c2 = _mm512_set1_epi8(0b11110000);

			for (auto i = 0; i <= 0xFF; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a1, b1, c1, i);
				const auto r2 = priv::ternary_not_reduced(a2, b2, c2, i);

				if (r1.m128i_u8[0] != r2.m512i_u8[0])
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "sse:    " << std::bitset<8>(r1.m128i_u8[0]).to_string() << std::endl;
					std::cout << "avx512: " << std::bitset<8>(r2.m512i_u8[0]).to_string() << std::endl;
					static_cast<void>(getchar());
				}
			}
		}
		void inline test_equal_sse_equals_avx2()
		{
			std::cout << "test_equal_sse_equals_avx2" << std::endl;

			const auto a1 = _mm_set1_epi8(0b10101010);
			const auto b1 = _mm_set1_epi8(0b11001100);
			const auto c1 = _mm_set1_epi8(0b11110000);

			const auto a2 = _mm256_set1_epi8(0b10101010);
			const auto b2 = _mm256_set1_epi8(0b11001100);
			const auto c2 = _mm256_set1_epi8(0b11110000);

			for (auto i = 0; i <= 0xFF; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a1, b1, c1, i);
				const auto r2 = priv::ternary_not_reduced(a2, b2, c2, i);

				if (r1.m128i_u8[0] != r2.m256i_u8[0])
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "sse:    " << std::bitset<8>(r1.m128i_u8[0]).to_string() << std::endl;
					std::cout << "avx512: " << std::bitset<8>(r2.m256i_u8[0]).to_string() << std::endl;
					static_cast<void>(getchar());
				}
			}
		}
		void inline test_equal_raw_equals_reduced()
		{
			std::cout << "test_equal_raw_equals_reduced" << std::endl;

			const auto a = _mm_set1_epi8(0b10101010);
			const auto b = _mm_set1_epi8(0b11001100);
			const auto c = _mm_set1_epi8(0b11110000);

			for (auto i = 0; i <= 0xFF; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a, b, c, i);
				const auto r2 = ternary(a, b, c, i);

				if (r1.m128i_u8[0] != r2.m128i_u8[0])
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "not reduced: " << std::bitset<8>(r1.m128i_u8[0]).to_string() << std::endl;
					std::cout << "reduced:     " << std::bitset<8>(r2.m128i_u8[0]).to_string() << std::endl;
					static_cast<void>(getchar());
				}
			}
		}
		void inline test_equal_avx512_equals_avx512raw()
		{
			std::cout << "test_equal_avx512_equals_avx512raw" << std::endl;

			const auto a = _mm512_set1_epi8(0b10101010);
			const auto b = _mm512_set1_epi8(0b11001100);
			const auto c = _mm512_set1_epi8(0b11110000);

			for (auto i = 0; i <= 0xFF; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a, b, c, i);
				const auto r2 = priv::ternary_no_vpternlog(a, b, c, i);

				if (r1.m512i_u8[0] != r2.m512i_u8[0])
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "not reduced: " << std::bitset<8>(r1.m512i_u8[0]).to_string() << std::endl;
					std::cout << "reduced:     " << std::bitset<8>(r2.m512i_u8[0]).to_string() << std::endl;
					static_cast<void>(getchar());
				}
			}
		}
		void inline test_equal_x86_32_equals_sse()
		{
			std::cout << "test_equal_x86_32_equals_sse" << std::endl;

			const auto a1 = _mm_set1_epi8(0b10101010);
			const auto b1 = _mm_set1_epi8(0b11001100);
			const auto c1 = _mm_set1_epi8(0b11110000);

			const unsigned int a2 = 0b10101010;
			const unsigned int b2 = 0b11001100;
			const unsigned int c2 = 0b11110000;

			for (int i = 0; i < 256; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a1, b1, c1, i);
				const auto r2 = priv::ternary_not_reduced(a2, b2, c2, i);

				const auto r1_char = r1.m128i_u8[0];
				const auto r2_char = static_cast<unsigned char>(r2);

				if (r1_char != r2_char)
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "sse:    " << std::bitset<8>(r1_char).to_string() << std::endl;
					std::cout << "x86 32: " << std::bitset<8>(r2_char).to_string() << std::endl;
					static_cast<void>(getchar());
				}
			}
		}
		void inline test_equal_x86_64_equals_sse()
		{
			std::cout << "test_equal_x86_64_equals_sse" << std::endl;

			const auto a1 = _mm_set1_epi8(0b10101010);
			const auto b1 = _mm_set1_epi8(0b11001100);
			const auto c1 = _mm_set1_epi8(0b11110000);

			const unsigned long long a2 = 0b10101010;
			const unsigned long long b2 = 0b11001100;
			const unsigned long long c2 = 0b11110000;

			for (auto i = 0; i <= 0xFF; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a1, b1, c1, i);
				const auto r2 = priv::ternary_not_reduced(a2, b2, c2, i);

				const auto r1_char = r1.m128i_u8[0];
				const auto r2_char = static_cast<unsigned char>(r2);

				if (r1_char != r2_char)
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "sse:    " << std::bitset<8>(r1_char).to_string() << std::endl;
					std::cout << "x86 64: " << std::bitset<8>(r2_char).to_string() << std::endl;
					static_cast<void>(getchar());
				}
			}
		}
		void inline test_equal_bitset_equals_sse()
		{
			std::cout << "test_equal_bitset_equals_sse" << std::endl;

			const auto a1 = std::bitset<8>(0b10101010);
			const auto b1 = std::bitset<8>(0b11001100);
			const auto c1 = std::bitset<8>(0b11110000);

			const unsigned int a2 = 0b10101010;
			const unsigned int b2 = 0b11001100;
			const unsigned int c2 = 0b11110000;

			for (int i = 0; i < 256; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a1, b1, c1, i);
				const auto r2 = priv::ternary_not_reduced(a2, b2, c2, i);

				const auto r1_char = static_cast<unsigned char>(r1.to_ulong());
				const auto r2_char = static_cast<unsigned char>(r2);

				if (r1_char != r2_char)
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "sse:    " << std::bitset<8>(r1_char).to_string() << std::endl;
					std::cout << "x86 32: " << std::bitset<8>(r2_char).to_string() << std::endl;
					static_cast<void>(getchar());
				}
			}
		}


		template <bf_type K>
		void inline test_speed_vpternlog()
		{
			const int n_experiments = 100000;
			const int n_loops = 1;

			const auto a = _mm512_set1_epi8(static_cast<char>(rand()));
			const auto b = _mm512_set1_epi8(static_cast<char>(rand()));
			const auto c = _mm512_set1_epi8(static_cast<char>(rand()));

			__m512i sum1 = _mm512_setzero_si512();
			__m512i sum2 = _mm512_setzero_si512();
			unsigned long long min_duration1 = std::numeric_limits<unsigned long long>::max();
			unsigned long long min_duration2 = std::numeric_limits<unsigned long long>::max();

			for (int experiment = 0; experiment < n_experiments; ++experiment)
			{
				{
					const unsigned long long timing_start = rdtsc();
					sum1 = _mm512_add_epi32(sum1, priv::ternary_intern<K>(a, b, c));
					min_duration1 = std::min(min_duration1, rdtsc() - timing_start);
				}
				{
					const unsigned long long timing_start = rdtsc();
					sum1 = _mm512_add_epi32(sum1, priv::ternary_intern_no_vpternlog<K>(a, b, c));
					min_duration2 = std::min(min_duration2, rdtsc() - timing_start);
				}
			}
			std::cout << "BF3[" << K << "] not_reduced  takes " << std::fixed << std::setprecision(8) << static_cast<float>(min_duration1) / n_loops << " cycles. Result = " << std::to_string(sum1.m512i_u8[0]) << std::endl;
			std::cout << "BF3[" << K << "] no_vpternlog takes " << std::fixed << std::setprecision(8) << static_cast<float>(min_duration2) / n_loops << " cycles. Result = " << std::to_string(sum2.m512i_u8[0]) << std::endl;

		}
		void inline test_speed_vpternlog_all()
		{
			test_speed_vpternlog<0>();
			test_speed_vpternlog<1>();
			test_speed_vpternlog<2>();
			test_speed_vpternlog<3>();
			test_speed_vpternlog<4>();
			test_speed_vpternlog<5>();
			test_speed_vpternlog<6>();
			test_speed_vpternlog<7>();
			test_speed_vpternlog<8>();
			test_speed_vpternlog<9>();
			test_speed_vpternlog<10>();
			test_speed_vpternlog<11>();
			test_speed_vpternlog<12>();
			test_speed_vpternlog<13>();
			test_speed_vpternlog<14>();
			test_speed_vpternlog<15>();
			test_speed_vpternlog<16>();
			test_speed_vpternlog<17>();
			test_speed_vpternlog<18>();
			test_speed_vpternlog<19>();
			test_speed_vpternlog<20>();
		}


		void inline tests()
		{
			test_equal_sse_equals_avx512();
			test_equal_sse_equals_avx2();
			test_equal_x86_32_equals_sse();
			test_equal_x86_64_equals_sse();
			test_equal_bitset_equals_sse();
			test_equal_raw_equals_reduced();
			test_equal_avx512_equals_avx512raw();



			//test_speed_vpternlog_all();
		}
	}
}
