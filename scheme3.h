#pragma once

#include <latch>
#include <vector>

namespace scheme3 {
    inline constexpr int NT = 5;
    inline constexpr int A = 7, B = 6, C = 5, D = 6,
                         E = 4, F = 7, G = 5, H = 5,
                         I = 8, J = 5;
    struct pipeline {
        std::latch a_done, b_done, c_done, d_done;
        std::latch e_done, f_done, g_done, h_done;
        std::latch i_done, j_done;
        std::latch ef_done, gh_done;

        pipeline();
        void run();

        private:
        static std::vector<int> split_even(int N);
        static std::vector<int> starts_from_quota(const std::vector<int>& q);

        void worker_body(int tid,
                         const std::vector<int>& qa, const std::vector<int>& sa,
                         const std::vector<int>& qb, const std::vector<int>& sb,
                         const std::vector<int>& qc, const std::vector<int>& sc,
                         const std::vector<int>& qd, const std::vector<int>& sd,
                         const std::vector<int>& qe, const std::vector<int>& se,
                         const std::vector<int>& qf, const std::vector<int>& sf,
                         const std::vector<int>& qg, const std::vector<int>& sg,
                         const std::vector<int>& qh, const std::vector<int>& sh,
                         const std::vector<int>& qi, const std::vector<int>& si,
                         const std::vector<int>& qj, const std::vector<int>& sj);

        static void do_action(char x, int i);
    };
}