#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>
#include <string>

using namespace std;

class Transport {
protected:
    int weight;
    int maxSpeed;
    double fuelConsumption;

    string number;

public:
    Transport(string number, int weight, int maxSpeed, double fuelConsumption)
        : weight(weight), maxSpeed(maxSpeed), fuelConsumption(fuelConsumption), number(number) {}

    virtual double calculateValue() = 0;
    virtual string getInfo() = 0;

    int getWeight() {
        return weight;
    }

    int getMaxSpeed() {
        return maxSpeed;
    }

    double getFuelConsumption() {
        return fuelConsumption;
    }

    string getNumber() {
        return number;
    }
};

class Car : public Transport {
private:
    int maxCargo;
    string segment;
    string bodyType;
    int passengerCount;
    string seatType;

public:
    Car(string number, int weight, int maxSpeed, double fuelConsumption, int maxCargo,
        string segment, string bodyType, int passengerCount, string seatType)
        : Transport(number, weight, maxSpeed, fuelConsumption), maxCargo(maxCargo),
        segment(segment), bodyType(bodyType), passengerCount(passengerCount),
        seatType(seatType) {}

    double calculateValue() override {
        if (seatType == "Шкiра" || seatType == "Шкіра") {
            double comfort = (maxSpeed * (2 - fuelConsumption / 100) * (maxCargo / 300) * 2.25) / 10;
            comfort = min(comfort, 100.0);
            return comfort;
        }
        else {
            double comfort = (maxSpeed * (2 - fuelConsumption / 100) * (maxCargo / 300) * 1.75) / 10;
            comfort = min(comfort, 100.0);
            return comfort;
        }
    }

    string getInfo() override {
        string Sweight = to_string(weight), SmaxSpeed = to_string(maxSpeed), SfuelConsumption = to_string(fuelConsumption),
            SmaxCargo = to_string(maxCargo), SpassengerCount = to_string(passengerCount);
        string info = "Номер: " + number + ". Вага: " + Sweight + ". Максимальна швидкiсть: " + SmaxSpeed + ". Витрата пального: " + SfuelConsumption
            + ". Максимальний багаж: " + SmaxCargo + ". Сегмент: " + segment + ". Тип кузова: " + bodyType + ". Кiлькiсть пасажирiв : " + SpassengerCount
            + ". Тип оббивки сидiнь: " + seatType;
        return info;
    }
};

class Motorcycle : public Transport {
private:
    bool hasSidecar;

public:
    Motorcycle(string number, int weight, int maxSpeed, double fuelConsumption, bool hasSidecar)
        : Transport(number, weight, maxSpeed, fuelConsumption), hasSidecar(hasSidecar) {}

    double calculateValue() override {
        double comfort = (maxSpeed * (2 - fuelConsumption / 10) * (1.5 + (hasSidecar ? 100 : 0) / 100)) / 10;
        comfort = min(comfort, 100.0);
        return comfort;
    }

    string getInfo() override {
        string Sweight = to_string(weight), SmaxSpeed = to_string(maxSpeed), SfuelConsumption = to_string(fuelConsumption), ShasSidecar;
        if (hasSidecar == 0)
        {
            ShasSidecar = "Коляски немає";
        }
        else
            ShasSidecar = "Коляска є";
        string info = "Номер: " + number + ". Вага: " + Sweight + ". Максимальна швидкiсть: " + SmaxSpeed + ". Витрата пального: " + SfuelConsumption
            + ". Наявнiсть коляски: " + ShasSidecar;
        return info;
    }
};

class Truck : public Transport {
private:
    int cargoCapacity;
    double cost;

public:
    Truck(string number, int weight, int maxSpeed, double fuelConsumption, int cargoCapacity, double cost)
        : Transport(number, weight, maxSpeed, fuelConsumption), cargoCapacity(cargoCapacity), cost(cost) {}

    double calculateValue() override {
        return cost;
    }

    string getInfo() override {
        string Sweight = to_string(weight), SmaxSpeed = to_string(maxSpeed), SfuelConsumption = to_string(fuelConsumption),
            ScargoCapacity = to_string(cargoCapacity), Scost = to_string(cost);
        string info = "Номер: " + number + ". Вага: " + Sweight + ". Максимальна швидкiсть: " + SmaxSpeed + ". Витрата пального: " + SfuelConsumption
            + ". Вантажнiсть: " + ScargoCapacity + ". Вартiсть (грн/місяць): " + Scost;
        return info;
    }
};

class Bus : public Transport {
private:
    int passengerCount;
    bool hasAirConditioning;
    bool hasRecliningSeats;
    bool hasGoodVisibility;
    int maxPassengerCargo;

public:
    Bus(string number, int weight, int maxSpeed, double fuelConsumption, int passengerCount,
        bool hasAirConditioning, bool hasRecliningSeats, bool hasGoodVisibility,
        int maxPassengerCargo)
        : Transport(number, weight, maxSpeed, fuelConsumption), passengerCount(passengerCount),
        hasAirConditioning(hasAirConditioning), hasRecliningSeats(hasRecliningSeats),
        hasGoodVisibility(hasGoodVisibility), maxPassengerCargo(maxPassengerCargo) {}

    double calculateValue() override {
        double comfort = ((maxSpeed * (2 - fuelConsumption / 100) + (hasAirConditioning ? 50 : 0) + (hasGoodVisibility ? 60 : 0)) * (2 + (maxPassengerCargo / 10))) / 10;
        comfort = min(comfort, 100.0);
        return comfort;
    }

    string getInfo() override {
        string Sweight = to_string(weight), SmaxSpeed = to_string(maxSpeed), SfuelConsumption = to_string(fuelConsumption),
            SpassengerCount = to_string(passengerCount), ShasAirConditioning, ShasRecliningSeats, ShasGoodVisibility, SmaxPassengerCargo = to_string(maxPassengerCargo);
        ShasAirConditioning = hasAirConditioning ? "Кондицiонер є" : "Кондицiонера немає";
        ShasRecliningSeats = hasRecliningSeats ? "Сидiння вiдкидуються" : "Сидiння не вiдкидуються";
        ShasGoodVisibility = hasGoodVisibility ? "Зручно" : "Незручно";
        string info = "Номер: " + number + ". Вага: " + Sweight + ". Максимальна швидкiсть: " + SmaxSpeed + ". Витрата пального: " + SfuelConsumption
            + ". Кiлькiсть пасажирiв: " + SpassengerCount + ". Наявнiсть кондицiонера: " + ShasAirConditioning + ". Наявнiсть вiдкидних сидiнь: " + ShasRecliningSeats
            + ". Зручнiсть видiв: " + ShasGoodVisibility + ". Максимальний багаж на пасажира: " + SmaxPassengerCargo;
        return info;
    }
};
class Transports {
private:
    vector<Transport*> transports;

public:
    void addTransport(Transport* transport)
    {
        transports.push_back(transport);
    }
    void addUserTransport() {
        string number;
        int weight, maxSpeed;
        double fuelConsumption;

        cin.ignore();
        cout << "Введiть номер транспортного засобу: ";
        getline(cin, number);

        cout << "Вага (кг): ";
        cin >> weight;

        cout << "Максимальна швидкiсть (км/г):  ";
        cin >> maxSpeed;

        cout << "Витрата пального на 100 км (л): ";
        cin >> fuelConsumption;
        cin.ignore();

        if (number.length() < 8 || weight <= 0 || maxSpeed <= 0 || fuelConsumption <= 0)
        {
            cout << "Некоректне значення." << endl;
        }
        else {
            string transportType;
            cout << "Тип транспортного засобу (Car - Легкове, Moto - Мотоцикл, Truck - Вантажiвка, Bus - Автобус): " << endl;
            getline(cin, transportType);

            if (transportType == "Car" || transportType == "car") {
                int maxCargo;
                string segment, bodyType;
                int passengerCount;
                string seatType;

                cout << "Максимальний можливий багаж (кг): ";
                cin >> maxCargo;
                cin.ignore();

                cout << "Клас за класифiкацiєю Європейської економiчної комiсiї (A-F, J, M, S): ";
                getline(cin, segment);

                cout << "Тип кузова (Седан, Кабрiолет, Унiверсал): ";
                cin >> bodyType;

                cout << "Кiлькiсть пасажирiв: ";
                cin >> passengerCount;
                cin.ignore();

                cout << "Тип оббивки сидiнь (Тканина, Шкiра): ";
                getline(cin, seatType);

                if (maxCargo <= 0 || passengerCount <= 0 || segment.length() > 2 || segment.length() < 1 || bodyType.length() < 1 || seatType.length() < 1) {
                    cout << "Некоректне значення." << endl;
                }
                else
                    transports.push_back(new Car(number, weight, maxSpeed, fuelConsumption, maxCargo, segment, bodyType, passengerCount, seatType));
            }
            else if (transportType == "Moto" || transportType == "moto") {
                bool hasSidecar;

                cout << "Наявнiсть коляски (yes - коляска є, no - коляски немає): ";
                string hasSidecarInput;
                cin.ignore();

                getline(cin, hasSidecarInput);
                hasSidecar = (hasSidecarInput == "yes");

                transports.push_back(new Motorcycle(number, weight, maxSpeed, fuelConsumption, hasSidecar));
            }
            else if (transportType == "Truck" || transportType == "truck") {
                int cargoCapacity;
                double cost;

                cout << "Вантажнiсть (кг): ";
                cin >> cargoCapacity;

                cout << "Цiна (грн): ";
                cin >> cost;
                cin.ignore();

                if (cargoCapacity <= 0 || cost <= 0)
                {
                    cout << "Некоректне значення." << endl;
                }
                else
                    transports.push_back(new Truck(number, weight, maxSpeed, fuelConsumption, cargoCapacity, cost));
            }
            else if (transportType == "Bus" || transportType == "bus") {
                int passengerCount;
                bool hasAirConditioning;
                bool hasRecliningSeats;
                bool hasGoodVisibility;
                int maxPassengerCargo;

                cout << "Кiлькiсть пасажирiв: ";
                cin >> passengerCount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Наявнiсть кондицiонера (yes - кондицiонер є, no - кондицiонеру немає): ";
                string hasAirConditioningInput;
                getline(cin, hasAirConditioningInput);
                hasAirConditioning = (hasAirConditioningInput == "yes");

                cout << "Наявнiсть вiдкидних сидiнь (yes - сидiння вiдкидуються, no - сидiння не вiдкидуються): ";
                string hasRecliningSeatsInput;
                getline(cin, hasRecliningSeatsInput);
                hasRecliningSeats = (hasRecliningSeatsInput == "yes");

                cout << "Зручнiсть видiв (yes - зручно, no - не зручно): ";
                string hasGoodVisibilityInput;
                getline(cin, hasGoodVisibilityInput);
                hasGoodVisibility = (hasGoodVisibilityInput == "yes");

                cout << "Максимальний можливий багаж на пасажира (кг): ";
                cin >> maxPassengerCargo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (passengerCount <= 0 || maxPassengerCargo <= 0)
                {
                    cout << "Некоректне значення." << endl;
                }
                else
                    transports.push_back(new Bus(number, weight, maxSpeed, fuelConsumption, passengerCount, hasAirConditioning, hasRecliningSeats, hasGoodVisibility, maxPassengerCargo));
            }
            else {
                cout << "Некоректний тип транспортного засобу." << endl;
            }
        }
    }

    vector<Transport*> findMostComfortableVehicles() {
        vector<Transport*> comfortableVehicles;

        int transportType;
        cout << "Тип транспортного засобу (1 - Легкове авто, 2 - Мотоцикл, 3 - Автобус): ";
        cin >> transportType;

        switch (transportType) {
        case 1: {
            for (Transport* transport : transports) {
                if (dynamic_cast<Car*>(transport)) {
                    comfortableVehicles.push_back(transport);
                }
            }
            sort(comfortableVehicles.begin(), comfortableVehicles.end(), [](Transport* a, Transport* b) {
                return a->calculateValue() > b->calculateValue();
                });
            return comfortableVehicles;
        }
        case 2: {
            for (Transport* transport : transports) {
                if (dynamic_cast<Motorcycle*>(transport)) {
                    comfortableVehicles.push_back(transport);
                }
            }
            sort(comfortableVehicles.begin(), comfortableVehicles.end(), [](Transport* a, Transport* b) {
                return a->calculateValue() > b->calculateValue();
                });
            return comfortableVehicles;
            break; }
        case 3: {
            for (Transport* transport : transports) {
                if (dynamic_cast<Bus*>(transport)) {
                    comfortableVehicles.push_back(transport);
                }
            }
            sort(comfortableVehicles.begin(), comfortableVehicles.end(), [](Transport* a, Transport* b) {
                return a->calculateValue() > b->calculateValue();
                });
            return comfortableVehicles;
            break; }
        default:
            cout << "Некоректний тип транспортного засобу." << endl;

        }
    }

    vector<Transport*> findMostAffordableVehicles() {
        vector<Transport*> affordableVehicles;

        for (Transport* transport : transports) {
            if (dynamic_cast<Truck*>(transport)) {
                affordableVehicles.push_back(transport);
            }
        }

        sort(affordableVehicles.begin(), affordableVehicles.end(), [](Transport* a, Transport* b) {
            return a->calculateValue() < b->calculateValue();
            });

        return affordableVehicles;
    }

    vector<Transport*> getList() {
        vector<Transport*> vehicleList;
        int transportType;
        cout << "Тип транспортного засобу (1 - Легкове авто, 2 - Мотоцикл, 3 - Вантажiвка, 4 - Автобус): ";
        cin >> transportType;

        switch (transportType) {
        case 1: {
            for (Transport* transport : transports) {
                if (dynamic_cast<Car*>(transport)) {
                    vehicleList.push_back(transport);
                }
            }
            break; }
        case 2: {
            for (Transport* transport : transports) {
                if (dynamic_cast<Motorcycle*>(transport)) {
                    vehicleList.push_back(transport);
                }
            }
            break;  }
        case 3: {
            for (Transport* transport : transports) {
                if (dynamic_cast<Truck*>(transport)) {
                    vehicleList.push_back(transport);
                }
            }
            break;  }
        case 4: {
            for (Transport* transport : transports) {
                if (dynamic_cast<Bus*>(transport)) {
                    vehicleList.push_back(transport);
                }
            }
            break;  }
        default: {
            cout << "Некоректний тип транспортного засобу." << endl;
            break;  }
        }
        return vehicleList;
    }

    ~Transports() {
        for (Transport* transport : transports) {
            delete transport;
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "ukr");

    Transports transports;

    Car* car1 = new Car("AA0011AH", 1500, 180, 8.5, 500, "C", "Седан", 5, "Шкiра");
    Car* car2 = new Car("AH1189HH", 1300, 200, 7.2, 400, "B", "Кабрiолет", 4, "Тканина");
    Motorcycle* moto1 = new Motorcycle("BH8900YY", 170, 190, 5.6, true);
    Motorcycle* moto2 = new Motorcycle("BT1189AK", 130, 220, 7.2, false);
    Truck* truck1 = new Truck("BC8995HK", 12000, 110, 27.4, 4240, 67000);
    Truck* truck2 = new Truck("AK9511AY", 4200, 130, 19.6, 1560, 30240);
    Bus* bus1 = new Bus("CE9500YH", 11000, 90, 26.2, 54, false, false, true, 15);
    Bus* bus2 = new Bus("AX1195YK", 19000, 100, 39.8, 90, true, true, false, 20);

    transports.addTransport(car1); transports.addTransport(car2);
    transports.addTransport(moto1); transports.addTransport(moto2);
    transports.addTransport(truck1); transports.addTransport(truck2);
    transports.addTransport(bus1); transports.addTransport(bus2);


    int choice = -1;

    cout << "Компанiя 'WheelsOfFortune - оренда транспорту' вiтає Вас! Ця програма створена компанiєю 'WheelsGoFar -оренда транспорту' в цiлях ознайомлення та спрощення менеджменту.\n";

    while (choice != 0) {
        cout << "Оберiть наступну дiю:\n1 - Додати транспортний засiб\n2 - Пiдбiр найкомфортнiшого транспортного засобу (легкове авто, мото, автобус)\n"
            << "3 - Пiдбiр найдоступнiшої вантажiвки для перевезення вантажу\n4 - Переглянути повну iнформацiю про транспортнi засоби\n0 - Завершити роботу\n";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            transports.addUserTransport();
            break; }
        case 2:
        {   vector<Transport*> comfortableVehiclesList = transports.findMostComfortableVehicles();
        cout << "Транспорти вiдсортованi за рiвнем комфорту:" << endl;
        for (Transport* vehicle : comfortableVehiclesList) {
            cout << "Номер: " << vehicle->getNumber() << ". Комфорт: " << vehicle->calculateValue() << endl;
        }
        break; }
        case 3:
        {   vector<Transport*> affordableVehiclesList = transports.findMostAffordableVehicles();
        cout << "Найдоступнiшi вантажiвки для перевезення вантажу:" << endl;
        for (Transport* vehicle : affordableVehiclesList) {
            cout << "Номер: " << vehicle->getNumber() << ". " << "Вартiсть: " << vehicle->calculateValue() << endl;
        }
        break; }
        case 4:
        {   vector<Transport*> list = transports.getList();
        for (Transport* vehicle : list) {
            cout << vehicle->getInfo() << endl;
        }
        break; }
        case 0:
        {   cout << "Завершення роботи.";
        break; }
        default:
        {   cout << "Помилка. Некоректне значення.\n";
        break; }
        }
    }
    transports.~Transports();

    return 0;
}


