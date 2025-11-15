#include "scheme3.h"
#include <syncstream>
#include <thread>
#include <iostream>

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

    void pipeline::do_action(char x, int i) {
        std::osyncstream(std::cout) << "З набору " << x << " виконано дію " << i << ".\n";
    }

    void pipeline::worker_body(
        int tid,
        const std::vector<int>& qa, const std::vector<int>& sa,
        const std::vector<int>& qb, const std::vector<int>& sb,
        const std::vector<int>& qc, const std::vector<int>& sc,
        const std::vector<int>& qd, const std::vector<int>& sd,
        const std::vector<int>& qe, const std::vector<int>& se,
        const std::vector<int>& qf, const std::vector<int>& sf,
        const std::vector<int>& qg, const std::vector<int>& sg,
        const std::vector<int>& qh, const std::vector<int>& sh,
        const std::vector<int>& qi, const std::vector<int>& si,
        const std::vector<int>& qj, const std::vector<int>& sj) 
    {
        for (int k = 0,  idx = sa[tid]; k < qa[tid]; ++k, ++idx) { do_action('a', idx); a_done.count_down(); }

        a_done.wait();
        for (int k = 0,  idx = sb[tid]; k < qb[tid]; ++k, ++idx) { do_action('b', idx); b_done.count_down(); }
        for (int k = 0,  idx = sc[tid]; k < qc[tid]; ++k, ++idx) { do_action('c', idx); c_done.count_down(); }
        for (int k = 0,  idx = sd[tid]; k < qd[tid]; ++k, ++idx) { do_action('d', idx); d_done.count_down(); }

        b_done.wait();
        for (int k = 0,  idx = se[tid]; k < qe[tid]; ++k, ++idx) { do_action('e', idx); e_done.count_down(); ef_done.count_down(); }

        c_done.wait();
        for (int k = 0,  idx = sf[tid]; k < qf[tid]; ++k, ++idx) { do_action('f', idx); f_done.count_down(); ef_done.count_down(); }
        for (int k = 0,  idx = sg[tid]; k < qg[tid]; ++k, ++idx) { do_action('g', idx); g_done.count_down(); gh_done.count_down(); }

        d_done.wait();
        for (int k = 0,  idx = sh[tid]; k < qh[tid]; ++k, ++idx) { do_action('h', idx); h_done.count_down(); gh_done.count_down(); }

        ef_done.wait();
        for (int k = 0,  idx = si[tid]; k < qi[tid]; ++k, ++idx) { do_action('i', idx); i_done.count_down(); }

        gh_done.wait();
        for (int k = 0,  idx = sj[tid]; k < qj[tid]; ++k, ++idx) { do_action('j', idx); j_done.count_down(); }
    }

    void pipeline::run() {
        auto qa = split_even(A), qb = split_even(B), qc = split_even(C),
             qd = split_even(D), qe = split_even(E), qf = split_even(F),
             qg = split_even(G), qh = split_even(H), qi = split_even(I),
             qj = split_even(J);

        auto sa = starts_from_quota(qa), sb = starts_from_quota(qb), sc = starts_from_quota(qc),
             sd = starts_from_quota(qd), se = starts_from_quota(qe), sf = starts_from_quota(qf),
             sg = starts_from_quota(qg), sh = starts_from_quota(qh), si = starts_from_quota(qi),
             sj = starts_from_quota(qj);


        std::osyncstream(std::cout) << "Обчислення розпочато.\n";
        {
            std::vector<std::jthread> ws;
            ws.reserve(NT);
            for (int t = 0; t < NT; ++t) {
            ws.emplace_back(&pipeline::worker_body, this, t,
               std::cref(qa), std::cref(sa), std::cref(qb), std::cref(sb),
               std::cref(qc), std::cref(sc), std::cref(qd), std::cref(sd),
               std::cref(qe), std::cref(se), std::cref(qf), std::cref(sf),
               std::cref(qg), std::cref(sg), std::cref(qh), std::cref(sh),
               std::cref(qi), std::cref(si), std::cref(qj), std::cref(sj));
            }
        }
        std::osyncstream(std::cout) << "Обчислення завершено.\n";
    }
}