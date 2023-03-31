import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class icouldhavewon_da {

    private void work() {
        Scanner sc = new Scanner(System.in);
        char[] s = sc.next().toCharArray();
        sc.close();

        int[] p = new int[s.length];
        for (int i = 0; i < p.length; i++) {
            if (s[i] == 'B') p[i] = 1;
        }

        int[] points = new int[2];
        int[] wins = new int[2];

        List<Integer> ans = new ArrayList<>();

        for (int i = 1; i <= s.length; i++) {
            points[0] = points[1] = 0;
            wins[0] = wins[1] = 0;
            for (int j = 0; j < s.length; j++) {
                points[p[j]]++;

                if (points[0] == i) {
                    wins[0]++;
                    points[0] = points[1] = 0;
                }

                if (points[1] == i) {
                    wins[1]++;
                    points[0] = points[1] = 0;
                }
            }

            if (wins[0] > wins[1]) ans.add(i);
        }

        System.out.println(ans.size());
        for (int i : ans) System.out.printf("%d ", i);
        System.out.println();
    }

    public static void main(String[] args) {
        new icouldhavewon_da().work();
    }
}
