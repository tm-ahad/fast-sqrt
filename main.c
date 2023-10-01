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
    const float mu = 0.0686593357;

    if (inp < 16) {
        float hexsqrtable[15] = {
            1, 
            1.41421356237,1.73205080757, 
            2,
            2.2360679775,2.44948974278,
            2.64575131106,2.82842712475,
            3,
            3.16227766017,3.31662479036,
            3.46410161514,3.60555127546,
            3.74165738677,3.87298334621
        };

        return hexsqrtable[inp-1];
    } else {
        bool add_const = false;
        if (inp % 2 != 0) {
            inp -= 1;
            add_const = true;
        }

        int* s = split_num_by_last_one(inp);
        float res = fast_sqrt(s[0]) * fast_sqrt(s[1]);

        if (add_const) {
            res += mu;
        }

        return res;
    }
}

int main() {
    int inp ;

    printf("Define sqrt of ");
    scanf("%d", &inp);
    printf("Sqrt of %d is %f\n", inp, fast_sqrt(inp));

    return 0;
}

