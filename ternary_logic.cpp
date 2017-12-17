#pragma once
#include <iostream>		// for cout

#include <bitset>
#include <intrin.h>
#include "ternary_sse.cpp"
#include "ternary_avx2.cpp"

namespace ternarylogic
{
	namespace priv
	{
		template<unsigned k>
		__forceinline __m128i ternary(const __m128i a, const __m128i b, const __m128i c)
		{
			return ternarylogic::sse::ternary<k>(a, b, c);
		}

		template<unsigned k>
		__forceinline __m256i ternary(const __m256i a, const __m256i b, const __m256i c)
		{
			return ternarylogic::avx2::ternary<k>(a, b, c);
		}

		template<unsigned k>
		__forceinline __m512i ternary(const __m512i a, const __m512i b, const __m512i c)
		{
			return _mm512_ternarylogic_epi64(a, b, c, k);
		}

		template<typename T>
		inline T ternary_not_reduced(const T a, const T b, const T c, const int i)
		{
			switch (i)
			{
				case 0: return ternary<0>(a, b, c);
				case 1: return ternary<1>(a, b, c);
				case 2: return ternary<2>(a, b, c);
				case 3: return ternary<3>(a, b, c);
				case 4: return ternary<4>(a, b, c);
				case 5: return ternary<5>(a, b, c);
				case 6: return ternary<6>(a, b, c);
				case 7: return ternary<7>(a, b, c);
				case 8: return ternary<8>(a, b, c);
				case 9: return ternary<9>(a, b, c);

				case 10: return ternary<10>(a, b, c);
				case 11: return ternary<11>(a, b, c);
				case 12: return ternary<12>(a, b, c);
				case 13: return ternary<13>(a, b, c);
				case 14: return ternary<14>(a, b, c);
				case 15: return ternary<15>(a, b, c);
				case 16: return ternary<16>(a, b, c);
				case 17: return ternary<17>(a, b, c);
				case 18: return ternary<18>(a, b, c);
				case 19: return ternary<19>(a, b, c);

				case 20: return ternary<20>(a, b, c);
				case 21: return ternary<21>(a, b, c);
				case 22: return ternary<22>(a, b, c);
				case 23: return ternary<23>(a, b, c);
				case 24: return ternary<24>(a, b, c);
				case 25: return ternary<25>(a, b, c);
				case 26: return ternary<26>(a, b, c);
				case 27: return ternary<27>(a, b, c);
				case 28: return ternary<28>(a, b, c);
				case 29: return ternary<29>(a, b, c);

				case 30: return ternary<30>(a, b, c);
				case 31: return ternary<31>(a, b, c);
				case 32: return ternary<32>(a, b, c);
				case 33: return ternary<33>(a, b, c);
				case 34: return ternary<34>(a, b, c);
				case 35: return ternary<35>(a, b, c);
				case 36: return ternary<36>(a, b, c);
				case 37: return ternary<37>(a, b, c);
				case 38: return ternary<38>(a, b, c);
				case 39: return ternary<39>(a, b, c);

				case 40: return ternary<40>(a, b, c);
				case 41: return ternary<41>(a, b, c);
				case 42: return ternary<42>(a, b, c);
				case 43: return ternary<43>(a, b, c);
				case 44: return ternary<44>(a, b, c);
				case 45: return ternary<45>(a, b, c);
				case 46: return ternary<46>(a, b, c);
				case 47: return ternary<47>(a, b, c);
				case 48: return ternary<48>(a, b, c);
				case 49: return ternary<49>(a, b, c);

				case 50: return ternary<50>(a, b, c);
				case 51: return ternary<51>(a, b, c);
				case 52: return ternary<52>(a, b, c);
				case 53: return ternary<53>(a, b, c);
				case 54: return ternary<54>(a, b, c);
				case 55: return ternary<55>(a, b, c);
				case 56: return ternary<56>(a, b, c);
				case 57: return ternary<57>(a, b, c);
				case 58: return ternary<58>(a, b, c);
				case 59: return ternary<59>(a, b, c);

				case 60: return ternary<60>(a, b, c);
				case 61: return ternary<61>(a, b, c);
				case 62: return ternary<62>(a, b, c);
				case 63: return ternary<63>(a, b, c);
				case 64: return ternary<64>(a, b, c);
				case 65: return ternary<65>(a, b, c);
				case 66: return ternary<66>(a, b, c);
				case 67: return ternary<67>(a, b, c);
				case 68: return ternary<68>(a, b, c);
				case 69: return ternary<69>(a, b, c);

				case 70: return ternary<70>(a, b, c);
				case 71: return ternary<71>(a, b, c);
				case 72: return ternary<72>(a, b, c);
				case 73: return ternary<73>(a, b, c);
				case 74: return ternary<74>(a, b, c);
				case 75: return ternary<75>(a, b, c);
				case 76: return ternary<76>(a, b, c);
				case 77: return ternary<77>(a, b, c);
				case 78: return ternary<78>(a, b, c);
				case 79: return ternary<79>(a, b, c);

				case 80: return ternary<80>(a, b, c);
				case 81: return ternary<81>(a, b, c);
				case 82: return ternary<82>(a, b, c);
				case 83: return ternary<83>(a, b, c);
				case 84: return ternary<84>(a, b, c);
				case 85: return ternary<85>(a, b, c);
				case 86: return ternary<86>(a, b, c);
				case 87: return ternary<87>(a, b, c);
				case 88: return ternary<88>(a, b, c);
				case 89: return ternary<89>(a, b, c);

				case 90: return ternary<90>(a, b, c);
				case 91: return ternary<91>(a, b, c);
				case 92: return ternary<92>(a, b, c);
				case 93: return ternary<93>(a, b, c);
				case 94: return ternary<94>(a, b, c);
				case 95: return ternary<95>(a, b, c);
				case 96: return ternary<96>(a, b, c);
				case 97: return ternary<97>(a, b, c);
				case 98: return ternary<98>(a, b, c);
				case 99: return ternary<99>(a, b, c);

				case 100: return ternary<100>(a, b, c);
				case 101: return ternary<101>(a, b, c);
				case 102: return ternary<102>(a, b, c);
				case 103: return ternary<103>(a, b, c);
				case 104: return ternary<104>(a, b, c);
				case 105: return ternary<105>(a, b, c);
				case 106: return ternary<106>(a, b, c);
				case 107: return ternary<107>(a, b, c);
				case 108: return ternary<108>(a, b, c);
				case 109: return ternary<109>(a, b, c);

				case 110: return ternary<110>(a, b, c);
				case 111: return ternary<111>(a, b, c);
				case 112: return ternary<112>(a, b, c);
				case 113: return ternary<113>(a, b, c);
				case 114: return ternary<114>(a, b, c);
				case 115: return ternary<115>(a, b, c);
				case 116: return ternary<116>(a, b, c);
				case 117: return ternary<117>(a, b, c);
				case 118: return ternary<118>(a, b, c);
				case 119: return ternary<119>(a, b, c);

				case 120: return ternary<120>(a, b, c);
				case 121: return ternary<121>(a, b, c);
				case 122: return ternary<122>(a, b, c);
				case 123: return ternary<123>(a, b, c);
				case 124: return ternary<124>(a, b, c);
				case 125: return ternary<125>(a, b, c);
				case 126: return ternary<126>(a, b, c);
				case 127: return ternary<127>(a, b, c);
				case 128: return ternary<128>(a, b, c);
				case 129: return ternary<129>(a, b, c);

				case 130: return ternary<130>(a, b, c);
				case 131: return ternary<131>(a, b, c);
				case 132: return ternary<132>(a, b, c);
				case 133: return ternary<133>(a, b, c);
				case 134: return ternary<134>(a, b, c);
				case 135: return ternary<135>(a, b, c);
				case 136: return ternary<136>(a, b, c);
				case 137: return ternary<137>(a, b, c);
				case 138: return ternary<138>(a, b, c);
				case 139: return ternary<139>(a, b, c);

				case 140: return ternary<140>(a, b, c);
				case 141: return ternary<141>(a, b, c);
				case 142: return ternary<142>(a, b, c);
				case 143: return ternary<143>(a, b, c);
				case 144: return ternary<144>(a, b, c);
				case 145: return ternary<145>(a, b, c);
				case 146: return ternary<146>(a, b, c);
				case 147: return ternary<147>(a, b, c);
				case 148: return ternary<148>(a, b, c);
				case 149: return ternary<149>(a, b, c);

				case 150: return ternary<150>(a, b, c);
				case 151: return ternary<151>(a, b, c);
				case 152: return ternary<152>(a, b, c);
				case 153: return ternary<153>(a, b, c);
				case 154: return ternary<154>(a, b, c);
				case 155: return ternary<155>(a, b, c);
				case 156: return ternary<156>(a, b, c);
				case 157: return ternary<157>(a, b, c);
				case 158: return ternary<158>(a, b, c);
				case 159: return ternary<159>(a, b, c);

				case 160: return ternary<160>(a, b, c);
				case 161: return ternary<161>(a, b, c);
				case 162: return ternary<162>(a, b, c);
				case 163: return ternary<163>(a, b, c);
				case 164: return ternary<164>(a, b, c);
				case 165: return ternary<165>(a, b, c);
				case 166: return ternary<166>(a, b, c);
				case 167: return ternary<167>(a, b, c);
				case 168: return ternary<168>(a, b, c);
				case 169: return ternary<169>(a, b, c);

				case 170: return ternary<170>(a, b, c);
				case 171: return ternary<171>(a, b, c);
				case 172: return ternary<172>(a, b, c);
				case 173: return ternary<173>(a, b, c);
				case 174: return ternary<174>(a, b, c);
				case 175: return ternary<175>(a, b, c);
				case 176: return ternary<176>(a, b, c);
				case 177: return ternary<177>(a, b, c);
				case 178: return ternary<178>(a, b, c);
				case 179: return ternary<179>(a, b, c);

				case 180: return ternary<180>(a, b, c);
				case 181: return ternary<181>(a, b, c);
				case 182: return ternary<182>(a, b, c);
				case 183: return ternary<183>(a, b, c);
				case 184: return ternary<184>(a, b, c);
				case 185: return ternary<185>(a, b, c);
				case 186: return ternary<186>(a, b, c);
				case 187: return ternary<187>(a, b, c);
				case 188: return ternary<188>(a, b, c);
				case 189: return ternary<189>(a, b, c);

				case 190: return ternary<190>(a, b, c);
				case 191: return ternary<191>(a, b, c);
				case 192: return ternary<192>(a, b, c);
				case 193: return ternary<193>(a, b, c);
				case 194: return ternary<194>(a, b, c);
				case 195: return ternary<195>(a, b, c);
				case 196: return ternary<196>(a, b, c);
				case 197: return ternary<197>(a, b, c);
				case 198: return ternary<198>(a, b, c);
				case 199: return ternary<199>(a, b, c);

				case 200: return ternary<200>(a, b, c);
				case 201: return ternary<201>(a, b, c);
				case 202: return ternary<202>(a, b, c);
				case 203: return ternary<203>(a, b, c);
				case 204: return ternary<204>(a, b, c);
				case 205: return ternary<205>(a, b, c);
				case 206: return ternary<206>(a, b, c);
				case 207: return ternary<207>(a, b, c);
				case 208: return ternary<208>(a, b, c);
				case 209: return ternary<209>(a, b, c);

				case 210: return ternary<210>(a, b, c);
				case 211: return ternary<211>(a, b, c);
				case 212: return ternary<212>(a, b, c);
				case 213: return ternary<213>(a, b, c);
				case 214: return ternary<214>(a, b, c);
				case 215: return ternary<215>(a, b, c);
				case 216: return ternary<216>(a, b, c);
				case 217: return ternary<217>(a, b, c);
				case 218: return ternary<218>(a, b, c);
				case 219: return ternary<219>(a, b, c);

				case 220: return ternary<220>(a, b, c);
				case 221: return ternary<221>(a, b, c);
				case 222: return ternary<222>(a, b, c);
				case 223: return ternary<223>(a, b, c);
				case 224: return ternary<224>(a, b, c);
				case 225: return ternary<225>(a, b, c);
				case 226: return ternary<226>(a, b, c);
				case 227: return ternary<227>(a, b, c);
				case 228: return ternary<228>(a, b, c);
				case 229: return ternary<229>(a, b, c);

				case 230: return ternary<230>(a, b, c);
				case 231: return ternary<231>(a, b, c);
				case 232: return ternary<232>(a, b, c);
				case 233: return ternary<233>(a, b, c);
				case 234: return ternary<234>(a, b, c);
				case 235: return ternary<235>(a, b, c);
				case 236: return ternary<236>(a, b, c);
				case 237: return ternary<237>(a, b, c);
				case 238: return ternary<238>(a, b, c);
				case 239: return ternary<239>(a, b, c);

				case 240: return ternary<240>(a, b, c);
				case 241: return ternary<241>(a, b, c);
				case 242: return ternary<242>(a, b, c);
				case 243: return ternary<243>(a, b, c);
				case 244: return ternary<244>(a, b, c);
				case 245: return ternary<245>(a, b, c);
				case 246: return ternary<246>(a, b, c);
				case 247: return ternary<247>(a, b, c);
				case 248: return ternary<248>(a, b, c);
				case 249: return ternary<249>(a, b, c);

				case 250: return ternary<250>(a, b, c);
				case 251: return ternary<251>(a, b, c);
				case 252: return ternary<252>(a, b, c);
				case 253: return ternary<253>(a, b, c);
				case 254: return ternary<254>(a, b, c);
				case 255: return ternary<255>(a, b, c);

				default:  return ternary<0>(a, b, c);
			}
		}
 	}
	
	template <typename T>
	inline T ternary(const T a, const T b, const T c, const int i)
	{
		// method is generated with test::create_method_reduced_ternary()
		switch (i)
		{
			case 0: return priv::ternary<0>(a, b, c);
			case 1: return priv::ternary<1>(a, b, c);
			case 2: return priv::ternary<2>(a, b, c);
			case 3: return priv::ternary<3>(a, b, c);
			case 4: return priv::ternary<2>(a, c, b);
			case 5: return priv::ternary<3>(a, c, b);
			case 6: return priv::ternary<6>(a, b, c);
			case 7: return priv::ternary<7>(a, b, c);
			case 8: return priv::ternary<8>(a, b, c);
			case 9: return priv::ternary<9>(a, b, c);
			case 10: return priv::ternary<10>(a, b, c);
			case 11: return priv::ternary<11>(a, b, c);
			case 12: return priv::ternary<10>(a, c, b);
			case 13: return priv::ternary<11>(a, c, b);
			case 14: return priv::ternary<14>(a, b, c);
			case 15: return priv::ternary<15>(a, b, c);
			case 16: return priv::ternary<2>(c, b, a);
			case 17: return priv::ternary<3>(c, b, a);
			case 18: return priv::ternary<6>(b, a, c);
			case 19: return priv::ternary<7>(b, a, c);
			case 20: return priv::ternary<6>(c, b, a);
			case 21: return priv::ternary<7>(c, b, a);
			case 22: return priv::ternary<22>(a, b, c);
			case 23: return priv::ternary<23>(a, b, c);
			case 24: return priv::ternary<24>(a, b, c);
			case 25: return priv::ternary<25>(a, b, c);
			case 26: return priv::ternary<26>(a, b, c);
			case 27: return priv::ternary<27>(a, b, c);
			case 28: return priv::ternary<26>(a, c, b);
			case 29: return priv::ternary<27>(a, c, b);
			case 30: return priv::ternary<30>(a, b, c);
			case 31: return priv::ternary<31>(a, b, c);
			case 32: return priv::ternary<8>(b, a, c);
			case 33: return priv::ternary<9>(b, a, c);
			case 34: return priv::ternary<10>(b, a, c);
			case 35: return priv::ternary<11>(b, a, c);
			case 36: return priv::ternary<24>(b, a, c);
			case 37: return priv::ternary<25>(b, a, c);
			case 38: return priv::ternary<26>(b, a, c);
			case 39: return priv::ternary<27>(b, a, c);
			case 40: return priv::ternary<40>(a, b, c);
			case 41: return priv::ternary<41>(a, b, c);
			case 42: return priv::ternary<42>(a, b, c);
			case 43: return priv::ternary<43>(a, b, c);
			case 44: return priv::ternary<44>(a, b, c);
			case 45: return priv::ternary<45>(a, b, c);
			case 46: return priv::ternary<46>(a, b, c);
			case 47: return priv::ternary<47>(a, b, c);
			case 48: return priv::ternary<10>(b, c, a);
			case 49: return priv::ternary<11>(b, c, a);
			case 50: return priv::ternary<14>(b, a, c);
			case 51: return priv::ternary<15>(b, a, c);
			case 52: return priv::ternary<26>(b, c, a);
			case 53: return priv::ternary<27>(b, c, a);
			case 54: return priv::ternary<30>(b, a, c);
			case 55: return priv::ternary<31>(b, a, c);
			case 56: return priv::ternary<44>(b, a, c);
			case 57: return priv::ternary<45>(b, a, c);
			case 58: return priv::ternary<46>(b, a, c);
			case 59: return priv::ternary<47>(b, a, c);
			case 60: return priv::ternary<60>(a, b, c);
			case 61: return priv::ternary<61>(a, b, c);
			case 62: return priv::ternary<62>(a, b, c);
			case 63: return priv::ternary<63>(a, b, c);
			case 64: return priv::ternary<8>(c, b, a);
			case 65: return priv::ternary<9>(c, b, a);
			case 66: return priv::ternary<24>(c, b, a);
			case 67: return priv::ternary<25>(c, b, a);
			case 68: return priv::ternary<10>(c, a, b);
			case 69: return priv::ternary<11>(c, a, b);
			case 70: return priv::ternary<26>(c, a, b);
			case 71: return priv::ternary<27>(c, a, b);
			case 72: return priv::ternary<40>(a, c, b);
			case 73: return priv::ternary<41>(a, c, b);
			case 74: return priv::ternary<44>(a, c, b);
			case 75: return priv::ternary<45>(a, c, b);
			case 76: return priv::ternary<42>(a, c, b);
			case 77: return priv::ternary<43>(a, c, b);
			case 78: return priv::ternary<46>(a, c, b);
			case 79: return priv::ternary<47>(a, c, b);
			case 80: return priv::ternary<10>(c, b, a);
			case 81: return priv::ternary<11>(c, b, a);
			case 82: return priv::ternary<26>(c, b, a);
			case 83: return priv::ternary<27>(c, b, a);
			case 84: return priv::ternary<14>(c, b, a);
			case 85: return priv::ternary<15>(c, b, a);
			case 86: return priv::ternary<30>(c, b, a);
			case 87: return priv::ternary<31>(c, b, a);
			case 88: return priv::ternary<44>(c, a, b);
			case 89: return priv::ternary<45>(c, a, b);
			case 90: return priv::ternary<60>(a, c, b);
			case 91: return priv::ternary<61>(a, c, b);
			case 92: return priv::ternary<46>(c, a, b);
			case 93: return priv::ternary<47>(c, a, b);
			case 94: return priv::ternary<62>(a, c, b);
			case 95: return priv::ternary<63>(a, c, b);
			case 96: return priv::ternary<40>(c, b, a);
			case 97: return priv::ternary<41>(c, b, a);
			case 98: return priv::ternary<44>(b, c, a);
			case 99: return priv::ternary<45>(b, c, a);
			case 100: return priv::ternary<44>(c, b, a);
			case 101: return priv::ternary<45>(c, b, a);
			case 102: return priv::ternary<60>(c, b, a);
			case 103: return priv::ternary<61>(c, b, a);
			case 104: return priv::ternary<104>(a, b, c);
			case 105: return priv::ternary<105>(a, b, c);
			case 106: return priv::ternary<106>(a, b, c);
			case 107: return priv::ternary<107>(a, b, c);
			case 108: return priv::ternary<106>(a, c, b);
			case 109: return priv::ternary<107>(a, c, b);
			case 110: return priv::ternary<110>(a, b, c);
			case 111: return priv::ternary<111>(a, b, c);
			case 112: return priv::ternary<42>(c, b, a);
			case 113: return priv::ternary<43>(c, b, a);
			case 114: return priv::ternary<46>(b, c, a);
			case 115: return priv::ternary<47>(b, c, a);
			case 116: return priv::ternary<46>(c, b, a);
			case 117: return priv::ternary<47>(c, b, a);
			case 118: return priv::ternary<62>(c, b, a);
			case 119: return priv::ternary<63>(c, b, a);
			case 120: return priv::ternary<106>(c, b, a);
			case 121: return priv::ternary<107>(c, b, a);
			case 122: return priv::ternary<110>(b, a, c);
			case 123: return priv::ternary<111>(b, a, c);
			case 124: return priv::ternary<110>(c, b, a);
			case 125: return priv::ternary<111>(c, b, a);
			case 126: return priv::ternary<126>(a, b, c);
			case 127: return priv::ternary<127>(a, b, c);
			case 128: return priv::ternary<128>(a, b, c);
			case 129: return priv::ternary<129>(a, b, c);
			case 130: return priv::ternary<130>(a, b, c);
			case 131: return priv::ternary<131>(a, b, c);
			case 132: return priv::ternary<130>(a, c, b);
			case 133: return priv::ternary<131>(a, c, b);
			case 134: return priv::ternary<134>(a, b, c);
			case 135: return priv::ternary<135>(a, b, c);
			case 136: return priv::ternary<136>(a, b, c);
			case 137: return priv::ternary<137>(a, b, c);
			case 138: return priv::ternary<138>(a, b, c);
			case 139: return priv::ternary<139>(a, b, c);
			case 140: return priv::ternary<138>(a, c, b);
			case 141: return priv::ternary<139>(a, c, b);
			case 142: return priv::ternary<142>(a, b, c);
			case 143: return priv::ternary<143>(a, b, c);
			case 144: return priv::ternary<130>(c, b, a);
			case 145: return priv::ternary<131>(c, b, a);
			case 146: return priv::ternary<134>(b, a, c);
			case 147: return priv::ternary<135>(b, a, c);
			case 148: return priv::ternary<134>(c, b, a);
			case 149: return priv::ternary<135>(c, b, a);
			case 150: return priv::ternary<150>(a, b, c);
			case 151: return priv::ternary<151>(a, b, c);
			case 152: return priv::ternary<152>(a, b, c);
			case 153: return priv::ternary<153>(a, b, c);
			case 154: return priv::ternary<154>(a, b, c);
			case 155: return priv::ternary<155>(a, b, c);
			case 156: return priv::ternary<154>(a, c, b);
			case 157: return priv::ternary<155>(a, c, b);
			case 158: return priv::ternary<158>(a, b, c);
			case 159: return priv::ternary<159>(a, b, c);
			case 160: return priv::ternary<136>(b, a, c);
			case 161: return priv::ternary<137>(b, a, c);
			case 162: return priv::ternary<138>(b, a, c);
			case 163: return priv::ternary<139>(b, a, c);
			case 164: return priv::ternary<152>(b, a, c);
			case 165: return priv::ternary<153>(b, a, c);
			case 166: return priv::ternary<154>(b, a, c);
			case 167: return priv::ternary<155>(b, a, c);
			case 168: return priv::ternary<168>(a, b, c);
			case 169: return priv::ternary<169>(a, b, c);
			case 170: return priv::ternary<170>(a, b, c);
			case 171: return priv::ternary<171>(a, b, c);
			case 172: return priv::ternary<172>(a, b, c);
			case 173: return priv::ternary<173>(a, b, c);
			case 174: return priv::ternary<174>(a, b, c);
			case 175: return priv::ternary<175>(a, b, c);
			case 176: return priv::ternary<138>(b, c, a);
			case 177: return priv::ternary<139>(b, c, a);
			case 178: return priv::ternary<142>(b, a, c);
			case 179: return priv::ternary<143>(b, a, c);
			case 180: return priv::ternary<154>(b, c, a);
			case 181: return priv::ternary<155>(b, c, a);
			case 182: return priv::ternary<158>(b, a, c);
			case 183: return priv::ternary<159>(b, a, c);
			case 184: return priv::ternary<172>(b, a, c);
			case 185: return priv::ternary<173>(b, a, c);
			case 186: return priv::ternary<174>(b, a, c);
			case 187: return priv::ternary<175>(b, a, c);
			case 188: return priv::ternary<188>(a, b, c);
			case 189: return priv::ternary<189>(a, b, c);
			case 190: return priv::ternary<190>(a, b, c);
			case 191: return priv::ternary<191>(a, b, c);
			case 192: return priv::ternary<136>(c, b, a);
			case 193: return priv::ternary<137>(c, b, a);
			case 194: return priv::ternary<152>(c, b, a);
			case 195: return priv::ternary<153>(c, b, a);
			case 196: return priv::ternary<138>(c, a, b);
			case 197: return priv::ternary<139>(c, a, b);
			case 198: return priv::ternary<154>(c, a, b);
			case 199: return priv::ternary<155>(c, a, b);
			case 200: return priv::ternary<168>(a, c, b);
			case 201: return priv::ternary<169>(a, c, b);
			case 202: return priv::ternary<172>(a, c, b);
			case 203: return priv::ternary<173>(a, c, b);
			case 204: return priv::ternary<170>(a, c, b);
			case 205: return priv::ternary<171>(a, c, b);
			case 206: return priv::ternary<174>(a, c, b);
			case 207: return priv::ternary<175>(a, c, b);
			case 208: return priv::ternary<138>(c, b, a);
			case 209: return priv::ternary<139>(c, b, a);
			case 210: return priv::ternary<154>(c, b, a);
			case 211: return priv::ternary<155>(c, b, a);
			case 212: return priv::ternary<142>(c, b, a);
			case 213: return priv::ternary<143>(c, b, a);
			case 214: return priv::ternary<158>(c, b, a);
			case 215: return priv::ternary<159>(c, b, a);
			case 216: return priv::ternary<172>(c, a, b);
			case 217: return priv::ternary<173>(c, a, b);
			case 218: return priv::ternary<188>(a, c, b);
			case 219: return priv::ternary<189>(a, c, b);
			case 220: return priv::ternary<174>(c, a, b);
			case 221: return priv::ternary<175>(c, a, b);
			case 222: return priv::ternary<190>(a, c, b);
			case 223: return priv::ternary<191>(a, c, b);
			case 224: return priv::ternary<168>(c, b, a);
			case 225: return priv::ternary<169>(c, b, a);
			case 226: return priv::ternary<172>(b, c, a);
			case 227: return priv::ternary<173>(b, c, a);
			case 228: return priv::ternary<172>(c, b, a);
			case 229: return priv::ternary<173>(c, b, a);
			case 230: return priv::ternary<188>(c, b, a);
			case 231: return priv::ternary<189>(c, b, a);
			case 232: return priv::ternary<232>(a, b, c);
			case 233: return priv::ternary<233>(a, b, c);
			case 234: return priv::ternary<234>(a, b, c);
			case 235: return priv::ternary<235>(a, b, c);
			case 236: return priv::ternary<234>(a, c, b);
			case 237: return priv::ternary<235>(a, c, b);
			case 238: return priv::ternary<238>(a, b, c);
			case 239: return priv::ternary<239>(a, b, c);
			case 240: return priv::ternary<170>(c, b, a);
			case 241: return priv::ternary<171>(c, b, a);
			case 242: return priv::ternary<174>(b, c, a);
			case 243: return priv::ternary<175>(b, c, a);
			case 244: return priv::ternary<174>(c, b, a);
			case 245: return priv::ternary<175>(c, b, a);
			case 246: return priv::ternary<190>(c, b, a);
			case 247: return priv::ternary<191>(c, b, a);
			case 248: return priv::ternary<234>(c, b, a);
			case 249: return priv::ternary<235>(c, b, a);
			case 250: return priv::ternary<238>(b, a, c);
			case 251: return priv::ternary<239>(b, a, c);
			case 252: return priv::ternary<238>(c, b, a);
			case 253: return priv::ternary<239>(c, b, a);
			case 254: return priv::ternary<254>(a, b, c);
			case 255: return priv::ternary<255>(a, b, c);
			default: return priv::ternary<0>(a, b, c);
		}
	}

	namespace test
	{
		// create the ternary method
		void create_method_reduced_ternary()
		{
			const auto a = _mm_set1_epi8(0b10101010);
			const auto b = _mm_set1_epi8(0b11001100);
			const auto c = _mm_set1_epi8(0b11110000);

			std::cout << "	template <typename T>" << std::endl;
			std::cout << "	inline T ternary(const T a, const T b, const T c, const int i)" << std::endl;
			std::cout << "	{" << std::endl;
			std::cout << "		switch (i)" << std::endl;
			std::cout << "		{" << std::endl;

			for (int i = 0; i < 256; ++i)
			{
				const auto r_abc = priv::ternary_not_reduced(a, b, c, i);
				bool found_rewrite = false;

				for (int j = 0; j < i; ++j)
				{
					if (r_abc.m128i_u8[0] == priv::ternary_not_reduced(b, a, c, j).m128i_u8[0])
					{
						std::cout << "			case " << i << ": return priv::ternary<" << j << ">(b, a, c);" << std::endl;
						found_rewrite = true;
					}
					else if (r_abc.m128i_u8[0] == priv::ternary_not_reduced(a, c, b, j).m128i_u8[0])
					{
						std::cout << "			case " << i << ": return priv::ternary<" << j << ">(a, c, b);" << std::endl;
						found_rewrite = true;
					}
					else if (r_abc.m128i_u8[0] == priv::ternary_not_reduced(c, b, a, j).m128i_u8[0])
					{
						std::cout << "			case " << i << ": return priv::ternary<" << j << ">(c, b, a);" << std::endl;
						found_rewrite = true;
					}
					else if (r_abc.m128i_u8[0] == priv::ternary_not_reduced(c, a, b, j).m128i_u8[0])
					{
						std::cout << "			case " << i << ": return priv::ternary<" << j << ">(c, a, b);" << std::endl;
						found_rewrite = true;
					}
					else if (r_abc.m128i_u8[0] == priv::ternary_not_reduced(b, c, a, j).m128i_u8[0])
					{
						std::cout << "			case " << i << ": return priv::ternary<" << j << ">(b, c, a);" << std::endl;
						found_rewrite = true;
					}
					if (found_rewrite) break;
				}
				if (!found_rewrite)
				{
					std::cout << "			case " << i << ": return priv::ternary<" << i << ">(a, b, c);" << std::endl;
				}
			}
			
			std::cout << "			default: return priv::ternary<0>(a, b, c);" << std::endl;
			std::cout << "		}" << std::endl;
			std::cout << "	}" << std::endl;
		}

		void test_equal_sse_equals_avx512()
		{
			const auto a1 = _mm_set1_epi8(0b10101010);
			const auto b1 = _mm_set1_epi8(0b11001100);
			const auto c1 = _mm_set1_epi8(0b11110000);

			const auto a2 = _mm512_set1_epi8(0b10101010);
			const auto b2 = _mm512_set1_epi8(0b11001100);
			const auto c2 = _mm512_set1_epi8(0b11110000);

			for (int i = 0; i < 256; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a1, b1, c1, i);
				const auto r2 = priv::ternary_not_reduced(a2, b2, c2, i);

				if (r1.m128i_u8[0] != r2.m512i_u8[0])
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "sse:    " << std::bitset<8>(r1.m128i_u8[0]).to_string() << std::endl;
					std::cout << "avx512: " << std::bitset<8>(r2.m512i_u8[0]).to_string() << std::endl;
					getchar();
				}
			}
		}
		void test_equal_sse_equals_avx2()
		{
			const auto a1 = _mm_set1_epi8(0b10101010);
			const auto b1 = _mm_set1_epi8(0b11001100);
			const auto c1 = _mm_set1_epi8(0b11110000);

			const auto a2 = _mm256_set1_epi8(0b10101010);
			const auto b2 = _mm256_set1_epi8(0b11001100);
			const auto c2 = _mm256_set1_epi8(0b11110000);

			for (int i = 0; i < 256; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a1, b1, c1, i);
				const auto r2 = priv::ternary_not_reduced(a2, b2, c2, i);

				if (r1.m128i_u8[0] != r2.m256i_u8[0])
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "sse:    " << std::bitset<8>(r1.m128i_u8[0]).to_string() << std::endl;
					std::cout << "avx512: " << std::bitset<8>(r2.m256i_u8[0]).to_string() << std::endl;
					getchar();
				}
			}
		}
		void test_equal_raw_equals_reduced()
		{
			const auto a = _mm_set1_epi8(0b10101010);
			const auto b = _mm_set1_epi8(0b11001100);
			const auto c = _mm_set1_epi8(0b11110000);

			for (int i = 0; i < 256; ++i)
			{
				const auto r1 = priv::ternary_not_reduced(a, b, c, i);
				const auto r2 = ternary(a, b, c, i);

				if (r1.m128i_u8[0] != r2.m128i_u8[0])
				{
					std::cout << "NOT EQUAL!" << std::endl;
					std::cout << "i = " << i << std::endl;
					std::cout << "not reduced: " << std::bitset<8>(r1.m128i_u8[0]).to_string() << std::endl;
					std::cout << "reduced:     " << std::bitset<8>(r2.m128i_u8[0]).to_string() << std::endl;
					getchar();
				}
			}
		}
		void tests()
		{
			test_equal_sse_equals_avx512();
			test_equal_sse_equals_avx2();
			test_equal_raw_equals_reduced();
		}
	}
}

// main for testing
int main()
{
	ternarylogic::test::tests();
	//ternarylogic::create_method_reduced_ternary();
	printf("\nPress RETURN to finish:");
	getchar();
	return 0;

}
