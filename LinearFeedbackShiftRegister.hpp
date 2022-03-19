#ifndef LINEAR_FEEDBACK_SHIFT_REGISTER_HPP
#define LINEAR_FEEDBACK_SHIFT_REGISTER_HPP 

#include <iostream>
#include <cstdint>

// Very efficient RNG with a period of 2^128
    class LinearFeedbackShiftRegister
    {
        uint64_t state[2];
    public:
        LinearFeedbackShiftRegister(uint64_t seed)
        {
            state[0] = 0;
            state[1] = seed;
            getbits(64);
            getbits(64);
        }
        LinearFeedbackShiftRegister() : LinearFeedbackShiftRegister(1)
        {
            
        }
        LinearFeedbackShiftRegister(LinearFeedbackShiftRegister const &lfsr)
        {
            state[0] = lfsr.state[0];
            state[1] = lfsr.state[1];
        }
        uint64_t getbits(int Nbits)
        {
            //taps 128,126,101,99
            uint64_t answer = 0;
            int i;
            for (i = 0; i < Nbits; i++)
            {
                uint64_t bit = state[1] & 0x01;
                answer <<= 1;
                answer |= bit;
                bit = (state[0] >> 63) ^ (state[0] >> 61) ^ (state[0] >> 36) ^ (state[0] >> 34) ^ bit;
                bit &= 0x01;
                state[1] >>= 1;
                state[1] |= (state[0] & 0x01) << 63;
                state[0] >>= 1;
                state[0] |= bit << 63;
            }
            return answer;
        }

  	typename std::uint64_t result_type;
        uint64_t operator() (void) 
        { 
	   return getbits(63);
        }
        static constexpr uint64_t min()  
        { 
          return 0;
        }
        static constexpr uint64_t max()  
        { 
          return 0x7FFFFFFFFFFFFFFF; 
        };
        void seed(uint64_t seed) 
        { 
           *this = LinearFeedbackShiftRegister(seed);
        }
        void discard(unsigned long long j)
        {
            for (unsigned long long i =0; i < j; i++)
                getbits(63);
        }
        #ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /**  Writes a @c rand48 to a @c std::ostream. */
    template<class CharT,class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os, const LinearFeedbackShiftRegister& r)
    { os << r.state[0]; os << ","; os << r.state[1]; return os; }

    /** Reads a @c rand48 from a @c std::istream. */
    template<class CharT,class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is, LinearFeedbackShiftRegister& r)
    { char comma; is >> r.state[0]; is >> comma; is >> r.state[1]; return is; }
#endif

    };

#endif
