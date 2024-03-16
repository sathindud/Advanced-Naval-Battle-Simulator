void simulation1();
void simulation2();

void escortSimulation(int escort_count, InitialConditionsEscort escort[escort_count], Coordinates battalian);
void findMaxMinAngle(float * minA, float * maxA);
bool check(Coordinates attacker, Coordinates victim, float min_range, float max_range);
float range(int angle, float velocity);