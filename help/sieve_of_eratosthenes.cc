#include <bits/stdc++.h>

using namespace std;

void sieve(long long int n){
    bool isprime[n+1];
    memset(isprime,true,sizeof(isprime));
    isprime[0]=false;
    isprime[1]=false;
    for(long long int i=2;i*i<=n;i++){
        if(isprime[i]){
            for(long long int j=i*i;j<=n;j+=i){
                isprime[j]=false;
            }
        }
    }
    for(long long int i=0;i<=n;i++){
        if(isprime[i]){
            cout<<i<<" ";
        }
    }
}

int main()
{
    long long int n;
    cin>>n;
    cout<<"Prime numbers less than or equal to n:\n";
    sieve(n);
    return 0;
}