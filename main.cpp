#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <conio.h>
using namespace std;

int digit(int i)
{
	int count = 0;
	do {
		i /= 10;
		count++;
	} while (i != 0);
	return count;
}


string LayerOn(string& text)
{
	const string Alphabet = "'8G-Mv/(q`mzt{FSA>Vg5 :*hC.Ox,!RQufdT=DZyoB&%KE$)c@rs+H<l?3eXW0_^JnY9wIL2U;7iP6]4kpj[a1~N}b#";
	const string KeyChain = "5;FOa?-bM/L& rH@9tCvzy_g7ZAf$!E[N4`,X.:]J{p*=PkV0ouSs>21+}K#lUcYqndGmT^Rwx%I)6ie<83jQWBD~h('";

	string message{};
	for (int i = 0; i < text.length(); i++)
		message += KeyChain[Alphabet.find(text.substr(i, 1))];

	return message;
}


string LayerOff(string& text)
{
	const string Alphabet = "'8G-Mv/(q`mzt{FSA>Vg5 :*hC.Ox,!RQufdT=DZyoB&%KE$)c@rs+H<l?3eXW0_^JnY9wIL2U;7iP6]4kpj[a1~N}b#";
	const string KeyChain = "5;FOa?-bM/L& rH@9tCvzy_g7ZAf$!E[N4`,X.:]J{p*=PkV0ouSs>21+}K#lUcYqndGmT^Rwx%I)6ie<83jQWBD~h('";

	string message{};
	for (int i = 0; i < text.length(); i++)
		message += Alphabet[KeyChain.find(text.substr(i, 1))];

	return message;
}



string KeyInverse(int*& KeyPass, int& Key_size)
{
	string SolidKey{};
	for (size_t i = 0; i < Key_size; i++)
		SolidKey += to_string(digit(KeyPass[i])) + to_string(KeyPass[i]);

	const string Alphabet = "0123456789";
	const string KeyChain = "ImDarkHeRo";

	for (size_t i = 0; i < SolidKey.length(); i++)
		SolidKey[i] = KeyChain[Alphabet.find(SolidKey[i])];

	return SolidKey;
}


void GenerateKey(const string& Alphabet, int*& KeyPass)
{
	unsigned int sval;
	time_t t;
	sval = (unsigned)time(&t);
	srand(sval);

	int key{};
	int size = Alphabet.length();
	KeyPass = new int[size];

	for (int i = 0; i < size - 1; i++)
	{
		key = rand() % (size - i);
		KeyPass[i] = key;
	}
}


void char_del(string& text, int pos)
{
	int size = text.length();
	for (int i = 1; i < size - pos; i++)
		text[(pos + i) - 1] = text[pos + i];
	text[size - 1] = NULL;
}



string crAlpha(string Alphabet, string& SolidKey)
{
	int* Key{ nullptr };
	GenerateKey(Alphabet, Key);
	int Key_size = Alphabet.length() - 1;
	string KeyChain{};

	for (int i = 0; i < Key_size; i++)
	{
		KeyChain += Alphabet[Key[i]];
		char_del(Alphabet, Key[i]);
	}
	KeyChain += Alphabet[0];

	SolidKey = KeyInverse(Key, Key_size);
	delete[] Key;
	return KeyChain;
}

string Encrype(string& text)
{
	const string Alphabet = "'QXR4F2#t$>Zy1EGUmz.7J:va;A0V({ ~6S!3rC-OYxPoB[q9Hp+@d}Mi?w%TejI]n*D_Lscf,h5lukg&<8b^=)N/KW";
	string Encryped{};
	string KeyChain = crAlpha(Alphabet, Encryped);
	Encryped += "`";

	int size = text.length();
	for (int i = 0; i < size; i++)
		Encryped += KeyChain[Alphabet.find(text.substr(i, 1))];

	Encryped = LayerOn(Encryped);
	return Encryped;
}


void KeyInverse(string& alphabet, string& SolidKey, int*& KeyPass)
{
	const string Alphabet = "0123456789";
	const string KeyChain = "ImDarkHeRo";
	int size = SolidKey.length();

	for (int i = 0; i < size; i++)
		SolidKey[i] = Alphabet[KeyChain.find(SolidKey[i])];

	KeyPass = new int[alphabet.length() - 1];

	string temp = "";
	int m = 0;
	for (int i = 0; i < size; i++)
	{
		temp += SolidKey.substr((i + 1), stoi(SolidKey.substr(i, 1)));
		KeyPass[m] = stoi(temp);
		m++;
		i += stoi(SolidKey.substr(i, 1));
		temp = "";
	}
}


string recrAlpha(string Alphabet, string& SolidKey)
{
	int* Key{ nullptr };
	KeyInverse(Alphabet, SolidKey, Key);
	int Key_size = Alphabet.length() - 1;
	string KeyChain{};

	for (int i = 0; i < Key_size; i++)
	{
		KeyChain += Alphabet[Key[i]];
		char_del(Alphabet, Key[i]);
	}
	KeyChain += Alphabet[0];

	delete[] Key;
	return KeyChain;
}

string Decrype(string text)
{
	text = LayerOff(text);

	const string Alphabet = "'QXR4F2#t$>Zy1EGUmz.7J:va;A0V({ ~6S!3rC-OYxPoB[q9Hp+@d}Mi?w%TejI]n*D_Lscf,h5lukg&<8b^=)N/KW";

	string SolidKey = text.substr(0, text.find("`"));
	string message = text.substr((text.find("`") + 1), (text.length() - 1));
	string KeyChain = recrAlpha(Alphabet, SolidKey);
	
	string Decryped{};
	
	for (int i = 0; i < message.length(); i++)
		Decryped += Alphabet[KeyChain.find(message.substr(i, 1))];

	return Decryped;
}


int main()
{
	ofstream errorList{ "errorList.txt", ios::out| ios::app };
	if (!errorList)
	{
		cerr << "Error while opening file...";
		_getch();
		return 0;
	}

	while (true)
	{
		system("cls");
		string userText{};
		string encryped{};
		string decryped{};

		cout << "\n\n\tEnter your text:\n\n\t";
		getline(cin, userText);

		encryped = Encrype(userText);
		cout << "\n\n\n\tEncryped:\n\n\t" << encryped << endl;

		decryped = Decrype(encryped);
		cout << "\n\n\n\tDecryped back:\n\n\t" << decryped;

		if(decryped != userText)
		{
			errorList << "\n====== ENCRYPE ====================================================================\n\n"
				<< userText
				<< "\n\n"
				<< encryped
				<< "\n\n"
				<< decryped
				<< endl;

			cout << "\n\n\n\tERROR OCCURRED!!!";
		}
		_getch();
	}


	//while (true)
	//{
	//	system("cls");
	//	string userText{};
	//	string decryped{};
	//	string encryped{};

	//	cout << "\n\n\tEnter your text:\n\n\t";
	//	getline(cin, userText);

	//	decryped = Decrype(userText);
	//	cout << "\n\n\n\tDecryped:\n\n\t" << decryped << endl;

	//	encryped = Encrype(decryped);
	//	cout << "\n\n\n\tEncryped back:\n\n\t" << encryped;

	//	if (decryped != Decrype(encryped))
	//	{
	//		errorList << "\n====== DECRYPE ====================================================================\n\n"
	//			<< userText
	//			<< "\n\n"
	//			<< decryped
	//			<< "\n\n"
	//			<< encryped
	//			<< "\n\n"
	//			<< Decrype(encryped)
	//			<< endl;

	//		cout << "\n\n\n\tERROR OCCURRED!!!";
	//	}
	//	_getch();
	//}

	errorList.close();
	cout << endl;
	system("pause");
	return 0;
}