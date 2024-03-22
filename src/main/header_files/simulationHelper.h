float range(int angle, float velocity);
bool check(float distance, float min_range, float max_range);
void findMaxMinAngle(float * minA, float * maxA);
bool escortSimulation(int escort_count, InitialConditionsEscort * escort , Coordinates battalian, float * health);
float calculateTime(float velocity, float distance);
void battalianSimulation(InitialConditionsBattalian battalian, int escort_count, InitialConditionsEscort escort[escort_count]);
void removeAttackedEscots(int * escort_count, InitialConditionsEscort * escorts);
Coordinates movePosition(Coordinates current, Coordinates destination);
int findItterationCount(Coordinates current, Coordinates destination);
Coordinates changeCoordinate(Coordinates current, Coordinates destination);

void removeRowTime(int * escort_count, Time * escort, int index);
void removeRowEscort(int * escort_count, InitialConditionsEscort * escort, int index);

float getDistance(Coordinates attacker, Coordinates victim);