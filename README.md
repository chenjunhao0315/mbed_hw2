# mbed_hw2
1. Setup and run program
    1. Using git clone to get the code
    * `$ git clone https://github.com/chenjunhao0315/mbed_hw2.git`
    2. Go to the working directory in a terminal.
    * `$ cd ee2405/mbed_hw2/hw2`
    4. Connect the wire as below picture.
    ![image](https://github.com/chenjunhao0315/mbed_hw2/blob/master/截圖%202021-03-28%20下午3.02.21.png)
    5. Compile the program.
    * `$ sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f`

2. Result

    The program run at 5Hz, below is python analysis
    ![image](https://github.com/chenjunhao0315/mbed_hw2/blob/master/截圖%202021-03-28%20下午2.16.36.png)
    This is the origin signal captured by picoscope without passing low-pass filter
    ![image](https://github.com/chenjunhao0315/mbed_hw2/blob/master/截圖%202021-03-28%20下午3.26.17.png)
    This is the origin signal captured by picoscope with passing low-pass filter
    ![image](https://github.com/chenjunhao0315/mbed_hw2/blob/master/截圖%202021-03-28%20下午3.24.51.png)
    Python analysis is almost identical to picoscope analysis, but the sample rate of picoscope is higher than STM.
