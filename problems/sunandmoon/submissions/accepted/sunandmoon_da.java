import java.util.Scanner;

public class sunandmoon_da {

    private void work() {
        Scanner sc = new Scanner(System.in);
        int da = sc.nextInt();
        int ya = sc.nextInt();
        int db = sc.nextInt();
        int yb = sc.nextInt();

        int ans = 0;
        do {
            ans++;
            da++;
            db++;
        } while (da % ya != 0 || db % yb != 0);

        System.out.println(ans);
    }

    public static void main(String[] args) {
        new sunandmoon_da().work();
    }
}
