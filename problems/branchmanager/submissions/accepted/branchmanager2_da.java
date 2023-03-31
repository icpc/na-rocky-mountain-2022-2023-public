import java.util.*;

public class branchmanager2_da {

    private void work() {

        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();

        g = new int[n][] ;
        int cnt[] = new int[n], from[] = new int[n-1], to[] = new int[n-1] ;
        for (int i = 0; i < n - 1; i++) {
            from[i] = sc.nextInt() - 1;
            to[i] = sc.nextInt() - 1;
            cnt[from[i]]++ ;
        }
        for (int i=0; i<n; i++) {
            g[i] = new int[cnt[i]] ;
            cnt[i] = 0 ;
        }
        for (int i = 0; i < n - 1; i++) {
            g[from[i]][cnt[from[i]]++] = to[i] ;
        }
        for (int i=0; i<n; i++)
            Arrays.sort(g[i]);
        qs = qe = 0;
        Arrays.fill(canDo, false);
        for (int i = 0; i < m; i++) {
            q[qe++] = sc.nextInt() - 1;
        }

        go(0);

        System.out.println(qs == qe ? m : (m - qe + qs));

        sc.close();
    }

    private int qs, qe;
    private final boolean[] canDo = new boolean[200001];
    private final int[] q = new int[200001];
    private int[][] g;

    private void go(int u) {
        canDo[u] = true;
        for (int i=0; i<g[u].length; i++) {
            go(g[u][i]);
        }

        while (qs < qe && canDo[q[qs]]) {
            qs++;
        }

        canDo[u] = false;
    }

    public static void main(String[] args) {
        new branchmanager2_da().work();
    }
}
