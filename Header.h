#include <iostream>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <string>
#include <time.h>
#include <conio.h>
#include<dos.h>

using namespace std;

//Global variables score - for displaying score 
//Disp array that will store the entire crossword.

int score = 0, attempt = 0, randLevel;
string disp[20][20], ans;


//Declaration of class - Level which houses difficulty level & genre of each level/stage in the crossword. It is inherited therefore its private members are declared as protected
class Level {
protected:
	int difficulty;		
	string genre;
public:
	Level(string g=" ", int d = 1)
	{
		if (d > 0 && d < 4)
		{
			difficulty = d;
		}
		genre = g;
	}
	void setDifficulty(int d=1)
	{
		if (d > 0 && d < 4)
		{
			difficulty = d;
		}
	}
	void setGenre(string g = " ")
	{
		genre = g;
	}
	string getGenre()
	{
		return genre;
	}
	int getDifficulty()
	{
		return difficulty;
	}

};


//Declaration of class words that contains each word. It inherits the Level class.
class Words: public Level {
private:
	Level l;
	int chars;
	string orient;
	string text;
	string hint;
	int xPos;
	int yPos;
	int ID;
	int length;
public:
	Words(string g = ".", int d = 1, string h = " ", int c = 1, string o = " ", int xp = 0, int yp = 0, int id = 1, int len = 2, string t =" ") :Level(g, d)
	{
		
		chars = c;
		orient = o;
		hint = h;
		xPos = xp;
		yPos = yp;
		ID = id;
		length = len;
		text = t;
	}
	void setChars(int c=1)
	{
		chars = c;
	}
	void setLevel(Level x)
	{
		l = x;
		l.setDifficulty(x.getDifficulty());
		l.setGenre(x.getGenre());
	}
	void setOrient(string o)
	{
		orient = o;
	}
	void setHint(string h)
	{
		hint = h;
	}
	void setxPos(int xp=0)
	{
		xPos = xp;
	}
	void setyPos(int yp = 0)
	{
		yPos = yp;
	}
	void setID(int id = 1)
	{
		ID = id;
	}
	void setLength(int len = 2)
	{
		length = len;
	}
	void setText(string t = " ")
	{
		text = t;
	}
	int getChars()
	{
		return chars;
	}
	string getOrient()
	{
		return orient;
	}
	string getHint()
	{
		return hint;
	}
	int getxPos()
	{
		return xPos;
	}
	int getyPos()
	{
		return yPos;
	}
	int getID()
	{
		return ID;
	}
	string getText()
	{
		return text;
	}
	int getLength()
	{
		return length;
	}
};



Words** Ar = new Words * [6];


void Clear()
{
	system("CLS");
}




void Display(int current = 0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
	Clear();

	
	


	//Display the header with score, level & genre
	cout << "\nLevel: " << Ar[current][0].getDifficulty() <<"\t\tGenre: " << Ar[current][0].getGenre() << "\t\t  Score: " << score <<"/8\n\n";
	for (int i = 0; i < 20; i++)
	{
		//Displaying the crosswords with the correct colours
		for (int j = 0; j < 20; j++)
		{
			//Condition for displaying boxes that are black
			if (disp[i][j] == "   ")
			{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << disp[i][j];
			}
			//IF condition for displaying boxes that are white (have text)
			else 			
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 242);
				cout << disp[i][j];

			}
			
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
	cout << "\nHints: \n";
	//Display hints here:
	for (int j = 0; j < 8;j++)
	{
		cout << j + 1 << ". ("<<Ar[current][j].getOrient()<<")" << Ar[current][j].getHint() << endl;
	}
}


void Input()
{
	if (randLevel==8 && score==8)
	{

	}
	
	cout << "Enter the number you would like to attempt: ";
	attempt = 0;
	while (attempt < 1 || attempt>8)
	{
		
		cin >> attempt;
		if (attempt < 1 || attempt>8)
		{
			cerr << "Please enter a valid number." << endl;
		}
		else
		{
			cout << attempt << ". Answer: ";
			cin >> ans;
			if (ans == "e"||ans=="E")
			{
				exit(1);
			}
			if (ans == Ar[randLevel][attempt - 1].getText())
			{
				if (Ar[randLevel][attempt - 1].getChars() == 0)
				{
					//Comparing the correct answer with the one stored in the object. Then replacing the ? in display array with the specific letter.
					cout << "Correct answer! Press any key to attempt another word." << endl;
					_getch();
					score++;
					Ar[randLevel][attempt - 1].setChars(1);
					
					if (Ar[randLevel][attempt - 1].getOrient() == "ACROSS")
					{
						for (int i = 0; i < Ar[randLevel][attempt - 1].getLength(); i++)
						{
							string x = "   ";
							x[1] = ans[i];
							disp[Ar[randLevel][attempt - 1].getyPos()][Ar[randLevel][attempt - 1].getxPos()+i] = x;
						}
					}
					else if (Ar[randLevel][attempt - 1].getOrient() == "DOWN")
					{
						for (int i = 0; i < Ar[randLevel][attempt - 1].getLength(); i++)
						{
							string x = "   ";
							x[1] = ans[i];
							disp[Ar[randLevel][attempt - 1].getyPos() + i][Ar[randLevel][attempt - 1].getxPos()] = x;
						}
					}
					
				}
				else
				{
					
					cout << "This has already been attempted. Please attempt a different word. Press any key to try again." << endl;
					_getch();
				}
			}
			else
			{
				cout << "Incorrect answer. Press any key to try again." << endl;
				_getch();
			}
		}
	}
}

//Initialising stage - to be used before each level is called.
void InitialiseStage(int randLevel)
{
	//Initialising display array with empty string.
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			disp[i][j] = "   ";
		}
	}

	//Populating display array with ? where there is a word according to the array of Words objects.
	for (int i = 0; i < 8; i++)
	{
		int xPos = Ar[randLevel][i].getxPos();
		int yPos = Ar[randLevel][i].getyPos();
		int ID = Ar[randLevel][i].getID();
		string x = " ";
		if (Ar[randLevel][i].getOrient() == "ACROSS")
		{
			
			for (int j = 0; j < Ar[randLevel][i].getLength(); j++)
			{
				disp[yPos][xPos+j]=" ? ";
			}
			x.append(to_string(ID));
			x.append(" ");
			disp[yPos][xPos -1] = x;
		}
		else if (Ar[randLevel][i].getOrient() == "DOWN")
		{
			for (int j = 0; j < Ar[randLevel][i].getLength(); j++)
			{

				disp[yPos+j][xPos] = " ? ";
			}
			x.append(to_string(ID));
			x.append(" ");
			disp[yPos-1][xPos] = x;
		}

	}
}
//Driver class that stores the function to run the game.
class Driver {
public:
	void Game();
};

void Driver::Game()
{
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 188);
	Clear();
	cout << "\n\n\n\n\n\t\t\t\t\tWelcome to Crosswords!\n\t\tPress any key to start. Enter e at any point to end the game.\n\n\n\n\n\t\t\t\t\t";
	_getch();

	

	for (int i = 0; i < 6; i++)
	{
		Ar[i] = new Words[8];
	}

	//File Handling to copy elements from a .txt file to objects of the class "Words"
	ifstream file;
	file.open("words.txt");
	string w;
	if (file.fail())
	{
		cerr << "Error opening file." << endl;
		exit(1);
	}
	else
	{
		int count = 0; //Counting the number of words in a category - 8 in one category
		int countl = 0; //Counting the lines in the text file - 5 per word
		int countcat = 0;//Counting the number of categories - 6 in total
		while (countcat < 6) //To only copy data from the file till all words of the 6 levels have been made into objects.
		{

			if (!file.eof())
			{
				getline(file, w);	
				if (countl == 0)
				{
					int num = stoi(w);
					Ar[countcat][count].setID(num);
				
				}
				else if (countl == 1)
				{

					Ar[countcat][count].setText(w);
				
				}
				else if (countl == 2)
				{
					Ar[countcat][count].setHint(w);
				
				}
				else if (countl == 3)
				{
					Ar[countcat][count].setOrient(w);
				
				}
				else if (countl == 4)
				{
					int num = stoi(w);
					Ar[countcat][count].setLength(num);
				
				}
				else if (countl == 5)
				{
					int num = stoi(w);
					Ar[countcat][count].setxPos(num);
				
				}
				else if (countl == 6)
				{
					int num = stoi(w);
					Ar[countcat][count].setyPos(num);
				
				}

				if (w == "END")
				{
				
					count++;
					countl = 0;
				}
				else
				{
					countl++;
				}
				if (w == "FINAL")
				{
					countcat++;
					count = 0;
					countl = 0;
				}

			}

		}
	}

	//Declaration of Level objects.
	Level A1("Sports", 1);
	Level A2("General", 1);
	Level A3("Animals", 2);
	Level A4("Literary Genres", 2);
	Level A5("ELectronics", 3);
	Level A6("Capitals", 3);
	//Initialisation of words array through level objects.
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Ar[i][j].setChars(0);
			if (i == 0)
			{
				Ar[i][j].setLevel(A1);
				Ar[i][j].setDifficulty(A1.getDifficulty());
				Ar[i][j].setGenre(A1.getGenre());
			}
			else if (i == 1)
			{
				Ar[i][j].setLevel(A2);
				Ar[i][j].setDifficulty(A2.getDifficulty());
				Ar[i][j].setGenre(A2.getGenre());
			}
			else if (i == 2)
			{
				Ar[i][j].setLevel(A3);
				Ar[i][j].setDifficulty(A3.getDifficulty());
				Ar[i][j].setGenre(A3.getGenre());
			}
			else if (i == 3)
			{
				Ar[i][j].setLevel(A4);
				Ar[i][j].setDifficulty(A4.getDifficulty());
				Ar[i][j].setGenre(A4.getGenre());
			}
			else if (i == 4)
			{
				Ar[i][j].setLevel(A5);
				Ar[i][j].setDifficulty(A5.getDifficulty());
				Ar[i][j].setGenre(A5.getGenre());
			}
			else if (i == 5)
			{
				Ar[i][j].setLevel(A6);
				Ar[i][j].setDifficulty(A6.getDifficulty());
				Ar[i][j].setGenre(A6.getGenre());
			}
		}
	}

	
	srand(time(0));
	randLevel = rand() % 2 + 0;
	int counter2 = 0;
	bool end=false;
	while (score < 9||end == false)
	{
		
		if (score == 8)
		{
			srand(time(0));
			if (randLevel != 5 && randLevel != 6)
			{
				Display(randLevel);
				cout << "Congratulations, you have completed this level!\nPress any key to proceed to the next level!" << endl;
				_getch();

			}
			else if(randLevel==5 || randLevel == 6)
			{
				Clear();
				end = true;
				string z;
				cout << "\n\n\n\t\t\t\tCongratulations! You have passed all difficulties.\nPress e to end the game." << endl;
				cin >> z;
				if (z == "e"||z=="E")
				{
					exit(1);
				}
				score = 10;
			}
			Clear();
			score = 0;
			if (randLevel == 0 || randLevel == 1)
			{
				randLevel = rand() % 2 + 2;
				InitialiseStage(randLevel);
				Display(randLevel);
			}
			else if (randLevel == 2 || randLevel == 3)
			{
				randLevel = rand() % 2 + 4;
				InitialiseStage(randLevel);
				Display(randLevel);
			}
			
		}
		else if(counter2==0) {
			InitialiseStage(randLevel);
			Display(randLevel);
			Input();
		}
		else
		{
			Display(randLevel);
			Input();
		}
		counter2++;
	}
	

	//Deleting dynamically allocated memory
	for (int i = 0; i < 6; i++)
	{
		delete[] Ar[i];
	}
	delete[] Ar;
}
