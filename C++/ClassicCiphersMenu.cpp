#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/* ============ CAESAR ============ */
string caesarEncrypt(const string &text, int k) {
    string res = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            res += char((c - base + k) % 26 + base);
        } else res += c;
    }
    return res;
}
string caesarDecrypt(const string &text, int k) {
    return caesarEncrypt(text, 26 - (k % 26));
}

/* ============ AFFINE ============ */
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}
string affineEncrypt(const string &text, int a, int b) {
    string res="";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c)?'A':'a';
            res += char((a*(c-base)+b)%26 + base);
        } else res += c;
    }
    return res;
}
string affineDecrypt(const string &text, int a, int b) {
    string res="";
    int inv = modInverse(a,26);
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c)?'A':'a';
            int val = (inv*((c-base)-b+26))%26;
            res += char(val+base);
        } else res += c;
    }
    return res;
}

/* ============ HOÁN VỊ ============ */
string hoanviEncrypt(const string &text, const vector<int> &key) {
    string res="";
    int blockSize=key.size();
    for (int i=0;i<text.size();i+=blockSize){
        string block=text.substr(i,blockSize);
        if (block.size()<blockSize) block.append(blockSize-block.size(),'X');
        string newblock(blockSize,' ');
        for (int j=0;j<blockSize;j++) newblock[j]=block[key[j]-1];
        res+=newblock;
    }
    return res;
}
string hoanviDecrypt(const string &text, const vector<int> &key) {
    string res="";
    int blockSize=key.size();
    vector<int> inv(blockSize);
    for (int i=0;i<blockSize;i++) inv[key[i]-1]=i;
    for (int i=0;i<text.size();i+=blockSize){
        string block=text.substr(i,blockSize);
        string newblock(blockSize,' ');
        for (int j=0;j<blockSize;j++) newblock[j]=block[inv[j]];
        res+=newblock;
    }
    return res;
}

/* ============ VIGENERE ============ */
string vigenereEncrypt(const string &text, const string &key) {
    string res="";
    int klen=key.size(), ki=0;
    for (char c : text) {
        if (isalpha(c)) {
            char base=isupper(c)?'A':'a';
            char kbase=isupper(key[ki%klen])?'A':'a';
            int shift=(key[ki%klen]-kbase);
            res+=char((c-base+shift)%26+base);
            ki++;
        } else res+=c;
    }
    return res;
}
string vigenereDecrypt(const string &text, const string &key) {
    string res="";
    int klen=key.size(), ki=0;
    for (char c : text) {
        if (isalpha(c)) {
            char base=isupper(c)?'A':'a';
            char kbase=isupper(key[ki%klen])?'A':'a';
            int shift=(key[ki%klen]-kbase);
            res+=char((c-base - shift +26)%26+base);
            ki++;
        } else res+=c;
    }
    return res;
}

/* ============ PLAYFAIR ============ */
void generateMatrix(const string &key, char mat[5][5]) {
    string used="";
    for (char c: key){
        c=tolower(c);
        if (c=='j') c='i';
        if (isalpha(c) && used.find(c)==string::npos) used+=c;
    }
    for (char c='a';c<='z';c++){
        if (c=='j') continue;
        if (used.find(c)==string::npos) used+=c;
    }
    int idx=0;
    for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
            mat[i][j]=used[idx++];
}
void findPos(char mat[5][5], char c, int &r, int &col){
    if (c=='j') c='i';
    for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
            if (mat[i][j]==c){r=i;col=j;return;}
}
string playfairEncrypt(string text, const string &key){
    char mat[5][5]; generateMatrix(key,mat);
    string newtext="";
    for (char c:text){
        if (isalpha(c)) {
            c=tolower(c);
            if (c=='j') c='i';
            newtext+=c;
        }
    }
    string prepared="";
    for (int i=0;i<newtext.size();i++){
        prepared+=newtext[i];
        if (i+1<newtext.size() && newtext[i]==newtext[i+1]) prepared+='x';
    }
    if (prepared.size()%2!=0) prepared+='x';
    string res="";
    for (int i=0;i<prepared.size();i+=2){
        char a=prepared[i],b=prepared[i+1];
        int r1,c1,r2,c2;
        findPos(mat,a,r1,c1); findPos(mat,b,r2,c2);
        if (r1==r2){
            res+=mat[r1][(c1+1)%5];
            res+=mat[r2][(c2+1)%5];
        } else if (c1==c2){
            res+=mat[(r1+1)%5][c1];
            res+=mat[(r2+1)%5][c2];
        } else {
            res+=mat[r1][c2];
            res+=mat[r2][c1];
        }
    }
    return res;
}
string playfairDecrypt(string text, const string &key){
    char mat[5][5]; generateMatrix(key,mat);
    string res="";
    for (int i=0;i<text.size();i+=2){
        char a=text[i],b=text[i+1];
        int r1,c1,r2,c2;
        findPos(mat,a,r1,c1); findPos(mat,b,r2,c2);
        if (r1==r2){
            res+=mat[r1][(c1+4)%5];
            res+=mat[r2][(c2+4)%5];
        } else if (c1==c2){
            res+=mat[(r1+4)%5][c1];
            res+=mat[(r2+4)%5][c2];
        } else {
            res+=mat[r1][c2];
            res+=mat[r2][c1];
        }
    }
    return res;
}

/* ============ MAIN ============ */
int main() {
    while (true) {
        int method;
        cout<<"\n==== MENU MA HOA ====\n";
        cout<<"1. Caesar\n2. Affine\n3. Hoan vi\n4. Vigenere\n5. Playfair\n0. Thoat\n";
        cout<<"Chon phuong phap: "; 
        cin>>method;
        cin.ignore();

        if (method == 0) break;

        int action;
        cout<<"1. Ma hoa\n2. Giai ma\nChon thao tac: "; 
        cin>>action;
        cin.ignore();

        string text,key;
        int k,a,b;

        switch(method){
        case 1: // Caesar
            cout<<"Nhap chuoi: "; getline(cin,text);
            cout<<"Nhap k: "; cin>>k; cin.ignore();
            if(action==1)
                cout<<"Ma hoa: "<<caesarEncrypt(text,k)<<endl;
            else
                cout<<"Giai ma: "<<caesarDecrypt(text,k)<<endl;
            break;

        case 2: // Affine
            cout<<"Nhap chuoi: "; getline(cin,text);
            cout<<"Nhap a: "; cin>>a; 
            cout<<"Nhap b: "; cin>>b; 
            cin.ignore();
            if(action==1)
                cout<<"Ma hoa: "<<affineEncrypt(text,a,b)<<endl;
            else
                cout<<"Giai ma: "<<affineDecrypt(text,a,b)<<endl;
            break;

        case 3: { // Hoán vị
            cout<<"Nhap chuoi: "; getline(cin,text);
            int n; cout<<"Nhap so phan tu khoa hoan vi: ";cin>>n;
            vector<int> hv(n);
            cout<<"Nhap khoa hoan vi (vd 3 1 2): ";
            for (int i=0;i<n;i++) cin>>hv[i];
            cin.ignore();
            if(action==1)
                cout<<"Ma hoa: "<<hoanviEncrypt(text,hv)<<endl;
            else
                cout<<"Giai ma: "<<hoanviDecrypt(text,hv)<<endl;
            break;}

        case 4: // Vigenere
            cout<<"Nhap chuoi: "; getline(cin,text);
            cout<<"Nhap khoa: "; getline(cin,key);
            if(action==1)
                cout<<"Ma hoa: "<<vigenereEncrypt(text,key)<<endl;
            else
                cout<<"Giai ma: "<<vigenereDecrypt(text,key)<<endl;
            break;

        case 5: // Playfair
            cout<<"Nhap chuoi: "; getline(cin,text);
            cout<<"Nhap khoa: "; getline(cin,key);
            if(action==1)
                cout<<"Ma hoa: "<<playfairEncrypt(text,key)<<endl;
            else
                cout<<"Giai ma: "<<playfairDecrypt(text,key)<<endl;
            break;

        default:
            cout<<"Khong hop le\n";
            break;
        }
    }

    cout<<"Tam biet!\n";
    return 0;
}
