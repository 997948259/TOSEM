 </
define p:sqlite3_prepare_v2_call=1;
define q:sqlite3_finalize_call=1;
alw(p->som(q))
/>

/*
* Entry point for the application.
*/
struct Trooper
{
	// Trooper Stats.
	int id and 
	char name[10] and 
	// Attack Stats.
	float attackRaw and
	float attackRawRange and
	float attackBonus and
	float attackBonusRange and
	int attackRange and

	// Defence Stats.
	float defence and

	// Percentages.
	float criticalChance and
	float criticalDamage and
	float evasion and
	float skillCooldown and

	// Health.
	float maximumHealth and
	float health and

	// Movement.
	int numberOfTiles and

	// Actions.
	int numberOfActions
};

function trooperID(int value,Trooper* _trooperData)
{ 
	_trooperData->id <== value and skip
};
function trooperName(char* value,Trooper* _trooperData)
{ 
	//_trooperData->id <== value and skip
	strcpy(_trooperData->name, value) and skip
};
function setRawAttack( float value,Trooper* _trooperData)
{
	 _trooperData->attackRaw  <== value and skip 
};
function setRawAttackRange( float value,Trooper* _trooperData)
{
	 _trooperData->attackRawRange  <== value and skip  
};
function setBonusAttack( float value,Trooper* _trooperData)
{ 
	_trooperData->attackBonus  <== value and skip  
};
function setBonusAttackRange( float value,Trooper* _trooperData)
{
	_trooperData->attackBonusRange  <== value and skip
};
function setAttackRange( int value,Trooper* _trooperData)			
{
	_trooperData->attackRange  <== value and skip  
};
function setRawDefence( float value,Trooper* _trooperData)			
{
	 _trooperData->defence  <== value and skip  
};
function setCriticalChance( float value,Trooper* _trooperData)		
{
	 _trooperData->criticalChance  <== value and skip  
};
function setCriticalMultiplier( float value,Trooper* _trooperData)	
{
	_trooperData->criticalDamage <== value and skip  
};
function setEvasion( float value,Trooper* _trooperData)				
{ 
	_trooperData->evasion  <== value and skip  
};
function setCooldown( float value,Trooper* _trooperData)			
{
	_trooperData->skillCooldown  <== value and skip  
};
function setMaxHealth( float value,Trooper* _trooperData)			
{ 
	_trooperData->maximumHealth  <== value and skip  
};
function setCurrentHealth( float value,Trooper* _trooperData)		
{ 
	_trooperData->health  <== value and skip 
};
function setMovement( int value,Trooper* _trooperData)				
{	
	_trooperData->numberOfTiles  <== value and skip  
};
function setNumberOfActions( int value,Trooper* _trooperData)		
{ 
	_trooperData->numberOfActions  <== value and skip  
};
function TrooperInit(Trooper* _trooperData)
{
	_trooperData->id<==1 and skip;
	_trooperData->attackRaw <== (float)10.0 and skip;
	_trooperData->attackRawRange <== 2.0 and skip;
	_trooperData->attackBonus <== 15.0 and skip;
	_trooperData->attackBonusRange <== 5.0 and skip;
	_trooperData->attackRange <== 1 and skip;
	_trooperData->defence <== 5.0 and skip;
	_trooperData->criticalChance <== 0.0 and skip;
	_trooperData->criticalDamage <== 1.0 and skip;
	_trooperData->evasion <== 0.0 and skip;
	_trooperData->skillCooldown <== 0.0 and skip;
	_trooperData->maximumHealth <== 100.0 and skip;
	_trooperData->health <== 100.0 and skip;
	_trooperData->numberOfTiles <== 2 and skip;
	_trooperData->numberOfActions <== 1 and skip
};
frame(verifystat,_trooperData,_trooperData1,databaseConnectionStatus,i) and(
Trooper _trooperData[3] and skip;
Trooper _trooperData1 and skip;
int i<==0 and skip;
while(i<3)
{
	TrooperInit(&_trooperData[i]);
	i:=i+1
};
TrooperInit(&_trooperData1);
 int verifystat<==0 and skip;
	 while(verifystat<10282719)
	 {
		verifystat:=verifystat+1
	 };
function onLoad()
{
	frame(databaseConnection,sqlCommand,index,trooper) and (
	//cout << "Loaded, now do something with the database." << endl;
	printf("Loaded, now do something with the database.\n") and skip;
	int databaseConnection and skip;
	char* sqlCommand and skip;
	int index<==0 and skip;

	// Select all of the objects in the Units table.
	sqlCommand <== "SELECT * from Units" and skip;

	// Send the command to the SQLite database and fetch the results to the trooper results variable.
	databaseConnection <== sqlite3_prepare_v2(_databaseConnection, sqlCommand, -1, &trooperResults, 0) and skip;
	
	// Loading trooper data!
	while (sqlite3_step(trooperResults) = 100)
	{
		Trooper trooper and skip;
		// Accessing the trooper data from the SQL database.
		//trooper.id <== sqlite3_column_int(trooperResults, 0) and skip;
		trooperID(sqlite3_column_int(trooperResults, 0),&trooper);

		//trooper.attackRaw <== sqlite3_column_double(trooperResults, 2) and skip;
		//trooper.attackRawRange <== sqlite3_column_double(trooperResults, 3) and skip;
		//trooper.attackBonus <== sqlite3_column_double(trooperResults, 4) and skip;
		//trooper.attackBonusRange <== sqlite3_column_double(trooperResults, 5) and skip;
		setRawAttack(sqlite3_column_double(trooperResults, 2),&trooper);
		setRawAttackRange(sqlite3_column_double(trooperResults, 3),&trooper);
		setBonusAttack(sqlite3_column_double(trooperResults, 4),&trooper);
		setBonusAttackRange(sqlite3_column_double(trooperResults, 5),&trooper);

		//trooper.attackRange <== sqlite3_column_int(trooperResults, 6) and skip;
		//trooper.defence <== sqlite3_column_double(trooperResults, 7) and skip;
		//trooper.criticalChance <== sqlite3_column_double(trooperResults, 8) and skip;
		//trooper.criticalDamage <== sqlite3_column_double(trooperResults, 9) and skip;
		setAttackRange(sqlite3_column_int(trooperResults, 6),&trooper);
		setRawDefence(sqlite3_column_double(trooperResults, 7),&trooper);
		setCriticalChance(sqlite3_column_double(trooperResults, 8),&trooper);
		setCriticalMultiplier(sqlite3_column_double(trooperResults, 9),&trooper);


		//trooper.evasion <== sqlite3_column_double(trooperResults, 10) and skip;
		//trooper.skillCooldown <== sqlite3_column_double(trooperResults, 11) and skip;
		//trooper.maximumHealth <== sqlite3_column_double(trooperResults, 12) and skip;
		//trooper.numberOfTiles <== sqlite3_column_int(trooperResults, 13) and skip;
		//trooper.numberOfActions <== sqlite3_column_int(trooperResults, 14) and skip;
		setEvasion(sqlite3_column_double(trooperResults, 10),&trooper);
		setCooldown(sqlite3_column_double(trooperResults, 11),&trooper);
		setMaxHealth(sqlite3_column_double(trooperResults, 12),&trooper);
		setMovement(sqlite3_column_int(trooperResults, 13),&trooper);
		setNumberOfActions(sqlite3_column_int(trooperResults, 14),&trooper);

		_trooperData[index]<==trooper and skip;
		trooperName((char*)(sqlite3_column_text(trooperResults, 1)), &_trooperData[index]);
		index:=index+1
	}
)
};

	int databaseConnectionStatus <== sqlite3_open("F:/SQLiteInputFile/project-database.db", &_databaseConnection) and skip;

	if (databaseConnectionStatus!=0)then
	{
		//cout << "Cannot open database." << endl;
		printf("Cannot open database.\n")
	}
	else
	{
		//cout << "Database opened successfully." << endl;
		printf("Database opened successfully.\n") and skip;
		onLoad();
		// Looping through the trooper data setup in SQLite Studio.
		i<==0 and skip;
		while(i<3)
		{
			// Displaying trooper information.
			Trooper trooper <== _trooperData[i] and skip;
			//string messagePrefix = trooper.name + " ";
			//cout << messagePrefix << "Raw Attack = " << trooper.attackRaw << endl;
			printf("%s Raw Attack = ", trooper.name) and skip;
			output(trooper.attackRaw) and skip;
			output("\n") and skip;
			i:=i+1
		};
		sqlite3_close(_databaseConnection) and skip
	}
)