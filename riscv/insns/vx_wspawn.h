// TODO: before overwriting PCs of the other warps, assert that those warps have
// terminated by checking if their thread_mask == 0
// wspawn is only executed on lane 0
assert(LANE == 0 && "vx_wspawn only executes on lane 0");
printf("vx_wspawn: RS1=%lu\n", RS1);
unsigned long i = 0;
for (; i < RS1; i++) {
  p->spawn_warp(i, true, RS2);
 }
// despawn the remaining warps
for (; i < NUM_WARPS; i++) {
  p->spawn_warp(i, false, RS2 /* dontcare */);
}
