#include <iostream>
#include <string>

using namespace std;

// Numarul total de culturi
#define MAX_CROPS 20

string GetUID(int size = 5) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string _;
	for (int i = 0; i < size; i++) _ += alphanum[rand() % (sizeof(alphanum) - 1)];
	return _;

}

// O clasa de baza pentru a pastra informatiile despre culturi
class Crop {
public:
	string id;
	string typeCrop;
	double cultivatedArea;
	double avgProdPerHectare;
	double pricePerUnit;

	void print() {
		cout << "Tipul de recolta                           : " << typeCrop << endl;
		cout << "Suprafata cultivata (pe hectar)         : " << cultivatedArea << endl;
		cout << "Productia medie pe hectar (tone) : " << avgProdPerHectare << endl;
		cout << "Pret pe unitate (tone)                : " << pricePerUnit << endl;
	}

	double calculateValue() {
		return (
			pricePerUnit * avgProdPerHectare
			) * cultivatedArea;
	}

};

class Farm {

	double FindCropValue(int index) {
		if (index <= 0 || index >= size) return -1L;

	}

public:
	int numCrops = MAX_CROPS;

	int findCropByID(string id) {
		if (id == "" || crops == nullptr) return -1;
		for (int i = 0; i < size; i++) {
			if (crops[i].id == id)
				return i;
		}
		return -1;
	}

	Crop* crops = nullptr;
	int size = 0;

	Farm(int numCrops = MAX_CROPS) : numCrops(numCrops) {

		if (numCrops <= 0) {
			cout << "[!] Numarul de culturi nu poate fi mai mic de 0! Setarea implicita." << endl;
			this->numCrops = MAX_CROPS;
		}

		crops = new Crop[this->numCrops];
	}

	void AddCrop(Crop crop) {

		// Creati un ID de utilizator aleatoriu:
		if (crop.id == "") {
			crop.id = GetUID();
		}

		if (size == numCrops) {
			cout << "[*] Ferma a fost plina de recolte! Nu se pot adauga mai multe" << endl;
			return;
		}
		crops[size++] = crop;

		cout << crop.typeCrop << " cu ID " << crop.id << " adaugat la ferma!" << endl;
	}

	void UpdateCrop(string id, Crop newCrop) {

		int index = findCropByID(id);
		if (index == -1) {
			cout << "[!] cu ID " << id << " nu a fost gasit!" << endl;
			return;
		}
		newCrop.id = id;
		crops[index] = newCrop;

		cout << "S-a actualizat decuparea cu ID " << newCrop.id << "!" << endl;
	}

	void CropsValue() {

		cout << "ID\tValue\tType" << endl;

		for (int i = 0; i < this->size; i++) {
			cout << this->crops[i].id
				<< "\t"
				<< this->crops[i].calculateValue()
				<< "\t"
				<< this->crops[i].typeCrop
				<< endl;
		}
	}

	double RealizedValue() {

		double sum = 0L;
		for (int i = 0; i < this->size; i++) {
			sum += this->crops[i].calculateValue();
		}

		return sum;
	}

	void DisplayCrops() {

		if (this->size <= 0) {
			cout << "[!] Nu au fost adaugate culturi la ferma!" << endl;
		}

		for (int i = 0; i < this->size; i++) {
			this->crops[i].print();
			cout << endl;
		}

	}

	Crop FindHighestValueCrop() {

		int index = 0;
		double val = this->crops[index].calculateValue();

		for (int i = 1; i < this->size; i++) {
			double aux = this->crops[i].calculateValue();
			if (aux > val) {
				index = i;
				val = aux;
			}
		}

		return this->crops[index];
	}

};


int main() {

	// Sterge ecranul de iesire al consolei
	system("cls");

	// Semanarea functiei aleatoare pentru a genera un sir aleator pentru functia GetUID
	srand((unsigned)time(NULL));

	int size = 0; // Dimensiune variabila
	int uOpt = 0; // Variabila optiunii utilizator
	string tmp;   // Variabila tmp de bazã pentru introducerea aleatorie a utilizatorului.
	Crop cropTmp; // Pentru pastrarea intrãrii utilizatorului.

	cout << "[[ Bine ati venit la Sistemul de gestiune al culturilor in ferma agricola ]]"
		<< endl << endl
		<< "- Inainte de a merge inainte. Va rugam sa specificati numarul de culturi pe care doriti sa le aveti in ferma dumneavoastra: ";
	cin >> size;

	// Validarea intrari
	while (size <= 0 || cin.fail()) {
		cin.clear();
		cin.ignore('\n', INT_MAX);
		cout << "Valoare invalida. Incearca din nou: ";
		cin >> size;
	}

	// Crearea obiectului
	Farm farm(size);

	cout << "Ferma a fost initializata cu valoarea de " << size << "!" << endl;
	system("pause");


	do {
		system("cls");
		cout << "[[ Bine ati venit la Sistemul de gestiune al culturilor in ferma agricola ]]"
			<< endl << endl
			<< "Va rugam sa selectati o optiune de mai jos:\n"
			<< "1. Adaugati culturi\n"
			<< "2. Actualizati culturile\n"
			<< "3. Determinati valoarea fiecarei culturi\n"
			<< "4. Valoare realizata de ferma\n"
			<< "5. Decupati cu cea mai mare valoare\n"
			<< "6. Afiseaza toate culturile\n"
			<< "0. Iesire\n"
			<< "\n>> ";

		cin >> uOpt;
		cout << endl;

		switch (uOpt) {


		case 1:
			cropTmp.id = GetUID();

			cout << "Introduceti tipul de culturi: ";
			cin >> cropTmp.typeCrop;

			cout << "Introduceti dimensiunea suprafetei cultivate: ";
			cin >> cropTmp.cultivatedArea;

			cout << "Introduceti productia medie pe hectar: ";
			cin >> cropTmp.avgProdPerHectare;

			cout << "Introduceti pretul pe unitate: ";
			cin >> cropTmp.pricePerUnit;

			farm.AddCrop(cropTmp);
			break;
		case 2:
			// Imprimarea tuturor UID-urilor existente:
			cout << "Urmatoarele culturi exista: ";
			for (int i = 0; i < farm.size; i++) {
				cout << farm.crops[i].id << " | " << farm.crops[i].typeCrop << endl;
			}
			cout << "\nIntroduceti ID-ul culturii pe care doriti sa o actualizati: ";
			cin >> tmp;

			cropTmp.id = tmp;

			cout << "Introduceti tipul actualizat de culturi: ";
			cin >> cropTmp.typeCrop;

			cout << "Introduceti dimensiunea actualizata a suprafetei cultivate: ";
			cin >> cropTmp.cultivatedArea;

			cout << "Introduceti productia medie actualizata pe hectar: ";
			cin >> cropTmp.avgProdPerHectare;

			cout << "Introduceti pretul actualizat pe unitate: ";
			cin >> cropTmp.pricePerUnit;

			farm.UpdateCrop(tmp, cropTmp);
			break;

		case 3:
			farm.CropsValue();
			break;

		case 4:
			cout << "Valoarea totala realizata a fermei: " << farm.RealizedValue() << endl;
			break;

		case 5:
			cout << "Cultura cu cea mai mare valoare:" << endl;
			farm.FindHighestValueCrop().print();
			break;

		case 6:
			farm.DisplayCrops();
			break;

		default:
			cout << "Valoare introdusa nevalida!" << endl;
			break;
		}

		system("pause");

	} while (uOpt != 0);
}