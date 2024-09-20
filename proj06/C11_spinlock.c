static inline int my_spin_lock (atomic_int *lock) {
    int val=0;
    // 透過以下指令避免lock被同時修改,acq_rel確保執行順序
    if (likely(atomic_exchange_explicit(lock, 1, memory_order_acq_rel) == 0))
        return 0;
    do {
        do {
            asm("pause");// 短暫等待,降低cpu使用頻率
        } while (*lock != 0);
        val = 0;
    } while (!atomic_compare_exchange_weak_explicit(lock, &val, 1, memory_order_acq_rel, memory_order_relaxed));
    return 0;
}


static inline int my_spin_unlock(atomic_int *lock) {
    atomic_store_explicit(lock, 0, memory_order_release);
    return 0;
}
