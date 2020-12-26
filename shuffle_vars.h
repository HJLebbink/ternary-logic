#pragma once
#include <set>
#include <iostream>		// for cout

#include "ternary_logic.cpp"


namespace ternarylogic::swap
{
	namespace 
	{
		[[nodiscard]] inline constexpr int shuffle_bits(const int i, const int pos7, const int pos6, const int pos5, const int pos4, const int pos3, const int pos2, const int pos1, const int pos0) noexcept
		{
			const int b0 = (i >> pos0) & 1;
			const int b1 = (i >> pos1) & 1;
			const int b2 = (i >> pos2) & 1;
			const int b3 = (i >> pos3) & 1;
			const int b4 = (i >> pos4) & 1;
			const int b5 = (i >> pos5) & 1;
			const int b6 = (i >> pos6) & 1;
			const int b7 = (i >> pos7) & 1;

			return (b7 << 7) | (b6 << 6) | (b5 << 5) | (b4 << 4) | (b3 << 3) | (b2 << 2) | (b1 << 1) | b0;
		}
	}

	/*
	abc		bac		acb		cba		cab		bca
	000=0	000=0	000=0	000=0	000=0	000=0
	001=1	001=1	010=2	100=4	100=4	010=2
	010=2	100=4	001=1	010=2	001=1	100=4
	011=3	101=5	011=3	110=6	101=5	110=6
	100=4	010=2	100=4	001=1	010=2	001=1
	101=5	011=3	110=6	101=5	110=6	011=3
	110=6	110=6	101=5	011=3	011=3	101=5
	111=7	111=7	111=7	111=7	111=7	111=7
	*/

	/// <summary>
	/// Update the provided Boolean Function for the variable shuffle from abc to abc
	/// </summary>
	/// <param name="bf">Boolean Function to be updated</param>
	/// <returns>The Boolean Function for the variable shuffle from abc to abc</returns>
	[[nodiscard]] inline constexpr int shuffle_vars_abc(const int bf) noexcept
	{
		return bf;
	}

	/// <summary>
	/// Update the provided Boolean Function for the variable shuffle from abc to bac
	/// </summary>
	/// <param name="bf">Boolean Function to be updated</param>
	/// <returns>The Boolean Function for the variable shuffle from abc to bac</returns>
	[[nodiscard]] inline constexpr int shuffle_vars_bac(const int bf) noexcept
	{
		return shuffle_bits(bf, 7, 6, 3, 2, 5, 4, 1, 0);
	}

	/// <summary>
	/// Update the provided Boolean Function for the variable shuffle from abc to acb
	/// </summary>
	/// <param name="bf">Boolean Function to be updated</param>
	/// <returns>The Boolean Function for the variable shuffle from abc to acb</returns>
	[[nodiscard]] inline constexpr int shuffle_vars_acb(const int bf) noexcept
	{
		return shuffle_bits(bf, 7, 5, 6, 4, 3, 1, 2, 0);
	}

	/// <summary>
	/// Update the provided Boolean Function for the variable shuffle from abc to cba
	/// </summary>
	/// <param name="bf">Boolean Function to be updated</param>
	/// <returns>The Boolean Function for the variable shuffle from abc to cba</returns>
	[[nodiscard]] inline constexpr int shuffle_vars_cba(const int bf) noexcept
	{
		return shuffle_bits(bf, 7, 3, 5, 1, 6, 2, 4, 0);
	}

	/// <summary>
	/// Update the provided Boolean Function for the variable shuffle from abc to cab
	/// </summary>
	/// <param name="bf">Boolean Function to be updated</param>
	/// <returns>The Boolean Function for the variable shuffle from abc to cab</returns>
	[[nodiscard]] inline constexpr int shuffle_vars_cab(const int bf) noexcept
	{
		//return detail::shuffle_bits(i, 7, 3, 6, 2, 5, 1, 4, 0); // TODO find why bca and cab shuffle is switched??
		return shuffle_bits(bf, 7, 5, 3, 1, 6, 4, 2, 0);
	}

	/// <summary>
	/// Update the provided Boolean Function for the variable shuffle from abc to bca
	/// </summary>
	/// <param name="bf">Boolean Function to be updated</param>
	/// <returns>The Boolean Function for the variable shuffle from abc to bca</returns>
	[[nodiscard]] inline constexpr int shuffle_vars_bca(const int bf) noexcept
	{
		//return detail::shuffle_bits(i, 7, 5, 3, 1, 6, 4, 2, 0);
		return shuffle_bits(bf, 7, 3, 6, 2, 5, 1, 4, 0);
	}

	namespace test
	{
		namespace {
			bool equal_bac(const int bf, const int bf1) {
				for (unsigned int a = 0; a <= 0xFF; ++a) {
					for (unsigned int b = 0; b <= 0xFF; ++b) {
						for (unsigned int c = 0; c <= 0xFF; ++c) {
							const auto r = ternarylogic::ternary(a, b, c, bf);
							const auto r2 = ternarylogic::ternary(b, a, c, bf1);
							if (r != r2) {
								return false;
							}
						}
					}
				}
				return true;
			}
			bool equal_acb(const int bf, const int bf1) {
				for (unsigned int a = 0; a <= 0xFF; ++a) {
					for (unsigned int b = 0; b <= 0xFF; ++b) {
						for (unsigned int c = 0; c <= 0xFF; ++c) {
							const auto r = ternarylogic::ternary(a, b, c, bf);
							const auto r2 = ternarylogic::ternary(a, c, b, bf1);
							if (r != r2) {
								return false;
							}
						}
					}
				}
				return true;
			}
			bool equal_cba(const int bf, const int bf1) {
				for (unsigned int a = 0; a <= 0xFF; ++a) {
					for (unsigned int b = 0; b <= 0xFF; ++b) {
						for (unsigned int c = 0; c <= 0xFF; ++c) {
							const auto r = ternarylogic::ternary(a, b, c, bf);
							const auto r2 = ternarylogic::ternary(c, b, a, bf1);
							if (r != r2) {
								return false;
							}
						}
					}
				}
				return true;
			}
			bool equal_cab(const int bf, const int bf1) {
				for (unsigned int a = 0; a <= 0xFF; ++a) {
					for (unsigned int b = 0; b <= 0xFF; ++b) {
						for (unsigned int c = 0; c <= 0xFF; ++c) {
							const auto r = ternarylogic::ternary(a, b, c, bf);
							const auto r2 = ternarylogic::ternary(c, a, b, bf1);
							if (r != r2) {
								return false;
							}
						}
					}
				}
				return true;
			}
			bool equal_bca(const int bf, const int bf1) {
				for (unsigned int a = 0; a <= 0xFF; ++a) {
					for (unsigned int b = 0; b <= 0xFF; ++b) {
						for (unsigned int c = 0; c <= 0xFF; ++c) {
							const auto r = ternarylogic::ternary(a, b, c, bf);
							const auto r2 = ternarylogic::ternary(b, c, a, bf1);
							if (r != r2) {
								return false;
							}
						}
					}
				}
				return true;
			}
			void test_swap_bac()
			{
				for (int bf1 = 0; bf1 <= 0xFF; ++bf1) {
					for (int bf2 = 0; bf2 <= 0xFF; ++bf2) {
						if (equal_bac(bf1, bf2)) {
							const int bf3 = shuffle_vars_bac(bf1);
							if (bf3 != bf2) {
								std::cout << "ERROR: test_swap_bac " << bf1 << ":" << std::bitset<8>(bf1).to_string() << "->" << bf2 << ":" << std::bitset<8>(bf2).to_string() << " swap_bac=" << bf3 << ":" << std::bitset<8>(bf3).to_string() << std::endl;
								return;
							}
							break;
						}
					}
				}
				std::cout << "test_swap_bac: No errors found!" << std::endl;
			}
			void test_swap_acb()
			{
				for (int bf1 = 0; bf1 <= 0xFF; ++bf1) {
					for (int bf2 = 0; bf2 <= 0xFF; ++bf2) {
						if (equal_acb(bf1, bf2)) {
							const int bf3 = shuffle_vars_acb(bf1);
							if (bf3 != bf2) {
								std::cout << "ERROR: test_swap_acb " << bf1 << ":" << std::bitset<8>(bf1).to_string() << "->" << bf2 << ":" << std::bitset<8>(bf2).to_string() << " swap_acb=" << bf3 << ":" << std::bitset<8>(bf3).to_string() << std::endl;
								return;
							}
							break;
						}
					}
				}
				std::cout << "test_swap_acb: No errors found!" << std::endl;
			}
			void test_swap_cba()
			{
				for (int bf1 = 0; bf1 <= 0xFF; ++bf1) {
					for (int bf2 = 0; bf2 <= 0xFF; ++bf2) {
						if (equal_cba(bf1, bf2)) {
							const int bf3 = shuffle_vars_cba(bf1);
							if (bf3 != bf2) {
								std::cout << "ERROR: test_swap_cba " << bf1 << ":" << std::bitset<8>(bf1).to_string() << "->" << bf2 << ":" << std::bitset<8>(bf2).to_string() << " swap_cba=" << bf3 << ":" << std::bitset<8>(bf3).to_string() << std::endl;
								return;
							}
							break;
						}
					}
				}
				std::cout << "test_swap_cba: No errors found!" << std::endl;
			}
			void test_swap_cab()
			{
				for (int bf1 = 0; bf1 <= 0xFF; ++bf1) {
					for (int bf2 = 0; bf2 <= 0xFF; ++bf2) {
						if (equal_cab(bf1, bf2)) {
							const int bf3 = shuffle_vars_cab(bf1);
							if (bf3 != bf2) {
								std::cout << "ERROR: test_swap_cab " << bf1 << ":" << std::bitset<8>(bf1).to_string() << "->" << bf2 << ":" << std::bitset<8>(bf2).to_string() << " swap_cab=" << bf3 << ":" << std::bitset<8>(bf3).to_string() << std::endl;
								return;
							}
							break;
						}
					}
				}
				std::cout << "test_swap_cab: No errors found!" << std::endl;
			}
			void test_swap_bca()
			{
				for (int bf1 = 0; bf1 <= 0xFF; ++bf1) {
					for (int bf2 = 0; bf2 <= 0xFF; ++bf2) {
						if (equal_bca(bf1, bf2)) {
							const int bf3 = shuffle_vars_bca(bf1);
							if (bf3 != bf2) {
								std::cout << "ERROR: test_swap_bca " << bf1 << ":" << std::bitset<8>(bf1).to_string() << "->" << bf2 << ":" << std::bitset<8>(bf2).to_string() << " swap_bca=" << bf3 << ":" << std::bitset<8>(bf3).to_string() << std::endl;
								return;
							}
							break;
						}
					}
				}
				std::cout << "test_swap_bca: No errors found!" << std::endl;
			}
		}

		void inline test_swap_correctness() {
			test_swap_bac();
			test_swap_acb();
			test_swap_cba();
			test_swap_cab();
			test_swap_bca();
		}

		void inline test_shuffle_variables() {
			std::cout << "shuffle_vars::test_shuffle_variables" << std::endl;

			constexpr unsigned long long a = 0b10101010;
			constexpr unsigned long long b = 0b11001100;
			constexpr unsigned long long c = 0b11110000;

			for (int i = 0; i <= 0xFF; ++i)
			{
				const unsigned long long r1 = ternarylogic::ternary(a, b, c, shuffle_vars_abc(i));
				const unsigned long long r2 = ternary(b, a, c, shuffle_vars_bac(i));
				const unsigned long long r3 = ternary(a, c, b, shuffle_vars_acb(i));
				const unsigned long long r4 = ternary(c, b, a, shuffle_vars_cba(i));
				const unsigned long long r5 = ternary(c, a, b, shuffle_vars_cab(i));
				const unsigned long long r6 = ternary(b, c, a, shuffle_vars_bca(i));

				if (r1 != r2) {
					std::cout << "ERROR: test_shuffle_variables: r1=" << std::bitset<8>(r1).to_string() << "; r2=" << std::bitset<8>(r2).to_string() << std::endl;
				}
				if (r1 != r3) {
					std::cout << "ERROR: test_shuffle_variables: r1=" << std::bitset<8>(r1).to_string() << "; r3=" << std::bitset<8>(r3).to_string() << std::endl;
				}
				if (r1 != r4) {
					std::cout << "ERROR: test_shuffle_variables: r1=" << std::bitset<8>(r1).to_string() << "; r4=" << std::bitset<8>(r4).to_string() << std::endl;
				}
				if (r1 != r5) {
					std::cout << "ERROR: test_shuffle_variables: r1=" << std::bitset<8>(r1).to_string() << "; r5=" << std::bitset<8>(r5).to_string() << std::endl;
				}
				if (r1 != r6) {
					std::cout << "ERROR: test_shuffle_variables: r1=" << std::bitset<8>(r1).to_string() << "; r6=" << std::bitset<8>(r6).to_string() << std::endl;
				}
			}
		}

	}
}
