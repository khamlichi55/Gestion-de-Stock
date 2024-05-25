#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <map>
#include <sstream> // Assurez-vous que cette bibliothèque est incluse

using namespace std;

class Produit {
public:
    string reference;
    string nom;
    double prix;
    string fournisseur;
    int quantite;

    Produit(string ref, string nm, double pr, string frn, int qty)
        : reference(ref), nom(nm), prix(pr), fournisseur(frn), quantite(qty) {}
};

class Fournisseur {
public:
    string nom;
    string adresse;

    Fournisseur(string n, string ad) : nom(n), adresse(ad) {}
};

class Magasin {
public:
    string nom;
    string adresse;
    vector<Produit> stock;
    vector<pair<string, string>> historique; // paire de (opération, date)
    map<string, vector<pair<string, string>>> historiqueFournisseur;

    Magasin(string nm, string addr) : nom(nm), adresse(addr) {}

    void ajouterProduit(Produit produit) {
        auto P = find_if(stock.begin(), stock.end(), [&](Produit& p) { return p.reference == produit.reference; });
        if (P == stock.end()) {
            stock.push_back(produit);
            cout << "Produit ajoute avec succes !" << endl;
        }
        else {
            cout << "Un produit avec la meme reference existe deja !" << endl;
        }
    }


    void modifierProduit(string reference, double nouveauPrix, int nouvelleQuantite) {
        auto P = find_if(stock.begin(), stock.end(), [&](Produit& p) { return p.reference == reference; });
        if (P != stock.end()) {
            P->prix = nouveauPrix;
            P->quantite = nouvelleQuantite;
            cout << "Produit modifie avec succes !" << endl;
        }
        else {
            cout << "Produit non trouve !" << endl;
        }
    }
    void afficherTOUTProduit() {
        for (auto& p : stock) {
            cout << "----------------------------" << endl;
            cout << "          " << endl;
            cout << "Reference : " << p.reference << endl;
            cout << "Nom : " << p.nom << endl;
            cout << "Prix : " << p.prix << endl;
            cout << "Fournisseur : " << p.fournisseur << endl;
            cout << "Quantite : " << p.quantite << endl;
        }
    }
    
    void afficherInfoProduit(string reference) {
        auto P = find_if(stock.begin(), stock.end(), [&](Produit& p) { return p.reference == reference; });
        if (P != stock.end()) {
            cout << "                          "<< endl;
            cout << "Reference : " << P->reference << endl;
            cout << "Nom : " << P->nom << endl;
            cout << "Prix : " << P->prix << endl;
            cout << "Fournisseur : " << P->fournisseur << endl;
            cout << "Quantite : " << P->quantite << endl;
            cout << "                  " << endl;
        }
        else {
            cout << "Produit non trouve !" << endl;
        }
    }

    void listerProduitsParFournisseur(string fournisseur) {
        for (auto& produit : stock) {
            if (produit.fournisseur == fournisseur) {
                cout << "Reference : " << produit.reference << " | Nom : " << produit.nom << " | Quantite : " << produit.quantite << endl;
            }
        }
    }

    void verifierDisponibilite(string reference) {
        auto P = find_if(stock.begin(), stock.end(), [&](Produit& p) { return p.reference == reference; });
        if (P != stock.end()) {
            if (P->quantite == 0) {
                cout << "" << endl;
                cout << "Produit non disponible !" << endl;
            }
            else {
                cout << "" << endl;
                cout << "Produit disponible." << endl;
                cout << "Avec une quantite :"<<P->quantite << endl;
            }
        }
        else {
            cout << "Produit non trouve !" << endl;
        }
    }

    void enregistrerAchat(string reference, int quantite) {
        auto P = find_if(stock.begin(), stock.end(), [&](Produit& p) { return p.reference == reference; });
        if (P != stock.end()) {
            if (P->quantite >= quantite) {
                P->quantite -= quantite;
                historique.push_back(make_pair("Vendu " + to_string(quantite) + " de " + reference + "/" + P->nom, obtenirDateActuelle()));
                cout << "Achat enregistre avec succes !" << endl;
            }
            else {
                cout << "Stock insuffisant !" << endl;
            }
        }
        else {
            cout << "Produit non trouve !" << endl;
        }
    }

    void afficherStockBas(int seuil) {
        for (auto& produit : stock) {
            if (produit.quantite < seuil) {
                cout << "Reference : " << produit.reference << " | Nom : " << produit.nom << " | Quantite : " << produit.quantite << endl;
            }
        }
    }

    void afficherProduitsParPrix(double prixMin, double prixMax) {
        for (auto& produit : stock) {
            if (produit.prix >= prixMin && produit.prix <= prixMax) {
                cout << "Reference : " << produit.reference << " | Nom : " << produit.nom << " | Prix : " << produit.prix << endl;
            }
        }
    }

    void afficherHistorique() {
        for (auto& entree : historique) {
            cout << entree.first << " le " << entree.second << endl;
        }
    }

private:
    string obtenirDateActuelle() {
        time_t maintenant = time(0);
        tm ltm;
        localtime_s(&ltm, &maintenant);
        stringstream ss;
        ss << 1900 + ltm.tm_year << "-"
            << setw(2) << setfill('0') << 1 + ltm.tm_mon << "-"
            << setw(2) << setfill('0') << ltm.tm_mday;
        return ss.str();
    }
};

int main() {
    Magasin magasin("MonMagasin", "123 Rue Principale");
    int ale=0;

    while (ale !=99) {
        std::cout << " __________________________________________________         " << std::endl;
        std::cout << "               " << std::endl;
        std::cout << "               " << std::endl;
        std::cout << "            -----  -----  ---   ----  |   /   ======  |   /     " << std::endl;
        std::cout << "           |         |   |   | |      |  /      ||    |  /     " << std::endl;
        std::cout << "             ---     |   |   | |      |-        ||    |-       " << std::endl;
        std::cout << "                 |   |   |   | |      |  \\      ||    |  \\    " << std::endl;
        std::cout << "           -----     |    ---   ----  |   \\     || o  |   \\   " << std::endl;
        cout << "\n--- Menu du Magasin ---\n";
        cout << "1. Ajouter un nouveau produit\n";
        cout << "2. Modifier les informations d'un produit\n";
        cout << "3. Chercher un produit\n";
        cout << "4. Lister les produits par fournisseur\n";
        cout << "5. Verifier la disponibilite d'un produit\n";
        cout << "6. Enregistrer un achat\n";
        cout << "7. Afficher les produits avec un stock faible\n";
        cout << "8. Afficher les produits dans une fourchette de prix\n";
        cout << "9. Afficher l'historique du stock\n";
        cout << "10. Afficher tout le stock\n";
        cout << "11. Quitter\n";
        cout << "Entrez votre choix : ";

        int choix;
        cin >> choix;

        if (choix == 0) break;

        string ref, nom, fournisseur;
        double prix;
        int quantite, seuil;

        switch (choix) {
        case 1:
            cout << "Entrez la reference : ";
            cin >> ref;
            cout << "Entrez le nom : ";
            cin >> nom;
            cout << "Entrez le prix : ";
            cin >> prix;
            cout << "Entrez le fournisseur : ";
            cin >> fournisseur;
            cout << "Entrez la quantite : ";
            cin >> quantite;
            magasin.ajouterProduit(Produit(ref, nom, prix, fournisseur, quantite));
            break;
        case 2:
            cout << "Entrez la reference : ";
            cin >> ref;
            cout << "Entrez le nouveau prix : ";
            cin >> prix;
            cout << "Entrez la nouvelle quantite : ";
            cin >> quantite;
            magasin.modifierProduit(ref, prix, quantite);
            break;
        case 3:
            cout << "Entrez la reference : ";
            cin >> ref;
            magasin.afficherInfoProduit(ref);
            break;
        case 4:
            cout << "Entrez le fournisseur : ";
            cin >> fournisseur;
            magasin.listerProduitsParFournisseur(fournisseur);
            break;
        case 5:
            cout << "Entrez la reference : ";
            cin >> ref;
            magasin.verifierDisponibilite(ref);
            break;
        case 6:
            cout << "Entrez la reference : ";
            cin >> ref;
            cout << "Entrez la quantite : ";
            cin >> quantite;
            magasin.enregistrerAchat(ref, quantite);
            break;
        case 7:
            cout << "Entrez le seuil de stock : ";
            cin >> seuil;
            magasin.afficherStockBas(seuil);
            break;
        case 8:
            cout << "Entrez le prix minimum : ";
            cin >> prix;
            cout << "Entrez le prix maximum : ";
            cin >> quantite; // utilisation temporaire pour le prix maximum
            magasin.afficherProduitsParPrix(prix, quantite);
            break;
        case 9:
            magasin.afficherHistorique();
            break;
        case 10:
            magasin.afficherTOUTProduit();
            break;
        case 11:
            ale = 99;
            
            std::cout << " __________________________________________________         " << std::endl;
            cout << "" << endl;
            cout << "DECONNECTER " << endl;
            break;
        default:
            cout << "Choix invalide ! Veuillez reessayer.\n";
            break;
        }
        cout << " \n";
    }

    return 0;
}