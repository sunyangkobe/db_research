#ifndef SM_STATS_T_OUT_GEN_CPP
#define SM_STATS_T_OUT_GEN_CPP

/* DO NOT EDIT --- GENERATED from sm_stats.dat by stats.pl
           on Fri Jul  8 11:47:59 2011

<std-header orig-src='shore' genfile='true'>

SHORE -- Scalable Heterogeneous Object REpository

Copyright (c) 1994-99 Computer Sciences Department, University of
                      Wisconsin -- Madison
All Rights Reserved.

Permission to use, copy, modify and distribute this software and its
documentation is hereby granted, provided that both the copyright
notice and this permission notice appear in all copies of the
software, derivative works or modified versions, and any portions
thereof, and that both notices appear in supporting documentation.

THE AUTHORS AND THE COMPUTER SCIENCES DEPARTMENT OF THE UNIVERSITY
OF WISCONSIN - MADISON ALLOW FREE USE OF THIS SOFTWARE IN ITS
"AS IS" CONDITION, AND THEY DISCLAIM ANY LIABILITY OF ANY KIND
FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.

This software was developed with support by the Advanced Research
Project Agency, ARPA order number 018 (formerly 8230), monitored by
the U.S. Army Research Laboratory under contract DAAB07-91-C-Q518.
Further funding for this work was provided by DARPA through
Rome Research Laboratory Contract No. F30602-97-2-0247.

*/

#include "w_defines.h"
/*  -- do not edit anything above this line --   </std-header>*/


ostream &
operator<<(ostream &o,const sm_stats_t &t)
{
	o << setw(W_sm_stats_t) << "bf_one_page_write " << t.bf_one_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_two_page_write " << t.bf_two_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_three_page_write " << t.bf_three_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_four_page_write " << t.bf_four_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_five_page_write " << t.bf_five_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_six_page_write " << t.bf_six_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_seven_page_write " << t.bf_seven_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_eight_page_write " << t.bf_eight_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_more_page_write " << t.bf_more_page_write << endl;
	o << setw(W_sm_stats_t) << "bf_cleaner_sweeps " << t.bf_cleaner_sweeps << endl;
	o << setw(W_sm_stats_t) << "bf_cleaner_signalled " << t.bf_cleaner_signalled << endl;
	o << setw(W_sm_stats_t) << "bf_evicted_while_cleaning " << t.bf_evicted_while_cleaning << endl;
	o << setw(W_sm_stats_t) << "bf_already_evicted " << t.bf_already_evicted << endl;
	o << setw(W_sm_stats_t) << "bf_dirty_page_cleaned " << t.bf_dirty_page_cleaned << endl;
	o << setw(W_sm_stats_t) << "bf_flushed_OHD_page " << t.bf_flushed_OHD_page << endl;
	o << setw(W_sm_stats_t) << "bf_kick_full " << t.bf_kick_full << endl;
	o << setw(W_sm_stats_t) << "bf_kick_replacement " << t.bf_kick_replacement << endl;
	o << setw(W_sm_stats_t) << "bf_kick_threshold " << t.bf_kick_threshold << endl;
	o << setw(W_sm_stats_t) << "bf_sweep_page_hot_skipped " << t.bf_sweep_page_hot_skipped << endl;
	o << setw(W_sm_stats_t) << "bf_discarded_hot " << t.bf_discarded_hot << endl;
	o << setw(W_sm_stats_t) << "bf_log_flush_all " << t.bf_log_flush_all << endl;
	o << setw(W_sm_stats_t) << "bf_log_flush_lsn " << t.bf_log_flush_lsn << endl;
	o << setw(W_sm_stats_t) << "bf_write_out " << t.bf_write_out << endl;
	o << setw(W_sm_stats_t) << "bf_sleep_await_clean " << t.bf_sleep_await_clean << endl;
	o << setw(W_sm_stats_t) << "bf_fg_scan_cnt " << t.bf_fg_scan_cnt << endl;
	o << setw(W_sm_stats_t) << "bf_unfix_cleaned " << t.bf_unfix_cleaned << endl;
	o << setw(W_sm_stats_t) << "rwlock_r_waits " << t.rwlock_r_waits << endl;
	o << setw(W_sm_stats_t) << "rwlock_w_waits " << t.rwlock_w_waits << endl;
	o << setw(W_sm_stats_t) << "need_latch_condl " << t.need_latch_condl << endl;
	o << setw(W_sm_stats_t) << "latch_condl_nowaits " << t.latch_condl_nowaits << endl;
	o << setw(W_sm_stats_t) << "need_latch_uncondl " << t.need_latch_uncondl << endl;
	o << setw(W_sm_stats_t) << "latch_uncondl_nowaits " << t.latch_uncondl_nowaits << endl;
	o << setw(W_sm_stats_t) << "latch_uncondl_waits " << t.latch_uncondl_waits << endl;
	o << setw(W_sm_stats_t) << "btree_latch_wait " << t.btree_latch_wait << endl;
	o << setw(W_sm_stats_t) << "io_latch_wait " << t.io_latch_wait << endl;
	o << setw(W_sm_stats_t) << "bf_look_cnt " << t.bf_look_cnt << endl;
	o << setw(W_sm_stats_t) << "bf_grab_latch_failed " << t.bf_grab_latch_failed << endl;
	o << setw(W_sm_stats_t) << "bf_hit_cnt " << t.bf_hit_cnt << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait " << t.bf_hit_wait << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_any_p " << t.bf_hit_wait_any_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_btree_p " << t.bf_hit_wait_btree_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_file_p " << t.bf_hit_wait_file_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_keyed_p " << t.bf_hit_wait_keyed_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_lgdata_p " << t.bf_hit_wait_lgdata_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_lgindex_p " << t.bf_hit_wait_lgindex_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_rtree_p " << t.bf_hit_wait_rtree_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_rtree_base_p " << t.bf_hit_wait_rtree_base_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_extlink_p " << t.bf_hit_wait_extlink_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_stnode_p " << t.bf_hit_wait_stnode_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_zkeyed_p " << t.bf_hit_wait_zkeyed_p << endl;
	o << setw(W_sm_stats_t) << "bf_hit_wait_scan " << t.bf_hit_wait_scan << endl;
	o << setw(W_sm_stats_t) << "bf_replace_out " << t.bf_replace_out << endl;
	o << setw(W_sm_stats_t) << "bf_replaced_dirty " << t.bf_replaced_dirty << endl;
	o << setw(W_sm_stats_t) << "bf_replaced_clean " << t.bf_replaced_clean << endl;
	o << setw(W_sm_stats_t) << "bf_replaced_unused " << t.bf_replaced_unused << endl;
	o << setw(W_sm_stats_t) << "bf_awaited_cleaner " << t.bf_awaited_cleaner << endl;
	o << setw(W_sm_stats_t) << "bf_no_transit_bucket " << t.bf_no_transit_bucket << endl;
	o << setw(W_sm_stats_t) << "bf_prefetch_requests " << t.bf_prefetch_requests << endl;
	o << setw(W_sm_stats_t) << "bf_prefetches " << t.bf_prefetches << endl;
	o << setw(W_sm_stats_t) << "bf_upgrade_latch_unconditional " << t.bf_upgrade_latch_unconditional << endl;
	o << setw(W_sm_stats_t) << "bf_upgrade_latch_race " << t.bf_upgrade_latch_race << endl;
	o << setw(W_sm_stats_t) << "bf_upgrade_latch_changed " << t.bf_upgrade_latch_changed << endl;
	o << setw(W_sm_stats_t) << "restart_repair_rec_lsn " << t.restart_repair_rec_lsn << endl;
	o << setw(W_sm_stats_t) << "vol_reads " << t.vol_reads << endl;
	o << setw(W_sm_stats_t) << "vol_writes " << t.vol_writes << endl;
	o << setw(W_sm_stats_t) << "vol_blks_written " << t.vol_blks_written << endl;
	o << setw(W_sm_stats_t) << "vol_alloc_exts " << t.vol_alloc_exts << endl;
	o << setw(W_sm_stats_t) << "vol_free_exts " << t.vol_free_exts << endl;
	o << setw(W_sm_stats_t) << "need_vol_lock_r " << t.need_vol_lock_r << endl;
	o << setw(W_sm_stats_t) << "need_vol_lock_w " << t.need_vol_lock_w << endl;
	o << setw(W_sm_stats_t) << "nowait_vol_lock_r " << t.nowait_vol_lock_r << endl;
	o << setw(W_sm_stats_t) << "nowait_vol_lock_w " << t.nowait_vol_lock_w << endl;
	o << setw(W_sm_stats_t) << "await_vol_lock_r " << t.await_vol_lock_r << endl;
	o << setw(W_sm_stats_t) << "await_vol_lock_w " << t.await_vol_lock_w << endl;
	o << setw(W_sm_stats_t) << "io_m_lsearch " << t.io_m_lsearch << endl;
	o << setw(W_sm_stats_t) << "io_m_lsearch_extents " << t.io_m_lsearch_extents << endl;
	o << setw(W_sm_stats_t) << "vol_cache_primes " << t.vol_cache_primes << endl;
	o << setw(W_sm_stats_t) << "vol_cache_prime_fix " << t.vol_cache_prime_fix << endl;
	o << setw(W_sm_stats_t) << "vol_cache_clears " << t.vol_cache_clears << endl;
	o << setw(W_sm_stats_t) << "vol_last_extent_search " << t.vol_last_extent_search << endl;
	o << setw(W_sm_stats_t) << "vol_last_page_cache_update " << t.vol_last_page_cache_update << endl;
	o << setw(W_sm_stats_t) << "vol_last_page_cache_invalidate " << t.vol_last_page_cache_invalidate << endl;
	o << setw(W_sm_stats_t) << "vol_last_page_cache_find " << t.vol_last_page_cache_find << endl;
	o << setw(W_sm_stats_t) << "vol_last_page_cache_hit " << t.vol_last_page_cache_hit << endl;
	o << setw(W_sm_stats_t) << "vol_resv_cache_insert " << t.vol_resv_cache_insert << endl;
	o << setw(W_sm_stats_t) << "vol_resv_cache_erase " << t.vol_resv_cache_erase << endl;
	o << setw(W_sm_stats_t) << "vol_resv_cache_hit " << t.vol_resv_cache_hit << endl;
	o << setw(W_sm_stats_t) << "vol_resv_cache_fail " << t.vol_resv_cache_fail << endl;
	o << setw(W_sm_stats_t) << "vol_lock_noalloc " << t.vol_lock_noalloc << endl;
	o << setw(W_sm_stats_t) << "log_dup_sync_cnt " << t.log_dup_sync_cnt << endl;
	o << setw(W_sm_stats_t) << "log_daemon_wait " << t.log_daemon_wait << endl;
	o << setw(W_sm_stats_t) << "log_daemon_work " << t.log_daemon_work << endl;
	o << setw(W_sm_stats_t) << "log_fsync_cnt " << t.log_fsync_cnt << endl;
	o << setw(W_sm_stats_t) << "log_chkpt_cnt " << t.log_chkpt_cnt << endl;
	o << setw(W_sm_stats_t) << "log_chkpt_wake " << t.log_chkpt_wake << endl;
	o << setw(W_sm_stats_t) << "log_fetches " << t.log_fetches << endl;
	o << setw(W_sm_stats_t) << "log_inserts " << t.log_inserts << endl;
	o << setw(W_sm_stats_t) << "log_full " << t.log_full << endl;
	o << setw(W_sm_stats_t) << "log_full_old_xct " << t.log_full_old_xct << endl;
	o << setw(W_sm_stats_t) << "log_full_old_page " << t.log_full_old_page << endl;
	o << setw(W_sm_stats_t) << "log_full_wait " << t.log_full_wait << endl;
	o << setw(W_sm_stats_t) << "log_full_force " << t.log_full_force << endl;
	o << setw(W_sm_stats_t) << "log_full_giveup " << t.log_full_giveup << endl;
	o << setw(W_sm_stats_t) << "log_file_wrap " << t.log_file_wrap << endl;
	o << setw(W_sm_stats_t) << "log_bytes_generated " << t.log_bytes_generated << endl;
	o << setw(W_sm_stats_t) << "log_bytes_written " << t.log_bytes_written << endl;
	o << setw(W_sm_stats_t) << "log_bytes_rewritten " << t.log_bytes_rewritten << endl;
	o << setw(W_sm_stats_t) << "log_bytes_generated_rb " << t.log_bytes_generated_rb << endl;
	o << setw(W_sm_stats_t) << "log_bytes_rbfwd_ratio " << t.log_bytes_rbfwd_ratio << endl;
	o << setw(W_sm_stats_t) << "log_flush_wait " << t.log_flush_wait << endl;
	o << setw(W_sm_stats_t) << "log_short_flush " << t.log_short_flush << endl;
	o << setw(W_sm_stats_t) << "log_long_flush " << t.log_long_flush << endl;
	o << setw(W_sm_stats_t) << "lock_deadlock_cnt " << t.lock_deadlock_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_false_deadlock_cnt " << t.lock_false_deadlock_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_dld_call_cnt " << t.lock_dld_call_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_dld_first_call_cnt " << t.lock_dld_first_call_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_dld_false_victim_cnt " << t.lock_dld_false_victim_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_dld_victim_self_cnt " << t.lock_dld_victim_self_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_dld_victim_other_cnt " << t.lock_dld_victim_other_cnt << endl;
	o << setw(W_sm_stats_t) << "nonunique_fingerprints " << t.nonunique_fingerprints << endl;
	o << setw(W_sm_stats_t) << "unique_fingerprints " << t.unique_fingerprints << endl;
	o << setw(W_sm_stats_t) << "rec_pin_cnt " << t.rec_pin_cnt << endl;
	o << setw(W_sm_stats_t) << "rec_unpin_cnt " << t.rec_unpin_cnt << endl;
	o << setw(W_sm_stats_t) << "rec_repin_cvt " << t.rec_repin_cvt << endl;
	o << setw(W_sm_stats_t) << "fm_pagecache_hit " << t.fm_pagecache_hit << endl;
	o << setw(W_sm_stats_t) << "fm_page_nolatch " << t.fm_page_nolatch << endl;
	o << setw(W_sm_stats_t) << "fm_page_moved " << t.fm_page_moved << endl;
	o << setw(W_sm_stats_t) << "fm_page_invalid " << t.fm_page_invalid << endl;
	o << setw(W_sm_stats_t) << "fm_page_nolock " << t.fm_page_nolock << endl;
	o << setw(W_sm_stats_t) << "fm_alloc_page_reject " << t.fm_alloc_page_reject << endl;
	o << setw(W_sm_stats_t) << "fm_page_full " << t.fm_page_full << endl;
	o << setw(W_sm_stats_t) << "fm_error_not_handled " << t.fm_error_not_handled << endl;
	o << setw(W_sm_stats_t) << "fm_ok " << t.fm_ok << endl;
	o << setw(W_sm_stats_t) << "fm_histogram_hit " << t.fm_histogram_hit << endl;
	o << setw(W_sm_stats_t) << "fm_search_pages " << t.fm_search_pages << endl;
	o << setw(W_sm_stats_t) << "fm_bogus_pbucketmap " << t.fm_bogus_pbucketmap << endl;
	o << setw(W_sm_stats_t) << "fm_search_failed " << t.fm_search_failed << endl;
	o << setw(W_sm_stats_t) << "fm_search_hit " << t.fm_search_hit << endl;
	o << setw(W_sm_stats_t) << "fm_lastpid_cached " << t.fm_lastpid_cached << endl;
	o << setw(W_sm_stats_t) << "fm_lastpid_hit " << t.fm_lastpid_hit << endl;
	o << setw(W_sm_stats_t) << "fm_alloc_pg " << t.fm_alloc_pg << endl;
	o << setw(W_sm_stats_t) << "fm_ext_touch " << t.fm_ext_touch << endl;
	o << setw(W_sm_stats_t) << "fm_ext_touch_nop " << t.fm_ext_touch_nop << endl;
	o << setw(W_sm_stats_t) << "fm_nospace " << t.fm_nospace << endl;
	o << setw(W_sm_stats_t) << "fm_cache " << t.fm_cache << endl;
	o << setw(W_sm_stats_t) << "fm_compact " << t.fm_compact << endl;
	o << setw(W_sm_stats_t) << "fm_append " << t.fm_append << endl;
	o << setw(W_sm_stats_t) << "fm_appendonly " << t.fm_appendonly << endl;
	o << setw(W_sm_stats_t) << "bt_find_cnt " << t.bt_find_cnt << endl;
	o << setw(W_sm_stats_t) << "bt_insert_cnt " << t.bt_insert_cnt << endl;
	o << setw(W_sm_stats_t) << "bt_remove_cnt " << t.bt_remove_cnt << endl;
	o << setw(W_sm_stats_t) << "bt_traverse_cnt " << t.bt_traverse_cnt << endl;
	o << setw(W_sm_stats_t) << "bt_partial_traverse_cnt " << t.bt_partial_traverse_cnt << endl;
	o << setw(W_sm_stats_t) << "bt_restart_traverse_cnt " << t.bt_restart_traverse_cnt << endl;
	o << setw(W_sm_stats_t) << "bt_posc " << t.bt_posc << endl;
	o << setw(W_sm_stats_t) << "bt_scan_cnt " << t.bt_scan_cnt << endl;
	o << setw(W_sm_stats_t) << "bt_splits " << t.bt_splits << endl;
	o << setw(W_sm_stats_t) << "bt_cuts " << t.bt_cuts << endl;
	o << setw(W_sm_stats_t) << "bt_grows " << t.bt_grows << endl;
	o << setw(W_sm_stats_t) << "bt_shrinks " << t.bt_shrinks << endl;
	o << setw(W_sm_stats_t) << "bt_links " << t.bt_links << endl;
	o << setw(W_sm_stats_t) << "bt_upgrade_fail_retry " << t.bt_upgrade_fail_retry << endl;
	o << setw(W_sm_stats_t) << "bt_clr_smo_traverse " << t.bt_clr_smo_traverse << endl;
	o << setw(W_sm_stats_t) << "bt_pcompress " << t.bt_pcompress << endl;
	o << setw(W_sm_stats_t) << "bt_plmax " << t.bt_plmax << endl;
	o << setw(W_sm_stats_t) << "sort_keycmp_cnt " << t.sort_keycmp_cnt << endl;
	o << setw(W_sm_stats_t) << "sort_lexindx_cnt " << t.sort_lexindx_cnt << endl;
	o << setw(W_sm_stats_t) << "sort_getinfo_cnt " << t.sort_getinfo_cnt << endl;
	o << setw(W_sm_stats_t) << "sort_mof_cnt " << t.sort_mof_cnt << endl;
	o << setw(W_sm_stats_t) << "sort_umof_cnt " << t.sort_umof_cnt << endl;
	o << setw(W_sm_stats_t) << "sort_memcpy_cnt " << t.sort_memcpy_cnt << endl;
	o << setw(W_sm_stats_t) << "sort_memcpy_bytes " << t.sort_memcpy_bytes << endl;
	o << setw(W_sm_stats_t) << "sort_keycpy_cnt " << t.sort_keycpy_cnt << endl;
	o << setw(W_sm_stats_t) << "sort_mallocs " << t.sort_mallocs << endl;
	o << setw(W_sm_stats_t) << "sort_malloc_bytes " << t.sort_malloc_bytes << endl;
	o << setw(W_sm_stats_t) << "sort_malloc_hiwat " << t.sort_malloc_hiwat << endl;
	o << setw(W_sm_stats_t) << "sort_malloc_max " << t.sort_malloc_max << endl;
	o << setw(W_sm_stats_t) << "sort_malloc_curr " << t.sort_malloc_curr << endl;
	o << setw(W_sm_stats_t) << "sort_tmpfile_cnt " << t.sort_tmpfile_cnt << endl;
	o << setw(W_sm_stats_t) << "sort_tmpfile_bytes " << t.sort_tmpfile_bytes << endl;
	o << setw(W_sm_stats_t) << "sort_duplicates " << t.sort_duplicates << endl;
	o << setw(W_sm_stats_t) << "sort_page_fixes " << t.sort_page_fixes << endl;
	o << setw(W_sm_stats_t) << "sort_page_fixes_2 " << t.sort_page_fixes_2 << endl;
	o << setw(W_sm_stats_t) << "sort_lg_page_fixes " << t.sort_lg_page_fixes << endl;
	o << setw(W_sm_stats_t) << "sort_rec_pins " << t.sort_rec_pins << endl;
	o << setw(W_sm_stats_t) << "sort_files_created " << t.sort_files_created << endl;
	o << setw(W_sm_stats_t) << "sort_recs_created " << t.sort_recs_created << endl;
	o << setw(W_sm_stats_t) << "sort_rec_bytes " << t.sort_rec_bytes << endl;
	o << setw(W_sm_stats_t) << "sort_runs " << t.sort_runs << endl;
	o << setw(W_sm_stats_t) << "sort_run_size " << t.sort_run_size << endl;
	o << setw(W_sm_stats_t) << "sort_phases " << t.sort_phases << endl;
	o << setw(W_sm_stats_t) << "sort_ntapes " << t.sort_ntapes << endl;
	o << setw(W_sm_stats_t) << "any_p_fix_cnt " << t.any_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "btree_p_fix_cnt " << t.btree_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "file_p_fix_cnt " << t.file_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "keyed_p_fix_cnt " << t.keyed_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "lgdata_p_fix_cnt " << t.lgdata_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "lgindex_p_fix_cnt " << t.lgindex_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "rtree_p_fix_cnt " << t.rtree_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "rtree_base_p_fix_cnt " << t.rtree_base_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "extlink_p_fix_cnt " << t.extlink_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "stnode_p_fix_cnt " << t.stnode_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "zkeyed_p_fix_cnt " << t.zkeyed_p_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "page_fix_cnt " << t.page_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "bf_fix_cnt " << t.bf_fix_cnt << endl;
	o << setw(W_sm_stats_t) << "bf_refix_cnt " << t.bf_refix_cnt << endl;
	o << setw(W_sm_stats_t) << "bf_unfix_cnt " << t.bf_unfix_cnt << endl;
	o << setw(W_sm_stats_t) << "vol_check_owner_fix " << t.vol_check_owner_fix << endl;
	o << setw(W_sm_stats_t) << "page_alloc_cnt " << t.page_alloc_cnt << endl;
	o << setw(W_sm_stats_t) << "page_dealloc_cnt " << t.page_dealloc_cnt << endl;
	o << setw(W_sm_stats_t) << "ext_lookup_hits " << t.ext_lookup_hits << endl;
	o << setw(W_sm_stats_t) << "ext_lookup_misses " << t.ext_lookup_misses << endl;
	o << setw(W_sm_stats_t) << "alloc_page_in_ext " << t.alloc_page_in_ext << endl;
	o << setw(W_sm_stats_t) << "vol_free_page " << t.vol_free_page << endl;
	o << setw(W_sm_stats_t) << "vol_next_page " << t.vol_next_page << endl;
	o << setw(W_sm_stats_t) << "vol_next_page_with_space " << t.vol_next_page_with_space << endl;
	o << setw(W_sm_stats_t) << "vol_find_free_exts " << t.vol_find_free_exts << endl;
	o << setw(W_sm_stats_t) << "xct_log_flush " << t.xct_log_flush << endl;
	o << setw(W_sm_stats_t) << "begin_xct_cnt " << t.begin_xct_cnt << endl;
	o << setw(W_sm_stats_t) << "commit_xct_cnt " << t.commit_xct_cnt << endl;
	o << setw(W_sm_stats_t) << "abort_xct_cnt " << t.abort_xct_cnt << endl;
	o << setw(W_sm_stats_t) << "log_warn_abort_cnt " << t.log_warn_abort_cnt << endl;
	o << setw(W_sm_stats_t) << "prepare_xct_cnt " << t.prepare_xct_cnt << endl;
	o << setw(W_sm_stats_t) << "rollback_savept_cnt " << t.rollback_savept_cnt << endl;
	o << setw(W_sm_stats_t) << "internal_rollback_cnt " << t.internal_rollback_cnt << endl;
	o << setw(W_sm_stats_t) << "s_prepared " << t.s_prepared << endl;
	o << setw(W_sm_stats_t) << "sdesc_cache_hit " << t.sdesc_cache_hit << endl;
	o << setw(W_sm_stats_t) << "sdesc_cache_search " << t.sdesc_cache_search << endl;
	o << setw(W_sm_stats_t) << "sdesc_cache_search_cnt " << t.sdesc_cache_search_cnt << endl;
	o << setw(W_sm_stats_t) << "sdesc_cache_miss " << t.sdesc_cache_miss << endl;
	o << setw(W_sm_stats_t) << "mpl_attach_cnt " << t.mpl_attach_cnt << endl;
	o << setw(W_sm_stats_t) << "anchors " << t.anchors << endl;
	o << setw(W_sm_stats_t) << "compensate_in_log " << t.compensate_in_log << endl;
	o << setw(W_sm_stats_t) << "compensate_in_xct " << t.compensate_in_xct << endl;
	o << setw(W_sm_stats_t) << "compensate_records " << t.compensate_records << endl;
	o << setw(W_sm_stats_t) << "compensate_skipped " << t.compensate_skipped << endl;
	o << setw(W_sm_stats_t) << "log_switches " << t.log_switches << endl;
	o << setw(W_sm_stats_t) << "get_logbuf " << t.get_logbuf << endl;
	o << setw(W_sm_stats_t) << "await_1thread_xct " << t.await_1thread_xct << endl;
	o << setw(W_sm_stats_t) << "lock_query_cnt " << t.lock_query_cnt << endl;
	o << setw(W_sm_stats_t) << "unlock_request_cnt " << t.unlock_request_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_request_cnt " << t.lock_request_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_acquire_cnt " << t.lock_acquire_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_head_t_cnt " << t.lock_head_t_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_await_alt_cnt " << t.lock_await_alt_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_extraneous_req_cnt " << t.lock_extraneous_req_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_conversion_cnt " << t.lock_conversion_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_cache_hit_cnt " << t.lock_cache_hit_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_request_t_cnt " << t.lock_request_t_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_esc_to_page " << t.lock_esc_to_page << endl;
	o << setw(W_sm_stats_t) << "lock_esc_to_store " << t.lock_esc_to_store << endl;
	o << setw(W_sm_stats_t) << "lock_esc_to_volume " << t.lock_esc_to_volume << endl;
	o << setw(W_sm_stats_t) << "lk_vol_acq " << t.lk_vol_acq << endl;
	o << setw(W_sm_stats_t) << "lk_store_acq " << t.lk_store_acq << endl;
	o << setw(W_sm_stats_t) << "lk_page_acq " << t.lk_page_acq << endl;
	o << setw(W_sm_stats_t) << "lk_kvl_acq " << t.lk_kvl_acq << endl;
	o << setw(W_sm_stats_t) << "lk_rec_acq " << t.lk_rec_acq << endl;
	o << setw(W_sm_stats_t) << "lk_ext_acq " << t.lk_ext_acq << endl;
	o << setw(W_sm_stats_t) << "lk_user1_acq " << t.lk_user1_acq << endl;
	o << setw(W_sm_stats_t) << "lk_user2_acq " << t.lk_user2_acq << endl;
	o << setw(W_sm_stats_t) << "lk_user3_acq " << t.lk_user3_acq << endl;
	o << setw(W_sm_stats_t) << "lk_user4_acq " << t.lk_user4_acq << endl;
	o << setw(W_sm_stats_t) << "lock_wait_cnt " << t.lock_wait_cnt << endl;
	o << setw(W_sm_stats_t) << "lock_block_cnt " << t.lock_block_cnt << endl;
	o << setw(W_sm_stats_t) << "lk_vol_wait " << t.lk_vol_wait << endl;
	o << setw(W_sm_stats_t) << "lk_store_wait " << t.lk_store_wait << endl;
	o << setw(W_sm_stats_t) << "lk_page_wait " << t.lk_page_wait << endl;
	o << setw(W_sm_stats_t) << "lk_kvl_wait " << t.lk_kvl_wait << endl;
	o << setw(W_sm_stats_t) << "lk_rec_wait " << t.lk_rec_wait << endl;
	o << setw(W_sm_stats_t) << "lk_ext_wait " << t.lk_ext_wait << endl;
	o << setw(W_sm_stats_t) << "lk_user1_wait " << t.lk_user1_wait << endl;
	o << setw(W_sm_stats_t) << "lk_user2_wait " << t.lk_user2_wait << endl;
	o << setw(W_sm_stats_t) << "lk_user3_wait " << t.lk_user3_wait << endl;
	o << setw(W_sm_stats_t) << "lk_user4_wait " << t.lk_user4_wait << endl;
	return o;
}

#endif /* SM_STATS_T_OUT_GEN_CPP */
