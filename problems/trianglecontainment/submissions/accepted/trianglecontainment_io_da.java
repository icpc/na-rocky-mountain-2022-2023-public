import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class trianglecontainment_io_da {

    static class Pt {
        int k;
        long x, y, val;

        Pt(int k, long x, long y, long val) {
            this.k = k;
            this.x = x;
            this.y = y;
            this.val = val;
        }
    }

    private int N;
    private long[] st;

    private void update(int k, long val) {
        k += N;
        st[k] = val;
        while (k > 1) {
            k >>= 1;
            st[k] = st[2 * k] + st[2 * k + 1];
        }
    }

    private long query(int b, int e) {
        long rb = 0;
        long re = 0;
        b += N;
        e += N;
        while (b < e) {
            if ((b & 1) != 0) {
                rb += st[b++];
            }
            if ((e & 1) != 0) {
                re += st[--e];
            }

            b >>= 1;
            e >>= 1;
        }

        return rb + re;
    }

    private void work() {
        fast_io io = new fast_io();

        N = io.nextInt();
        long X = io.nextInt();

        List<Pt> barn0 = new ArrayList<>();
        List<Pt> barnX = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            long x = io.nextInt();
            long y = io.nextInt();
            long val = io.nextInt();
            barn0.add(new Pt(i, x, y, val));
            barnX.add(new Pt(i, x - X, y, val));
        }

        barn0.sort((p, q) -> Long.compare(p.y * q.x, p.x * q.y));
        barnX.sort((p, q) -> Long.compare(p.x * q.y, p.y * q.x));

        int[] map = new int[N];
        for (int i = 0; i < N; i++) {
            map[barnX.get(i).k] = i;
        }

        st = new long[2 * N];
        long total = 0;
        long[] ans = new long[N];
        for (Pt p : barn0) {
            ans[p.k] = total - query(map[p.k], N);
            update(map[p.k], p.val);
            total += p.val;
        }

        for (long i : ans) {
            io.println(i);
        }

        io.close();
    }

    public static void main(String[] args) {
        new trianglecontainment_io_da().work();
    }

    static class fast_io {
        private static final int IN_BUFFER_SIZE = 1 << 16;
        private static final int OUT_BUFFER_SIZE = 1 << 16;
        private final byte[] input = new byte[IN_BUFFER_SIZE];
        private int ix = IN_BUFFER_SIZE;
        private int bytesRead = ix;
        private final byte[] output = new byte[OUT_BUFFER_SIZE];
        private int ox = 0;
        private final char[] nn = new char[32];

        public void readMore() {
            try {
                bytesRead = System.in.read(input, 0, IN_BUFFER_SIZE);
                if (bytesRead <= 0) throw new RuntimeException();
                ix = 0;
            } catch (IOException e) {
                throw new RuntimeException();
            }
        }

        public void append(char c) {
            if (ox == OUT_BUFFER_SIZE) flushOut();
            output[ox++] = (byte) c;
        }

        public long nextLong() {
            skipSpaces();
            long ret = 0;
            if (ix == bytesRead) {
                readMore();
            }
            int sign = 1;
            if (input[ix] == '-') {
                sign = -1;
                ix++;
            }
            while (true) {
                if (ix == bytesRead) {
                    try {
                        readMore();
                    } catch (RuntimeException e) {
                        return ret;
                    }
                }
                if (input[ix] < '0') {
                    break;
                }
                ret *= 10;
                ret += input[ix++] - '0';
            }
            return sign * ret;
        }

        public int nextInt() {
            return (int) nextLong();
        }

        public void println(long n) {
            print(n);
            append('\n');
        }

        public void print(long n) {
            if (n == 0) {
                append('0');
            } else {
                if (n < 0) {
                    append('-');
                    n = -n;
                }
                int kk = 0;
                while (n > 0) {
                    nn[kk++] = (char) (n % 10 + '0');
                    n /= 10;
                }
                for (int i = kk - 1; i >= 0; i--) {
                    append(nn[i]);
                }
            }
        }

        public void close() {
            flushOut();
            System.out.close();
        }

        private void flushOut() {
            System.out.write(output, 0, ox);
            ox = 0;
        }

        private void skipSpaces() {
            while (true) {
                if (ix == bytesRead) {
                    readMore();
                }
                if (input[ix] > ' ') break;
                ix++;
            }
        }
    }
}
