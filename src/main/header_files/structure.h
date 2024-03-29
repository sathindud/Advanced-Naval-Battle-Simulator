#define BATTALIAN_SHIPS_TYPES 5
#define BMAX_ANGLE 45

#define GRAVITY 9.8
#define HEALTH 100



typedef struct{
	int x;
	int y;
}Coordinates;

// Creatinf a Structure for Escort Ships
typedef struct{
        int index;
        Coordinates position;
		float impact_power;
		float maxV;
        float minV;
        float maxA;
        float minA;
		int time;
        char type[5];
}InitialConditionsEscort;

typedef struct{
	int index;
	float time;
}Time;

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
	int time;
}EscortShipType;

// Creating a Structer for Battalian Ships
typedef struct{
    Coordinates position;
	float maxV;
	int max_angle;
	float time;
    char type;
}InitialConditionsBattalian;

//Creating a structure for Battalian Ship Types
typedef struct{
	char name[10];
	char type;
	char gun_name[10];
}BattalianShipType;

typedef struct{
	Coordinates position;
	int battaleship_status;
	int escort_index;
	float cumulative_impact;
}BattalianShipLog;

typedef struct{
	int index;
	float time;
}EscortShipsLog;

typedef struct 
{
	Coordinates canvas_size;
	int escort_count;
}UserInput;

