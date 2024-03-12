#define BATTALIAN_SHIP_COUNT 4

typedef struct{
	int x;
	int y;
}Coordinates;

// Creatinf a Structure for Escort Ships
typedef struct{
        int index;
        Coordinates position;
	float maxV;
        float minV;
        float maxA;
        float minA;
        char type[5];
}InitialConditionsEscort;

//Creatinf a Structure for EscortShip types
typedef struct{
	char type[5];
	char name[50];
	char gun_name[50];
	float impact_power;
	int angle_range;
	float minA;
	float maxV;
	float minV;
}EscortShipType;

// Creating a Structer for Battalian Ships
typedef struct{
        Coordinates position;
	float maxV;
        char type;
}InitialConditionsBattalian;

//Creating a structure for Battalian Ship Types
typedef struct{
	char name[10];
	char type;
	char gun_name[10];
}BattalianShipType;
