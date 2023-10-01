#include <stdbool.h>
#include <stdio.h>

int* split_num_by_last_one(int inp) {
    static int arr[2]; 
    bool inc_af = true; 
    int a = 1;          
    int z = 0;          

    for (int i=0;i < 32;i++) {      
        bool bit = (inp ^ a) != (inp + a);

        if (bit && inc_af) {
            arr[0] = 1 << i;
            inc_af = false;
            z=i;                       
            break;
        }             

        a = a << 1;                    
    }

    arr[1] = inp >> z;
    if (arr[1] == 1) {
        arr[0] = arr[0] >> 1;
        arr[1] = arr[1] << 1;
    }

    return arr;
}

float fast_sqrt(int inp) {
    const float mu = 0.498;

    if (inp < 32) {
        float _32bitsqrtable[31] = {
            1,1.414213,1.732050,
            2,2.2360,2.449489,
            2.645751,2.828427,
            3,3.162277,3.316624,
            3.464101,3.605551,
            3.741657,3.872983,
            4,4.12310,4.242640,
            4.358898,4.472135,
            4.582575,4.690415,
            4.795831,4.898979,
            5,5.09901,5.196152,
            5.291502,5.385164,
            5.477225,5.567764
        };

        return _32bitsqrtable[inp-1];
    } else {
        bool add_const = false;
        if (inp % 2 != 0) {
            inp -= 1;
            add_const = true;
        }

        int* s = split_num_by_last_one(inp);
        float res = fast_sqrt(s[0]) * fast_sqrt(s[1]);

        if (add_const) {
            res += mu/res;
        }

        return res;
    }
}

int main() {
    int inp = 0;

    printf("Define sqrt of ");
    scanf("%d", &inp);
    printf("Sqrt of %d is %f\n", inp, fast_sqrt(inp));

    return 0;
}

