#pragma once

#include <latch>

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
    };
}