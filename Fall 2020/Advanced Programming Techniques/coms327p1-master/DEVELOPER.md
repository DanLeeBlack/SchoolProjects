#coms327p1

#gensnd.c
    gensnd.c contains 7 functions gensine, genDTMF, gensil, gensine2, genDTMF2, genSilence, and outputSound
    -gensine: generates a sample size of sin values between -1 and 1 for the given Frequency (Hz), Sample Rate(Hz), and Duration(sec)
        this is to be used as a function in other files and supplying input arguments to receive the list of values
    -genDTMF: Generates a Dual Tone Frequency in the form of a Sample of sin values between -1 and 1 based on a character input from a 16-digit phone pad
        this is to be used as a funtion in other files and supplying an input argument to receive the list of values
    -gensil: generates a silent tone of value 0 for the given sample rate(Hz) and duration(sec)
        this is to be used as a function in other files and supplying input arguments to receive the list of values
    -gensine2: returns a struct sound * countaining the peramiters of the sound wave given a Frequency (Hz), Sample Rate(Hz), and Duration(sec).
        using the struct sound * output of this function allows storable values of samples and related configuration data to be implemented in other functions.
    -genDTMF2: Generates a struct sound * based on the input of a Character, Sample Rate(Hz), and Duration(sec) to simulate a 16-digit phone pad
        using the struct sound * output of this function allows storable values of samples and related configuration data to be implemented in other functions.
    -genSilence: operates similar to gensil with the output being a struct sound * for use in other functions
    -outputSound: given a struct sound * and a file will send samples values to the provided files. to be used in other functions.
    

#main.c
    main
    -generates a terminal prompt for function gensine which after compiling with the makefile will befound within gensine.exe
        will prompt the user for Frequency (Hz), Sample Rate(Hz), and Duration(sec) and will reseive input one variable at a time(i.e '400' 'enter' '200' 'enter' '100' 'enter'

#main2.c
    main
    -generates a terminal prompt for funcion genDTMF and gensil which after compiling with the makefile will befound within gendial.exe
        will prompt the user to provide 10 digits in the range of 0-9,8,#,a-d/A-D.  the input method askes all 10 characters be in one input  (i.e. '18001234' 'enter' or '8a2B3D*#99' 'enter' )

#main1b.c
    main1b.c has 2 helper function (validChar and printSound) and a main
    -main: generates a series of sample sound values based on the first value provided after declaring dtmf.  All charaters of the first value provided must have charaters in
         the range 0-9,8,#,a-d/A-D.  There is an optional second value for input after the first value seperated by a space.  If a value is provided it is used as a filename to which   the sample values will be printed into otherwise if it is blank that values will be printed into the stdout.
    -validChar: takes a character argument and checks that it is in the range 0-9,8,#,a-d/A-D.
    -printSound: takes a struct sound * to print the samples values into the stdout.
