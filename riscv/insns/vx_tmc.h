// find the leftmost active lane
unsigned int leftmost = 0;
for (; leftmost < NUM_THREADS; leftmost++) {
  if (STATE.thread_mask[leftmost]) {
    break;
  }
}
// execute tmc for only that lane
// FIXME: not sure this assertion should be true
assert(leftmost == 0 && "vx_tmc executing on something other than 0th-lane");
if (LANE == leftmost) {
  for (unsigned int i = 0; i < NUM_THREADS; i++) {
    reg_t bitmask = (1ul << i);
    STATE.thread_mask[i] = ((bitmask & RS1) != 0ul);
  }
  fprintf(stderr, "warp: %u: set thread_mask: ", p->get_id());
  for (unsigned int i = 0; i < NUM_THREADS; i++) {
    fprintf(stderr, "%d ", STATE.thread_mask[i] ? 1 : 0);
  }
  // if all threads got deactivated, deactivate this warp
  bool all_inactive = true;
  for (unsigned int i = 0; i < NUM_THREADS; i++) {
    if (STATE.thread_mask[i]) {
      all_inactive = false;
      break;
    }
  }
  fprintf(stderr, "\n");
  if (all_inactive) {
    p->spawn_warp(p->get_id(), false, 0 /* dontcare */);
    fprintf(stderr, "warp: %u: all lanes inactive, despawning warp\n", p->get_id());
  }
}
