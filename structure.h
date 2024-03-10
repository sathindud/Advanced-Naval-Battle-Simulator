#define BATTALIAN_SHIP_COUNT 4

typedef struct{
        int index;
        int x;
        int y;
        float maxV;
        float minV;
        float maxA;
        float minA;
        char type[5];
}InitialConditionsEscort;

// Creating a Structer for Battalian Ships
typedef struct{
        int x;
        int y;
        float maxV;
        char type;
}InitialConditionsBattalian;

//Creating a structure for Battalian Ship Types
typedef struct{
	char name[10];
	char type;
	char gun_name[10];
}BattalianShipType;

typedef struct{
	char type[5];
	char name[10];
	char gun_name[10];
	float impact_power;
	float angle_range;
	float minA;
	float maxV;
	float minV;
}EscortShipType;
