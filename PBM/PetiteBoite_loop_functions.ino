// These functions are going to be used by both loop_master.ino and loop_slave.ino

void setupGoalSpeed() {
  //
  if (checkMicroSwitchState() == HIGH) {
    goal_speed = goal_speed_part1;
  }
  else {
    goal_speed = goal_speed_part2;
  }
}