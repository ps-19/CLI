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

enum Access { READ, WRITE };

map<string, set<Access>> resources;
map<string, set<string>> roles;
map<string, string> users;

void addAccess(Access access) {
    cout << "Creating universal access for " << (access == READ ? "READ" : "WRITE") << endl;
}

void addResource(string resource) {
    cout << "Creating resource " << resource << endl;
    resources[resource] = {};
}

void addAccessOnResource(Access access, string resource) {
    cout << "Adding " << (access == READ ? "READ" : "WRITE") << " access on resource " << resource << endl;
    resources[resource].insert(access);
}

void addRole(string role) {
    cout << "Creating role " << role << endl;
    roles[role] = {};
}

void addAccessOnResourceToRole(Access access, string resource, string role) {
    cout << "Adding " << (access == READ ? "READ" : "WRITE") << " access on resource " << resource << " to role " << role << endl;
    roles[role].insert(resource);
}

void addUser(string user) {
    cout << "Creating user " << user << endl;
    users[user] = "";
}

void addRoleToUser(string role, string user) {
    cout << "Assigning role " << role << " to user " << user << endl;
    users[user] = role;
}

bool checkAccess(string user, string resource, Access access) {
    string role = users[user];
    if (roles[role].count(resource) > 0 && resources[resource].count(access) > 0) {
        cout << "Yes, user " << user << " has " << (access == READ ? "READ" : "WRITE") << " access on resource " << resource << endl;
        return true;
    } else {
        cout << "No, user " << user << " does not have " << (access == READ ? "READ" : "WRITE") << " access on resource " << resource << endl;
        return false;
    }
}

signed main() {
    addAccess(READ);
    addAccess(WRITE);
    addResource("IMAGE");
    addAccessOnResource(READ, "IMAGE");
    addAccessOnResource(WRITE, "IMAGE");
    addRole("ADMIN");
    return 0;
}
