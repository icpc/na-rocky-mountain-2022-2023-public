import java.util.Scanner;

public class champernownecount_da {

    private void work() {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int k = sc.nextInt();
        int ans = 0;
        int mul = 10;
        long cur = 0;
        for (int i = 1; i <= n; i++) {
            if (i % mul == 0) mul *= 10;
            cur *= mul;
            cur += i;
            cur %= k;
            if (cur == 0) {
                ans++;
            }
        }

        System.out.println(ans);
    }

    public static void main(String[] args) {
        new champernownecount_da().work();
    }
}
