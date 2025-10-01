import numpy as np

def succ_ratio(key, q, conv, distinguisher, accept_neg=True, clear_nan=True):
    succs = []

    if clear_nan:
        distinguisher.convergence_traces[np.isnan(distinguisher.convergence_traces)] = 0

    for key_index in range(distinguisher.convergence_traces.shape[1]):
        N_t = conv
        for j in range(distinguisher.convergence_traces.shape[2]):
            s = (distinguisher.convergence_traces[:,key_index,j].argsort()[::-1][0]) % q
            if (key[key_index] == s) or (accept_neg and (q - key[key_index]) == s):
                succs.append(N_t)
                break
            N_t += conv
    
    succs_np = np.array(succs)
    succ_ratios = []

    for j in range(distinguisher.convergence_traces.shape[2]):
        N_t = (j + 1)*conv
        succ_ratios.append((succs_np <= N_t).sum() / distinguisher.convergence_traces.shape[1])

    return succ_ratios


def unpack_guess(guess, q):
    return guess%q, guess//q

def pack_guess(low, high, q):
    return high*q + low


def print_scores_packed(ki, scores, q, scores_sorted=None, l=10):
    if scores_sorted is None:
        scores_sorted = scores.argsort()[::-1]

    for i in range(l):
        print(ki, i, unpack_guess(scores_sorted[i], q), scores[scores_sorted[i]])
    print()


def save_top_scores(filename, scores, scores_sorted=None, l=10):
    if scores_sorted is None:
        scores_sorted = scores.argsort()[::-1]

    np.save(f'{filename}_k', scores_sorted[:l])
    np.save(f'{filename}_v', scores[scores_sorted[:l]])
