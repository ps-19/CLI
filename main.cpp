#include <bits/stdc++.h>
using namespace std;
#define fastio() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define ll  long long
#define int long long
#define ld  long double
#define endl "\n"
#define pb  insert
#define fill(a,val) memset(a,val,sizeof(a))
#define ff  first
#define ss  second
#define test  ll t; cin>>t; while(t--)
#define loop(i,a,b)  for(ll i=a;i<b;i++)
#define loopr(i,a,b) for(ll i=a;i>=b;i--)
#define pii pair<ll,ll>
#define all(v) v.begin(),v.end()
const ll mod     = 1000*1000*1000+7;
const ll inf     = 1ll*1000*1000*1000*1000*1000*1000 + 7;
const ll mod2    = 998244353;
const ll N       = 1000 * 1000 + 10;
const ld pi      = 3.141592653589793;
ll power(ll x,ll y,ll p = LLONG_MAX ){ll res=1;x%=p;while(y>0){if(y&1)res=(res*x)%p;y=y>>1;x=(x*x)%p;}return res;}
ll ncr(ll n,ll r,ll m){if(r>n)return 0;ll a=1,b=1,i;for(i=0;i<r;i++){a=(a*n)%m;--n;}while(r){b=(b*r)%m;--r;}return (a*power(b,m-2,m))%m;}

set<string> cache;
string createID(){
    string curr;
    for(int i=0;i<26;i++){
        curr+=(rand()%26+'a');
    }
    if(cache.find(curr)==cache.end()){
        cache.insert(curr);
        return curr;
    }
    else return createID();
}


class IMAGE{
    public:
        string ImageID;
        bool READ, WRITE;
    IMAGE(){
        READ=0;
        WRITE=0;
        ImageID=createID();
    }
};

set<IMAGE> storage;    // global storage of all Images


class ADMINUSER{
    public:
    string ADMINUSER_id;
};

class ADMIN: public ADMINUSER{
    public:
        string adminID;
        bool READ, WRITE;
        set<IMAGE> images_;
        set<ADMINUSER> users;      // string id;
    ADMIN(){
        READ=0;
        WRITE=0;
        adminID=createID();
        users.clear();
    }    
};

class RBAC: public ADMIN{
    private:
        string id;
        bool READ, WRITE;
    public:
        set<ADMIN> allAdmins;
        set<ADMINUSER> allAdminsUSers;
    RBAC(){
        READ=false;
        WRITE=false;
        id=createID();
    }
    void read(){
        READ=1;
        cout<<"Read access have been granted!";
    }
    void write(){
        WRITE=1;
        cout<<"Write access have been granted!";
    }
    IMAGE image(){
        IMAGE a;
        return a;
    }
    void imageRead(string id){
        for(auto i:storage){
            if(i.ImageID == id){
                i.READ=1;
            }
        }
    }
    void imageWrite(string id){
        for(auto i:storage){
            if(i.ImageID == id){
                i.WRITE=1;
            }
        }
    }
    ADMIN createAdmin(){
        ADMIN a;
        return a;
    }
    void readAdmin(ADMIN a, IMAGE b){
        a.images_.insert(b);
        return;
    }
    ADMINUSER createUserAdmin(string ID){
        ADMINUSER a;
        a.ADMINUSER_id=ID;
        return a;
    }
    void addAdmin(ADMIN a, ADMINUSER b){
        a.users.insert(b);
        return;
    }
    bool checkAccess(string id, IMAGE resource, string access, RBAC obj){
        if(access=="READ"){
            if(obj.READ==1) return 1;
            for(auto i:allAdmins){
                for(auto j:i.users){
                    if(j.ADMINUSER_id == id){
                        if(i.READ == 1) return 1;
                    }
                }
            }
        }
        else{
            if(obj.WRITE==1) return 1;
        }
        return 0;
    }
};






void solve(){
    RBAC obj;
    string command;
    while(getline(cin, command)){
        
        vector<string> p;
        ll n=command.size();
        string curr;
        for(ll i=0;i<n;i++){
            if(command[i]==' '){
                p.push_back(curr);
                curr="";
            }
            else{
                curr+=command[i];
            }
        }
        if(curr.size())
        p.push_back(curr);
        curr="";
        
        if(p[0]=="addAccess"){
            if(p[1]=="READ"){
                obj.read();
            }
            else{
                obj.write();
            }
        }
        else if(p[0]=="addResource"){
            IMAGE img=obj.image();
            storage.pb(img);
        }
        else if(p[0]=="addAccessOnResource"){
            string img=p[2];
            obj.imageRead(img);
        }
        else if(p[0]=="addActionOnResource"){
            string img=p[2];
            obj.imageWrite(img);
        }
        else if(p[0]=="addRole"){
            ADMIN current=obj.createAdmin();
            obj.allAdmins.insert(current);
        }
        else if(p[0]=="addAccessOnResourceToRole"){
            if(p[1]=="READ"){
                string img=p[2];
                string adm=p[3];
                ADMIN a=NULL;
                IMAGE b=NULL;
                for(auto i:obj.allAdmins){
                    if(i.adminID == adm){
                        a=i;
                    }
                }
                for(auto i:storage){
                    if(i.ImageID == img){
                        b=i;
                    }
                }
                if(a==NULL){
                    cout<<"ADMIN is not created!";
                    continue;
                }
                if(b==NULL){
                    cout<<"IMAGE is not created!";
                    continue;
                }
                obj.readAdmin(a, b);
            }
        }
        else if(p[0]=="addUser"){
            ADMINUSER a=createUserAdmin(p[1]);
            obj.allAdminsUSers.insert(a);
        }
        else if(p[0]=="addRoleToUser"){
            string adm=p[2];
            string adm_user=p[3];
            ADMIN a=NULL;
            ADMINUSER b=NULL;
            for(auto i:obj.allAdmins){
                if(i.adminID == adm){
                    a=i;
                }
            }
            for(auto i:obj.allAdminsUSers){
                if(i.ADMINUSER_id == adm_user){
                    b=i;
                }
            }
            if(a==NULL){
                cout<<"Admin is not created!";
                continue;
            }
            if(b==NULL){
                cout<<"User is not created!";
                continue;
            }
            obj.addAdmin(a, b);
        }
        else {
            string userID=p[1];
            string imgID=p[2];
            string access=p[3];
            IMAGE a=NULL;
            for(auto i:storage){
                if(i.ImageID == imgID) {
                    a=i;
                    break;
                }
            }
            if(a==NULL){
                cout<<"Image is not created!";
                continue;
            }
            bool result=obj.checkAccess(userID, a, access, obj);
            if(result==1){
                cout<<"YES";
            }
            else{
                cout<<"NO";
            }
        }
    }
}


signed main(){
    fastio();
    solve();
    return 0;
}
