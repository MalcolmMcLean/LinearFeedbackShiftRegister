# LinearFeedbackShiftRegister
A random number generator using linear feeedback shift register algorithm.

## Algorithm
It's an extremely simple algorithm. There is a rack of 128 bits. When a
random bit is needed, a bit bit is shifted out. The bit is then replaced by
an new bit generated by an Exclusive-OR of "taps" on chosen bits. The bits
are chosen to create chaotic behaviour.

## Usage
It needs to be seeded with a non-zero seed. 

To get random bytes

    // Seed wth current time
    LinearFeedbackShiftRegister engine(time(0));
    for (int i = 0; i < 10; i++)
    {
        unsigned char byte = (unsigned char) engine.getbits(8);
       printf("%d, ", byte);
    }

You can also use as a standard library random number generator with
all the apparatus of ranges and distributions. For instance for a
uniform distribution.

     LinearFeedbackShiftRegister eng(1234);
     std::uniform_real_distribution<double> distribution(0.0,1.0);

     for (int i=0; i<10; ++i) 
     {
         std::cout << distribution(eng) << std::endl;
     }



