#include "scheme3.h"

namespace scheme3 {
    pipeline::pipeline()
        : a_done(A), b_done(B), c_done(C), d_done(D),
          e_done(E), f_done(F), g_done(G), h_done(H),
          i_done(I), j_done(J),
          ef_done(E + F), gh_done(G + H) {}

    std::vector<int> pipeline::split_even(int N) {
        std::vector<int> q(NT, N / NT);
        for (int t = 0; t < (N % NT); ++t) q[t] += 1;
        return q;
    }

    std::vector<int> pipeline::starts_from_quota(const std::vector<int>& q) {
        std::vector<int> s(NT, 1);
        int run = 1;
        for (int t = 0; t < NT; ++t) { s[t] = run; run +=q[t]; }
        return s;
    }

    void pipeline::run() {

    }
}