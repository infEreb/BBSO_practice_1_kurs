#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include "practice.h"


using namespace std;

void cleanBuff()
{
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();
}

void mainMenu()
{
        cout << "What do you want?\n";
		cout << "1. Create own army\n";
		cout << "2. Use existing army\n";
		cout << "3. Exit\n";
		cout << ">> ";
}
void createMenu()
{
    cout << "1. Create a solder\n";
    cout << "2. Create a mechanism\n";
    cout << "3. Create a rider\n";
    cout << "4. Damage army\n";
    cout << "5. Show army info\n";
	cout << "6. Show unit info\n";
	cout << "7. Exit\n";
    cout << ">> ";
}
void existMenu()
{
    cout << "1. Create a solder\n";
    cout << "2. Create a mechanism\n";
    cout << "3. Create a rider\n";
    cout << "4. Damage army\n";
    cout << "5. Show army info\n";
    cout << "6. Show unit info\n";
    cout << "7. Exit\n";
    cout << ">> ";
}
void soldierMenu()
{
    cout << "1. Barbarian\n";
    cout << "2. Back\n";
    cout << ">> ";
}
void mechanismMenu()
{
    cout << "1. Cannon\n";
    cout << "2. Catapult\n";
    cout << "3. Back\n";
    cout << ">> ";
}
void animalMenu()
{
    cout << "1. Elephant\n";
    cout << "2. Back\n";
    cout << ">> ";
}
void armorMenu()
{
    cout << "1. None armor\n";
    cout << "2. Iron armor\n";
    cout << "3. Back\n";
    cout << ">> ";
}
void ammoMenu()
{
    cout << "1. None ammo\n";
    cout << "2. Stone\n";
    cout << "3. Bullet\n";
    cout << "4. Back\n";
    cout << ">> ";
}

void createSoldier(Army &army);
void createMechanism(Army &army);
void createRider(Army &army);


int main()
{

	int main_choice;

	do
	{
		mainMenu();
        
		cin >> main_choice;
        
        cleanBuff();

		switch(main_choice)
		{
			case 1:
			{
                
				// CREATE A FILE WITH ARMY INFO
				string n;
				cout << "An army file name(without format): ";
				getline(cin, n);
                n = n + ".txt";
                
                Army army(n, 'n');
				// CREATE AN ARMY
                
				int create_choice;
				do
				{
					// MAIN CREATE MENU
					createMenu();

					cin >> create_choice;
                    cleanBuff();

					switch(create_choice)
					{
						case 1:
						{
                            createSoldier(army);
                            break;
						}
						case 2:
						{
                            createMechanism(army);
                            break;
						}
						case 3:
						{
                            createRider(army);
                            break;
						}
						case 4:
						{
                            cout << "\n=====DAMAGE ARMY" << "\n";
                            cout << "Enter damge: ";
                            unsigned int damage;
                            cin >> damage;
                            cleanBuff();
                            
                            army.takeDamage(damage);
                            cout << "==========\n\n";
                            
                            break;
						}
						case 5:
						{
                            cout << "\n==========ARMY STATES==========\n";
                            cout << "Army COUNT: " << army.getArmyCount() << "\n";
                            cout << "Army HP: " << army.getArmyHealth() << "\n";
                            cout << "Army DEF: " << army.getArmyDefence() << "\n";
                            cout << "Army DMG: " << army.getArmyDamage() << "\n";
                            cout << "===============================\n\n";
                            
                            break;
						}
						case 6:
						{
                            cout << "Enter unit's index: ";
                            int idx;
                            cin >> idx;
                            cleanBuff();
                            
                            cout << "\n========UNIT INFO========\n";
                            if(army.getArmyCount() >= 0 && idx > 0 && idx < army.getArmyCount())
                            {
                                cout << army[idx]->getInfo() << "\n";
                            }
                            else
                            {
                                cout << "FAIL INDEX\n";
                            }
                            cout << "===========================\n\n";
                            
                            break;
                        }
						default:
						{
							break;
						}
					}
					
				}
				while(create_choice != 7);
                
                for(int i = 0; i < army.getArmyCount(); i++)
                {
                    army.writeUnit(army[i]);
                }
                
				break;
			}
			case 2:
			{
                string n;
                cout << "An army file name(without format): ";
                getline(cin, n);
                n = n + ".txt";
                
                Army army(n, 'e');
                
                int exist_choice;
                
                do
                {
                    existMenu();
                    
                    cin >> exist_choice;
                    cleanBuff();
                    
                    switch(exist_choice)
                    {
                        case 1:
						{
                            createSoldier(army);
                            break;
						}
						case 2:
						{
                            createMechanism(army);
                            break;
						}
						case 3:
						{
                            createRider(army);
                            break;
						}
                        case 4:
                        {
                            cout << "\n=====DAMAGE ARMY" << "\n";
                            cout << "Enter damge: ";
                            unsigned int damage;
                            cin >> damage;
                            cleanBuff();
                            
                            army.takeDamage(damage);
                            cout << "==========\n\n";
                            
                            break;
                        }
                        case 5:
                        {
                            cout << "\n==========ARMY STATES==========\n";
                            cout << "Army COUNT: " << army.getArmyCount() << "\n";
                            cout << "Army HP: " << army.getArmyHealth() << "\n";
                            cout << "Army DEF: " << army.getArmyDefence() << "\n";
                            cout << "Army DMG: " << army.getArmyDamage() << "\n";
                            cout << "===============================\n\n";
                            
                            break;
                        }
                        case 6:
                        {
                            cout << "Enter unit's index: ";
                            int idx;
                            cin >> idx;
                            cleanBuff();
                            
                            cout << "\n========UNIT INFO========\n";
                            if(army.getArmyCount() > 0 && idx >= 0 && idx < army.getArmyCount())
                            {
                                cout << army[idx]->getInfo() << "\n";
                            }
                            else
                            {
                                cout << "FAIL INDEX\n";
                            }
                            cout << "===========================\n\n";
                            
                            break;
                        }
                        
                        default:
                            break;
                    }
                }
                while(exist_choice != 7);
                
                for(int i = 0; i < army.getArmyCount(); i++)
                {
                    army.writeUnit(army[i]);
                }
                
				break;
			}
			default:
			{
				break;
			}
			
		}

	}
	while(main_choice != 3);
	return 0;
}

void createSoldier(Army &army)
{
    cout << "Choose soldier:\n";
    int soldier_choice;
    do
    {
        soldierMenu();
        cin >> soldier_choice;
        cleanBuff();
        
        switch(soldier_choice)
        {
            case 1:
            {
                cout << "\nChoose armor:\n";
                int armor_choice;
                do
                {
                    armorMenu();
                    cin >> armor_choice;
                    cleanBuff();
                    
                    switch(armor_choice)
                    {
                        case 1:
                        {
                            
                            Unit *unit = new Barbarian(250, 25, new NoneArmor());
                            army.addUnit(unit);
                            
                            break;
                        }
                        case 2:
                        {
                            
                            Unit *unit = new Barbarian(250, 25, new IronArmor(25));
                            army.addUnit(unit);
                            
                            break;
                        }
                        default:
                            break;
                    }
                }
                while(armor_choice < 1 || armor_choice > 3);
                
                break;
            }
            default:
                break;
        }
    }
    while(soldier_choice < 1 || soldier_choice > 2);
}
void createMechanism(Army &army)
{
    cout << "\nChoose mechanism:\n";
    int mechanism_choice;
    do
    {
        mechanismMenu();
        cin >> mechanism_choice;
        cleanBuff();
        
        switch(mechanism_choice)
        {
            case 1:
            {
                cout << "\nChoose ammo:\n";
                int ammo_choice;
                do
                {
                    ammoMenu();
                    cin >> ammo_choice;
                    cleanBuff();
                    
                    switch(ammo_choice)
                    {
                        case 1:
                        {
                            
                            Unit *unit = new Cannon(850, new NoneAmmo(), 10);
                            army.addUnit(unit);
                            
                            break;
                        }
                        case 2:
                        {
                            
                            Unit *unit = new Cannon(850, new Stone("*SKILL*", 20), 10);
                            army.addUnit(unit);
                            
                            break;
                        }
                        case 3:
                        {
                            
                            Unit *unit = new Cannon(850, new Bullet("*SKILL*", 25), 10);
                            army.addUnit(unit);
                            
                            break;
                        }
                        default:
                            break;
                    }
                }
                while(ammo_choice < 1 || ammo_choice > 4);
                
                break;
            }
            case 2:
            {
                cout << "\nChoose ammo:\n";
                int ammo_choice;
                do
                {
                    ammoMenu();
                    cin >> ammo_choice;
                    cleanBuff();
                    
                    switch(ammo_choice)
                    {
                        case 1:
                        {
                            
                            Unit *unit = new Catapult(850, new NoneAmmo(), 10);
                            army.addUnit(unit);
                            
                            break;
                        }
                        case 2:
                        {
                            
                            Unit *unit = new Catapult(850, new Stone("*SKILL*", 20), 10);
                            army.addUnit(unit);
                            
                            break;
                        }
                        case 3:
                        {
                            
                            Unit *unit = new Catapult(850, new Bullet("*SKILL*", 25), 10);
                            army.addUnit(unit);
                            
                            break;
                        }
                        default:
                            break;
                    }
                }
                while(ammo_choice < 1 || ammo_choice > 4);
                
                break;
            }
            default:
                break;
        }
    }
    while(mechanism_choice < 1 || mechanism_choice > 3);
}
void createRider(Army &army)
{
    cout << "\nChoose rider:\n";
    int rider_choice;
    
    do
    {
        soldierMenu();
        
        cin >> rider_choice;
        cleanBuff();
        
        switch(rider_choice)
        {
            case 1:
            {
                cout << "\nChoose animal:\n";
                int animal_choice;
                
                do
                {
                    animalMenu();
                    
                    cin >> animal_choice;
                    cleanBuff();
                    
                    switch(animal_choice)
                    {
                        case 1:
                        {
                            
                            Unit *unit = new Rider(new Barbarian(150, 25, new NoneArmor()), new Elephant(350, 10, 15));
                            army.addUnit(unit);
                            
                            break;
                        }
                        default:
                            break;
                    }
                    
                }
                while(animal_choice < 1 || animal_choice > 2);
                
                break;
            }
            default:
                break;
        }
        
    }
    while(rider_choice < 1 || rider_choice > 2);
}









