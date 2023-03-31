import java.util.Scanner;

public class blueberrywaffle_da {

    private void work() {
        Scanner sc = new Scanner(System.in);
        int r = sc.nextInt();
        int f = 2 * sc.nextInt();
        String ans = "up";
        if (r < f) {
            f -= r;
            if (f % (4 * r) < 2 * r) ans = "down";
        }

        System.out.println(ans);
    }

    public static void main(String[] args) {
        new blueberrywaffle_da().work();
    }
}
