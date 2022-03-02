# coms327p1

#features
    1. sound generation with inputs for frequency, sample rate, and duration
    2. sound generation with input from 16-character touchpad
    3. sound generation of a silent tone with input of samplerate and duration
    4. user terminal prompt for user to interact with sound generation
    5. user terminal prompt for user to generate sound for a 10-digit telephone number dial
    6. makefile creates 2 executable files (gensine executes feature 4) (gendial executes feature 5)
    7. sound structure containing an array of sound values, total number of samples, and sample rate.
    8. a second way to generate sound similar to feature 1 and instead outputs a sound structure.
    9. a second way to generate sound similar to feature 2 and instead outputs a sound structure.
    10. a second way to generate sound similar to feature 3 and instead outputs a sound structure.
    11. a new function that sends the sample values of a sound structure to a a provided file.
    12. a new executable files (dtmf) that will generate DTMF sound structures that will then be sent to a provided file or stdout if no file is provided.