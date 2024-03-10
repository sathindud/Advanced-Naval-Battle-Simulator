typedef struct{
        int index;
        int x;
        int y;
        float maxV;
        float minV;
        float maxA;
        float minA;
        char type;
}InitialConditionsEscort;

// Creatinf a Structer for Battalian Ships
typedef struct{
        int x;
        int y;
        float maxV;
        char type;
}InitialConditionsBattalian;

void inputBattalianShip();
void inputEscortShips();
void getship();
