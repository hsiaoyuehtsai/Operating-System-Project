int __pthread_spin_lock (pthread_spinlock_t *lock)
{
    int val = 0;
    // 透過以下指令避免lock被同時修改
    if (__glibc_likely (atomic_exchange_acquire (lock, 1) == 0)) 
            return 0;
    do {
        do {
	        /* TODO Back-off.  */
            // 短暫等待,等同 asm("pause"),降低cpu使用頻率
	        atomic_spin_nop ();
	        val = atomic_load_relaxed (lock); // 取出lock,避免過度使用atomic_compare_exchange
	    } while (val != 0);
    } while (!atomic_compare_exchange_weak_acquire (lock, &val, 1));
     
    return 0;
}


int pthread_spin_unlock (pthread_spinlock_t *lock)
{
    atomic_store_release (lock, 0);
    return 0;
}
