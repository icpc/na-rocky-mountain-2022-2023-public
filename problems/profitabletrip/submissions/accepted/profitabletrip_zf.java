import java.util.*;

public class profitabletrip_zf {

    static class Edge {
        int v, p;

        Edge(int v, int p) {
            this.v = v;
            this.p = p;
        }
    }

    private int n, w;
    private int[] val;
    private Map<Integer, List<Edge>> g;
    private Queue<Integer> q;

    private void update(int v, int x) {
        if (Math.min(w, x) > val[v]) {
            val[v] = Math.min(w, x);
            q.add(v);
        }
    }

    private void work() {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        int m = sc.nextInt();
        w = sc.nextInt();

        g = new HashMap<>();

        while (m-- > 0) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            int p = sc.nextInt();
            if (!g.containsKey(u)) g.put(u, new ArrayList<>());
            g.get(u).add(new Edge(v, p));
        }

        val = new int[n + 1];
        Arrays.fill(val, Integer.MIN_VALUE / 16);
        q = new LinkedList<>();

        update(1, 0);

        while (!q.isEmpty()) {
            int u = q.poll();
            if (g.containsKey(u)) {
                for (Edge e : g.get(u)) {
                    update(e.v, e.p + val[u]);
                }
            }
        }

        System.out.println(val[n]);
    }

    public static void main(String[] args) {
        new profitabletrip_zf().work();
    }
}
