// TODO: currently num_warp is fixed to 1.  Implement proper warp activation.
// wspawn is only executed on lane 0
if (LANE == 0) {
  printf("vx_wspawn: RS1=%lu\n", RS1);
  unsigned long i = 0;
  for (; i < RS1; i++) {
    p->spawn_warp(i, true, RS2);
  }
  // despawn the remaining warps
  for (; i < NUM_THREADS; i++) {
    p->spawn_warp(i, false, RS2 /* dontcare */);
  }
}
