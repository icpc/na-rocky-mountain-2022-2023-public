import java.util.Arrays;
import java.util.Scanner;

public class everythingisanail_da {

    private void work() {
        Scanner sc = new Scanner(System.in);
        t = sc.nextInt();
        ts = new int[t];
        for (int i = 0; i < t; i++) {
            ts[i] = sc.nextInt();
        }

        memo = new int[4][8][t];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                Arrays.fill(memo[i][j], -1);
            }
        }

        System.out.println(go(3, 7, 0));
    }

    private int t;
    private int[] ts;
    private int[][][] memo;

    private int go(int tool, int av, int k) {
        if (k == t) return 0;
        if (memo[tool][av][k] >= 0) return memo[tool][av][k];
        int ret = go(tool, av, k + 1);

        if (tool == 3 || tool == ts[k]) {
            int nav = tool == 3 ? (av ^ (1 << ts[k])) : av;
            int t = 1 + go(ts[k], nav, k + 1);
            if (t > ret) ret = t;
        } else if (av > 0) {
            for (int i = 0; i < 3; i++) {
                if (ts[k] != tool && ((1 << ts[k]) & av) != 0) {
                    int t = 1 + go(ts[k], av ^ (1 << ts[k]), k + 1);
                    if (t > ret) ret = t;
                }
            }
        }

        return memo[tool][av][k] = ret;
    }

    public static void main(String[] args) {
        new everythingisanail_da().work();
    }
}
