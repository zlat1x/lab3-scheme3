#include "scheme3.h"

namespace scheme3 {
    pipeline::pipeline()
        : a_done(A), b_done(B), c_done(C), d_done(D),
          e_done(E), f_done(F), g_done(G), h_done(H),
          i_done(I), j_done(J),
          ef_done(E + F), gh_done(G + H) {}

    void pipeline::run() {

    }
}