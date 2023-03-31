import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class colortubes_da {

    class Move {
        int from, to;

        Move(int from, int to) {
            this.from = from;
            this.to = to;
        }

        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append(from + 1);
            sb.append(' ');
            sb.append(to + 1);
            return sb.toString();
        }
    }

    private int n;
    private int tubes[][];
    private List<Move> moves;


    private void work() {
        Scanner sc = new Scanner(new BufferedReader(new InputStreamReader(System.in)));

        n = sc.nextInt();
        tubes = new int[n + 1][3];
        moves = new ArrayList<>();

        int empty = -1;
        for (int i = 0; i <= n; i++) {
            int sum = 0;
            for (int j = 0; j < 3; j++) {
                sum += tubes[i][j] = sc.nextInt();
            }
            if (sum == 0) {
                empty = i;
            }
        }

        if (empty < 0) {
            int k = 2;
            while (tubes[0][k] == 0) k--;
            while (k >= 0) {
                for (int i = 1; i <= n && k >= 0; i++) {
                    if (tubes[i][2] > 0) continue;
                    int j = 2;
                    while (tubes[i][j] == 0) j--;
                    move(0, k--, i, ++j);
                }
            }

            empty = 0;
        }

        int[] cur = new int[3];
        int curK = 0;
        for (int color = 1; color <= n; color++) {
            curK = 0;
            for (int tube = 0; tube <= n; tube++) {
                if (tube == empty) continue;
                for (int i = 0; i < 3; i++) {
                    if (tubes[tube][i] == color) {
                        cur[curK++] = tube;
                        break;
                    }
                }
            }

            if (curK == 1) continue;

            // do I really need this swap?
            if (curK == 2) {
                int cnt = 0;
                for (int i = 0; i < 3; i++) {
                    if (tubes[cur[0]][i] == color) cnt++;
                }
                if (cnt == 2) {
                    int t = cur[0];
                    cur[0] = cur[1];
                    cur[1] = t;
                }
            }

            if (curK == 3) {
                int[] combined = combine(color, empty, cur[1], cur[2]);
                empty = combined[0];
                cur[1] = combined[1];
            }

            empty = solve(color, empty, cur[0], cur[1]);
        }

        System.out.println(moves.size());
        for (Move m : moves) {
            System.out.println(m);
        }
    }

    private int solve(int color, int empty, int one, int two) {
        int newEmpty = -1;
        if (match(color, one, 2, two, 2)) {
            // tops of the stacks match
            move(one, 2, empty, 0);
            move(two, 2, empty, 1);
            // we now have same two in originally empty tube, meaning one of the others have different types
            if (match(color, one, 0, one, 1)) {
                // move the other one
                if (match(color, two, 1, empty, 1)) {
                    move(two, 1, empty, 2);
                    move(two, 0, one, 2);
                } else {
                    move(two, 1, one, 2);
                    move(two, 0, empty, 2);
                }

                newEmpty = two;
            } else {
                if (match(color, one, 1, empty, 1)) {
                    move(one, 1, empty, 2);
                    move(one, 0, two, 2);
                } else {
                    move(one, 1, two, 2);
                    move(one, 0, empty, 2);
                }

                newEmpty = one;
            }
        } else {
            // tops of the stacks do not match
            // if there are two of the same at the top, move them
            if (match(color, one, 2, one, 1)) {
                move(one, 2, empty, 0);
                move(one, 1, empty, 1);
                move(two, 2, one, 1);
                if (match(color, two, 1, empty, 1)) {
                    move(two, 1, empty, 2);
                    move(two, 0, one, 2);
                } else {
                    move(two, 1, one, 2);
                    move(two, 0, empty, 2);
                }

                newEmpty = two;
            } else if (match(color, two, 2, two, 1)) {
                move(two, 2, empty, 0);
                move(two, 1, empty, 1);
                move(one, 2, two, 1);
                if (match(color, one, 1, empty, 1)) {
                    move(one, 1, empty, 2);
                    move(one, 0, two, 2);
                } else {
                    move(one, 1, two, 2);
                    move(one, 0, empty, 2);
                }

                newEmpty = one;
            } else {
                // blah, so much c&p :)
                // this is either
                // x c
                // c x
                // x c
                // or
                // c x
                // x c
                // x c

                // Swap tops
                move(one, 2, empty, 0);
                move(two, 2, one, 2);
                move(empty, 0, two, 2);
                
                // if it is solved, return
                if (match(color, one, 0, one, 1) && match(color, one, 1, one, 2)) {
                    newEmpty = empty;
                } else { // otherwise, try again
                    newEmpty = solve(color, empty, one, two);
                }
            }
        }

        return newEmpty;
    }

    private boolean match(int color, int tube0, int k0, int tube1, int k1) {
        boolean isColor0 = tubes[tube0][k0] == color;
        boolean isColor1 = tubes[tube1][k1] == color;
        return isColor0 == isColor1;
    }

    private int[] combine(int color, int empty, int tube0, int tube1) {
        int[] ret = new int[2]; // first is empty, second combined
        int k0 = 0;
        while (tubes[tube0][k0] != color) k0++;
        int k1 = 0;
        while (tubes[tube1][k1] != color) k1++;
        // order them - c&p galore
        if (k0 > k1) {
            int t = tube0;
            tube0 = tube1;
            tube1 = t;
            t = k0;
            k0 = k1;
            k1 = t;
        }

        if (k0 == 1 && k1 == 1) {
            // the only tricky one?
            // x x
            // c c
            // x x
            move(tube0, 2, empty, 0);
            move(tube1, 2, empty, 1);
            move(tube0, 1, tube1, 2);
            move(tube0, 0, empty, 2);
            ret[0] = tube0;
            ret[1] = tube1;
        } else if (k0 == 0 && k1 == 2) {
            // nope!
            // x c
            // x x
            // c x
            move(tube0, 2, empty, 0);
            move(tube1, 2, tube0, 2);
            move(tube1, 1, empty, 1);
            move(tube1, 0, empty, 2);
            ret[0] = tube1;
            ret[1] = tube0;
        } else {
            move(tube0, 2, empty, 0);
            move(tube0, 1, empty, 1);
            move(tube1, 2, empty, 2);
            move(tube0, 0, tube1, 2);
            ret[0] = tube0;
            ret[1] = tube1;
            for (int i = 0; i < 3; i++) {
                if (tubes[empty][i] == color) {
                    ret[1] = empty;
                    break;
                }
            }
        }

        return ret;
    }

    private void move(int from, int fromK, int to, int toK) {

        tubes[to][toK] = tubes[from][fromK];
        tubes[from][fromK] = 0;

        moves.add(new Move(from, to));
    }

    public static void main(String[] args) {
        new colortubes_da().work();
    }
}
