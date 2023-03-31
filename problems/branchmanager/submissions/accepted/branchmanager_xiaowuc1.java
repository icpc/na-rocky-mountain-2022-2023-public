import java.util.*;
public class branchmanager_xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int m = sc.nextInt();
    long[] edges = new long[n-1];
    for(int i = 0; i < n-1; i++) {
      int a = sc.nextInt();
      int b = sc.nextInt();
      a--; b--;
      edges[i] = a;
      edges[i] <<= 18;
      edges[i] |= b;
    }
    Arrays.sort(edges);
    start = new int[n]; Arrays.fill(start, -1);
    to = new int[n-1];
    nextID = new int[n-1];
    for(int i = 0; i < n-1; i++) {
      int a = (int)(edges[i] >> 18);
      int b = (int)(edges[i] & 262143);
      to[i] = b;
      nextID[i] = start[a];
      start[a] = i;
    }
    q = new int[2*n];
    int qr = 0;
    q[qr++] = 0;
    int t = 0;
    int[] startt = new int[n];
    int[] endt = new int[n];
    while(qr > 0) {
      int curr = q[--qr];
      int id = curr / 2;
      if((curr&1) > 0) endt[id] = t++;
      else {
        startt[id] = t++;
        q[qr++] = (curr | 1);
        for(int nid = start[id]; nid != -1; nid = nextID[nid]) {
          q[qr++] = to[nid]*2;
        }
      }
    }
    int nowt = 0;
    int ans = 0;
    for(int i = 0; i < m; i++) {
      int curr = sc.nextInt()-1;
      if(nowt > endt[curr]) {
        System.out.println(ans);
        return;
      }
      nowt = Math.max(nowt, startt[curr]);
      ans++;
    }
    System.out.println(ans);
  }
  static int[] q;
  static int[] to, nextID, start;
}