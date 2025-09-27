#include <iostream>
#include <cmath>
#include <map>
#include <string.h>
#include <vector>
#include <inttypes.h>
using namespace std;

void decToBinary(int n){
    int binaryNum[32];
    int i=0;
    while (n>0){
        binaryNum[i] = n%2;
        n = n/2;
        i++;
    }
    for(int j=i-1; j>=0; j--)
        cout << binaryNum[j];
}

int getSum(int num){
    int sum=0, digit=0;
    while(num>0){
        digit = num % 10;
        num = num / 10;
        sum = sum + digit;
    }
    return sum;
}

int getRev(int num){
    int rev;
    while(num>0){
        rev = (rev*10) + (num%10);
        num = num / 10;
    }
    return rev;
}

void simple_pascaltriangle(){
    int a=0, b=1, c, n;
    cout << "Enter the limit: ";
    cin >> n;
    for(int i=1; i<=n; i++){
        a=0;
        b=1;
        cout << b << "\t";
        for(int j=1; j<i; j++){
            c=a+b;
            cout << c << "\t";
            a=b;
            b=c;
        }
        cout << endl;
    }
}

bool is_prime(int n){
    if(n<=1) return false;
    for (int i=2; i<=sqrt(n); i++)
            if(n%i==0)
                return false;
    return true;
}

int gcd_bymod(int a, int b){
    if(a==0)
        return b;
    return gcd_bymod(b%a, a);
}

int gcd(int a, int b){
    while(a!=b){
        if(a>b){
            a=a-b;
        }else{
            b=b-a;
        }
    }
    return a;
}

int gcd_multipleinput(int arr[], int n){
    int result = arr[0];
    for(int i=1; i<n; i++){
        result = gcd(arr[i], result);
        if(result==1)
            return 1;
    }
    return result;
}

long long int lcm_multipleinput(int arr[], int n){
    long long int ans = arr[0];

    for(int i=1; i<n; i++){
        ans = (arr[i]*ans)/(gcd(arr[i],ans));
    }
    return ans;
}


int fibo(int n){
    if(n<=1)
        return n;

    return fibo(n-2) + fibo(n-1);
}

int fibo(int n, map<int, int> &memo){
    if(n<=1)
        return n;

    if(memo.count(n)>1)
        return memo[n];

    memo[n] = fibo(n-2, memo) + fibo(n-1, memo);
    return memo[n];
}

bool isPalindrome(string s){
    char str[s.size()-1];
    for(int i=0; i<s.size(); i++)
            str[i] = s[i];

    int l=0;
    int r= s.size()-1;
    while(r>l){
        if(str[l++] != str[r--]){
            return false;
        }
    }
    return true;
}

vector<vector<int>> createPascalTriangle(int n){
    vector<vector<int>> mat;

    for(int row=0; row<n; row++){
        vector<int> arr;
        for(int col=0; col<=row; col++){
            if(row==col || col==0)
                arr.push_back(1);
            else
                arr.push_back(mat[row-1][col-1] + mat[row-1][col]);
        }
        mat.push_back(arr);
    }
    return mat;
}

void Log_createPascalTriangle(){
    int n=5;
    vector<vector<int>> mat = createPascalTriangle(n);
    for(int row=0; row<mat.size(); row++){
        for(int col=0; col<mat[row].size(); col++){
            cout << mat[row][col] << " ";
        }
        cout << endl;
    }
}

int hammingWeight(uint32_t n){
    int res=0;
    while (n){
        res+= n%2;
        n=n>>1;
    }
    return res;
}

int revByte(uint32_t n){
    uint32_t res = 0;
    for(int i=0; i<32; i++){
        res = res << 1;
        if(n%2==1)
            res++;
        n=n>>1;
    }
    return res;
}
