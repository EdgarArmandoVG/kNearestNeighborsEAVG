#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
class KNNClasificador {
private:
    struct PuntoDatos {
        std::string cliente;
        int edad;
        double prestamo;
        std::string estadoPago;
    };
    std::vector<PuntoDatos> conjuntoDatos;
public:
    KNNClasificador() {
        conjuntoDatos = {
            {"juan", 25, 40000, "n"},
            {"pedro", 35, 60000, "n"},
            {"luis", 45, 80000, "n"},
            {"javier", 20, 20000, "n"},
            {"carlos", 35, 120000, "n"},
            {"marcos", 52, 18000, "n"},
            {"anita", 23, 95000, "y"},
            {"patricia", 40, 62000, "y"},
            {"gabriel", 60, 100000, "y"},
            {"jimmy", 48, 200000, "y"},
            {"jorge", 33, 150000, "y"}
        };
    }
    double calcularDistancia(int edad1, double prestamo1, int edad2, double prestamo2) {
        double diferenciaEdad = edad1 - edad2;
        double diferenciaPrestamo = prestamo1 - prestamo2;
        return std::sqrt(diferenciaEdad * diferenciaEdad + diferenciaPrestamo * diferenciaPrestamo);
    }
    std::string clasificar(int edad, double prestamo, int k) {
        std::vector<std::pair<double, std::string>> distancias;
        for (const auto& punto : conjuntoDatos) {
            double distancia = calcularDistancia(edad, prestamo, punto.edad, punto.prestamo);
            distancias.emplace_back(distancia, punto.estadoPago);
        }
        std::sort(distancias.begin(), distancias.end());
        int contadorSi = 0;
        int contadorNo = 0;
        for (int i = 0; i < k; ++i) {
            if (distancias[i].second == "y")
                contadorSi++;
            else
                contadorNo++;
        }
        if (contadorSi > contadorNo)
            return "y";
        else
            return "n";
    }
};
int main() {
    KNNClasificador clasificador;
    int k = 5;
    int edad;
    double prestamo;
    std::string nombre;
    std::cout << "Ingrese el nombre de la persona: ";
    std::getline(std::cin, nombre);
    std::cout << "Ingrese la edad de la persona (anios): ";
    std::cin >> edad;
    std::cout << "Ingrese el prestamo de la persona (cantidad): ";
    std::cin >> prestamo;
    std::string prediccion = clasificador.clasificar(edad, prestamo, k);
    std::cout << "Para la persona con el nombre de:"<<nombre<<" su valor default (clasificacion) es: " << prediccion << std::endl;
    return 0;
}
