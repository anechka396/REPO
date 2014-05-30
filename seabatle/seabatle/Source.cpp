#include <iostream>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

extern "C"  int __stdcall userhit(int, int, char*);

vector <pair<int, int> > oneV;
map < pair<int, int>, vector<int> > compShips;
char *fildComp = new char[100];
int id = 0;

void ppolef(char **pole)
{
	for (int i = 0; i < 10; i++)
	for (int j = 0; j < 10; j++)
		pole[i][j] = 0;
}

int chooseorient()
{
	srand(time(NULL));
	return rand() % 2;
}

int CoordK()
{
	srand(time(NULL));
	return rand() % 10;
}

int place_ship(int s, int c, int dir, int deck, char** ar)
{
	int e = 0;
	switch (dir)
	{
	case 0:
		if (s>0 && c>0)
		if (ar[s - 1][c - 1] == 127)
		{
			e = 1;
		}
		if (s>0 && (c + deck)<10)
		if (ar[s - 1][c + deck] == 127)
		{
			e = 1;
		}
		if (s <9 && c>0)
		if (ar[s + 1][c - 1] == 127)
		{
			e = 1;
		}
		if (s<9 && (c + deck)<10)
		if (ar[s + 1][c + deck] == 127)
		{
			e = 1;
		}
		if (c>0)
		if (ar[s][c - 1] == 127)
		{
			e = 1;
		}
		if ((c + deck)<10)
		if (ar[s][c + deck] == 127)
		{
			e = 1;
		}
		for (int i = 0; i < deck; i++)
		{
			if (s>0 && (c + i)<10)
			if (ar[s - 1][c + i] == 127)
			{
				e = 1;
			}
			if (s<9 && (c + i)<10)
			if (ar[s + 1][c + i] == 127)
			{
				e = 1;
			}
		}
		break;
	case 1:
		if (s > 0 && c > 0)
		if (ar[s - 1][c - 1] == 127)
		{
			e = 1;
		}
		if (s > 0 && c < 9)
		if (ar[s - 1][c + 1] == 127)
		{
			e = 1;
		}
		if ((s + deck)<10 && c>0)
		if (ar[s + deck][c - 1] == 127)
		{
			e = 1;
		}
		if ((s + deck) < 10 && c<9)
		if (ar[s + deck][c + 1] == 127)
		{
			e = 1;
		}
		if (s>0)
		if (ar[s - 1][c] == 127)
		{
			e = 1;
		}
		if ((s + deck) < 10)
		if (ar[s + deck][c] == 127)
		{
			e = 1;
		}
		for (int i = 0; i < deck; i++)
		{
			if ((s + i)<10 && c>0)
			if (ar[s + i][c - 1] == 127)
			{
				e = 1;
			}
			if ((s + i) < 10 && c < 9)
			if (ar[s + i][c + 1] == 127)
			{
				e = 1;
			}
		}
		break;
	}
	return e;
}

void set(char** ar, int k)
{
	bool isset = 0;
	int hCoord, vCoord;
	int dir;
	while (isset == 0) 
	{
		dir = chooseorient(); 
		hCoord = CoordK(); 
		vCoord = CoordK();
		int e = 0;
		switch (dir)
		{
		case 0:
			if ((vCoord + k - 1)<10)
			if (ar[hCoord][vCoord + k - 1] == 0)
			{
				e = place_ship(hCoord, vCoord, dir, k, ar); // проверка смежных клеток
				if (e == 0)
				{
					id++;
					for (int i = 0; i < k; i++)
					{
						compShips[make_pair(hCoord, vCoord + i)].push_back(id);
						compShips[make_pair(hCoord, vCoord + i)].push_back(0);
						ar[hCoord][vCoord + i] = 127;
					}
					isset = 1;
				}
			}
			break;
		case 1:
			if ((hCoord - 1) >= 0 && (vCoord + k) <10 && (hCoord + k - 1)<10)
			if (ar[hCoord + k - 1][vCoord] == 0)
			{
				e = place_ship(hCoord, vCoord, dir, k, ar);
				if (e == 0)
				{
					id++;
					for (int i = 0; i < k; i++)
					{
						compShips[make_pair(hCoord + i, vCoord)].push_back(id);
						compShips[make_pair(hCoord + i, vCoord)].push_back(0);
						ar[hCoord + i][vCoord] = 127;
					}
					isset = 1;
				}
			}
			break;
		}
	}
}

void vect_one(char** ar)
{
	for (int i = 0; i < 10; i++)
	for (int j = 0; j < 10; j++)
	if (ar[i][j] == 0)
	{
		bool flag = true;
		if (i>0)
		if (ar[i - 1][j] != 0)
			flag = false;
		if (j>0)
		if (ar[i][j - 1] != 0)
			flag = false;
		if (i<9)
		if (ar[i + 1][j] != 0)
			flag = false;
		if (j<9)
		if (ar[i][j + 1] != 0)
			flag = false;
		if (i>0 && j>0)
		if (ar[i - 1][j - 1] != 0)
			flag = false;
		if (i>0 && j<9)
		if (ar[i - 1][j + 1] != 0)
			flag = false;
		if (i<9 && j>0)
		if (ar[i + 1][j - 1] != 0)
			flag = false;
		if (i<9 && j<9)
		if (ar[i + 1][j + 1] != 0)
			flag = false;
		if (flag == true)
			oneV.push_back(make_pair(i, j));
	}
}

void setone(char** ar)
{
	vect_one(ar);
	int sizeV = oneV.size();
	if (sizeV != 0)
	{
		id++;
		srand(time(NULL));
		int number = rand() % sizeV;
		ar[oneV[number].first][oneV[number].second] = 127;
		compShips[make_pair(oneV[number].first, oneV[number].second)].push_back(id);
		compShips[make_pair(oneV[number].first, oneV[number].second)].push_back(0);
	}
	else
		cout << "kslj" << endl;
	oneV.clear();
}

/*int userhit(int &x, int &y, char** ar)
{
	if (ar[x][y] == 127)
	{
		return 1;
	}
	else if (ar[x][y] == '*' || ar[x][y] == '.')
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
*/

int chekerHit(int &x, int &y, char** ar)
{
	int temp_id = compShips[make_pair(x, y)][0];
	compShips[make_pair(x, y)][1] = 1;
	for (map < pair<int, int>, vector<int> >::iterator iter = compShips.begin(); iter != compShips.end(); iter++)
	{
		if (iter->second[0] == temp_id)
		{
			if (iter->second[1] == 0)
				return 0;
		}
	}
	return 1;
}

bool FreeField(int& x_c, int& y_c, char** user)
{
	if (user[x_c][y_c] == 0)
		return true;
	else
		return false;
}

void GenShot(int& x_c, int& y_c, char** user)
{
	bool fl = true;
	do
	{
		fl = true;
		x_c = CoordK();
		y_c = CoordK();
		if (FreeField(x_c, y_c, user) == 0)
			fl = false;
	} while (fl == false);
}

void Game(int& countOfShipsC, int& countOfShipsU, char** user, char** fieldComp)
{
	bool flag = true;
	while (countOfShipsC < 20 || countOfShipsU != 20)
	{
		int x, y;
		do
		{
			flag = true;
			cout << "User, enter the horizontal coordinate 0-9." << endl;
			cin >> x;
			cout << "User, enter the vertical coordinate 0-9." << endl;
			cin >> y;
			int condition = userhit(x, y, fildComp);
			if (condition == 1)
			{
				countOfShipsC++;
				fieldComp[x][y] = '*';
				fildComp[x + 10 * y] = '*';
				int condition2 = chekerHit(x, y, fieldComp);
				if (condition2 == 0)
					cout << "You have hit!!!" << endl;
				else
					cout << "You have kill!!!" << endl;
				flag = false;
			}
			else
			if (condition == -1)
			{
				cout << "You have already shot in this place. Try again." << endl;
				flag = false;
			}
			else
			if (condition == 0)
			{
				fieldComp[x][y] = '.';
				fildComp[x + 10 * y] = '.';
				cout << "You've missed!" << endl;
			}
		} while (flag == false);

		int hit = 0;
		int route;
		int x_c = 0, y_c = 0;
		int result_of_shot;
		bool flag2 = true;
		do
		{
			flag2 = true;
			GenShot(x_c, y_c, user);

			cout << "The horizontal coordinate is " << x_c << endl;
			cout << "The vertical coordinate is " << y_c << endl;
			cout << "Enter the result of shot(if missed - 0, hit - 1, kill - 2): ";
			cin >> result_of_shot;
			if (result_of_shot == 1 || result_of_shot == 2)
			{
				flag2 = false;
				countOfShipsU++;
				user[x_c][y_c] = 1;
			}
			else
				user[x_c][y_c] = -1;
		} while (flag2 == false);
	}
}

int main()
{
	char **fieldComp = new char *[10];
	for (int i = 0; i < 10; i++)
		fieldComp[i] = new char[10];
	ppolef(fieldComp);

	char **user = new char*[10];
	for (int i = 0; i<10; i++)
		user[i] = new char[10];
	ppolef(user);

	cout << "Please, waiting some secods!" << endl;

	set(fieldComp, 4);
	set(fieldComp, 3);
	cout << "Hello!" << endl;
	set(fieldComp, 3);
	cout << "I'm your computer." << endl;
	set(fieldComp, 2);
	cout << "I want to play with you in the sea battle." << endl;
	set(fieldComp, 2);
	cout << "Please, waiting some secods!" << endl;
	set(fieldComp, 2);
	cout << "           >__<" << endl;
	setone(fieldComp);
	setone(fieldComp);
	setone(fieldComp);
	setone(fieldComp);

	int countOfShipsC = 0;
	int countOfShipsU = 0;

	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		if (fieldComp[i][j] != 0)
			cout << fieldComp[i][j];
		else
			cout << '-';
		cout << endl;
	}*/

	for (int i = 0; i < 10; i++)
	for (int j = 0; j < 10; j++)
		fildComp[i + 10 * j] = fieldComp[i][j];

	Game(countOfShipsC, countOfShipsU, user, fieldComp);

	if (countOfShipsC == 20)
		cout << "Computer win!" << endl;
	else
		cout << "User win!" << endl;

	for (int i = 0; i<10; i++)
		delete[]user[i];
	delete[]user;

	for (int i = 0; i<10; i++)
		delete[]fieldComp[i];
	delete[]fieldComp;

	delete[] fildComp;
}