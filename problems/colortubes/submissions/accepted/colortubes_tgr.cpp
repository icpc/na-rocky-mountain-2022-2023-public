#include <iostream>
#include <map>
#include <vector>
using namespace std ;
const int MAXN = 100000 ;
int st[MAXN][3] ;
int st2[MAXN][3] ;
int colof[MAXN*4] ;
int marked[MAXN] ;
int cookie = 0 ;
int n ;
vector<int> wc ; // columns we work with
int gcolor, gcolumn ; // destination column
void move(int src, int dst) {
   int si = 2 ;
   int di = 0 ;
   while (st[src][si] == 0)
      si-- ;
   while (st[dst][di] != 0)
      di++ ;
   swap(st[dst][di], st[src][si]) ;
   swap(st2[dst][di], st2[src][si]) ;
   swap(colof[st2[dst][di]], colof[st2[src][si]]) ;
}
int enc() {
   int r = 0 ;
   for (int i=0; i<6; i++)
      for (int j=0; j<3; j++)
         r = r * 3 + st[i][j] ;
   return r ;
}
int enc2() {
   int r = 0 ;
   for (int i=0; i<(int)wc.size(); i++)
      for (int j=0; j<3; j++) {
         int t = st[wc[i]][j] ;
         if (t > 0)
            t = (t == gcolor ? 1 : 2) ;
         r = r * 3 + t ;
      }
   return r ;
}
void dec(int v) {
   for (int i=5; i>=0; i--)
      for (int j=2; j>=0; j--) {
         st[i][j] = v % 3 ;
         v /= 3 ;
      }
}
map<int, int> dist ;
void recur(int at, int togo) {
   if (togo == 0) {
      dist[enc()] = 0 ;
      return ;
   }
   if (at >= 6)
      return ;
   for (int i=0; i<=3 && i<=togo; i++) {
      recur(at+1, togo-i) ;
      if (i < 3)
         st[at][2-i] = 0 ;
   }
   for (int i=0; i<3; i++)
      st[at][i] = 2 ;
}
int main() {
   for (int i=0; i<6; i++)
      for (int j=0; j<3; j++)
         st[i][j] = min(i+1, 2) ;
   recur(1, 3) ;
   for (int d=0; ; d++) {
      vector<int> cs ;
      for (auto x: dist)
         if (x.second == d)
            cs.push_back(x.first) ;
      if (cs.size() == 0)
         break ;
      for (auto prev: cs) {
         dec(prev) ;
         for (int i=0; i<6; i++) {
            if (st[i][0] != 0) {
               int fi = 0 ;
               while (fi < 2 && st[i][fi+1] != 0)
                  fi++ ;
               int ok = 0 ;
               for (int k=0; k<=fi; k++)
                  if (st[i][k] == 1) {
                     ok = 1 ;
                     break ;
                  }
               for (int j=0; j<6; j++) {
                  if (i != j && st[j][2] == 0) {
                     int tj = 2 ;
                     while (tj > 0 && st[j][tj-1] == 0)
                        tj-- ;
                     if (i == 0 && fi == 0) // never move first one
                        continue ;
                     swap(st[i][fi], st[j][tj]) ;
                     int dst = enc() ;
                     if (dist.find(dst) == dist.end())
                        dist[dst] = d+1 ;
                     swap(st[i][fi], st[j][tj]) ;
                  }
               }
            }
         }
      }
   }
   cin >> n ;
   n++ ;
   vector<int> seq(n) ;
   vector<pair<int, int>> sol ;
   for (int i=0; i<n; i++)
      for (int j=0; j<3; j++) {
         cin >> st[i][j] ;
         st2[i][j] = 4 * st[i][j] + seq[st[i][j]]++ ;
         colof[st2[i][j]] = i ;
      }
   for (int i=0; i<3; i++)
      st[n][i] = n ; // dummy column
   int osollen = 0 ;
   while (1) {
      for (int i=0; i<n; i++) {
         if (st[i][0] == 0)
            continue ;
         gcolor = st[i][0] ;
         gcolumn = i ;
         wc.clear() ;
         cookie++ ;
         wc.push_back(i) ;
         marked[i] = cookie ;
         for (int i=0; i<3; i++) {
            int c = colof[4*gcolor+i] ;
            if (marked[c] != cookie) {
               marked[c] = cookie ;
               wc.push_back(c) ;
            }
            c = colof[i] ;
            if (marked[c] != cookie) {
               marked[c] = cookie ;
               wc.push_back(c) ;
            }
         }
         while ((int)wc.size() < 6)
            wc.push_back(n) ;
         while (1) {
            int state = enc2() ;
            int d = dist[state] ;
            if (d == 0)
               break ;
            for (int src=0; src<6; src++) {
               int sc = wc[src] ;
               if (sc != n && st[sc][0] != 0) {
                  for (int dst=0; dst<6; dst++) {
                     int dc = wc[dst] ;
                     if (dc != n && dc != sc && st[dc][2] == 0) {
                        move(sc, dc) ;
                        if (st[gcolumn][0] == gcolor) { // don't move first piece
                           int state2 = enc2() ;
                           if (dist[state2] < d) {
                              sol.push_back({sc, dc}) ;
                              goto foundmove ;
                           }
                        }
                        move(dc, sc) ;
                     }
                  }
               }
            }
foundmove: ;
         }
      }
      if ((int)sol.size() == osollen)
         break ;
      osollen = sol.size() ;
   }
   cout << sol.size() << endl ;
   for (auto s: sol)
      cout << 1+s.first << " " << 1+s.second << endl ;
}
