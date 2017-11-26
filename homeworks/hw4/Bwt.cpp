//In the name of God
//written by:Milad Aghajohari
//date:30/8/1396
/*This code will generate a bwt end of the genome string{ACTG}
And can search in the string as you wish*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const long long n = 50000+10000;
const long long logN = 20;
string S ="";
/*
Rank[start][i] is the rank of string S[start] to S[max(start+2^i, S.size()-1)]
not including S[start+2^i] itself
*/
long long Rank[n][logN];
char index[n];
int index_d[n][4];
int main(){
  cin>>S;
  for(int i = 0; i<S.size(); i++){
    if(S[i] == 'C')
      S[i] = 'B';
    if(S[i] == 'G')
      S[i] = 'C';
    if(S[i] == 'T')
      S[i] = 'D';
  }
  S.push_back('$');
  //pushing the values in the vector
  for(int i = 0; i<S.size(); i++){
    Rank[i][0] = S[i]-'A'+1;
  }
  //will fill Rank[0 to length(S)-1][k]
  for (int k=1; k<18; k++){
    vector<long long> v;
    v.clear();
    //---fill v with new values for strings with length max(2^k, S.size()-i+1)
    for(int i=0; i<S.size(); i++){
      long long val = 0;
      val += (n+1)*Rank[i][k-1];
      if((i+(1<<(k-1))) <= S.size())
        val += Rank[(i+(1<<(k-1)))][k-1];
      v.push_back(val);
      //just for filling this with vals to lower_bound later
      Rank[i][k] = val;
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    //---now we have the values sorted in v and they are unique
    for(int i=0; i<S.size(); i++)
      Rank[i][k] = lower_bound(v.begin(), v.end(), Rank[i][k]) - v.begin()+1;
  }
  for(int i = 0; i<S.size(); i++)
    index[Rank[i][17]-1] = S[(i-1+S.size())%S.size()];
  for(int i = 0; i<S.size(); i++){
    switch (index[i]) {
      case 'A':
        cout <<'A';
        break;
      case 'B':
        cout <<'C';
        break;
      case 'C':
        cout <<'G';
        break;
      case 'D':
        cout <<'T';
        break;
      case '$':
        cout <<'$';
        break;
    }
  }
  cout << endl;
  //fill index_d's
  for(int i = 0; i<S.size(); i++){
    if(index[i] != '$')
    index_d[i][index[i]-'A'] = 1;
  }
  for(long long i = 1; i<S.size(); i++)
    for(long long j = 0; j<4; j++)
      index_d[i][j] += index_d[i-1][j];

  long long n_read;
  cin >> n_read;
  string T;
  while(n_read){
    n_read--;
    cin>>T;
    for(long long i = 0; i<T.size(); i++){
      if(T[i] == 'C')
        T[i] = 'B';
      if(T[i] == 'G')
        T[i] = 'C';
      if(T[i] == 'T')
        T[i] = 'D';
    }
    long long begin = 0, end = S.size();
    do{
    long long last_char = T[T.size()-1]-'A';
    long long range_len;
    if(begin == 0)
      range_len = index_d[end-1][last_char];
    else{
      range_len = index_d[end-1][last_char] - index_d[begin-1][last_char];
      begin = index_d[begin-1][last_char];
    }
    begin++;//the first string start with $
    for(long long i = 0; i<last_char; i++)
      begin += index_d[S.size()-1][i];
    end = begin + range_len;
    T.pop_back();
    if(end <= begin)
      break;
    }while(T.size());

    if(end > begin){
    cout << begin+1 <<" "<< end << endl;
    }
    else{
      cout <<"not found"<<endl;
    }
  }
}
