#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include<math.h>
#include <fstream>

using namespace sf;

int size = 56;
int szachownica[8][8];



void ustaw_szachownice()

{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			szachownica[i][j] = 0;
		}
	}

	szachownica[0][0] = -1;
	szachownica[0][1] = -2;
	szachownica[0][2] = -3;
	szachownica[0][3] = -4;
	szachownica[0][4] = -5;
	szachownica[0][5] = -3;
	szachownica[0][6] = -2;
	szachownica[0][7] = -1;
	szachownica[1][0] = -6;
	szachownica[1][1] = -6;
	szachownica[1][2] = -6;
	szachownica[1][3] = -6;
	szachownica[1][4] = -6;
	szachownica[1][5] = -6;
	szachownica[1][6] = -6;
	szachownica[1][7] = -6;

	szachownica[7][0] = 1;
	szachownica[7][1] = 2;
	szachownica[7][2] = 3;
	szachownica[7][3] = 4;
	szachownica[7][4] = 5;
	szachownica[7][5] = 3;
	szachownica[7][6] = 2;
	szachownica[7][7] = 1;
	szachownica[6][0] = 6;
	szachownica[6][1] = 6;
	szachownica[6][2] = 6;
	szachownica[6][3] = 6;
	szachownica[6][4] = 6;
	szachownica[6][5] = 6;
	szachownica[6][6] = 6;
	szachownica[6][7] = 6;

}


bool isPath(Vector2i from, Vector2i to)//sprawdza czy nic nie stoi po drodze
{
	int dx = from.x - to.x;
	int dy = from.y - to.y;
	Vector2i check(0, 0);
	if (dx != 0)
		check.x = dx < 0 ? 1 : -1;
	if (dy != 0)
		check.y = dy < 0 ? 1 : -1;
	bool ret = true;
	Vector2i wek = from;
	
	while (wek != to) {
		wek.x += check.x;
		wek.y += check.y;
		int tileType = szachownica[wek.y][wek.x];
		
		if (tileType != 0 && wek != to) {
			ret = false;
			break;
		}
	}
	return ret;
}


int ktoWygral()
{
	bool czyjestbialykrol = false, czyjestczarnykrol = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (szachownica[i][j] == 5) czyjestbialykrol = true;
			if (szachownica[i][j] == -5) czyjestczarnykrol = true;
		}
	}
	if (czyjestbialykrol == true && czyjestczarnykrol == false) return 1;
	if (czyjestbialykrol == false && czyjestczarnykrol == true) return -1;
	else return 0;
	}




bool isValidMove(Vector2i from, Vector2i to, int typ)
{
	int targetType = szachownica[to.y][to.x];

	int dx = abs(from.x - to.x);
	int dy = abs(from.y - to.y);
	
	// logika gry 
	if (typ == 6) { // pionek
		if (dx != 0) {
			if (dx > 1)
				return false;
			if (dy == 1)
				if (targetType == 0)
					return false;
				else
					return true;
			else
				return false;
		}
		else {
			if (dy > 2) // wiecej niz 2 pola
				return false;
			else if (dy == 2) // o 2 pola
				if (from.y == 1 || from.y == 6) // czy z odpowiedniej linii?
					if (targetType != 0) // zajete
						return false;
					else
						return true;
				else
					return false;
			else // o 1 pole
				if (targetType != 0) // cos tam stoi
					return false;
		}
	}
	else if (typ == 5) { // Król
		if (dx < 2 && dy < 2)
			return true;
		else
			return false;
	}
	else if (typ == 4) { // królowa
		if (!isPath(from, to))
			return false;
		if (dx == 0 && dy != 0)
			return true;
		else if (dy == 0 && dx != 0)
			return true;
		else if (dy == dx)
			return true;
		else
			return false;
	}
	else if (typ == 3) { // laufer
		if (dx == dy && isPath(from, to))
			return true;
		else
			return false;
	}
	else if (typ == 2) { // Koñ
		int dx = abs(from.x - to.x);
		int dy = abs(from.y - to.y);
		if (dx == 2 && dy == 1)
			return true;
		else if (dx == 1 && dy == 2)
			return true;
		return false;
	}
	else if (typ == 1) { // wie¿a
		if (!isPath(from, to))
			return false;
		if (dx != 0 && dy != 0)
			return false;
		else
			return true;
	}
	return true;
}

Vector2i sprawdz_ktore_pole(Vector2i poz) // funkcja ustala ktore pole szchownicy zosta³o klikniete
{
	int a = 0, b = 0;
	a = floor(poz.x / 54);
	b = floor(poz.y / 54);
	return Vector2i(a, b);
}

std::string ruch(Vector2i z, Vector2i dokad, int typ)//funkcja zwracaj¹ca zapis ruchy w polskiej szachowej notacji algebraicznej
{
	std::string text;
	if (abs(typ) == 1) text = "W";
	if (abs(typ) == 2) text = "S";
	if (abs(typ) == 3) text = "G";
	if (abs(typ) == 4) text = "H";
	if (abs(typ) == 5) text = "K";
	

	if (z.x == 0) text = text + "a";
	if (z.x == 1) text = text + "b";
	if (z.x == 2) text = text + "c";
	if (z.x == 3) text = text + "d";
	if (z.x == 4) text = text + "e";
	if (z.x == 5) text = text + "f";
	if (z.x == 6) text = text + "g";
	if (z.x == 7) text = text + "h";

	text = text + std::to_string(abs(z.y - 8));
	if (dokad.x == 0) text = text + "a";
	if (dokad.x == 1) text = text + "b";
	if (dokad.x == 2) text = text + "c";
	if (dokad.x == 3) text = text + "d";
	if (dokad.x == 4) text = text + "e";
	if (dokad.x == 5) text = text + "f";
	if (dokad.x == 6) text = text + "g";
	if (dokad.x == 7) text = text + "h";
	text =text+ std::to_string(abs(dokad.y - 8));
	return text;
}


int main()
{
	RenderWindow window(VideoMode(448, 448), "Szachy");

	std::fstream plik;
	Texture t1, t2,t3,selectorTexture;
	Font font;

	plik.open("obrazy/gra.txt", std::ios::out);
	t1.loadFromFile("obrazy/figury.png");
	t2.loadFromFile("obrazy/plansza.png");
	t3.loadFromFile("obrazy/plansza_koncowa.png");
	selectorTexture.loadFromFile("obrazy/selector.png");
	font.loadFromFile("obrazy/arial.ttf");
		
	String miejsce = "start";
	Sprite selectorSprite;
	Sprite koniec(t3);
	Sprite sBoard(t2);
	RectangleShape rectangle(Vector2f(54, 54));
	selectorSprite.setTextureRect(IntRect(0, 0, 56, 56));
	selectorSprite.setTexture(selectorTexture);
	
	int selectedType = 0;
	Vector2i pole;
	ustaw_szachownice();
	Vector2i selected(0, 0);
	int kolejGracza = 1; // 1 - bialy, 0 - czarny

	
	while (window.isOpen())
	{
		

		window.setSize(sf::Vector2u(448, 448));//w petli glownej aby nie mozna by³o zmienic rozmiaru
		Vector2i pozycja = Mouse::getPosition(window); //pozycja myszy

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		if (e.type == Event::MouseButtonPressed)
		{
			pole = sprawdz_ktore_pole(pozycja); //które pole zosta³o klikniete
			int typFigury = szachownica[pole.y][pole.x];
		

			if ((kolejGracza == 0 && typFigury < 0) || (kolejGracza == 1 && typFigury > 0)) // gracz klika na swoja figure
			{
				selectorSprite.setPosition((pole.x) * 56, (pole.y) * 56);
				selected.x = pole.x;
				selected.y = pole.y;
				selectedType = typFigury;

			}
			else if (selectedType != 0)
			{
				// pionek jest juz wybrany, a gracz kliknal na puste pole
				// abs bo nie ma znaczenia kogo - jak kliknie na swoja figure zlapie go wczesniejszy if
				if (isValidMove(selected, pole, abs(selectedType)) == true)
				{
					plik << ruch(selected, pole, selectedType) << std::endl;
					szachownica[selected.y][selected.x] = 0;
					szachownica[pole.y][pole.x] = selectedType;
					selectedType = 0;
					kolejGracza = (kolejGracza + 1) % 2;
					
				}
			}
			
		}
	
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			ustaw_szachownice();
			miejsce = "start";
			kolejGracza = 1;
			plik << "Kolejna partia:\n";

		}


		window.clear();
		if (miejsce == "start")
		{
			
			window.draw(sBoard);
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					Sprite f;
					int n = szachownica[i][j];
					if (n == 0) continue;//pomin puste pole
					int x = abs(n) - 1;// wartosc ca³kowita -1 odpowiada za figure
					int y = n > 0 ? 1 : 0; //warunek : n>0 , jeœli prawda 1, jeœli fa³sz 0, odpowiada za kolor figury
					f.setTextureRect(IntRect(size*x, size*y, size, size));
					f.setPosition(size*j, size*i);
					f.setTexture(t1);
					window.draw(f);
				}
			}
			if (selectedType != 0) window.draw(selectorSprite);
		}

		if (ktoWygral() == -1 || ktoWygral() == 1) miejsce= "koniec";
			
		
			if (miejsce == "koniec")
		{
			String tekst;
			if (ktoWygral() == -1) { tekst = "Wygraly czarne"; plik << "Wygraly czarne\n"; }
			if (ktoWygral() == 1) { tekst = "Wygraly biale"; plik << "Wygraly biale\n"; }
			Text text(tekst, font, 50);
			Text text2("aby zaczac od nowa wcisnij spacje",font,20);
			text2.setPosition(75, 250);
			text.setPosition(60, 170);
			window.draw(koniec);
			window.draw(text);
			window.draw(text2);
			
		}
	
		window.display();
	}

	return 0;
}