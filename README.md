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

    station_id | mean_presure
    -----------|:-----------:|
    C0A880     | 1016.7291666666666
    C0F9A0     | 967.7125
    C0G640     | 1016.2375000000002
    C0R190     | 1011.0291666666667
    C0X260     | 1011.5090909090908
